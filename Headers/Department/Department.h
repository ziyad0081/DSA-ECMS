#pragma once 
#include <iostream>
#include <vector>
#include "../District/District.h"
using namespace std;

struct DeptRecord{
    string year;
    int amount;
};
class MarketingDepartment {

public:
    string city;
    vector<DeptRecord> yearly_payment;
    vector<DeptRecord> yearly_budget;
    DistrictTree* department_districts;
    MarketingDepartment(string _city) : city(_city){
        department_districts = new DistrictTree();
    } 
    
    


};