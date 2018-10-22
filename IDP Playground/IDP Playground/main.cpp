#include <iostream>

using namespace std;

#define NODE_NUM 34

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
//
    node():
        isWall(false), left(NULL), right(NULL), up(NULL), down(NULL){};
};

node* enrichMap(node* nodes){
    for(int i=0; i<NODE_NUM; i++){
        node* thisNode = nodes + i;
        if(thisNode->left){
            if(!thisNode->left->right)
                thisNode->left->right = thisNode;
        }
        
        if(thisNode->right){
            if(!thisNode->right->left)
                thisNode->right->left = thisNode;
        }
        
        if(thisNode->up){
            if(!thisNode->up->down)
                thisNode->up->down = thisNode;
        }
        
        if(nodes[i].down){
            if(!thisNode->down->up)
                thisNode->down->up = thisNode;
        }
    }
    
    // sanity check
    node* dbug = nodes+32;
    for(int i=0; i<NODE_NUM; i++){
        node* thisNode = nodes + i;
        if(thisNode->left && thisNode->left->right != thisNode)
            cout << "nodes " << i << " left right false" << endl;
        if(thisNode->right && thisNode->right->left != thisNode)
            cout << "nodes " << i << " right left false" << endl;
        if(thisNode->up && thisNode->up->down != thisNode)
            cout << "nodes " << i << " up down false" << endl;
        if(thisNode->down && thisNode->down->up != thisNode)
            cout << "nodes " << i << " down up false" << endl;
    }
    return nodes;
}


node* createMap(){
    // initialize the node array
    node* nodes = new node[NODE_NUM];
    for(int i=0; i<NODE_NUM; i++){
        nodes[i].id = i;
    }
    
    // interconnect  nodess
    nodes[0].left =  nodes+1;
    nodes[0].down =  nodes+32;
    nodes[32].down =  nodes+6;
    nodes[1].down =  nodes+7;
    nodes[1].left =  nodes+2;
    nodes[6].left =  nodes+33;
    nodes[33].left =  nodes+7;
    nodes[7].left =  nodes+8;
    nodes[7].down =  nodes+16;
    nodes[1].left =  nodes+2;
    nodes[2].down =  nodes+8;
    nodes[2].left =  nodes+3;
    nodes[8].left =  nodes+9;
    nodes[8].down =  nodes+17;
    nodes[16].left =  nodes+17;
    nodes[16].down =  nodes+20;
    nodes[17].down =  nodes+21;
    nodes[17].left =  nodes+18;
    nodes[20].left =  nodes+21;
    nodes[20].down =  nodes+24;
    nodes[21].left =  nodes+22;
    nodes[21].down =  nodes+25;
    nodes[24].left =  nodes+25;
    nodes[24].down =  nodes+28;
    nodes[25].left =  nodes+26;
    nodes[25].down =  nodes+29;
    nodes[28].left =  nodes+29;
    nodes[29].left =  nodes+30;
    nodes[5].right =  nodes+4;
    nodes[5].down =  nodes+11;
    nodes[4].right =  nodes+3;
    nodes[4].down =  nodes+10;
    nodes[10].right =  nodes+9;
    nodes[10].down =  nodes+12;
    nodes[11].right =  nodes+10;
    nodes[11].down =  nodes+13;
    nodes[13].right =  nodes+12;
    nodes[13].down =  nodes+15;
    nodes[12].down =  nodes+14;
    nodes[15].right =  nodes+14;
    nodes[15].down =  nodes+19;
    nodes[14].down =  nodes+18;
    nodes[19].down =  nodes+23;
    nodes[19].right =  nodes+18;
    nodes[18].down =  nodes+22;
    nodes[23].right =  nodes+22;
    nodes[23].down =  nodes+27;
    nodes[22].down =  nodes+26;
    nodes[27].right =  nodes+26;
    nodes[27].down =  nodes+31;
    nodes[26].down =  nodes+30;
    nodes[31].right =  nodes+30;
    
    // enrich the manully labelled map
    return enrichMap(nodes);
}

int main(){
    node* nodes = createMap();
    return 0;
}

