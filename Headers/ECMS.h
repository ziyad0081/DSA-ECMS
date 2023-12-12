#ifndef ECMS_H
#define ECMS_H


#include "Country.h"
#include <fstream>
#include <algorithm>

class ECMS{

    public:
    CountryTree GetCountries() const {
        return countries;
    }
    int LoadRecordsFromFile(){
        fstream records_file;
        records_file.open("../DataFiles/records.csv",ios::in);
        if(records_file.is_open()){
            auto alg = countries.SearchCountry("Algeria");
            string line;

            while(getline(records_file,line)){
                vector<string> values;
                string token;
                istringstream iss(line);
                while(getline(iss,token,',')) {
                    values.push_back(token);
                }
                //This part updates both the customer's records and the department to which he belongs
                auto cust = alg->GetCustomerByID(stoi(values[0]));
                if(!cust){
                    continue;
                }
                auto custDept = GetCustomerDept(*cust);
                auto RecordYear = values[1].substr(0,4); //We extract the first four chars of the date passed in YYYY-MM-DD format
                auto InsertedRecord = cust->addRecord(stoi(values[2]),stoi(values[3]),values[1],values[4],stoi(values[5]),stoi(values[6]),stoi(values[7]));
                auto TargetDeptRecord = custDept->GetYearlyRecord(RecordYear); //This function checks if there's a record for that year, if there is it returns it else it creates and returns it
                TargetDeptRecord->amount += InsertedRecord->GetNetCost(); //We get the net cost of the customer and insert it into the appropriate dept 's appropriate record 
            }
            records_file.close();
            return 1;
        }
        else{
            return 0;
        }
    }
    int LoadCustomerFromFile(){
    fstream customers_file;
    customers_file.open("../DataFiles/customers.txt",ios::in);
    
    if(customers_file.is_open()){
        auto alg = countries.InsertCountry("Algeria");
        
        string line;
        while(getline(customers_file,line)){
            istringstream ss(line);
            vector<string> values;
            vector<unsigned int> ages;
            string token;
            while(getline(ss,token,',')){
                values.push_back(token);
            }
            if(values.size()>5){
                for(int i = 5; i < values.size();i++){
                    ages.push_back(stoi(values[i]));
                }
            }
            
            auto newCust = alg->AddCustomer(stoi(values[0]),values[1],values[2],values[3],values[4],ages);
            
        }
        customers_file.close();
        return 1;
    }
    else{
        return 0;
    }
    
}

void RunProgram();

private:
CountryTree countries;
MarketingDepartment *GetCustomerDept(const Customer &cust)
{
    istringstream address(cust.GetCustomerAddress());
    string dept;
    // The address is stored as "Region,Dept,District" so advancing
    getline(address, dept, ',');
    getline(address, dept, ',');

    auto country_depts = countries.SearchCountry("Algeria")->country_departments;
    auto target_dept = find_if(country_depts.begin(), country_depts.end(), [dept](MarketingDepartment *_dept)
                               { return _dept->city == dept; });
    return *target_dept;            
        }
        vector<MarketingDepartment*> GetSortedDeptsByYear(string year){ // Input format YYYY
            // This function retrieves the country's departments and sorts them based on their annual customer income for a given year  
            auto algeria_depts = countries.SearchCountry("Algeria")->country_departments;
            sort(algeria_depts.begin(),algeria_depts.end(),[year](MarketingDepartment* a,MarketingDepartment* b){
                return a->GetYearlyRecord(year) > b->GetYearlyRecord(year);
            });
            return algeria_depts;
        }
        
};

#endif