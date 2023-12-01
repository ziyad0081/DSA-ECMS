#include<iostream>
#include "../../Headers/Country/CountryTree.h"

void CountryTree::Insert(string country_name){
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

Country* CountryTree::Search(string name){
    Country* current=root;
    if(!current) return nullptr;
    //Will traverse the tree while current is non null
    //And compare the tageted name to the name of the current Country
    while(current){
        if(current->name==name) return current;
        if(name<current->name) current=current->left;
        else current=current->right;
    }
    return nullptr;
}