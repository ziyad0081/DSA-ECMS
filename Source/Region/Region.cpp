#include<iostream>
#include "../../Headers/Region/Region.h"

/*--------------------Region----------------------------------------*/
Region::Region(string n) {
    name = n;
    left = right = nullptr;
    
}
    

Region::~Region(){
    delete left;
    delete right;
}

MarketingDepartment* Region::GetDeptByCityName(string _name){
    if(!region_departments.size()){
        return nullptr;
    }
    for(int i = 0; i < 10; i++){
        if(region_departments[i]->city == _name){
            return region_departments[i];
        }
    }
    return nullptr;
}
MarketingDepartment* Region::InsertDepartment(MarketingDepartment* dept){
    region_departments.push_back(dept);
    return dept;
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

Region* RegionTree::InsertRegion(string region_name){
    Region* new_region= new Region(region_name);
    //Check if tree is empty
    if(!root) root=new_region;
    else{
        //Set current to traverse the tree and parent to keep updated with current's parent
        Region* current=root, *parent=root;
        while(current){
            parent=current; //Parent gets updated before each movement of the current
            if(region_name<current->name){
                current=current->left;
                if(!current){
                    parent->left=new_region;
                }
            }
            else if(region_name>current->name){
                current=current->right;
                if(!current){
                    parent->right=new_region;
                }
            }
            else break;
        }
    }
    return new_region;
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