#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <string>
#include "Matrix.h" 
using namespace std;

//*******************************//
//Implementação das funções membros
//*******************************//


void Matrix::init(const int& linha, const int& coluna){
    this-> size = 0; 
    this->linha = linha;
    this->coluna = coluna;

    //cria o primeiro nó cabeça (ponta esquerda-cima)
    Node *headPrincipal = new (nothrow) Node;
    
    if(headPrincipal == nullptr)
        return;
    headPrincipal->line = -1;
    headPrincipal->colun = -1;

    atual = headPrincipal;
    head = headPrincipal;

    //cria os nós cabeças das colunas
    for(int i = 0; i < coluna; i++){
        Node *headColuna = new (nothrow) Node;
        headColuna->line = 0;
        headColuna->colun = -1;
        atual->right = headColuna;
        atual = headColuna;
        headColuna->right = head;
        headColuna->down = headColuna;
    }
    atual = head;

    //cria os nós cabeças das linhas
    for(int i = 0; i < linha; i++){
        Node *headLinhas = new (nothrow) Node;
        headLinhas->colun = 0;
        headLinhas->line = -1;
        atual->down = headLinhas;
        atual = headLinhas;
        headLinhas->down = head;
        headLinhas->right = headLinhas;
    }
}

void Matrix::removeAll(){
    if(linha <= 0 and coluna <= 0) return; 
 
    //Desalocando a matriz
    //Pocisionamos o atual
    
    atual = head; 
    atual = atual->down; 
    atual = atual->right; 
    
    for(int i=1; i<=linha; i++){
        for(int j=1; j<=coluna; j++){
            if(atual->line == i and atual->colun == j){
                Node *aux;    //Caminhamos por toda a matriz onda a valor alocado 
                aux = atual;  //Colocamos aux para receber atual e apagamos aux
                atual = atual->right; 
                delete aux;
            }
        atual = atual->down->right; //Andamos com o atual para a proxíma linha
        }
    }

    //Desalocando os nós principais 
    //Nós colunas 
    atual = head; 
    atual = head->right;

    for(int i=1; i<=coluna; i++){ //Andando pelas as colunas e deletando cada nó
        Node *aux; 
        aux = atual; 
        atual = atual->right;
        delete aux; 
    } 

    atual = head; 
    atual = head->down; 

    for(int j=1; j<=linha; j++){ //Andando pelas as linha e deletando cada nó
        Node *aux; 
        aux = atual; 
        atual = atual->down; 
        delete aux; 
    }


    Node *aux;  //Deletando o nó cabeça principal
    aux  = head; 
    delete aux; 

    head = atual = nullptr; 
    linha = coluna = 0; 

    return; 

}

Matrix::Matrix(int m, int n){
    init(m,n);
}

Matrix::~Matrix(){
    removeAll();
}
// se   atual->right->colun  for menor que j     
void Matrix::insert(int i, int j, double value){
    bool substituir = false;

    if(i < 1 or j < 1 ){
        cout << "Error: posicao invalida" << endl; 
        return;
    }
    if(i > linha or j > coluna){
        cout << "Error: posicao invalida" << endl; 
        return;
    }

    //No 'for' caminhamos com o '*atual' até o nó cabeça da linha i
    atual = head;
    int it;
    for(it = 0; it < i; it++){
        atual = atual->down;
    }
    //Criamos o nó a ser inserido 
    Node *aux = new (nothrow) Node;
    aux->colun = j;
    aux->line = i;
    aux->value = value;

    //Aqui fazemos com que o nó anterior aponte para o nó criado, e o nó criado aponte para o próximo 
    it = 0;
    while(it < j and atual->right->line != -1){                                           
        if(atual->right->colun == aux->colun and atual->right->line == aux->line){        
            atual->right->value = aux->value;
            substituir = true;
            break;
        }
        if(atual->right->colun > aux->colun){
            aux->right = atual->right;
            atual->right = aux;
        }
        else
            atual = atual->right;
        it++;
    }
    if(atual->right->line == -1 and !substituir){
        aux->right = atual->right;
        atual->right = aux;
    }

    //No 'for' caminhamos com o '*atual' até o nó cabeça da coluna j
    atual = head;
    for(it = 0; it < j; it++){
        atual = atual->right;
    }
    
    //Aqui fazemos com que o nó anterior aponte para o nó criado, e o nó criado aponte para o próximo 
    it = 0;
    while(it < i and atual->down->colun != -1){
        if(substituir){
            break;
        }
        if(atual->down->line > aux->line){
            aux->down = atual->down;
            atual->down = aux;
        }
        else
            atual = atual->down;
        it++;
    }
    if(atual->down->colun == -1 and !substituir){
        aux->down = atual->down;
        atual->down = aux;
    }
    if(substituir)
        delete aux;
    else
        size++;
    cout<<"Valor adicionado: " << "linha: " << aux->line << " coluna: " << aux->colun << " valor: " << aux->value <<endl; 

}

