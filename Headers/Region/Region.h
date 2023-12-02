#ifndef REGION_H
#define REGION_H

#include<iostream>
using namespace std;

struct Region{
    string name;
    Region* left;
    Region* right;

    Region(string n);
    ~Region();
};

class RegionTree{
    Region* root;
    void Print(Region* root);
public:

    RegionTree();
    ~RegionTree();
    void InsertRegion(string region_name);
    Region* SearchRegion(string region_name);
    void DeleteRegion(string region_name);
    void PrintRegions(Region* root);
};

#endif // REGION_H
