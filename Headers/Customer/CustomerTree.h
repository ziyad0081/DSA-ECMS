#pragma once 

#include<iostream>
#include<vector>
#include "../Record/RecordList.h"
using namespace std;




class Customer
        {
            public:
                
                Customer(int id ,string , string addr,const vector<unsigned int>&);
                ~Customer();

                string GetCustomerName();
                int GetCustomerID() const { return account_id; }
                bool addRecord(int consomation, int injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours); //Adding a record into the customer's account;
                vector<RecordList::Record> GetRecordsByPeriod(string start_date, string end_date) ; //Start and end dates will be passed as strings and parsed in the records tree.
                float GetInjectionByMonth(string year_month) ; // This will return customer total injection by month specified in format YYYY/MM
                
            private:
                int unsigned account_id;
                string customer_name;
                string customer_address;
                unsigned int family_members_count;
                vector<unsigned int>family_ages;
                vector<pair<string,int>> cumulative_inj;
                RecordList customer_records;
};

