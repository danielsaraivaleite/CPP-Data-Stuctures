/***************************************************************************
*                         Daniel Saraiva Leite                             *
*   A classe 'MATRIZ' armazena elementos numéricos, utilizando para isso   *
*   gabaritos.                                                             *
*                          Novembro/2003                                   *
***************************************************************************/


#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <fstream.h>
#include "vetor.h"


template <class T>
class matriz
 {
   public:
     matriz(int=0, int=0); // construtor

     ~matriz(); // destrutor

     matriz(const matriz&); // construtor por copia

     void definematriz(int, int); // funcao de alocacao e desalocacao

     int pegacolunas(); // acessa no. de colunas da matriz

     int pegalinhas();  // acessa no. de linhas da matriz

     vetor<T>& operator[](int); // operador de subscricao, para a linha

     void inicia(T=0); // inicia a matriz com um valor

     // Sobrecarga do operador de atribuicao
     matriz& operator=(const matriz &);  // atribuicao MATRIZ=MATRIZ
     const matriz& operator=(T);         // atribuicao MATRIZ=ESCALAR

    // Sobrecarga dos operadores de insercao e extracao
    friend ostream& operator<<(ostream&, const matriz&); // escrita
    friend istream& operator>>(istream&, matriz&);       // leitura


//// FUNCOES ARITMETICAS ------------------------------------------------

    // COM ESCALARES ----------------------------------------------------

    // SOMA
    const matriz operator+(const T&); // soma com escalar
    friend const matriz operator+(const T&, matriz &); // friend

    // SUBTRACAO
    const matriz operator-(const T&); // subtrai escalar
    friend const matriz operator-(const T&, matriz &); // friend

    // MULTIPLICACAO
    friend const matriz operator*(const T &, matriz &); // friend
    const matriz operator*(const T &); // multiplica por escalar


    // DIVISAO
    const matriz operator/(const T&); // divide por escalar

    // COM SOMENTE MATRIZES -----------------------------------------------

    // SOMA
    const matriz operator+(const matriz & );

    // SUBTRACAO
    const matriz operator-(const matriz & );

    // MULTIPLICACAO
    const matriz operator*(const matriz & );

    // MATRIZ OPOSTA - matriz dos sinais trocados
    friend const matriz operator -(matriz & );

    // MATRIZ TRANSPOSTA
    friend const matriz transposta(matriz& );

//// ---------------------------------------------------------------------

    // FUNCOES MATRIZ <operacao>= <MATRIZ ou ESCALAR>
    void operator+=(const matriz&); // recebe a soma com outra matriz
    void operator+=(const T&);   // recebe a soma com escalar
    void operator-=(const matriz&); // recebe a subtracao por outra matriz
    void operator-=(const T&);   // recebe a subtracao com escalar
    void operator*=(const matriz&); // recebe a multiplicao por outra matriz
    void operator*=(const T&);   // recebe a multiplicacao por escalar
    void operator/=(const T&);   // recebe a divisao dela por escalar

    // FUNCOES BOOLEANAS (igualdade e nao-igualdade)
    const bool operator==(const matriz &); // igualdade matriz==matriz
    const bool operator!=(const matriz &); // nao-igualdade matriz!=matriz
    const bool operator==(const T &); // igualdade matriz==escalar
    const bool operator!=(const T &); // nao-igualdade matriz==escalar

	// FUNCAO DE LEITURA A PARTIR DE ARQUIVO
	void leiturasequencial();
	void leiturasequencial(char*);



   private:
     int ncolunas, nlinhas;
     vetor<T>* Ptrmat; // "um ponteiro duplo"

 };