double Matrix::getValue(int i, int j){ 
    atual = head;  
    for(int it=0; it<j; it++) 
        atual = atual->right;  //Andamos com o atual até a coluna desejada
    for(int it=0; it<i; it++){
        atual = atual->down; //Descemos com atual até a linha desejada
        if(atual->colun == -1) return 0; 
        if(atual->line == i) return atual->value; //Retornamos o valor
    }
    return 0;
}

int Matrix::getLine(){
    return this->linha; 
}

int Matrix::getColun(){
    return this->coluna; 
}

int Matrix::getSize(){
    return this->size; 
}

void Matrix::print(){
    //Caso a matriz não exista 
    if(linha < 1 and coluna < 1)
        return;

    atual = head->down;  

    for(int i = 1; i <= linha; i++){  //Verificamos cada posição referente a linha e coluna e, caso exista, printamos o valor correspondente 
        for(int j = 1; j <= coluna; j++){ 
            if(atual->right->line == i and atual->right->colun == j){  
                atual = atual->right; 
                cout << atual->value;   
            }
            else
                cout << "0"; //Se a linha e coluna daquela posição não existir, colocamos 0 na tela
            cout << "  ";
        }
        cout << endl;
        atual = atual->right->down; // Descemos a proxíma linha 
    }

}



Matrix* Matrix::soma(Matrix *A, Matrix *B){
    //Tem que ter o mesmo número de linhas e de colunas
    if(A->linha != B->linha or A->coluna != B->coluna ){ 
        cout<<"Impossivel : Matrizes com ordens diferentes"<<endl;
        return nullptr; 
    }
    
    //Alocando a matriz resultante da soma
    Matrix *sum = new (nothrow) Matrix(A->linha , A->coluna); 
    //Inciando a soma
    double aux_sum;
    for(int i=1; i<=A->linha; i++){  //linha 1
        for(int j=1; j<=A->coluna;j++){ //Coluna 1 , 2 , 3  , 4 ... n 
            aux_sum = 0;
            aux_sum = A->getValue(i,j) + B->getValue(i,j);
            sum->insert(i,j,aux_sum); 
        }
    }
    return sum; 
}

Matrix* Matrix::subtracao(Matrix *A, Matrix *B){
    //Verifica se as matrizes possuem a mesma ordem
    if(A->linha != B->linha and A->coluna != B->coluna){ 
        cout << "Impossivel :Matrizes com ordens diferentes"; 
        return nullptr; 
    }

    //Alocando a matriz resultante da subtração que será retornada
    Matrix *sub = new (nothrow) Matrix(A->linha , A->coluna);
    //Inciando a subtração
    double aux_sub; 
    for(int i = 1; i <= A->linha; i++){
        for(int j = 1; j <= A->coluna; j++){
            aux_sub = 0; 
            aux_sub = A->getValue(i,j) - B->getValue(i,j); 
            sub->insert(i,j,aux_sub); 
        }
    }

    return sub; 
}
 
