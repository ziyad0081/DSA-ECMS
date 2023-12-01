#ifndef COUNTRYTREE_H
#define COUNTRYTREE_H

#include<iostream>
using namespace std;

struct Country{
    string name;
    Country* left;
    Country* right;
    Country(string n): name(n), left(nullptr), right(nullptr){}
};

class CountryTree{
    Country* root;
public:
    CountryTree(): root(nullptr) {}

    void Insert(string country_name);

    Country* Search(string name);

};

#endif // COUNTRYTREE_H