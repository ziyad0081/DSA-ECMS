#pragma "-Wall"
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include "../Country/Country.cpp"
#include "../Region/Region.cpp"
#include "../Customer/CustomerTree.cpp"
#include "../Record/RecordList.cpp"
#include "../District/District.cpp"

using namespace std;
void LoadRecordsFromFile(CountryTree& tree){
    fstream records_file;
    records_file.open("records.csv",ios::in);
    if(records_file.is_open()){
        auto alg = tree.SearchCountry("Algeria");
        string line;
        
        while(getline(records_file,line)){
            vector<string> values;
            string token;
            istringstream iss(line);
            while(getline(iss,token,',')) {
                values.push_back(token);
            }
            auto cust = alg->GetCustomerByID(stoi(values[0]));
            cust->addRecord(stoi(values[2]),stoi(values[3]),values[1],values[4],stoi(values[5]),stoi(values[6]),stoi(values[7]));
        }
    }
}
void LoadCustomerFromFile(CountryTree& tree){
    fstream customers_file;
    customers_file.open("customers.txt",ios::in);
    
    if(customers_file.is_open()){
        auto alg = tree.InsertCountry("Algeria");
        
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
            
            alg->AddCustomer(stoi(values[0]),values[1],values[2],values[3],values[4],ages);
            
        }
        customers_file.close();
    }
    LoadRecordsFromFile(tree);
}

int main()
{
    CountryTree tree;
    
    LoadCustomerFromFile(tree);
    auto custo = tree.SearchCountry("Algeria")->GetCustomerByID(1);
    auto id1_records = custo->GetCumInjectionByMonth("2010-10");
    cout << id1_records;
    return 0;
}

