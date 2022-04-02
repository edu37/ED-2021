/* 

Sparse Matrix
Coded  by Richarde de Oliveira Lira - Registration 497319 
Coded  by Eduardo Tercio Viana Bezerra Filho - Registration 495337

*/

//Definição das bibliotecas e inclusão do TAD
//-------------------------// 

#include <iostream>
#include <string>
#include <sstream>
#include <fstream> 
#include "Matrix.h"  
#include <vector>
using namespace std;

//-------------------------// 

//Funções extras para funcionamento correto do programa
//-----------------------------------------------------//

void menu(); 
void createMatrix(vector<Matrix*> *mat); 
void insertValue(vector<Matrix*> mat); 
void getValue(vector<Matrix*> mat); 
void printMatrix(vector<Matrix*> mat);
void sizeMatrix(vector<Matrix*> mat); 
void sumMatrix(vector<Matrix*> mat, vector<Matrix*> *matSoma); 
void multiplyMatrix(vector<Matrix*> mat, vector<Matrix*> *matMult); 
void subMatrix(vector<Matrix*> mat, vector<Matrix*> *matSub);
void readMatrix(vector<Matrix*> *mat);
void printAll(vector<Matrix*> mat);

//-----------------------------------------------------//

//Função Principal
int main(){
    menu(); 
    return 0; 
}
//-----------------------------------------------------// 

//Definição das funções extras

