#include <iostream>
#include <vector>

#include "../Country/Country.cpp"
#include "../Region/Region.cpp"
#include "../Customer/CustomerTree.cpp"
#include "../Record/RecordList.cpp"

using namespace std;

int main()
{
    CountryTree tree;
    tree.InsertCountry("Algeria");
    auto cust = tree.SearchCountry("Algeria");
    cout << "HI";

    return 0;
}
