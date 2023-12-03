#include<iostream>
#include "../../Headers/Region/Region.h"

/*--------------------Region----------------------------------------*/
Region::Region(string n): name(n), left(nullptr), right(nullptr) {}

Region::~Region(){
    delete left;
    delete right;
}

MarketingDepartment Region::GetDeptByCityName(string _name){
    for(auto & dept : region_departments){ 
        if(dept.city == _name){
            return dept;
        }
    }
    throw out_of_range("Region not found!");
}
/*--------------------RegionTree----------------------------------------*/

RegionTree::RegionTree(): root(nullptr) {}

void RegionTree::DestroyRegions(Region *root){
    if (root){
        DestroyRegions(root->left);
        DestroyRegions(root->right);
        delete root;
    }
}

RegionTree::~RegionTree(){
    DestroyRegions(root);
}

void RegionTree::InsertRegion(string region_name){
    Region* new_region= new Region(region_name);
    //Check if tree is empty
    if(!root) root=new_region;
    else{
        //Set current to traverse the tree and parent to keep updated with current's parent
        Region* current=root, *parent=root;
        while(1){
            parent=current; //Parent gets updated before each movement of the current
            if(region_name<current->name){
                current=current->left;
                if(!current){
                    parent->left=new_region;
                    break;
                }
            }
            else if(region_name>current->name){
                current=current->right;
                if(!current){
                    parent->right=new_region;
                    break;
                }
            }
            else break;
        }
    }
}

Region* RegionTree::SearchRegion(string region_name){
    Region* current=root;
    if(!current) return nullptr;
    //Will traverse the tree while current is non null
    //And compare the tageted name to the name of the current Region
    while(current){
        if(current->name==region_name) return current;
        if(region_name<current->name) current=current->left;
        else current=current->right;
    }
    return nullptr;
}

void RegionTree::DeleteRegion(string region_name){
    Region* target= SearchRegion(region_name);
    if(!target) return;
    //No children; Delete directly
    if(!target->left && !target->right){
        delete target;
        target=nullptr;
    }
    //No left child; Keep right child
    else if(!target->left){
        Region* temp=target->right;
        delete target;
        target=temp;
    }
    //No right child; Keep left child
    else if(!target->right){
        Region* temp=target->left;
        delete target;
        target=temp;
    }
    //Both children there; 
    else{
        Region* temp=target->right;
        while(temp->left) temp=temp->left;
        target->name=temp->name;
        DeleteRegion(temp->name);
    }
}

void RegionTree::Print(Region* root) {
    if (root == nullptr) return;
    Print(root->left);
    cout << root->name << " ";
    Print(root->right);
}

void RegionTree::PrintRegions(Region* root){
    Print(root);
}