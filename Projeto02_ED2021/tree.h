#ifndef TREE
#define TREE
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node *left;
    Node *right;

    Node(int valor, Node *l = nullptr, Node *r = nullptr) {
        value = valor;
        left = l;
        right = r;
    }
};

class tree{
    private:
    bool repeated = false;
    int i = 0;
    int height;
    int max;
    int min;
    Node *root; 
    vector<int> keepValues;
    vector<int> sortValues;
    
    void setupAtributes(vector<int> &values);
    Node *createTree(Node *node);
    void clear(Node *node);
    void insertList(Node *node);
    void sort(Node *node, int height);
    void changeValueMin(Node *node);
    int getMax(vector<int> vetor);
    
    public:
    tree();
    ~tree();
    vector<int>& sortTree(vector<int> values);
     
};


#endif 