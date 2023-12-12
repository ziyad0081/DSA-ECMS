#ifndef COUNTRY_H
#define COUNTRY_H

#include<iostream>
#include<vector>
#include<sstream>
#include "Region.h"
using namespace std;

class Country{
    public : 
    string name;
    Country* left;
    Country* right;
    
    vector<MarketingDepartment*> country_departments;
    vector<Customer*> country_customers;

    RegionTree country_regions;
    Country(string n);
    Customer* AddCustomer(int customer_id,string _name, string addr_region,string addr_city,string addr_district,const vector<unsigned int>& _family_ages);
    Customer* GetCustomerByID(int customer_id);
    Customer* GetMonthWinnerCustomer(string year_month);
    MarketingDepartment* InsertDepartment(string region, string city); //Dept address should be a region and a city;
    vector<MarketingDepartment*> GetSortedDeptsByYear(string year){
        sort(country_departments.begin(), country_departments.end(), [&year](MarketingDepartment* deptA, MarketingDepartment* deptB ){return deptA->GetYearlyRecord(year) < deptB->GetYearlyRecord(year);});
        return country_departments;
    }
    
    private:
        bool CumInjComparator(Customer*, Customer*, string);    
};


class CountryTree{
    Country* root;
    void Print(Country* root);
public:
    CountryTree():root(nullptr){};
    void DestroyCountries(Country *root);
    ~CountryTree();
    Country* InsertCountry(string country_name);
    Country* SearchCountry(string country_name);
    void DeleteCountry(string country_name);
    void PrintCountries(Country* root);
    void EditCountry(string country_name, string new_country_name);
    Customer* GetBestCountryCumInjUtil(Country* root, string year_month);
    Customer* GetBestCountryCumInj(string year_month);
};

#endif