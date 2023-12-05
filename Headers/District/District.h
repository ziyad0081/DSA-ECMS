#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;



struct District{
    public:
      friend class DistrictTree;
        District(const string& _name ="");
        string GetDistName();
        ~District();
        Customer* InsertCustomer(Customer*);
    private:
        string dist_name;
        District* left_dist;
        District* right_dist;
        vector<Customer*> district_customers;

 };

 class DistrictTree{
    
    public:
        DistrictTree();
        DistrictTree(const string&);
        DistrictTree(District*);
        ~DistrictTree();
        District* InsertDist(const string&);
        void DeleteDist(const string&);
        District* SearchForDist(const string&);
        void PrintDistTree();
        District* root_dist;

        
        

 private:
    District* InsertDistAct(District*& new_dist, District*& root);
    District* MinDist(District*);
    void DeleteDistAct(const string &, District * &);
    void PrintDistTreeAct(District*, int &);
} ;
