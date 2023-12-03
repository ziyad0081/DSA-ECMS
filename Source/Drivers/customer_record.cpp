#include <iostream>
#include <vector>

#include "../Country/Country.cpp"
#include "../Region/Region.cpp"
#include "../Customer/CustomerTree.cpp"
#include "../Record/RecordList.cpp"

using namespace std;

int main()
{
    CountryTree tree;
    tree.InsertCountry("Algeria");
    cout<<"*";
    auto cust = tree.SearchCountry("Algeria");
    
    auto cust_ = cust->AddCustomer("TEST","aaaa",vector<unsigned int>({1,2,3}));
    
    for(int i=10; i <= 31; i++){
        cust_.addRecord(abs(10* rand()%34),abs(20* rand()%34),string("2022/12/"+to_string(i)),"SUNNY",40,30,10);
    }
    cust_.GetRecordsByPeriod("2022/12/20","2022/12/25");

    return 0;
}
