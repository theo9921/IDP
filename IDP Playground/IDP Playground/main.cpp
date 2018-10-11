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
    
    node(int const id, bool const isWall, int const leftDis, int const rightDis, int const upDis, int const downDis):
    id(id), isWall(isWall), leftDis(leftDis), rightDis(rightDis), upDis(upDis), downDis(downDis){};
};

node createMap(int* size){
    // create the start node
    node* start = new node(0, false, 0, 0, 0, 0);
    return *start;
    
    // create a map of nodes interconnected
}

int main(){
    node* start = new node(0, false, 0, 0, 0, 0);
    cout << start->leftDis << endl;
    return 0;
}

