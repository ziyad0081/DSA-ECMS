#include"../../Headers/District/District.h"


district :: district(const string& name) : dist_name(name), right_dist(nullptr), left_dist(nullptr){}


district :: ~district(){}


string district :: GetDistName() {return dist_name;}


district_tree :: district_tree() : root_dist(nullptr){}//default constructor;


//constructor for tree with already made root district:
district_tree :: district_tree(district* root) : root_dist(root){}


//directly create tree with root_dist name;
district_tree :: district_tree(const string & name) : root_dist(new district(name)){};


district_tree:: ~district_tree(){}



//the function to call when needing to insert, the work is done by the other function
district* district_tree :: InsertDist(const string& name)
{   //if root is null then done
    if(!root_dist) {root_dist=new district(name); return root_dist;}
    //else
    district* new_dist=new district(name);//creating a new dist obj to place in other insert funct;
    InsertDistAct(new_dist, root_dist);//insertion process
    return new_dist;
}



district* district_tree :: InsertDistAct(district*& new_dist, district*& root)//Insertion process
{
       if(!root){
            return new_dist; // this would be the right value for the current root's parent;
    }
    //traverse until correct position
    if(root->dist_name > new_dist->dist_name)
    {
      root->left_dist=InsertDistAct(new_dist, root->left_dist);
    }

     if(root->dist_name < new_dist->dist_name)
    {
      root->right_dist=InsertDistAct(new_dist, root->right_dist);
    }

    return root;//if it already exists; just to not get a non void with no return type;
}



 bool district_tree :: SearchForDist(const string& name)
 {
     district* search_dist=root_dist;
     //traverse tree;
     while( search_dist !=nullptr   && search_dist->dist_name != name)
     {
        if(search_dist->dist_name > name) search_dist=search_dist-> left_dist;
        else search_dist=search_dist-> right_dist;
     }
// if null then 0 , else 1;
     return(search_dist!=nullptr) ;

 }



//just to make it easier to use with one parameter string;
 void district_tree :: DeleteDist(const string& name)
 {
     DeleteDistAct(name, root_dist); //deletion process;
 }



  void district_tree :: DeleteDistAct(const string &name, district * & traverse_dist) {

    if (traverse_dist == nullptr)
        return;
//traverse tree;
    if (name < traverse_dist->GetDistName())
        DeleteDistAct(name, traverse_dist->left_dist);
    else if (traverse_dist->GetDistName() < name)
        DeleteDistAct(name, traverse_dist->right_dist);

        //found it;
        //case 1 : both children not null
    else if (traverse_dist->left_dist != nullptr &&  traverse_dist->right_dist != nullptr)
    {
        traverse_dist->dist_name = MinDist(traverse_dist->right_dist)->GetDistName();//MinDist returns pointer to most left leaf;
        DeleteDistAct(traverse_dist->GetDistName(), traverse_dist->right_dist);
    }

    //case 2, only one is null;
     else {
        district *old_dist = traverse_dist;//keep traverse_dist which is now the node to be deleted;
        traverse_dist = (traverse_dist->left_dist != nullptr) ? traverse_dist->left_dist : traverse_dist->right_dist;
        delete old_dist;
    }
}



district* district_tree ::  MinDist(district* node) {
    //returns most left node ptr;
    while (node->left_dist != nullptr) {
        node = node->left_dist;
    }
    return node;
}


void district_tree :: PrintDistTree()
{
  int n=0;//to keep track of n in recursive function;
  PrintDistTreeAct(root_dist, n);//printing process;
}


 void district_tree :: PrintDistTreeAct(district* root, int& n) {

    if (root == nullptr) return;
    PrintDistTreeAct(root->left_dist,n);//keep going until most left node;
    cout << root->dist_name << " "; ++n;//first occurence of this: name of most left leaf
    if( n % 10==0) cout<<endl;    //this would print 10 districts per line from smallest upwards;
    PrintDistTreeAct(root->right_dist,n);//first occurence of this: goes to right subtree of the most left leaf's parent and continues;

    //keep going up until root then move to right subtree of root;
}


