#include<iostream>
#include<cmath>
#include<string>
using namespace std;



struct district{
 public:
 friend class district_tree;
 district(const string& ="");
 string GetDistName();
 ~district();

 private:
 string dist_name;
 district* left_dist;
 district* right_dist;

 };

 class district_tree{
 public:
 district_tree();
 district_tree(const string&);
 district_tree(district*);
 ~district_tree();
 district* InsertDist(const string&);
 void DeleteDist(const string&);
 bool SearchForDist(const string&);
 void PrintDistTree();
 district* root_dist;


 private:
  district* InsertDistAct(district*& new_dist, district*& root);
  district* MinDist(district*);
  void DeleteDistAct(const string &, district * &);
  void PrintDistTreeAct(district*, int &);
 };