void menu(){
    //Vectors para auxiliar nas alocações das matrizes     
    //-----------------------------------------------//
    vector<Matrix*> matManual;
    vector<Matrix*> matSoma;
    vector<Matrix*> matSub; 
    vector<Matrix*> matMult;
    vector<Matrix*> matFile; 
    //-----------------------------------------------//
    
    
    cout <<"** Matrizes esparsas **"<<endl; // Introdução
    

	while(true) {
        // Variáveis para controlar o que é digitado pelo usuário
	    string cmd;
        //Definindo as opções do menu
        cout << endl;
        cout <<"Menu"<<endl;
        cout<<"Digite : 'criar' e informe o numero de linhas e colunas para criar uma matriz manual"<<endl;
        cout<<"Digite : 'inserir' para inserir um valor na celula (i,j) da matriz, i linha e j coluna"<<endl; 
        cout<<"Digite : 'devolver' para devolver um valor na celula (i,j) da matriz, i linha e j linha "<<endl;
        cout<<"Digite : 'imprimir' para imprimir a matriz, incluindo valores iguais a zero"<<endl;
        cout<<"Digite : 'somar' para somar sua matriz com outra matriz"<<endl;
        cout<<"Digite : 'multiplicar' para multiplicar sua matriz com outra matriz"<<endl; 
        cout<<"Digite : 'subtrair' para subtrair uma matriz com outra"<<endl;
        cout<<"Digite : 'tamanho' para ver quantos elementos foram inseridos em uma matriz"<<endl;
        cout<<"Digite : 'ler' para ler um arquivo que contenha uma matriz"<<endl; 
        cout<<"Digite : 'todas' mostrar todas as matrizes carregadas"<<endl;
        cout<<"Digite : 'guardar' para guardar todas as matrizes carregadas em um documento"<<endl;
        cout<<"Digite : 'limpar' para limpar o arquivo salvo"<<endl;
        cout<<"Digite : 'encerrar' para encerrar o programa"<<endl;  
        //Lê a string digitada pelo usuário
        getline(cin,cmd);
		
        if(cmd == "criar"){
            cout << endl;
            createMatrix(&matManual);
            cout << endl << "Matriz criada" << endl;
        }
       
        else if(cmd == "inserir"){
            cout << endl;
            int tipo;
            cout << "Qual tipo de matriz que deseja inserir um valor"<<endl;
            cout << "Digite : '1' para matrizes cridadas manualmente " << " quantidade: " << matManual.size() <<endl;
            cout << "Digite : '2' para matrizes lidas de arquivos " << " quantidade: " << matFile.size() <<endl;
            cin >> tipo;
            if(tipo == 1)
                insertValue(matManual);
            else if(tipo == 2)
                insertValue(matFile);
            else{
                cin.ignore();
                cout << "Tipo de matriz solicitado nao existe" << endl;
            }
        }

        else if(cmd == "devolver"){
            cout << endl;
            int tipo;
            cout << "Qual tipo de matriz deseja obter o valor"<<endl;
            cout<<"Pressione : 1 para matrizes cridadas manualmente " << " quantidade: " << matManual.size() <<endl;
            cout<<"Pressione : 2 para matrizes cridadas de soma " << " quantidade: " << matSoma.size() <<endl;
            cout<<"Pressione : 3 para matrizes lidas de arquivos " << " quantidade: " << matFile.size() <<endl;
            cout<<"Pressione : 4 para matrizes cridadas de multiplicacao " << " quantidade: " << matMult.size() <<endl;
            cout<<"Pressione : 5 para matrizes criadas de subtracao " << " quantidade: " << matSub.size() <<endl;
            cin >> tipo;
            if(tipo == 1 and matManual.size() > 0)
                getValue(matManual);
            else if(tipo == 2 and matSoma.size() > 0)
                getValue(matSoma);
            else if(tipo == 3 and matFile.size() > 0)
                getValue(matFile); 
            else if(tipo == 4 and matMult.size() > 0)
                getValue(matMult);
            else if(tipo == 5 and matSub.size() > 0)
                getValue(matSub);
            else{
                cin.ignore();
                cout << "Tipo de matriz solicitado nao existe" << endl;
            }
        }

        else if(cmd == "imprimir"){
            cout << endl;
            int tipo;
            cout << "Qual tipo de matriz deseja ver"<<endl;
            cout<<"Digite : '1' para matrizes cridadas manualmente " << " quantidade: " << matManual.size() <<endl;
            cout<<"Digite : '2' para matrizes cridadas de soma " << " quantidade: " << matSoma.size() <<endl;
            cout<<"Digite : '3' para matrizes lidas de arquivos " << " quantidade: " << matFile.size() <<endl;
            cout<<"Digite : '4' para matrizes cridadas de multiplicacao " << " quantidade: " << matMult.size() <<endl;
            cout<<"Digite : '5' para matrizes criadas de subtracao " << " quantidade: " << matSub.size() <<endl;
            cin >> tipo;
            if(tipo == 1 and matManual.size() > 0)
                printMatrix(matManual);
            else if(tipo == 2 and matSoma.size() > 0)
                printMatrix(matSoma);
            else if(tipo == 3 and matFile.size() > 0)
                printMatrix(matFile); 
            else if(tipo == 4 and matMult.size() > 0)
                printMatrix(matMult);
            else if(tipo == 5 and matSub.size() > 0)
                printMatrix(matSub);
            else{
                cin.ignore();
                cout << "Tipo de matriz solicitado nao existe" << endl;
            }
        }

        else if(cmd == "somar"){
            cout << endl;
            int tipo;
            cout << "Qual tipo de matriz que deseja somar"<<endl;
            cout<<"Pressione : 1 para matrizes cridadas manualmente " << " quantidade: " << matManual.size() <<endl;
            cout<<"Pressione : 2 para matrizes lidas de arquivos " << " quantidade: " << matFile.size() <<endl;
            cin >> tipo; 
            if(tipo == 1)
                sumMatrix(matManual,&matSoma);
            else if(tipo == 2)
                sumMatrix(matFile,&matSoma);
            else{
                cin.ignore();
                cout << "Tipo de matriz solicitado nao existe" << endl;
            }
        }

        else if(cmd == "multiplicar"){
            cout << endl;
            int tipo;
            cout << "Qual tipo de matriz que deseja multiplicar"<<endl;
            cout<<"Pressione : 1 para matrizes cridadas manualmente " << " quantidade: " << matManual.size() <<endl;
            cout<<"Pressione : 2 para matrizes lidas de arquivos " << " quantidade: " << matFile.size() <<endl;
            cin >> tipo;
            if(tipo == 1)
                multiplyMatrix(matManual,&matMult);
            else if(tipo == 2)
                multiplyMatrix(matFile,&matMult);
            else{
                cin.ignore();
                cout << "Tipo de matriz solicitado nao existe" << endl;
            }
        }

        else if(cmd == "subtrair"){
            cout << endl;
            int tipo;
            cout << "Qual tipo de matriz que deseja subtrair"<<endl;
            cout<<"Pressione : 1 para matrizes cridadas manualmente " << " quantidade: " << matManual.size() <<endl;
            cout<<"Pressione : 2 para matrizes lidas de arquivos " << " quantidade: " << matFile.size() <<endl;
            cin >> tipo; 
            if(tipo == 1)
                subMatrix(matManual,&matSub);
            else if(tipo == 2)
                subMatrix(matFile,&matSub);
            else{
                cin.ignore();
                cout << "Tipo de matriz solicitado nao existe" << endl;
            }
        }

        else if(cmd == "tamanho"){
            cout << endl;
            int tipo;
            cout << "Qual tipo de matriz deseja ver"<<endl;
            cout<<"Digite : '1' para matrizes cridadas manualmente " << " quantidade: " << matManual.size() <<endl;
            cout<<"Digite : '2' para matrizes cridadas de soma " << " quantidade: " << matSoma.size() <<endl;
            cout<<"Digite : '3' para matrizes lidas de arquivos " << " quantidade: " << matFile.size() <<endl;
            cout<<"Digite : '4' para matrizes cridadas de multiplicacao " << " quantidade: " << matMult.size() <<endl;
            cout<<"Digite : '5' para matrizes criadas de subtracao " << " quantidade: " << matSub.size() <<endl;
            cin >> tipo;
            if(tipo == 1 and matManual.size() > 0)
                sizeMatrix(matManual);
            else if(tipo == 2 and matSoma.size() > 0)
                sizeMatrix(matSoma);
            else if(tipo == 3 and matFile.size() > 0)
                sizeMatrix(matFile); 
            else if(tipo == 4 and matMult.size() > 0)
                sizeMatrix(matMult);
            else if(tipo == 5 and matSub.size() > 0)
                sizeMatrix(matSub);
            else{
                cin.ignore();
                cout << "Tipo de matriz solicitado nao existe" << endl;
            }
        }

        else if (cmd == "ler"){
            cout << endl;
            readMatrix(&matFile);
        }

        else if(cmd == "todas"){
            cout << endl;
            cout << "Matrizes adicionadas manualmente"<<endl;
            cout << "--------------------------------"<<endl; 
            printAll(matManual);  

            cout<<endl; 
            cout << "Matrizes adicionadas por leitura de arquivo"<<endl;
            cout << "--------------------------------"<<endl;   
            printAll(matFile);
            
            cout<<endl; 
            cout << "Matrizes resultantes de soma"<<endl;
            cout << "--------------------------------"<<endl; 
            printAll(matSoma);

            cout<<endl; 
            cout << "Matrizes resultantes de multiplicacao"<<endl;
            cout << "--------------------------------"<<endl;  
            printAll(matMult);

            cout<<endl; 
            cout << "Matrizes resultantes de subtracao"<<endl;
            cout << "--------------------------------"<<endl; 
            printAll(matSub);
        }

        else if(cmd == "guardar"){
            cout << endl;
            Matrix *mm; 
            mm->print_in_the_file(matManual, matSoma, matFile, matMult, matSub);
        }

        else if(cmd == "limpar"){
            cout << endl;
            cout << "** Documento apagado **";
            remove("MatrixFile.txt");
        }

        else if(cmd == "encerrar"){
            cout << endl;
			for(int i = 0; i < (int)matManual.size(); i++)
                delete matManual[i]; 
			matManual.clear();
            for(int i = 0; i < (int)matFile.size(); i++)
                delete matFile[i];
			matFile.clear();
            for(int i = 0; i < (int)matSoma.size(); i++)
                delete matSoma[i];
		    matSoma.clear();
            for(int i = 0; i < (int)matMult.size(); i++)
                delete matMult[i];   
			matMult.clear();
            for(int i = 0; i < (int)matSub.size(); i++)
                delete matSub[i];    
			matSub.clear();
			cout << "saindo..." << endl;
			break;
		}
        
        else{
            cout << endl;
            cout << "----------Comando invalido!!----------" << endl; 
            cout << "(lembre-se de nao utilizar espaco ao digitar algum comando do menu)" << endl;
            cout << endl;
        }
     }
    
     return; 
}