// IMPLEMENTACAO DAS FUNCOES ************************************************


   // CONSTRUTOR
   template <class T>
   matriz<T>::matriz(int linhas, int colunas) : Ptrmat(0)
     {
       definematriz(linhas, colunas);  // define a matriz especificada
     }


   // DESTRUTOR
   template <class T>
   matriz<T>::~matriz()
     {
       definematriz(0, 0);  // desaloca matriz
     }


   // CONSTRUTOR POR COPIA
   template <class T>
   matriz<T>::matriz(const matriz& a) : Ptrmat(0)
     {
       // define uma nova matriz de dimensoes apropriadas
       definematriz(a.nlinhas, a.ncolunas);
       for(int i =0; i<a.nlinhas; i++)
           {
             for(int j=0; j<a.ncolunas; j++)
                {
                  Ptrmat[i][j] = a.Ptrmat[i][j];
                }
           }
     }


   // FUNCAO DE DEFINICAO - realiza alocacao e desalocacao dinamica
   template <class T>
   void matriz<T>::definematriz(int linhas, int colunas)
     {
       if(linhas) delete[] Ptrmat;
       if(colunas>0&&linhas>0)
          {
            Ptrmat = new vetor<T>[linhas];
            for(int i=0; i<linhas; i++)
               {
                 Ptrmat[i].definevetor(colunas);
               }
          }
       else
          {  Ptrmat = 0;
             linhas = 0;
          }
       ncolunas = colunas;
       nlinhas = linhas;
     }


   // ACESSORA DO NUMERO DE COLUNAS
   template <class T>
   int matriz<T>::pegacolunas()
     {
       return ncolunas;
     }


   // ACESSORA DO NUMERO DE LINHAS
   template <class T>
   int matriz<T>::pegalinhas()
     {
       return nlinhas;
     }


   // SOBRECARGA DO OPERADOR DE SUBSCRICAO - []
   template <class T>
   /* O subscrito recebera a linha da matriz, que aponta para
      1ª. posicao do vetor de colunas                        */
   vetor<T>& matriz<T>::operator[](int linha)
     {
       assert(linha<nlinhas); // verifica se a linha e valida
       return Ptrmat[linha];
     }


   // INICIA - inicia a matriz com um valor
   template <class T>
   void matriz<T>::inicia(const T valor)
     {
       for(int i=0; i<nlinhas; i++)
          for(int j=0; j<ncolunas; j++)
             Ptrmat[i][j] = valor;
     }


   // SOBRECARGA DO OPERADOR DE ATRIBUICAO MATRIZ=MATRIZ
   template <class T>
   matriz<T>& matriz<T>::operator=(const matriz<T> &a)
     {
      if(&a!=this) // verifica auto-atribuicao
        {
         definematriz(a.nlinhas, a.ncolunas); // realoca a matriz da esquerda
         // atribuicao elemento-a-elemento
         for(int i =0; i<a.nlinhas; i++)
             {
               for(int j=0; j<a.ncolunas; j++)
                  {
                    /* O primeiro subscrito relaciona-se ao ponteiro Ptrmat(linha)
                     o segundo ao vetor de colunas                             */
                     Ptrmat[i][j] = a.Ptrmat[i][j];
                  }
             }
        }
      return *this;
     }


   // OPERADOR DE ATRIBUICAO MATRIZ=ESCALAR
   template <class T>
   const matriz<T>& matriz<T>::operator=(T valor)    // atribui MATRIZ=ESCALAR
     {
        inicia(valor);
        return *this;
     }


   // OPERADOR DE EXTRACAO SOBRECARREGADO - "escrita da matriz"
   // escreve uma matriz centralizada na tela
   template <class T>
   ostream& operator<<(ostream &escreva, const matriz<T> &a)
    {
      const int largnum = 3; // largura de cada numero
      int recuo = ( 80  - (a.ncolunas+2)*largnum)/2; // margem esquerda calculada
      // laco para varrer a matriz
      for(int i=0; i<a.nlinhas; i++)
         {
           // imprime bordas
           if(i==0) cout<<setw(recuo)<<"/";
           else
             {
               if(i==a.nlinhas-1) cout<<setw(recuo)<<"\\"; else cout<<setw(recuo)<<"|";
             }
           for(int j=0; j<a.ncolunas; j++)
              {
                cout<<setw(largnum)<<a.Ptrmat[i][j];
              }
           // imprime bordas
           if(i==0) cout<<setw(largnum)<<"\\"<<endl;
           else
             {
               if(i==a.nlinhas-1)
                  cout<<setw(largnum)<<"/"<<endl;
               else
                   cout<<setw(largnum)<<"|"<<endl;
             }
         }
      return escreva;
    }


   // OPERADOR DE INSERCAO SOBRECARREGADO - "leitura da matriz"
   template <class T>
   istream& operator>>(istream &leia, matriz<T> &a)
    {
      for(int i=0; i<a.nlinhas; i++)
         {
           for(int j=0; j<a.ncolunas; j++)
              {
                cout<<"M["<<i<<"]["<<j<<"]: ";  // escreve posicao do elemento
                cin>>a.Ptrmat[i][j]; // le um elemento
                cout<<endl;
              }
         }
      return leia;
    }


