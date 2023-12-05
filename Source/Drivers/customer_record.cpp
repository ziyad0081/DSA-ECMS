#include <iostream>
#include <vector>
#include <fstream>
#include "../Country/Country.cpp"
#include "../Region/Region.cpp"
#include "../Customer/CustomerTree.cpp"
#include "../Record/RecordList.cpp"
#include "../District/District.cpp"

using namespace std;
void LoadCustomerFromFile(CountryTree& tree){
    fstream customers_file;
    customers_file.open("customers.txt",ios::in);
    
    if(customers_file.is_open()){
        string name, region_address, city_address, district_address;
        string line;
        int customer_id;
        string age;
        vector<unsigned int> family_ages;
        auto alg = tree.InsertCountry("Algeria");

        while(getline(customers_file,line)){
            istringstream ss(line);
            getline(ss,name,',');
            getline(ss,region_address,',');
            getline(ss,city_address,',');
            getline(ss,district_address,',');
            getline(ss,age,',');
            family_ages.push_back(stoi(age));
            alg->AddCustomer(name,region_address,city_address,district_address,family_ages);
        }
    }
}
int main()
{
    CountryTree tree;
    LoadCustomerFromFile(tree);

    
    return 0;
}
