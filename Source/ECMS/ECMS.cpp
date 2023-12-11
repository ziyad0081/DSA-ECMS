#pragma once

#include "../../Headers/ECMS/ECMS.h"
#include "../../Headers/tabulate.hpp"
#include "../../Headers/conio.h"
using namespace tabulate;
using namespace std;

//WARNING THIS SECTION IN ITS ENTIRETY HANDLES SCREEN DISPLAY MENUS , MOST OF THE CODE IS STYLING
//AND TABLE CREATION , AND IS THE UGLIEST CODE I HAVE EVER WRITTEN OR WILL EVER WRITE,
//A PLETHORA OF REPETITIONS AND CODE THAT IS IN DIRE NEED FOR REFACTORING AND DOCUMENTATION. UNDERSTANDING THIS
//CODE IS A JOURNEY I WISH NOBODY GOES THROUGH.

template <typename ReturnType, typename ClassType, typename... Args>
std::pair<ReturnType, double> measureExecutionTime(
    ReturnType(ClassType::*func)(Args...), ClassType* obj, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();  // Record the start time

    ReturnType result = (obj->*func)(std::forward<Args>(args)...);  // Call the callback member function

    auto end = std::chrono::high_resolution_clock::now();    // Record the end time
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

    return std::make_pair(result, duration.count());
}
Table StyleTable(Table& table_input){
        table_input.format().width(160);
        table_input.format().font_color(Color::cyan);
        table_input.format().font_style({FontStyle::bold});
        table_input.format().font_align(FontAlign::center);
        return table_input;
}
Table StyleTableNoWidth(Table& table_input){
    table_input.format().font_color(Color::cyan);
    table_input.format().font_style({FontStyle::bold});
    table_input.format().font_align(FontAlign::center);
    return table_input;
}
int LaunchProgram(){
    bool current_highlight = 0;
    
    while(1){
        system("clear");
        Table table;
        table.add_row({"E   C   M   S ~~~~~~~ L A U N C H E R"});
        table.add_row({">>> LAUNCH ECMS"});
        table.add_row({">>> EXIT PROGRAM"});
        table.add_row({"SELECT OPERATION USING ARROW KEYS TO CONTINUE..."});
        table.format().width(160);
        table.format().font_color(Color::cyan);
        table.format().font_align(FontAlign::center);
        table[current_highlight+1].format().font_style({FontStyle::blink});
        table[current_highlight+1].format().font_align(FontAlign::center);
        
        cout << table;
        if (getch() == '\033') { // if the first value is esc
            getch(); // skip the [
            switch(getch()) { // the real value
                case 'A':
                    current_highlight = !current_highlight;
                    
                    break;
                case 'B':
                    current_highlight = !current_highlight;
                    
                    break;
            }
        }
        else {
            if(getch()== '\n'){
            return !current_highlight;
            }
        }
    }
}
int DataLoadingHandler(ECMS* program){
    system("clear");
        Table table;
        table.add_row({">>> Hang Tight While ECMS Loads Data ."});
        StyleTable(table);
        table[0].format().font_style({FontStyle::blink});
        cout << table;
        auto customer_load = measureExecutionTime(&ECMS::LoadCustomerFromFile,program);
        
        if(customer_load.first){
            table.add_row({">>>>> Customers file has been loaded (" + to_string(customer_load.second) + " s)"});
            table[1].format().color(Color::red).font_style({FontStyle::bold});
        }
        else{
            //FatalErrorExitHandler(FILE_ERROR);
        }
        auto records_load = measureExecutionTime(&ECMS::LoadRecordsFromFile,program);

        if(records_load.first){
            table.add_row({">>>>> Records file has been loaded (" + to_string(records_load.second) + " s)"});
            table[0].cells()[0].get()->set_text(">>>>> DATA LOADING COMPLETE ! PRESS ENTER TO CONTINUE <<<<<");
            table[0].cells()[0].get()->format().font_color(Color::green);
            table[2].format().color(Color::red).font_style({FontStyle::bold});
        }
        else{
            //FatalErrorExitHandler(FILE_ERROR);    
        }
        cout << endl ;
        system("clear");
        cout << table;
        getch();
        if(getch()=='\n'){
            return 1;
        }
}

