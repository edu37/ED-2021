#include <iostream>
#include <vector> 
#include <math.h>
#include "tree.h"
using namespace std;


// Métodos Públicos:

tree::tree(){
    Node *novo = new Node(0);
    root = novo;
}

tree::~tree(){
    clear(root);
}

// Método público utilizado para ordenar a lista que o usuário passa como parâmetro
// Esse método é responsável por várias chamadas, sendo elas: setar os atributos, criar a árvore,
// colocar os valores digitados pelo usuário nas folhas, ordenar e alterar o menor valor.
vector<int>& tree::sortTree(vector<int> values){
    int size = values.size();
    setupAtributes(values);
    for(int j = 0; j < height-1; j++)
        createTree(root);
    insertList(root);

    for(int j = 0; j < size; j++){
        sort(root, 1);                      //organiza os valores na arvore de acordo os filhos   
        min = root->value;                  //o valor minimo recebe o valor da raiz
        sortValues.push_back(root->value);  //adicionamos o valor da raiz a lista
        changeValueMin(root);               //substituimos o menor valor pelo maior valor
        repeated = false;
    }                  
    return sortValues;
}

// Métodos Privados:

// Utilizado para atribuir os valores para os atributos da árvore e também completamos as folhas restantes, caso a quantidade
// de valores inseridos pelo usuário não seja o suficiente para completar as folhas da árvore, de acordo com sua altura
void tree::setupAtributes(vector<int> &values){
    keepValues = values;
    int completeLeaves; 
    int bigger;

    bigger = getMax(keepValues) + 1; 
    height = ceil(log2(keepValues.size())) + 1; 
    completeLeaves = pow(2, height-1) - keepValues.size();
    for(int k = 0; k < completeLeaves; k++){ 
        keepValues.push_back(bigger);
    } 
    max = getMax(keepValues); 
}

// Criamos uma árvore cheia, de acordo com a altura que é usada como a condição de parada do laço
Node *tree::createTree(Node *node){
    if(node == nullptr){
        Node *novo = new Node(0);
        return novo;
    }
    node->left = createTree(node->left);
    node->right = createTree(node->right);
    return node;
}

// Inserimos o vetor digitado pelo usuário nas folhas da árvore
void tree::insertList(Node *node){
    if(node->left == nullptr){ 
        node->value = keepValues[i];
        i++; 
        return;
    }
    insertList(node->left);
    insertList(node->right);
}

// Ordenamos a árvore, colocando o menor valor no root
void tree::sort(Node *node, int height){
    if(height == this->height){
        return;
    }
    sort(node->left,height+1);
    sort(node->right,height+1);
    int value1 = node->left->value;
    int value2 = node->right->value;
    if(value1 < value2)
        node->value = value1;
    else if(value2 == value1)
        node->value = value2;
    else
        node->value = value2;
} 

// Modificamos o menor valor atual e substituímos pelo valor maior
void tree::changeValueMin(Node *node){    
    if(node != nullptr) {
        if(node->left == nullptr){ // se estivermos em um dos ultimos elementos da árvore(folha)
            if(node->value == min and !repeated){
                node->value = max;
                repeated = true;
            }
        }
        else if(node->value == min)
            node->value = max;
        changeValueMin(node->left); 
        changeValueMin(node->right);
    }
}

// limpamos a árvore, desalocando os valores dela
void tree::clear(Node *node){  
    if(node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

// Pega o maior valor do vector
int tree::getMax(vector<int> vetor){
    int result; 
    for(int k = 0; k < (int)vetor.size(); k++){
        if(vetor[k] > result) 
            result = vetor[k];  
    }
    return result; 
}  