//Definindo o que cada comando faz; 


void createMatrix(vector <Matrix*> *mat){
    int n, m;
    cout << "linhas, colunas" << endl;
    cin >> n >> m; 
    cin.ignore();
    Matrix *nova = new Matrix(n,m);
    mat->push_back(nova); 
} 

void insertValue(vector<Matrix*> mat){
    int n, m, value, matriz;
    cout << "Escolha a matriz(1, 2, 3 etc...)" << endl;
    cin >> matriz;
    if(mat.size() > 0 and matriz > 0 and matriz <= (int)mat.size()){ //Confere se o número digitado referente a matriz representa uma matriz existente
        matriz--;
        cout << "linhas, colunas, valor" << endl;
        cin >> n >> m >> value;
        cin.ignore();
        mat[matriz]->insert(n,m,value);
    }
    else{
        cin.ignore();
        cout << "Error: matriz selecionada nao existe" << endl;
    }
}

void getValue(vector<Matrix*> mat){
    int matriz, n, m;
    cout << "qual matriz deseja obter o valor(1, 2, 3 etc..)" << endl;
    cin >> matriz;
    matriz--;
    cout << "linha e coluna desejada" << endl;
    cin >> n >> m; // Linha e coluna
    cin.ignore();
    int linha = mat[matriz]->getLine();
    int coluna = mat[matriz]->getColun();
    if(n > linha || n < 1 || m > coluna || m < 1)
        cout << "Error: posicao invalida";
    else
        cout << "Valor na posicao [" << n << "][" << m << "]: " << mat[matriz]->getValue(n,m) << endl;
}