int MainMenuHandler(ECMS* program){
    int user_choice = 0;
    while(1){
        system("clear");
        Table MainMenuTable;
        MainMenuTable.add_row({">>>> E C M S     M a i n     M e n u <<<<<"});
        MainMenuTable.add_row({">>>> Get a bill for a customer."});
        MainMenuTable.add_row({">>>> Get Summarizing Bills By Location."});
        MainMenuTable.add_row({">>>> Get Departments Performances By Year."});
        MainMenuTable.add_row({">>>> Get Winner Customer By Month."});
        MainMenuTable.add_row({">>>> Exit the program."});
        MainMenuTable.add_row({"USE ARROW KEYS THEN PRESS ENTER TO SELECT"});
        MainMenuTable.format().width(160);
        MainMenuTable.format().font_color(Color::cyan);
        MainMenuTable.format().font_align(FontAlign::center);
        MainMenuTable[user_choice+1].format().font_style({FontStyle::blink});
        MainMenuTable[user_choice+1].format().font_align(FontAlign::center);
        cout << MainMenuTable;
        
        if (getch() == '\033') { // if the first value is esc
            
            getch(); // skip the [
            switch(getch()) { // the real value
                case 'A': //Up Arrow clicked
                    user_choice = (user_choice+4)%5; 
                    //+4 instead of -1 because for some reason the modulo function in c++ is defined on [-abs(d),abs(d)] so (user_choice-1)%5 could result in a negative value being passed to the vector indexing operator of table rows (sadge)
                    //and to encounter that we use +4 (Try to think of why that gives the same result)
                    //5 is the number of options btw so if you extend this in the future , change it accordingly
                    break;
                case 'B': //Down arrow clicked
                    user_choice = (user_choice+1)%5; //Not rocket science.
                    break;
            }
        }
        else if(getch()=='\n'){
            //If the user presses enter , return his choice .
            return user_choice;
        }
    }
}
//This function takes in charge printing the customer details + his records in the specified dates
int CustomerDetailsByIDHandler(int cust_id,string start_date, string end_date,ECMS* program){
    //First we locate the customer
    auto target_customer = program->GetCountries().SearchCountry("Algeria")->GetCustomerByID(cust_id);
    //Here we instanciate three different tables for three different jobs : One for a title , One for the personal user Info and one for his records
    //We instanciate three different tables because for some reason the library crashes when the columns do not match e.g : First row one column + Second row 4 columns = sad student and unhappy heap allocator
    Table InfoTable;
    Table UserInfoTable;
    Table DataTable;
    //We fill the title table and style it
    InfoTable.add_row({"C u s t o m e r I D :  " + to_string(cust_id) + "     I n f o     B y    P e r i o d  "});
    StyleTable(InfoTable);
    //We style the User info table without specifying the width of each column
    StyleTableNoWidth(UserInfoTable);
    UserInfoTable.format().width(39); //Proportional to the number of columns the table has
    UserInfoTable.add_row({"Name","Address","Family Members","First Record"});
    if(target_customer==nullptr){
        
        // We enter this branch if the customer doesn't exist
        //Instanciate a table and display the error in it.
        InfoTable.add_row({">>>>> C u s t o m e r    N o t    F o u n d <<<<<"});
        InfoTable.add_row({"Press >>>ENTER<<< to go back ..."});
        InfoTable[1].format().font_color(Color::red);
        InfoTable.format().font_style({FontStyle::bold});
        InfoTable[2].format().font_color(Color::green);
        InfoTable[2].format().font_style({FontStyle::blink});
        do {
            system("clear");
            cout << InfoTable << endl;
        } while(getch() != '\n');
        return 0;
    }
    else{
        //We get here if the customer does in fact exist;
        //We fill his info into the second row of the user info table
        UserInfoTable.add_row({target_customer->GetCustomerName(),target_customer->GetCustomerAddress(),to_string(target_customer->GetFamilyMembersCount()),target_customer->GetHeadRecord()->getDateString()});
        //Look for his record in the period
        auto records = target_customer->GetRecordsByPeriod(start_date,end_date);
        //If there are no records in the period, we display a message in title table since it has one column
        if(records.empty()){
            InfoTable.add_row({">>>>> Customer : " + target_customer->GetCustomerName() + " Has No Records In Specified Period ! "});
            InfoTable[1].format().font_color(Color::red);
            InfoTable[1].format().font_style({FontStyle::bold});
            InfoTable.add_row({"Press >>>Enter<<< to continue ..."});
            InfoTable[2].format().font_style({FontStyle::blink}).font_color(Color::green);
            do{
                system("clear");
                cout << InfoTable << endl
                     << UserInfoTable << endl;
            } while(getch() != '\n');
            return 0;
        }
        else{
            //If he does have records , fill the Data table with them.
            InfoTable.add_row({"Press >>>Enter<<< to continue ..."});
            InfoTable[1].format().font_style({FontStyle::blink}).font_color(Color::green);
            DataTable.add_row({"Date","Injection(Kw)","Consumption(Kw)","Amount (DA)","Day Weather","Min Temp(C)","Max Temp(C)"});
            DataTable.format().width(22);
            StyleTableNoWidth(DataTable);
            float injection_sum = float();
            float consumption_sum= float();
            float Amount = float();
            
            for(auto& record : records){
                DataTable.add_row({record.getDateString(), to_string(record.GetInjection()), to_string(record.GetConsumption()), to_string(-record.GetNetCost()), record.GetDayWeather(), to_string(record.GetDayMinTemp()), to_string(record.GetDayMaxTemp())});
                injection_sum += record.GetInjection();
                consumption_sum += record.GetConsumption();
                Amount -= record.GetNetCost();
            }
            DataTable.add_row({"TOTAL >>>>", to_string(injection_sum), to_string(consumption_sum),to_string(Amount),"N/A","N/A","N/A"});
            DataTable.row(1+records.size()).format().font_color(Color::green);
            do{
                system("clear");
                cout << InfoTable << endl;
                cout << UserInfoTable << endl;
                cout << DataTable << endl;
            }while(getch() != '\n');
            return 1;
        }
    }
}
int LocationDataDisplayHandler(ECMS* program,string start_date, string end_date,string location){
    //This will be a function that takes in dates and a location string that can have a format R,C,D or R,C or R 
    //Where R is a region , C is a city and D is a district
    //This might be the function that is most prone to invalid arguments in the universe
    vector<string> parsed_location;;
    string token;
    istringstream iss(location);
    while(getline(iss,token,',')){
        if(token != "") parsed_location.push_back(token);
    }
    Table TitleTable ;
    Table LocationInfo;
    StyleTable(TitleTable);
    TitleTable.add_row({"P e r i o d    S u m m a r y     F o r     L o c a t i o n :    "+location});
    //We check for the existance of the location :
    if(parsed_location.size()==1){
        auto target_region = program->GetCountries().SearchCountry("Algeria")->country_regions.SearchRegion(parsed_location[0]);
        if(!target_region){
            TitleTable.add_row({"The specified Location Doesn't Exist..."});
            TitleTable[1].format().font_color(Color::red);
            TitleTable[1].format().font_style({FontStyle::bold});
            TitleTable[1].format().font_align(FontAlign::center);
            do{
                system("clear");
                cout << TitleTable << endl;
            }while(getch() != '\n');
            return 1;
        }
        else{
            vector<Customer*> Customers;
            float consumption = 0;
            float injection = 0;
            float revenue = 0;
            int customers = 0;
            //Evil loop to extract all customers total records of a region

            for(auto& dept : target_region->region_departments){
                for(auto& dist : dept->department_districts->GetAllDistricts()){
                    for(auto& cust : dist->GetCustomers()){
                        customers++;
                        for(auto& rec : cust->GetRecordsByPeriod(start_date,end_date)){
                            consumption += rec.GetConsumption();
                            injection += rec.GetInjection();
                            revenue -= rec.GetNetCost();
                        }   
                    }
                }
            }
            TitleTable.add_row({"Press ENTER to continue ..."});
            TitleTable[1].format().font_align(FontAlign::center).font_color(Color::green).font_style({FontStyle::blink});
            if(!customers){
                TitleTable.add_row({"No Customers Available..."});
                TitleTable[2].format().font_color(Color::red).font_style({FontStyle::bold}).font_align(FontAlign::center);
            }
            Table DataTable;
            StyleTableNoWidth(DataTable);
            DataTable.format().width(39);
            DataTable.add_row({"Customers Count","Total Revenue (DA)","Total Customers Injection(Kw)","Total Customers Consumption(Kw)"});
            DataTable.add_row({to_string(customers),to_string(revenue),to_string(injection),to_string(consumption)});
            DataTable[1].format().color(Color::green);
            do{
                system("clear");
                cout << TitleTable << endl;
                cout << DataTable << endl;
            }while(getch() != '\n');
            return 1;
        }
    }
    else if(parsed_location.size() == 2){
        auto target_region = program->GetCountries().SearchCountry("Algeria")->country_regions.SearchRegion(parsed_location[0]);
        if(!target_region){
            TitleTable.add_row({"The specified Location Doesn't Exist..."});
            TitleTable.add_row({">>>> Press ENTER to go back ..."});
            TitleTable[1].format().font_color(Color::red);
            TitleTable[1].format().font_style({FontStyle::bold});
            TitleTable[1].format().font_align(FontAlign::center);
            TitleTable[2].format().font_color(Color::green);
            TitleTable[2].format().font_style({FontStyle::bold});
            TitleTable[2].format().font_align(FontAlign::center);
            do{
                system("clear");
                cout << TitleTable << endl;
            }while(getch() != '\n');
            return 0;
        }
        else {
            auto target_city = target_region->GetDeptByCityName(parsed_location[1]);
            if(!target_city){
            TitleTable.add_row({"The specified Location Doesn't Exist..."});
            TitleTable.add_row({">>>> Press ENTER to go back ..."});
            TitleTable[1].format().font_color(Color::red);
            TitleTable[1].format().font_style({FontStyle::bold});
            TitleTable[1].format().font_align(FontAlign::center);
            TitleTable[2].format().font_color(Color::green);
            TitleTable[2].format().font_style({FontStyle::bold});
            TitleTable[2].format().font_align(FontAlign::center);
            do{
                system("clear");
                cout << TitleTable << endl;
            }while(getch() != '\n');
            return 0;
            }
            else{
                float consumption = 0;
                float injection = 0;
                float total_profit = 0;
                int customers = 0;
                for(auto& district : target_city->department_districts->GetAllDistricts()){
                    for(auto& cust : district->GetCustomers()){
                        customers++;
                        for(auto& cust_rec : cust->GetRecordsByPeriod(start_date,end_date)){
                            consumption += cust_rec.GetConsumption();
                            injection += cust_rec.GetInjection();
                            total_profit -= cust_rec.GetNetCost();
                        }
                    }
                }
            TitleTable.add_row({"Press ENTER to continue ..."});
            TitleTable[1].format().font_align(FontAlign::center).font_color(Color::green).font_style({FontStyle::blink});
            if(!customers){
                TitleTable.add_row({"No Customers Available..."});
                TitleTable[2].format().font_color(Color::red).font_style({FontStyle::bold}).font_align(FontAlign::center);
            }
            Table DataTable;
            StyleTableNoWidth(DataTable);
            DataTable.format().width(39);
            DataTable.add_row({"Customers Count","Total Revenue (DA)","Total Customers Injection(Kw)","Total Customers Consumption(Kw)"});
            DataTable.add_row({to_string(customers),to_string(total_profit),to_string(injection),to_string(consumption)});
            DataTable[1].format().color(Color::green);
            do{
                system("clear");
                cout << TitleTable << endl;
                cout << DataTable << endl;
            }while(getch() != '\n');
            return 1;
            }
        }
    }
    else if(parsed_location.size() == 3){
        auto target_region = program->GetCountries().SearchCountry("Algeria")->country_regions.SearchRegion(parsed_location[0]);
        MarketingDepartment* target_city = nullptr;
        District* target_district = nullptr;
        if(target_region){
            target_city = target_region->GetDeptByCityName(parsed_location[1]);
        }
        if(target_city){
            target_district = target_city->department_districts->SearchForDist(parsed_location[2]);
        }
        if(!target_region || !target_city || !target_district){
            TitleTable.add_row({"The specified Location Doesn't Exist..."});
            TitleTable.add_row({">>>> Press ENTER to go back ..."});
            TitleTable[1].format().font_color(Color::red);
            TitleTable[1].format().font_style({FontStyle::bold});
            TitleTable[1].format().font_align(FontAlign::center);
            TitleTable[2].format().font_color(Color::green);
            TitleTable[2].format().font_style({FontStyle::bold});
            TitleTable[2].format().font_align(FontAlign::center);
            do{
                system("clear");
                cout << TitleTable << endl;
            }while(getch() != '\n');
            return 0;
        }
        else{
            Table DataTable;
            DataTable.add_row({""})
            float consumption = 0;
            float injection = 0;
            float total_profit = 0;
            int customers = 0;
            for(auto& cust : target_district->GetCustomers()){
                for(auto& rec : cust->GetRecordsByPeriod(start_date,end_date)){

                    consumption += rec.GetConsumption();
                    injection += rec.GetInjection();
                    total_profit -= rec.GetNetCost();

                }
            }
        }
    }
}
int CitySummaryBillHandler(ECMS* program,string start_date, string end_date){
    string region_city;
    char a;
    Table TitleTable;
    TitleTable.add_row({">>>> E C M S     L o c a t i o n     B i l l    S u m m a r y <<<<<"});
    TitleTable.add_row({"Enter City Location Format is RegionName,CityName >>>> "});
    TitleTable.add_row({"Space to DELETE ~~~~~ Enter to CONFIRM"});
    TitleTable.format().width(160);
    TitleTable.format().font_style({FontStyle::bold});
    TitleTable.format().font_color(Color::cyan);
    TitleTable.format().font_align(FontAlign::center);
    int commacount = 0;
    do{
    if(a==' ') {
        region_city = region_city.substr(0,region_city.size()-1);
    }
    commacount = count_if(region_city.begin(),region_city.end(),[](char& c){ return c == ',';});
    
    if(isalpha(a) || (a==',' && region_city.size() != 0 && commacount < 1 )) region_city += a; //This validation could be a lot improved
    TitleTable.row(1).cell(0).set_text("Enter City Location Format is RegionName-CityName >>>> " + region_city);
    system("clear");
    std::cout << TitleTable << endl;
    }while((a=getch())!='\n' || region_city.size()==0 || commacount<1); //here comma count insures that the input is in format 'something-somethingelse'
    LocationDataDisplayHandler(program,start_date,end_date,region_city);
}
int DistrictSummaryBillHandler(ECMS* program,string start_date_input, string end_date_input){
    string region_city_district;
    char a;
    Table TitleTable;
    TitleTable.add_row({">>>> E C M S     L o c a t i o n     B i l l    S u m m a r y <<<<<"});
    TitleTable.add_row({"Enter City Location : (RegionName,CityName,DistrictName) >>>> "});
    TitleTable.add_row({"Space to DELETE ~~~~~ Enter to CONFIRM"});
    TitleTable.format().width(160);
    TitleTable.format().font_style({FontStyle::bold});
    TitleTable.format().font_color(Color::cyan);
    TitleTable.format().font_align(FontAlign::center);
    int commacount = 0;
    do{
    if(a==' ') {
        region_city_district = region_city_district.substr(0,region_city_district.size()-1);
    }
    commacount = count_if(region_city_district.begin(),region_city_district.end(),[](char& c){ return c == ',';});
    
    if(isalpha(a) || (a==',' && region_city_district.size() != 0 && commacount < 2 )) region_city_district += a; //This validation could be a lot improved
    TitleTable.row(1).cell(0).set_text("Enter City Location : (RegionName,CityName,DistrictName) >>>> " + region_city_district);
    system("clear");
    std::cout << TitleTable << endl;
    }while((a=getch())!='\n' || region_city_district.size()==0 || commacount<2); //here comma count insures that the input is in format 'something-somethingelse'
    LocationDataDisplayHandler(program,start_date_input,end_date_input,region_city_district);
}
int RegionSummaryBillHandler(ECMS* program,string start_date, string end_date){
    string region;
    char a;
    Table TitleTable;
    TitleTable.add_row({">>>> E C M S     L o c a t i o n     B i l l    S u m m a r y <<<<<"});
    TitleTable.add_row({"Enter Region Name >>>> "+region});
    TitleTable.add_row({"Space to DELETE ~~~~~ Enter to CONFIRM"});
    TitleTable.format().width(160);
    TitleTable.format().font_style({FontStyle::bold});
    TitleTable.format().font_color(Color::cyan);
    TitleTable.format().font_align(FontAlign::center);
    do{
    if(a==' ') {
        region = region.substr(0,region.size()-1);
    }
    if(isalpha(a) && a != ' ') region += a;
    TitleTable.row(1).cell(0).set_text("Enter Region Name >>>> "+region);
    system("clear");
    std::cout << TitleTable << endl;
    }while((a=getch())!='\n' || region.size()==0);

    LocationDataDisplayHandler(program,start_date,end_date,region);

}
int LocationSummaryMenuHandler(ECMS* program){
    int Highlighted_option = 0;
    string start_date_input ;
    string end_date_input ;
    char a;
    do{
        system("clear");
        Table TitleTable;
        TitleTable.add_row({">>>> E C M S     L o c a t i o n     B i l l    S u m m a r y <<<<<"});
        TitleTable.format().width(160);
        TitleTable.format().font_color(Color::cyan);
        TitleTable.format().font_align(FontAlign::center);
        TitleTable.add_row({"Get Summary Bill By Region."});
        TitleTable.add_row({"Get Summary Bill By City."});
        TitleTable.add_row({"Get Summary Bill By District."});
        
        if (a == '\033') {
            getch();
            switch(getch()) {
                case 'A':
                    Highlighted_option = (Highlighted_option+2)%3; 
                    break;
                case 'B': //Down arrow clicked
                    Highlighted_option = (Highlighted_option+1)%3;  //Not rocket science.
                    break;
            }
        }
        TitleTable[Highlighted_option+1].format().font_style({FontStyle::blink});
        TitleTable[Highlighted_option+1].format().font_align(FontAlign::center);
        cout << TitleTable << endl;
    }while((a = getch()) != '\n');
    Table TitleTable;
    TitleTable.add_row({">>>> E C M S     L o c a t i o n     B i l l    S u m m a r y <<<<<"});
    TitleTable.add_row({">>>> Enter Fetching Start Date (YYYY-MM-DD) : "+start_date_input});
    TitleTable.format().width(160);
    TitleTable.format().font_color(Color::cyan);
    TitleTable.format().font_align(FontAlign::center);
    do{
        if(isdigit(a)){ // User inputs digits , hiphens are inserted automatically
            if(start_date_input.size()<10) //Doesn't accept input more than 10 characters
            start_date_input += a;
            if(start_date_input.size()==4 || start_date_input.size()==7 || start_date_input.size()==7){ //When the hiphen is inserted
                start_date_input += "-";
            }
        }
        if(a==' '){ // space button to delete again
            start_date_input = start_date_input.substr(0,start_date_input.size()-1);
        }
        system("clear");
        TitleTable.row(1).cells()[0]->set_text(">>>> Enter Fetching Start Date (YYYY-MM-DD) : "+start_date_input);
        cout << TitleTable;
    }while((a = getch())!='\n' || start_date_input.size() != 10);

    do{
        if(isdigit(a)){ // User inputs digits , hiphens are inserted automatically
            if(end_date_input.size()<10) //Doesn't accept input more than 10 characters
            end_date_input += a;
            if(end_date_input.size()==4 || end_date_input.size()==7 || end_date_input.size()==7){ //When the hiphen is inserted
                end_date_input += "-";
            }
        }
        if(a==' '){ // space button to delete again
            end_date_input = end_date_input.substr(0,end_date_input.size()-1);
        }
        system("clear");
        TitleTable.row(1).cells()[0]->set_text(">>>> Enter End of Fetching Period (YYYY-MM-DD) : "+end_date_input);
        cout << TitleTable;
    }while((a = getch())!='\n' || end_date_input.size() != 10);

    switch (Highlighted_option)
    { 
    case 0:
        RegionSummaryBillHandler(program,start_date_input,end_date_input);
        break;
    case 1:
        CitySummaryBillHandler(program,start_date_input,end_date_input);
    default:
        DistrictSummaryBillHandler(program,start_date_input,end_date_input);
        break;
    }
}
int GetBillSummaryByLocation(string location,ECMS* program){

}
int UserBillInfoHandler(ECMS* program){
    system("clear");
    Table UserBillInfoTable;
        UserBillInfoTable.add_row({">>>> E C M S     C u s t o m e r     B i l l <<<<<"});
        UserBillInfoTable.add_row({">>>> Enter Customer ID :"});
        UserBillInfoTable.add_row({"Use space to delete -------- Enter to confirm"});
        StyleTable(UserBillInfoTable);
    cout << UserBillInfoTable;
    char a;
    string id_input;
    string start_date_input;
    string end_date_input;
    //This gets part the id from the user
    while((a = getch())!='\n' || id_input.size()==0)
    {   
        if(isdigit(a)) id_input += a;
        if(a==' ') id_input = id_input.substr(0,id_input.size()-1); //Space for deletion
        system("clear");
        UserBillInfoTable.row(1).cells()[0]->set_text(">>>> Enter Customer ID :"+id_input);
        cout << UserBillInfoTable;   
    }
    //Next we get the start date : //These all should have been their own functions but well , I'll deal with SRP later
    do{
        if(isdigit(a)){ // User inputs digits , hiphens are inserted automatically
            if(start_date_input.size()<10) //Doesn't accept input more than 10 characters
            start_date_input += a;
            if(start_date_input.size()==4 || start_date_input.size()==7 || start_date_input.size()==7){ //When the hiphen is inserted
                start_date_input += "-";
            }
        }
        if(a==' '){ // space button to delete again
            start_date_input = start_date_input.substr(0,start_date_input.size()-1);
        }
        system("clear");
        UserBillInfoTable.row(1).cells()[0]->set_text(">>>> Enter Start of Fetching Period (YYYY-MM-DD) : "+start_date_input);
        cout << UserBillInfoTable;
    }while((a = getch())!='\n' || start_date_input.size() != 10);
    // Again the same logic for the end date
    do{
        if(isdigit(a)){ // User inputs digits , hiphens are inserted automatically
            if(end_date_input.size()<10) //Doesn't accept input more than 10 characters
            end_date_input += a;
            if(end_date_input.size()==4 || end_date_input.size()==7 || end_date_input.size()==7){ //When the hiphen is inserted
                end_date_input += "-";
            }
        }
        if(a==' '){ // space button to delete again
            end_date_input = end_date_input.substr(0,end_date_input.size()-1);
        }
        system("clear");
        UserBillInfoTable.row(1).cells()[0]->set_text(">>>> Enter End of Fetching Period (YYYY-MM-DD) : "+end_date_input);
        cout << UserBillInfoTable;
    }while((a = getch())!='\n' || end_date_input.size() != 10);
    
    CustomerDetailsByIDHandler(stoi(id_input),start_date_input,end_date_input,program);
    return 1;
}
void ECMS::RunProgram(){

    int user_choice = LaunchProgram();
    if(!user_choice){
        //UserExitHandler()
    }
    DataLoadingHandler(this);
    while(1){
        int choice = MainMenuHandler(this);
        switch(choice){
            case 0:
                UserBillInfoHandler(this);
                break;
            case 1:
                LocationSummaryMenuHandler(this);
                break;
            case 4:
                //UserExitHandler();
                break;
        }

    }
    // Entry Point (Lanuch/Exit)
        // Launch : Load Files => Loop Main Menu Function
    // Main Menu :
    // Print Bill For Customer : Choose By Region , City, District then Customer ID Then select period
    // Print Bill By Location : Each Location should have a function to retrieve all customers Then select period (Print Summary)
    // Get Best Department By Year
    // Each function Execution will be followed by time of execution;



}