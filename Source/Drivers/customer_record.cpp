#include <iostream>
#include <vector>
#include "../../Headers/Country/Country.h"
#include "../../Headers/Customer/CustomerTree.h"
using namespace std;

int main()
{
    CountryTree tree;
    tree.InsertCountry("Algeria");
    auto cust = tree.SearchCountry("Algeria")->AddCustomer("TEST", "Algeria, Something", vector<unsigned int>({10,20,10}));
    for(int i=10; i <= 31; i++){
        cust->addRecord(abs(10* rand()%34),abs(20* rand()%34),string("2022/12/"+to_string(i)),"SUNNY",40,30,10);
    }
    

    cust->GetRecordsByPeriod("2022/12/12","2022/12/22");
    return 0;
}
