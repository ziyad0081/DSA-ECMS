#ifndef COUNTRY_H
#define COUNTRY_H

#include<iostream>
#include<vector>
#include "../../Source/Customer/CustomerTree.cpp"
#include "../../Source/Region/Region.cpp"
using namespace std;

struct Country{
    string name;
    Country* left;
    Country* right;
    vector<Customer> country_customers;
    RegionTree country_regions;
    Country(string n);
    ~Country();
    Customer* AddCustomer(string _name, string addr,const vector<unsigned int>& _family_ages);
    static unsigned int customer_id;
};


class CountryTree{
    Country* root;
    void Print(Country* root);
public:
    CountryTree();
    ~CountryTree();
    void InsertCountry(string country_name);
    Country* SearchCountry(string country_name);
    void DeleteCountry(string country_name);
    void PrintCountries(Country* root);
    void EditCountry(string country_name, string new_country_name);
};

#endif // COUNTRYTREE_H