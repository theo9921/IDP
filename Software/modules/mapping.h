#include <iostream>

using namespace std;

struct node{
    // id of the corner
    int id;
    
    // is this a wall node?
    bool isWall;

    // pointers to surroundings
    node* left;
    node* right;
    node* up;
    node* down;
   
    // distance to surroundings
    int leftDis;
    int rightDis;
    int upDis;
    int downDis;

};

node createMap(int* size){
    // create the start node
    node start;
    return start;
    
    // create a map of nodes interconnected
    
}
