/***************************************************************************
*                          Daniel Saraiva Leite                            *
*   Esta classe vetor utiliza alocacao dinamica para armezanar vetores     *
*                          Novembro/2003                                   *
***************************************************************************/


#ifndef VETOR_H
#define VETOR_H

#include <iostream.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include <stdio.h>


template <class T> // gabarito de classe
class vetor
 {
   public:

     vetor(int = 0);  // construtor
     vetor (const vetor<T>&); //construtor por copia
     ~vetor();  // destrutor
     void definevetor(int); // funcao de construcao, destruicao e alocacao
     int pegatamanho(); // funcao acessora do no. de elementos
     // operador subscrito sobrecarregado
     T& operator[](int);

   private:
     int nposicoes;  // armazena tamanho do vetor
     T* arranjo; // ponteiro

 };

// IMPLEMENTACAO DAS FUNCOES ************************************************

    template <class T>
    vetor<T>::vetor(int colunas) : arranjo(0)  // construtor
        {
          definevetor(colunas); // chama funcao para alocacao
        }


    template <class T>
    vetor<T>::vetor (const vetor<T> &a ) : arranjo(0) //construtor por copia
        {
          definevetor(a.nposicoes); // define um novo arranjo
          for (int i=0; i<nposicoes; i++)
             {
               arranjo[i] = a.arranjo[i]; // copia elemento-a-elemento
             }
        }


    template <class T>
    vetor<T>::~vetor()  // destrutor
        {
          definevetor(0);       // chama funcao de desalocacao
        }


    template <class T>
    void vetor<T>::definevetor(int tamanho) // funcao de construcao, destrucao e alocacao
        {
          if (arranjo) // caso de arranjo ja alocado
             {
               delete[] arranjo; // desalocacao
             }
          if (tamanho>0)
             {
               arranjo = new T[tamanho];  // alocacao dinamica
               assert(arranjo!=0); // verifica problemas na alocacao
               for (int i=0; i<tamanho; i++) // inicia arranjo com zeros
                  {
                    arranjo[i] = 0;
                  }
             }
          else // caso de tamanho invalido
             {
               arranjo = NULL; // atribui NULL ao ponteiro
             }
          nposicoes = tamanho;  // salva o no. de elementos do vetor
        }


    template <class T>
    int vetor<T>::pegatamanho() // funcao acessora do no. de elementos
         {
           return nposicoes;
         }


    // operador subscrito sobrecarregado
    template <class T>
    T& vetor<T>::operator[](int coluna)
        {
          if(coluna<0||coluna>=nposicoes) //verifica se o indice e valido
            {
              cout<<"\n** Indice fora dos limites  ** "<<endl;
              getch(); // pausa
              exit(1); //forca o termino da execucao, com erro
            }
          return arranjo[coluna];
        }


#endif




