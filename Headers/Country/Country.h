#ifndef COUNTRY_H
#define COUNTRY_H

#include<iostream>
using namespace std;

struct Country{
    string name;
    Country* left;
    Country* right;

    Country(string n);
    ~Country();
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