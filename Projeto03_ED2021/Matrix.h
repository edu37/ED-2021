#ifndef MATRIX_ED_2021
#define MATRIX_ED_2021
#include <vector> 
 
using namespace std; 
 
//*************************//
//Declaração da Classe Matrix 
//*************************//



struct Node
{
    Node *right;
    Node *down;   
    int line;    
    int colun; 
    double value;     
};

class Matrix
{
private:

    Node *head;
    Node *atual;
    int size;  
    int linha;
    int coluna;
    
    //Função utilizada pelo construtor para inicializar a matriz
    void init(const int& linha, const int& coluna);
    //Função utilizada pelo destrutor para apagar a matriz
    void removeAll();

public:
    
    //Inicializa uma matriz esparsa vazia com capacidade para m linhas e n colunas.
    Matrix(int m = 0, int n = 0);

    //Destrutor  que  libera  toda  a  mem oria  que  foi 
    //alocada  dinamicamente  para  esta estrutura de dados.
    ~Matrix();
    
    //Insere um valor na célula (i, j) da matriz, ondei ́e alinha ej ́e a coluna.
    void insert(int i, int j, double value);
    
    //Devolve o valor na c ́elula (i, j) da matriz, onde i ́e a linha ej ́e a coluna.
    double getValue(int i, int j);

    //Devolve o número de linhas
    int getLine();

    //Devolve o número de colunas
    int getColun();

    //Devolve o número de elementos *INSERIDOS*
    int getSize();
    
    //Esse mé todo imprime a matriz A, inclusive os elementos iguais a zero.
    void print();
    
    //Essa função recebe como parâmetro as matrizes A e B, 
    //devolvendo uma matriz C que  ́e a soma de Acom B.
   Matrix *soma(Matrix *A, Matrix *B);

    //Essa função recebe como parâmetro as matrizes A e B, 
    //devolvendo uma matriz C que ́e a subtração de A com B.
   Matrix* subtracao(Matrix *A, Matrix *B); 
    
    //Essa fun ̧c ̃ao recebe como parˆametro as matrizes A e B, 
   //devolvendo uma matriz Cque  ́e o produto de A por B.
    Matrix *multiplica(Matrix *A, Matrix *B);
    
    //Essa função lê, de um arquivo de entrada, os 
    //elementos diferentes de zero de uma matriz 
    //e monta a estrutura especificada anteriormente, 
    //devolvendo um ponteiro para uma Matriz alocada dinamicamente.  
    //Considere que a primeira linha do arquivo de entrada 
    //consiste dos valores dos m e n( números de linhas e de colunas da matriz), 
    //eas demais linhas do arquivo são constituídas de triplas (i, j, valor) 
    //para os elementos diferentes de zero da matriz.  
    //Por exemplo, para a matriz A anterior, o conteúdo do arquivo de entrada seria:
    
    Matrix *lerMatrizDeArquivo(string nome_do_arquivo); 
    
    //Recebe um conjuntto de vectors de matrizes e escreve cada matriz em cada posição respectiva a cada vector
    //em um documento do tipo .txt
    void print_in_the_file(vector <Matrix*> mat, vector<Matrix*> soma, vector<Matrix*> File, vector<Matrix*> mult, vector<Matrix*> sub); 

};

#endif
