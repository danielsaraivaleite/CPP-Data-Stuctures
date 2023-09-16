/***************************************************************************
*                          Daniel Saraiva Leite                            *
*                            Lista ordernada                               *
*                          Novembro/2003                                   *
***************************************************************************/

#ifndef LISTA_ORD_H
#define LISTA_ORD_H
#include "iostream.h"
#include "assert.h"

// LISTA_ORD.H
struct no;
     typedef no* pontno; // definicao do tipo pontno
template <class TEL>
class lista_ord
 {
   // ************************* DADOS PROTEGIDOS ***************************
   protected:            // preve uma possivel herança
     struct no;          // define a struct no
     typedef no* pontno; // definicao do tipo pontno
     struct no
      {
        TEL info;        // campo de informação
        pontno lig;      // Ligação com o próximo
      };
     pontno inicio;            // guarda quem é o primeiro (ponteiro)
     pontno fim;               // guarda o último elemento (ponteiro)
     pontno posicao_corrente;  // mantem um ponteiro para o elem. corrente
   // ***********************************************************************

   public:
    // Construtor
    lista_ord();
   // ************************** MÉTODOS ***********************************
     void insere(const TEL&);         // Inserção ascendente
     void moveinicio();               // Move para o Início
     bool moveproximo();              // Move para o Fim
     bool primeiro(TEL&);             // FindFirst
     bool proximo(TEL&);              // FindNext
     TEL& pegacorrente();             // Pega a posição corrente
     bool vazia();                    // Verifica se a lista está vazia
     bool eliminar(const TEL&);       // Elimina um nó
     bool encontrar(const TEL&);      // Retorna verdadeiro encontrá-lo
     int tamanho();                   // Retorna o tamanho da lista
   // **********************************************************************

 };


// construtor
template <class TEL>
lista_ord<TEL>::lista_ord()
 {
   inicio = posicao_corrente = fim = 0;
 }

// verifica se a lista está vazia
template <class TEL>
bool lista_ord<TEL>::vazia()
 {
   if(inicio==0) return true;
   return false;
 }

// Insere um elemento em ordem ascendente
template <class TEL>
void lista_ord<TEL>::insere(const TEL &valor)
// realiza a insercao em ordem crescente
 {
   pontno novono = new no;  // aloca um novono
   assert(novono);          // verifica alocacao
   novono->info = valor;    // insercao
   if(vazia())
    {
      novono->lig=0;
      inicio=novono;
      fim=novono;
    }
   else
    {
      // procurando ponto de insercao
      if((inicio->info)>valor) // no inicio
       {
         novono->lig=inicio;
         inicio = novono;
       }
      else
       {
         if((fim->info)<valor) // no final
          {
            novono->lig=0;
            fim->lig=novono;
            fim = novono;
          }
         else // insercao no meio da lista
          {
            pontno aux = inicio;
            while(aux->lig->info<valor)
             {
               aux = aux->lig;
             }
            novono->lig=aux->lig;
            aux->lig = novono;
          }
       }
    }
 }


// retorna o tamanho da lista
template <class TEL>
int lista_ord<TEL>::tamanho()
 {
   if(vazia()) return 0;
   int cont = 1;
   pontno aux = inicio;
   while(aux->lig!=0)
    {
      aux = aux->lig;
      cont++;
    }
   return cont;
 }

// encontra o valor
template <class TEL>
bool lista_ord<TEL>::encontrar(const TEL &valor)
 {
   if( vazia() ) return false;;
   pontno aux = inicio;
   while( aux!=0 && aux->info!=valor )
    {
      aux = aux->lig;
    }
   if(aux!=0) return true; 
   else return false;
 }

// retorna a posicao corrente
// ou seja, o conteudo da posicao
template <class TEL>
TEL& lista_ord<TEL>::pegacorrente()
 {
   return posicao_corrente->info;
 }


// retorna o primeiro
template <class TEL>
bool lista_ord<TEL>::primeiro(TEL &valor)
 {
   if(vazia()) return false;
   posicao_corrente = inicio;
   valor = posicao_corrente->info;
   return true;
 }


// retorna o proximo
template <class TEL>
bool lista_ord<TEL>::proximo(TEL &valor)
 {
   assert(posicao_corrente);
   if(posicao_corrente->lig==0) return false;
   posicao_corrente = posicao_corrente->lig;
   valor = posicao_corrente->info;
   return true;
 }

// move para o inicio
template <class TEL>
void lista_ord<TEL>::moveinicio()
 {
   posicao_corrente = inicio;
 }


// move para a proxima posicao
template <class TEL>
bool lista_ord<TEL>::moveproximo()
 {
   if(posicao_corrente==fim) return false;
   posicao_corrente = posicao_corrente->lig;
   return true;
 }


// elimina o valor da lista
template <class TEL>
bool lista_ord<TEL>::eliminar(const TEL &valor)
 {
   if(vazia()) return false;   // lista vazia
   if(inicio->info==valor)     // se estiver na primeira posicao
    {
      pontno aux = inicio;
      inicio = inicio->lig;
      delete aux;

      return true;
    }
   else    // em outras posicoes
    {
      pontno aux = inicio;
      while ( aux!=0 && aux->lig!=0 && aux->lig->info!=valor)
       {
         aux = aux->lig;
       }
      if(aux==0) return false;
      pontno noeliminar = aux->lig;
      aux->lig = noeliminar->lig;
      if(noeliminar==fim) fim=aux;
      delete noeliminar;
    
      return true;
    }
}


#endif

