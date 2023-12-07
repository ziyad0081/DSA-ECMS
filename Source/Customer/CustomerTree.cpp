
#include "../../Headers/Customer/CustomerTree.h"
#include <chrono>
#include <iostream>
#include <iomanip>
using namespace std;

Customer::Customer(int id,string _name, string addr,const vector<unsigned int>& _family_ages)
{   account_id = id;
    customer_name = _name;
    customer_address = addr;
    family_ages = vector<unsigned int>(family_ages);
    family_members_count = _family_ages.size();
}

Customer::~Customer()
{
    //Destruction of the tree and updating the files (if implemented)
}
string Customer::GetCustomerName(){
    return customer_name;
}

// CustomerTree::CustomerTree():customer_root(nullptr){

// }
// CustomerTree::~CustomerTree(){

// }

// Customer* CustomerTree::InsertCustomer(string _name, const vector<unsigned int>& ages){
//     Customer* ref_last = InsertCustomerHelper(_name,ages,customer_root,ref_last);
//     return ref_last;
// }

// Customer* CustomerTree::InsertCustomerHelper(string _name, const vector<unsigned int>& ages,Customer*& root, Customer*& newCustomerRef){
//     if(!root){
//         newCustomerRef = new Customer(_name, ages);
//         root = newCustomerRef;
//         return root;
//     }

//     if(root->customer_name > _name){
//         root->customer_l = InsertCustomerHelper(_name, ages, root->customer_l,newCustomerRef);

//     }

//     if(root->GetCustomerName() < _name){
//         root->customer_r = InsertCustomerHelper(_name, ages, root->customer_r,newCustomerRef);
//     }

//     return root;
// }


// void CustomerTree::printCustomers(Customer* root){
//     if(!root) return;
//     cout << root->customer_name << "   " << root->family_members_count << endl;

//     printCustomers(root->customer_l);
//     printCustomers(root->customer_r);

// }

// Customer* CustomerTree::GetCustomerByName(const string& _name){

//     Customer* it = CustomerTree::customer_root;

//     while(it != nullptr){

//         if(it->customer_name > _name){
//             it = it->customer_l;
//         }
//         if(it->customer_name < _name){
//             it = it->customer_r;
//         }
//         if(it->customer_name == _name){
//             return it;
//         }
//     }
//     return it ;

// }

bool Customer::addRecord(int consomation, int injection, string _date, string day_weather, int max_temp, int min_temp, int sunny_hours){

    return customer_records.insertRecord(consomation, injection, _date, day_weather, max_temp,  min_temp, sunny_hours);
}
bool dateGreaterThan(string _date1, string _date2){
    int date1_parsed[3] ;
    date1_parsed[0] = stoi(_date1.substr(0,4));
    date1_parsed[1] = stoi(_date1.substr(5,2));
    date1_parsed[2] = stoi(_date1.substr(8,2));
    int date2_parsed[3] ;
    date2_parsed[0] = stoi(_date2.substr(0,4));
    date2_parsed[1] = stoi(_date2.substr(5,2));
    date2_parsed[2] = stoi(_date2.substr(8,2));
    return (date1_parsed[0]>date2_parsed[0]) || (date1_parsed[0]==date2_parsed[0] && date1_parsed[1]>date2_parsed[1]) || (date1_parsed[0]==date2_parsed[0] && date1_parsed[1]==date2_parsed[1] && date1_parsed[2]>=date2_parsed[2] );
}

vector<RecordList::Record> Customer::GetRecordsByPeriod(string start_date, string end_date)
{
    // This checks for errors in parsing the period
    try{
        auto start_tp = ParseDateStrings(start_date);

        auto end_tp = ParseDateStrings(end_date);
        if(start_tp > end_tp){
            return vector<RecordList::Record>({});
        }
        vector<RecordList::Record> records; // Records will be gathered in a vector and redirected to the interface function
        auto it = customer_records.head_record;
        while(it){
            if(it->getDate() >= start_tp && it->getDate() <= end_tp){
                records.push_back(*it);
            }
            it = it->next_record;
            
        }
        return records; //Returning vectors is appearently not as costly since c++ compilers use RVO (Return Value Optimization) to construct the return variable directly with the resulting vector instead of copying it
    } 
    catch(const exception& e){
        throw e; // Redirecting the exception to the higher function to deal with it
    }
}
float Customer::GetInjectionByMonth(string year_month)
{    
    return 0.0f;
}
