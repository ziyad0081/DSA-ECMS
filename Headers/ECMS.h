#ifndef ECMS_H
#define ECMS_H


#include "Country.h"
#include <fstream>
#include <algorithm>
#include <mutex>
#include <thread>
class ECMS{

    public:
    CountryTree GetCountries() const {
        return countries;
    }
    int LoadRecordsFromFiles(string filename,mutex& mtx){

        fstream records_file;
        records_file.open("./DataFiles/"+filename,ios::in);
        if(records_file.is_open()){
            auto alg = GetCountries().SearchCountry("Algeria");
            string line;

            while(getline(records_file,line)){
                vector<string> values;
                string token;
                istringstream iss(line);
                while(getline(iss,token,',')) {
                    values.push_back(token);
                }
                //This part updates both the customer's records and the department to which he belongs
                lock_guard<mutex> lock(mtx);
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
    int LoadRecordsFromFilesWrapper(){
        vector<string> files = {"records_trim1.csv","records_trim2.csv","records_trim3.csv","records_trim4.csv"};
        vector<thread> threads;
        mutex mtx;
        for(int i = 0; i < 4; i++){
            threads.emplace_back([this,files,i,&mtx](){
                this->LoadRecordsFromFiles(files[i],ref(mtx));
            });
        }
        for(auto& thread : threads){
            thread.join();
        }
        return 1;
    }
    int LoadCustomerFromFile(){
    fstream customers_file;
    customers_file.open("DataFiles/customers.csv",ios::in);
    
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
    string token;
    // The address is stored as "Region,Dept,District" so advancing once for the region then again for the dept within the region
    getline(address, token, ',');
    auto region = countries.SearchCountry("Algeria")->country_regions.SearchRegion(token);
    getline(address, token, ',');
    if(!region) return 0;
    auto dept = region->GetDeptByCityName(token);
    return dept;
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