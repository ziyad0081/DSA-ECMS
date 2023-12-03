#include<iostream>
#include<vector>
#include "../Record/RecordList.h"
using namespace std;


#ifndef CUSTOMERTREE_H
#define CUSTOMERTREE_H

class Customer
        {
            public:
                friend class CustomerTree;
                Customer( int ,string , string addr,const vector<unsigned int>&);
                ~Customer();

                string GetCustomerName();

                bool addRecord(int consomation, int injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours); //Adding a record into the customer's account;
                void GetRecordsByPeriod(string start_date, string end_date); //Start and end dates will be passed as strings and parsed in the records tree.
                void PrintRecords() {
                    auto it = customer_records.head_record;
                    while(it){
                        it->PrintRecord();
                        it = it->next_record;
                    }

                };
            private:
                int unsigned account_id;
                string customer_name;
                string customer_address;
                unsigned int family_members_count;
                vector<unsigned int>family_ages;
                vector<pair<string,int>> cumulative_inj;
                RecordList customer_records;
};
// VECTOR OF IDS IN DISTRICT , VECTOR OF CUSTOMERS IN THE COUNTRY , AFTER INSERTION WE RESOLVE THE ADRESS AND ADD THE ID IN THE APPROPRIATE DISTRICT , IDS AUTO INCREMENT.                    


#endif
