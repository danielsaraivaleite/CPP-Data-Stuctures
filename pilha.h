#ifndef PILHA_H
#define PILHA_H

#include <iostream.h>
#include <assert.h>

// DEFINIÇÃO DA CLASSE PILHA
template<class TEP>
class pilha
{
  protected:
  struct no;
  typedef no* pontno;
  struct no
   {
     TEP info;
     pontno lig;
   };

  pontno topo;

  public:
  pilha() {topo = 0;}  // construtor
  // Métodos
  void empilha(const TEP&);
  bool vazia() {return (topo==0);}
  bool desempilha(TEP&);
  bool ver_topo(TEP&);
};

// IMPLEMENTAÇÃO

template<class TEP>
void pilha<TEP>::empilha(const TEP &valor)
{
  pontno novono = new no;
  assert(novono);
  novono->info = valor;
  novono->lig = topo;
  topo = novono;
}

template<class TEP>
bool pilha<TEP>::desempilha(TEP &valor)
{
  if(!vazia())
   {
     valor = topo->info;
     pontno aux = topo;
     topo = topo->lig;
     delete aux;
     return true;
   }
  return false;
}

template<class TEP>
// retorna o valor do topo, mas sem desempilhá-lo.
bool pilha<TEP>::ver_topo(TEP &valor)
{
  if(!vazia())
   {
     valor = topo->info;
     return true;
   }
  return false;
}

#endif
