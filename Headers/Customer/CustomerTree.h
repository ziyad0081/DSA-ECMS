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
                Customer(string , const vector<unsigned int>&);
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

                string customer_name;
                string district_address;
                unsigned int family_members_count;
                vector<unsigned int>family_ages;
                Customer* customer_l;
                Customer* customer_r;
                unsigned int cumulative_injection;
                RecordList customer_records;
};





class CustomerTree{


    public:
        CustomerTree();
        ~CustomerTree();
        void printCustomers(Customer*);

        Customer* InsertCustomer(string, const vector<unsigned int>&);

        bool GetAllRecords();
        string GetAllRecords(unsigned int , unsigned int , unsigned int , unsigned int);

        Customer* GetCustomerByName(const string&);

        Customer* customer_root;

    private:
        Customer* InsertCustomerHelper(string, const vector<unsigned int>&, Customer*&,Customer*&);

};
#endif
