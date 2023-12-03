#ifndef COUNTRY_H
#define COUNTRY_H

#include<iostream>
#include<vector>
#include "../Customer/CustomerTree.h"
#include "../Region/Region.h"
using namespace std;

struct Country{
    
    string name;
    Country* left;
    Country* right;
    vector<Customer> country_customers;
    RegionTree country_regions;
    Country(string n);
    Customer AddCustomer(string _name, string addr,const vector<unsigned int>& _family_ages);
    static unsigned int customer_id;
};


class CountryTree{
    Country* root;
    void Print(Country* root);
public:
    CountryTree():root(nullptr){};
    void DestroyCountries(Country *root);
    ~CountryTree();
    void InsertCountry(string country_name);
    Country* SearchCountry(string country_name);
    void DeleteCountry(string country_name);
    void PrintCountries(Country* root);
    void EditCountry(string country_name, string new_country_name);
};

#endif // COUNTRYTREE_H