// FUNCOES ARITMETICAS ******************************************************

   // COM ESCALARES ---------------------------------------------------------

   // soma com escalar
   template <class T>
   const matriz<T> matriz<T>::operator+(const T& escalar)
      {
        matriz<T> resultado(nlinhas, ncolunas); //cria matriz auxiliar
        for(int i=0; i<nlinhas; i++)
           for(int j=0; j<ncolunas; j++)
              resultado[i][j] = escalar + Ptrmat[i][j];
        return resultado;
      }

     // soma com escalar (FRIEND)
     template <class T>
     const matriz<T> operator+(const T &valor, matriz<T> &a)
       {
         return a+valor;
       }


   // multiplica por escalar
   template <class T>
   const matriz<T> matriz<T>::operator*(const T& escalar)
      {
        matriz<T> resultado(nlinhas, ncolunas); //cria matriz auxiliar
        for(int i=0; i<nlinhas; i++)
           for(int j=0; j<ncolunas; j++)
              resultado[i][j] = escalar * Ptrmat[i][j];
        return resultado;
      }

     // multiplica por escalar (FRIEND)
     template <class T>
     const matriz<T> operator*(const T& valor, matriz<T> &a)
       {
         return a*valor;
       }


   // subtrai escalar
   template <class T>
   const matriz<T> matriz<T>::operator-(const T& escalar)
      {
        matriz<T> resultado(nlinhas, ncolunas); //cria matriz auxiliar
        for(int i=0; i<nlinhas; i++)
           for(int j=0; j<ncolunas; j++)
              resultado[i][j] = (-escalar) + Ptrmat[i][j];
        return resultado;
      }


     // subtrai escalar (FRIEND)
     template <class T>
     const matriz<T> operator-(const T &valor, matriz<T> &a)
       {
         return (-1)*a + valor;
       }


   // divide por escalar
   template <class T>
   const matriz<T> matriz<T>::operator/(const T& escalar)
      {
        if(escalar==0) // verifica o escalar
          { // imprime mensagem de erro e aborta execucao
            cout<<"ERRO de Logica. Tentativa de dividir por zero";
            getch();
            exit(1); //pausa
          }
        matriz<T> resultado(nlinhas, ncolunas); //cria matriz auxiliar
        for(int i=0; i<nlinhas; i++)
           for(int j=0; j<ncolunas; j++)
              resultado[i][j] = Ptrmat[i][j] / escalar;
        return resultado;
      }


   // COM SOMENTE MATRIZES--------------------------------------------------

   // SOMA
   template <class T>
   const matriz<T> matriz<T>::operator+(const matriz &a)
      {
        if(a.ncolunas!=ncolunas||a.nlinhas!=nlinhas) // verifica dimensoes
          { // imprime mensagem de erro e aborta execucao
            cout<<"ERRO de Logica. Tentativa de somar matrizes de dimensoes diferentes";
            getch();
            exit(1); //pausa
          }
        matriz<T> resultado(a.nlinhas, a.ncolunas);  // cria matriz auxiliar
        for(int i=0; i<nlinhas; i++)
           for(int j=0; j<ncolunas; j++)
              resultado[i][j] = Ptrmat[i][j] + a.Ptrmat[i][j];
        return resultado;
      }

      
   // SUBTRACAO
   template <class T>
   const matriz<T> matriz<T>::operator-(const matriz &a)
      {
        if(a.ncolunas!=ncolunas||a.nlinhas!=nlinhas) // verifica dimensoes
          { // imprime mensagem de erro e aborta execucao
            cout<<"ERRO de Logica. Tentativa de subtrair matrizes de dimensoes diferentes";
            getch();
            exit(1); //pausa
          }
        matriz<T> resultado(a.nlinhas, a.ncolunas);  // cria matriz auxiliar
        for(int i=0; i<nlinhas; i++)
           for(int j=0; j<ncolunas; j++)
              resultado[i][j] = Ptrmat[i][j] - a.Ptrmat[i][j];
        return resultado;
      }


   // MULTIPLICACAO
   template <class T>
   const matriz<T> matriz<T>::operator*(const matriz &a)
      {
        if(a.ncolunas!=ncolunas||a.nlinhas!=nlinhas) // verifica dimensoes
          { // imprime mensagem de erro e aborta execucao
            cout<<"ERRO de Logica. Tentativa de multiplicar matrizes de dimensoes incompativeis";
            getch();
            exit(1); //pausa
          }
        matriz<T> resultado(a.nlinhas, a.ncolunas);  // cria matriz auxiliar
			for(int j = 0; j < nlinhas; j++)  // multiplicacao
				for(int k = 0; k < a.ncolunas; k++)
					for(int l = 0; l < ncolunas; l++)
						resultado.Ptrmat[j][k] = Ptrmat[j][l] * a.Ptrmat[l][k] + resultado.Ptrmat[j][k];
        return resultado;
      }


   // MATRIZ OPOSTA - troca os sinais de cada elemento
   template <class T>
   const matriz<T> operator-(matriz<T> &a)
      {
        return (-1)*a;
      }


   // MATRIZ TRANSPOSTA
   template <class T>
   const matriz<T> transposta(matriz<T> &a)
      {
        matriz<T> resultado(a.ncolunas, a.nlinhas);  // cria matriz auxiliar
        for(int i=0; i<resultado.nlinhas; i++)
           for(int j=0; j<resultado.ncolunas; j++)
              resultado[i][j] = a[j][i];           // copia termos invertidos

        return resultado;
      }

