
#include "../../Headers/Customer/CustomerTree.h"


Customer::Customer(string _name, const vector<unsigned int>& _family_ages)
{
    
    customer_name = _name;
    family_ages = vector<unsigned int>(family_ages);
    family_members_count = _family_ages.size();
    
    customer_l = nullptr;
    customer_r = nullptr;

}

Customer::~Customer()
{
    //Destruction of the tree and updating the files (if implemented)
}
string Customer::GetCustomerName(){
    return customer_name;
}


CustomerTree::CustomerTree():customer_root(nullptr){

}
CustomerTree::~CustomerTree(){

}

Customer* CustomerTree::InsertCustomer(string _name, const vector<unsigned int>& ages){
    Customer* ref_last = InsertCustomerHelper(_name,ages,customer_root,ref_last);
    return ref_last;
}

Customer* CustomerTree::InsertCustomerHelper(string _name, const vector<unsigned int>& ages,Customer*& root, Customer*& newCustomerRef){
    if(!root){
        newCustomerRef = new Customer(_name, ages);
        root = newCustomerRef;
        return root;
    }

    if(root->customer_name > _name){
        root->customer_l = InsertCustomerHelper(_name, ages, root->customer_l,newCustomerRef);

    }

    if(root->GetCustomerName() < _name){
        root->customer_r = InsertCustomerHelper(_name, ages, root->customer_r,newCustomerRef);
    }

    return root;
}


void CustomerTree::printCustomers(Customer* root){
    if(!root) return;
    cout << root->customer_name << "   " << root->family_members_count << endl;

    printCustomers(root->customer_l);
    printCustomers(root->customer_r);

}

Customer* CustomerTree::GetCustomerByName(const string& _name){

    Customer* it = CustomerTree::customer_root;

    while(it != nullptr){

        if(it->customer_name > _name){
            it = it->customer_l;
        }
        if(it->customer_name < _name){
            it = it->customer_r;
        }
        if(it->customer_name == _name){
            return it;
        }
    }
    return it ;

}

bool Customer::addRecord(int consomation, int injection, string _date, string day_weather, int max_temp, int min_temp, int sunny_hours){
    return customer_records.insertRecord(consomation, injection, _date, day_weather, max_temp,  min_temp, sunny_hours);
}




