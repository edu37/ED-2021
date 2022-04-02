/* 

Tree Project 
Coded  by Richarde de Oliveira Lira - Registration 497319 
Coded  by Eduardo Tercio Viana Bezerra Filho - Registration 495337

*/

//Definição das bibliotecas e inclusão do TAD
//-------------------------//
#include <iostream>
#include <vector>
#include "tree.h"

using namespace std; 
//-------------------------// 

//Funções extras para funcionamento correto do programa
//-----------------------------------------------------//

void printAllSorts(vector<int> &sort);

//-----------------------------------------------------//



//Função Principal
int main(){
    vector<vector<int>> allLists;
    
    while(true){
        vector<int> list;  
        int sizeList; 
        tree trees; 

        cout << "Digite a quantidade de numeros que deseja ordenar" << endl; 
        cin >> sizeList; 
        if(sizeList <= 0){
            break;
        }
        cout << "Digite os valores a ser ordenados"<<endl; 
        for(int k = 0; k < sizeList; k++){
            int value = 0; 
            cin >> value; 
            list.push_back(value); 
        }
        list = trees.sortTree(list); //Recebe os elementos ordenados e coloca na lista 
        allLists.push_back(list);
        cout << endl;
    }
    cout << endl;
    if(allLists.size() > 0){
        cout << "Valores ordenados:" << endl;
    }
    for(int i = 0; i < (int)allLists.size(); i++){
       printAllSorts(allLists[i]);
    }
    return 0; 
}

// Printa os valores do vector passado
void printAllSorts(vector<int> &sort){
    for(int j = 0; j < (int)sort.size(); j++)  
        std::cout << sort[j] << " ";        
    std::cout << std::endl; 
}
   