#include "Country.h"
#include <algorithm>

using namespace std;

/*--------------------Country----------------------------------------*/
Country::Country(string n): name(n), left(nullptr), right(nullptr) {

}


MarketingDepartment* Country::InsertDepartment(string region, string city){
    auto newDept = new MarketingDepartment(city);
    country_departments.push_back(newDept);
    auto located_region = (country_regions.SearchRegion(region) ? country_regions.SearchRegion(region) : country_regions.InsertRegion(region));
    located_region->InsertDepartment(newDept);
    return newDept;
}
//The add customer function first parses the address string, tries to resolve his location by region then by city and lastly the district within the latter
Customer* Country::AddCustomer(int customer_id,string _name, string addr_region,string addr_city,string addr_district,const vector<unsigned int>& _family_ages){
    
    //If the region is found then store it , else create it and store it    
    auto located_region = (country_regions.SearchRegion(addr_region) ? country_regions.SearchRegion(addr_region) : country_regions.InsertRegion(addr_region)) ;
    //The same logic as above but for the city
    auto located_dept = (located_region->GetDeptByCityName(addr_city) ? located_region->GetDeptByCityName(addr_city) : InsertDepartment(addr_region, addr_city));
    //Again , for the district :
    auto located_district = (located_dept->department_districts->SearchForDist(addr_district) ? located_dept->department_districts->SearchForDist(addr_district) : located_dept->department_districts->InsertDist(addr_district));
    auto addr = string(addr_region+","+addr_city+","+addr_district);
    auto newCustomer = new Customer(customer_id,_name,addr,_family_ages);
    

    _country_customers[customer_id] = newCustomer;
    located_district->InsertCustomer(newCustomer);
    
    return newCustomer;
}
/*--------------------CountryTree----------------------------------------*/

Customer* Country::GetCustomerByID(int customer_id)
{
    try{
        auto target = _country_customers.at(customer_id);
    } catch(const exception& e){
        return nullptr;
    }
    // if(country_customers.empty()) return nullptr;
    // auto target = (find_if(country_customers.begin(),country_customers.end(),[customer_id](const Customer* cust){ return customer_id == cust->GetCustomerID();}));
    // if(target == country_customers.end()){
    //     return nullptr;
    // }
    // return *target;
}
bool Country::CumInjComparator(Customer* a, Customer* b, string year_month){
    return a->GetCumInjectionByMonth(year_month) > b->GetCumInjectionByMonth(year_month);
}

Customer* Country::GetMonthWinnerCustomer(string year_month)
{
    Customer* max = nullptr ;
    for(auto& [id , customer] : _country_customers){
       if(max == nullptr){
        max = customer;       
       }
       if(customer->GetCumInjectionByMonth(year_month) > max->GetCumInjectionByMonth(year_month)){
        max = customer;
       }
    }
    return max;
}

void CountryTree::DestroyCountries(Country *root){
    if (root){
        DestroyCountries(root->left);
        DestroyCountries(root->right);
        delete root;
    }
}

CountryTree::~CountryTree(){}

Country* CountryTree::InsertCountry(string country_name){
    Country* new_country= new Country(country_name);
    //Check if tree is empty
    if(!root) {root=new_country; return new_country;}
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
    return root;
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

/*
Customer* CountryTree::GetBestCountryCumInjUtil(Country* root, string year_month){
    if (root == nullptr) return nullptr;

    stack<Customer*> best_country_customers;
    GetBestCountryCumInjUtil(root->left);
    if(root->country_regions.GetBestRegionCumInj(year_month).GetCumInjectionByMonth(year_month)>best_country_customers.top()->GetCumInjectionByMonth(year_month))
        best_country_customers.push(root->country_regions.GetBestRegionCumInj(year_month).GetCumInjectionByMonth(year_month));
    GetBestCountryCumInjUtil(root->right);
    return best_country_customers.top();
}

Customer* CountryTree::GetBestCountryCumInj(string year_month){
    return GetBestCountryCumInjUtil(root, year_month);
}
*/