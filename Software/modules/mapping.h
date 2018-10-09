#include <iostream>

using namespace std;

struct node{
# id of the corner
    int id;
    
# is this a wall node?
    bool isWall;

# pointers to surroundings
    corner* left;
    corner* right;
    corner* up;
    corner* down;
   
# distane to surroundings
    int leftDis;
    int rightDis;
    int upDis;
    int downDis;

};

node corner createMap(int* size){
# create the start node
    node start = ;
    
# create a map of nodes interconnected
    node tmp;
    for(i=0; i<size[0]; i++){
        for(j=0; j<size[1]; j++){
            node tmp = new node;
        }
    }
}
