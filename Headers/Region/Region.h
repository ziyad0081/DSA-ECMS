#pragma once
#include "../Department/Department.h"
#include<iostream>
#include<vector>
using namespace std;

struct Region{
    string name;
    Region* left;
    Region* right;
    vector<MarketingDepartment*> region_departments;
    MarketingDepartment* GetDeptByCityName(string _name);
    MarketingDepartment* InsertDepartment(MarketingDepartment*);
    Region(string _name);
    ~Region();
};

class RegionTree{
    Region* root;
    void Print(Region* root);
public:
    RegionTree();
    void DestroyRegions(Region *root);
    ~RegionTree();
    Region* InsertRegion(string region_name);
    Region* SearchRegion(string region_name);
    void DeleteRegion(string region_name);
    void PrintRegions(Region* root);
};