void printMatrix(vector<Matrix*> mat){
    int matriz;
    cout << "qual matriz deseja ver(1, 2, 3 etc..)" << endl;
    cin >> matriz;
    cin.ignore(); 
    if(mat.size() > 0 and matriz > 0 and matriz <= (int)mat.size()){//Confere se o número digitado referente a matriz representa uma matriz existente
        matriz--;
        mat[matriz]->print();    
    }
    else
        cout << "Error: matriz selecionada nao existe" << endl;
}

void sizeMatrix(vector<Matrix*> mat){
    int matriz;
    cout << "qual matriz deseja ver(1, 2, 3 etc..)" << endl;
    cin >> matriz;
    cin.ignore(); 
    if(mat.size() > 0 and matriz > 0 and matriz <= (int)mat.size()){//Confere se o número digitado referente a matriz representa uma matriz existente
        matriz--;
        cout << mat[matriz]->getSize() << endl;    
    }
    else
        cout << "Error: matriz selecionada nao existe" << endl;
}

void sumMatrix(vector<Matrix*> mat, vector<Matrix*> *matSoma){
    int mat1, mat2;
    cout << "escolha as duas matrizes que deseja somar" << endl;
    cin >> mat1 >> mat2;
    cin.ignore();
    if(mat.size() > 0 and mat1 > 0 and mat2 > 0 and mat1 <= (int)mat.size() and mat2 <= (int)mat.size()){  //Confere se o número digitado referente a matriz representa uma matriz existente
        mat1--; 
        mat2--; 
        Matrix *resultado;
        resultado = resultado->soma(mat[mat1], mat[mat2]);
        if(resultado != nullptr){ 
            matSoma->push_back(resultado);
            resultado->print();
        }

    }   
    else{
        cout << "Error: matriz selecionada nao existe" << endl;
    }
} 

void multiplyMatrix(vector<Matrix*> mat, vector<Matrix*> *matMult){
    int mat1, mat2;
    cout << "escolha as duas matrizes que deseja multiplicar" << endl;
    cin >> mat1 >> mat2;
    cin.ignore();
    if(mat.size() > 0 and mat1 > 0 and mat2 > 0 and mat1 <= (int)mat.size() and mat2 <= (int)mat.size()){ //Confere se o número digitado referente a matriz representa uma matriz existente
        mat1--; 
        mat2--; 
        Matrix *resultado;
        resultado = resultado->multiplica(mat[mat1], mat[mat2]);
        if(resultado != nullptr) {
            matMult->push_back(resultado);
            resultado->print();       
        } 
    }
    else
        cout << "Error: matriz selecionada nao existe" << endl;
} 

void subMatrix(vector<Matrix*> mat, vector<Matrix*> *matSub){
    int mat1, mat2;
    cout << "escolha as duas matrizes que deseja subtrair" << endl;
    cin >> mat1 >> mat2;
    cin.ignore();
    if(mat.size() > 0 and mat1 > 0 and mat2 > 0 and mat1 <= (int)mat.size() and mat2 <= (int)mat.size()){ //Confere se o número digitado referente a matriz representa uma matriz existente
        mat1--; 
        mat2--; 
        Matrix *resultado;
        resultado = resultado->subtracao(mat[mat1], mat[mat2]);
        if(resultado != nullptr){ 
            matSub->push_back(resultado);
            resultado->print();
        }
    }   
    else{
        cout << "Error: matriz selecionada nao existe" << endl;
    }
} 

void readMatrix(vector<Matrix*> *mat){
    string name; 
    Matrix *m;  
    cout<<"Digite o nome do arquivo"<<endl; 
    getline(cin,name);
    m = m->lerMatrizDeArquivo(name);
    if(m != nullptr) 
        mat->push_back(m);
}

void printAll(vector<Matrix*> mat){
    int it = 0;
    mat.begin();
    if(mat.size() == 0) cout<<"Vazio"<<endl; 
    else{
        while(it < (int)mat.size()){
            cout << "Matriz " << it+1 << ":" << endl;
            mat[it]->print();
            it++;   
        }
    }   
}