//// *************************************************************************


//// FUNCOES MATRIZ <operacao>= <MATRIZ ou ESCALAR> *************************

   // SOMENTE ENVOLVENDO MATRIZES ------------------------------------------

   //SOMA
   template <class T>
   void matriz<T>::operator+=(const matriz &a)
      {
        *this = *this + a;
      }

   //SUBTRACAO
   template <class T>
   void matriz<T>::operator-=(const matriz &a)
      {
        *this = *this - a;
      }

   // MULTIPLICACAO
   template <class T>
   void matriz<T>::operator*=(const matriz &a)
      {
        *this = *this * a;
      }

   // ENVOLVENDO ESCALARES -------------------------------------------------

   // SOMA
   template <class T>
   void matriz<T>::operator+=(const T& escalar)
      {
        *this  =  *this + escalar;
      }

   // SUBTRACAO
   template <class T>
   void matriz<T>::operator-=(const T& escalar)
      {
        *this = *this - escalar;
      }

   // MULTIPLICACAO
   template <class T>
   void matriz<T>::operator*=(const T& escalar)
      {
        *this = *this * escalar;
      }

   // DIVISAO
   template <class T>
   void matriz<T>::operator/=(const T& escalar)
      {
        *this = *this / escalar;
      }


   // FUNCOES BOOLEANAS
    template <class T>
    const bool matriz<T>::operator==(const matriz &a) // igualdade matriz==matriz
      {
        if(a.ncolunas!=ncolunas||a.nlinhas!=nlinhas) return 0; // analise das dimensoes
        for(int i=0; i<nlinhas; i++)
           {
             for(int j=0; j<ncolunas; j++)
                {
                  if(Ptrmat[i][j]!=a.Ptrmat[i][j]) return 0;
                }
           }
        return 1;
      }

    template <class T>
    const bool matriz<T>::operator!=(const matriz &a) // nao-igualdade matriz!=matriz
      {
        if(a.ncolunas!=ncolunas||a.nlinhas!=nlinhas) return 1; // analise das dimensoes
        for(int i=0; i<nlinhas; i++)
           {
             for(int j=0; j<ncolunas; j++)
                {
                  if(Ptrmat[i][j]!=a.Ptrmat[i][j]) return 1;
                }
           }
        return 0;
      }

    template <class T>
    const bool matriz<T>::operator==(const T &escalar) // igualdade matriz==escalar
      {
        for(int i=0; i<nlinhas; i++)
           {
             for(int j=0; j<ncolunas; j++)
                {
                  if(Ptrmat[i][j]!=escalar) return 0;
                }
           }
        return 1;
      }

    template <class T>
    const bool matriz<T>::operator!=(const T &escalar) // nao-igualdade matriz==escalar
      {
        for(int i=0; i<nlinhas; i++)
           {
             for(int j=0; j<ncolunas; j++)
                {
                  if(Ptrmat[i][j]!=escalar) return 1;
                }
           }
        return 0;
      }

	// FUNCOES DE LEITURA A PARTIR DE ARQUIVO
	template <class T>
	void matriz<T>::leiturasequencial() // sem paremetros, solicita entrada
	// le a partir de arquivo sequencial nao-formatado
	{   char arquivo[21]; //define uma string
		cout<<"\n Digite o nome do arquivo (max = 20 car. ): ";
		cin>>arquivo; // pede o nome do arquivo
		ifstream lemat(arquivo, ios::in); // define o objeto da classa ifstream
		if(!lemat) // verifica se o arquivo foi aberto
		{
			cerr<<" Arquivo nao pode ser aberto ";
			exit(1);
		}
		for(int i=0; i<nlinhas; i++) // le a matriz
			for(int j=0; j<ncolunas; j++)
				lemat>>Ptrmat[i][j];
		lemat.close(); // fecha o arquivo
	}


	template <class T>
	void matriz<T>::leiturasequencial(char* arquivo) // com parametro
	// le a partir de arquivo sequencial nao-formatado
	{   
		ifstream lemat(arquivo, ios::in); // define o objeto da classa ifstream
		if(!lemat) // verifica se o arquivo foi aberto
		{
			cerr<<" Arquivo nao pode ser aberto ";
			exit(1);
		}
		for(int i=0; i<nlinhas; i++) // le a matriz
			for(int j=0; j<ncolunas; j++)
				lemat>>Ptrmat[i][j];
		lemat.close(); // fecha o arquivo
	}



#endif










