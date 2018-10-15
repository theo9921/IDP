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
    
    node(int const id, bool const isWall):
        id(id), isWall(isWall){};
};

node createMap(int* size){
    // create the start node
    node* start = new node(0, false);
    return *start;
    
    // create a map of nodes interconnected
}

int main(){
    node* nodes[34];
    for(int i=0; i<34; i++){
        nodes[i] = new node(i, false);
    }
    nodes[0]->left = nodes[1];
    nodes[0]->down = nodes[32];
    nodes[32]->down = nodes[6];
    nodes[1]->down = nodes[7];
    nodes[1]->left = nodes[2];
    nodes[6]->left = nodes[33];
    nodes[33]->left = nodes[7];
    nodes[7]->left = nodes[8];
    nodes[7]->down = nodes[16];
    nodes[1]->left = nodes[2];
    nodes[2]->down = nodes[8];
    nodes[2]->left = nodes[3];
    nodes[8]->left = nodes[9];
    nodes[8]->down = nodes[17];
    nodes[16]->left = nodes[17];
    nodes[16]->down = nodes[20];
    nodes[17]->down = nodes[21];
    nodes[17]->left = nodes[18];
    nodes[20]->left = nodes[21];
    nodes[20]->down = nodes[24];
    nodes[21]->left = nodes[22];
    nodes[21]->down = nodes[25];
    nodes[24]->left = nodes[25];
    nodes[24]->down = nodes[28];
    nodes[25]->left = nodes[26];
    nodes[25]->down = nodes[29];
    nodes[28]->left = nodes[29];
    nodes[29]->left = nodes[30];
    
    
    
    
    cout << start->leftDis << endl;
    return 0;
}

