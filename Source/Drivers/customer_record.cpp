#include <iostream>
#include <vector>
#include "CustomerTree.h"
using namespace std;

int main()
{
    CustomerTree tree ;
    Customer* refr;

    Customer* cust = tree.InsertCustomer("Naser", vector<unsigned int>({1,2,3}));


    for(int i=1; i <= 31; i++){
        cust->addRecord(10* rand()%34,20* rand()%34,string("2022/12/"+to_string(i)),"SUNNY",40,30,10);
    }
    


    cust->PrintRecords();
    
    return 0;
}