Matrix* Matrix::multiplica(Matrix *A, Matrix *B){
    //Verifica se é possível fazer a multiplicação
    if(A->coluna != B->linha){
        cout << "Nao e possivel multiplicar essas matrizes" << endl;
        return nullptr;
    }
    //Alocação de uma matriz auxiliar para ser retornada
    Matrix *produto = new (nothrow) Matrix(A->linha, B->coluna);
    
    //Variável que faz o controle da soma das colunas de A com as linhas de B
    int aux = A->coluna = B->linha;

    //A nova matriz deve ter a ordem da linha de A com a coluna de B
    for(int i = 1; i <= A->linha; i++){
        double result;
        for(int j = 1; j <= B->coluna; j++){
            result = 0;
            for(int k = 1; k <= aux; k++){
                result += (A->getValue(i,k) * B->getValue(k,j));
            }
            produto->insert(i,j,result);
        }
    }
    return produto;
} 
  
 Matrix* Matrix::lerMatrizDeArquivo(std::string nome_do_arquivo){
    
  
    ifstream matriz; 
    double number;
    matriz.open(nome_do_arquivo); //Abrimos o arquivo colocando o seu nome 
     
    if(!matriz.is_open()){  //Verificamos se o arquivo foi aberto corretamente 
        cout<<"Erro de leitura"<<endl;
        return nullptr;    
    }
    
    //Vector para guardar os valores lidos 
    vector<double>storage_value; 
    

    cout << "Matriz encontrada" << endl; 
    cout << endl; 
       
    while(matriz >> number){
        storage_value.push_back(number); //Passamos todas as informas do arquivo .txt para dentro do vector 
    }

    storage_value.begin(); //Posicionamos para o primeiro elemento     
    Matrix *file = new Matrix(storage_value[0], storage_value[1]); //Alocamos uma nova matriz  **Obs : posição 0 e 1 do vector guardas as linhas de colunas da matiz **
    int line,colun; 
    int counter=0;  
    double storage=0; 
    storage_value.begin();  
    for(int it=2; it < (int)storage_value.size(); it++){ //Portanto começamos da posição 2
       if(counter == 0){
           line = storage_value[it]; //Linha recebe valor de vector na posicao que representa a linha 
           counter++; 
       }else if(counter == 1){
           colun = storage_value[it];//Coluna recebe o valor de vector na posicao que representa a coluna
           counter++; 
       }else if(counter == 2){
           storage = storage_value[it]; 
           file->insert(line,colun,storage); //Por fim, usamos a função insert para inserir todos os valores
           counter = line = colun = storage = 0; //Zeramos tudo e reiniciamos 
       }

    }

    matriz.close(); //Fechamos o arquivo 
    return file;   //Retornamos a matriz
} 

 
void Matrix:: print_in_the_file(vector<Matrix*> mat, vector<Matrix*> soma, vector<Matrix*> File, vector<Matrix*> mult, vector<Matrix*> sub){

    ofstream file; 

    //Apagamos o arquivo ao criar para que sempre seja criado um atualizado
    remove("MatrixFile.txt");
    
    file.open("MatrixFile.txt",ios::app); //Criando arquivo 
    int i,j,size;   
    i = j = size = 0;
   
        file << "Matrizes adicionadas manualmente.\n";
        if(mat.size()==0) 
            file << "Nao foi adicionada matrizes de forma manual.\n";  //Caso não tenha nenhuma matriz. 
        else{ 
            while(size < (int)mat.size()){  //Acessaremos todos as matrizes contidas no vector até size()-1
                file<<"Matriz :"<<size+1<<endl; 
                for(i=1; i<=mat[size]->linha; i++){ //Posicionar as linhas 
                    for(j=1; j<=mat[size]->coluna; j++){ //Posicionar as colunas 
                        file << mat[size]->getValue(i,j) << " "; //Depois chamamos o método GetValue para acessar os valores correspondentes   
                    }                                            //Passomos esses valores para dentro do arquivo file
                    file << "\n";
                }
                size++; //Atualizamos size para acessar o proxíma matriz 
                file <<"\n";
            }
        }//Processo acima se repete para todas as outras situações          
    
        i = j = size = 0;   
        file<<"\n"; 
        file << "Matrizes adicionadas por leitura de arquivo\n";
        if(File.size()==0)
            file << "Nao foi lida nenhuma matriz de nenhum arquivo\n"; 
        else{
            while(size < (int)File.size()){
                file<<"Matriz :"<<size+1<<endl;
                for(i=1; i<=File[size]->linha; i++){
                    for(j=1; j<=File[size]->coluna; j++){   
                        file << File[size]->getValue(i,j) << " "; 
                    }
                    file<<"\n"; 
                }
                size++;
                file <<"\n";  
            }
        }
      
       
        i = j = size =0; 
        file <<"\n"; 
        file << "Matrizes resultantes da soma\n";
        if(soma.size()==0)
            file << "Nao foi somada nenhuma matriz\n";
        else{
            while(size < (int)soma.size()){
                file<<"Matriz :"<<size+1<<endl;
                for(i=1; i<=soma[size]->linha; i++){
                    for(j=1; j<=soma[size]->coluna; j++)
                        file << soma[size]->getValue(i,j) << " ";
                    file<<"\n";
                }
                size++;
                file << "\n"; 
            }
        }  
    
        
        i = j = size =0; 
        file <<"\n"; 
        file << "Matrizes resultantes da multiplicação\n";
        if(mult.size()==0) 
            file << "Nao foi multiplicada nenhuma matriz\n";
        else{
            while(size < (int)mult.size()){                
                file<<"Matriz :"<<size+1<<endl;
                for(i=1; i<=mult[size]->linha; i++){
                    for(j=1; j<=mult[size]->coluna; j++)
                        file << mult[size]->getValue(i,j) << " "; 
                    file<<"\n";
                }
                size++;
                file<<"\n";
            }
        }  


        i = j = size =0; 
        file <<"\n"; 
        file << "Matrizes resultantes da subtracao\n";
        if(sub.size()==0) 
            file << "Nao foi subtraida nenhuma matriz\n";
        else{
            while(size < (int)sub.size()){
                file<<"Matriz :"<<size+1<<endl;
                for(i=1; i<=sub[size]->linha; i++){
                    for(j=1; j<=sub[size]->coluna; j++)
                        file << sub[size]->getValue(i,j) << " "; 
                    file<<"\n";
                }
                size++;
                file<<"\n";
            }
        }
    
     
    cout<<" ** Documento gerado com o nome : MatrixFile.txt ** "<<endl; //Declaramos que o documento foi gerado com sucesso
    file.close(); //Fechamos o arquivo
   
}

 