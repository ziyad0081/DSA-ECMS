#include<iostream>
#include "../../Headers/Country/Country.h"

/*--------------------Country----------------------------------------*/
Country::Country(string n): name(n), left(nullptr), right(nullptr) {}

unsigned int Country::customer_id = 0;

Customer Country::AddCustomer(string _name, string addr,const vector<unsigned int>& _family_ages){

    
    country_customers.push_back(Customer(customer_id,_name,addr,_family_ages));
    //country_regions.SearchRegion().SearchCity().searchDistrict().customers.pushback(id)
    return country_customers[customer_id++];
}
/*--------------------CountryTree----------------------------------------*/

// CountryTree::CountryTree(): root(nullptr) {}

void CountryTree::DestroyCountries(Country *root){
    if (root){
        DestroyCountries(root->left);
        DestroyCountries(root->right);
        delete root;
    }
}

CountryTree::~CountryTree(){
    DestroyCountries(root);
}

void CountryTree::InsertCountry(string country_name){
    Country* new_country= new Country(country_name);
    //Check if tree is empty
    if(!root) root=new_country;
    else{
        //Set current to traverse the tree and parent to keep updated with current's parent
        Country* current=root, *parent=root;
        while(1){
            parent=current; //Parent gets updated before each movement of the current
            if(country_name<current->name){
                current=current->left;
                if(!current){
                    parent->left=new_country;
                    break;
                }
            }
            else if(country_name>current->name){
                current=current->right;
                if(!current){
                    parent->right=new_country;
                    break;
                }
            }
            else break;
        }
    }
}

Country* CountryTree::SearchCountry(string country_name){
    Country* current=root;
    if(!current) return nullptr;
    //Will traverse the tree while current is non null
    //And compare the tageted name to the name of the current Country
    while(current){
        if(current->name==country_name) return current;
        if(country_name<current->name) current=current->left;
        else current=current->right;
    }
    return nullptr;
}

void CountryTree::DeleteCountry(string country_name){
    Country* target= SearchCountry(country_name);
    if(!target) return;
    //No children; Delete directly
    if(!target->left && !target->right){
        delete target;
        target=nullptr;
    }
    //No left child; Keep right child
    else if(!target->left){
        Country* temp=target->right;
        delete target;
        target=temp;
    }
    //No right child; Keep left child
    else if(!target->right){
        Country* temp=target->left;
        delete target;
        target=temp;
    }
    //Both children there; 
    else{
        Country* temp=target->right;
        while(temp->left) temp=temp->left;
        target->name=temp->name;
        DeleteCountry(temp->name);
    }
}

void CountryTree::Print(Country* root) {
    if (root == nullptr) return;
    Print(root->left);
    cout << root->name << " ";
    Print(root->right);
}

void CountryTree::PrintCountries(Country* root){
    Print(root);
}

void CountryTree::EditCountry(string country_name, string new_country_name){
    SearchCountry(country_name)->name=new_country_name;
}