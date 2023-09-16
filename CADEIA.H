// cadeia.h - autor Daniel Saraiva Leite

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#ifndef cadeia_h
#define cadeia_h

class cadeia
{
// *************************** DADOS PROTEGIDOS *****************************
protected:
	char *cad;
	int tamanho;
// **************************************************************************

// ************************** MÉTODOS PÚBLICOS  *****************************
public:

	// construtores
	cadeia(char *s="");
	cadeia(char);   
	cadeia (const cadeia& ); // construtor por cópia
	
	//destrutor
	~cadeia(void);
	
	// operador de atribuição
	cadeia& operator=(const cadeia&); //cadeia=cadeia
	cadeia& operator=(char* ); // cadeia=string em C++
	
	// operadores relacionais
	bool operator==(const cadeia&) const; // cadeia=cadeia
	bool operator==(char*) const; // cadeia=string em C++
	friend bool operator==(char*, const cadeia&); //string em C++=cadeia
	bool operator!=(const cadeia&) const; // cadeia!=cadeia
	bool operator!=(char*) const; // cadeia!=string em C++
	friend bool operator!=(char*, const cadeia&); //string em C++=cadeia
	bool operator<(const cadeia&) const; // cadeia<cadeia
	bool operator<(char*) const; // cadeia<string em C++
	friend bool operator<(char*, const cadeia&); //string em C++<cadeia
	bool operator<=(const cadeia&) const; // cadeia<=cadeia
	bool operator<=(char*) const; // cadeia<=string em C++
	friend bool operator<=(char*, const cadeia&); //string em C++<=cadeia
	bool operator>(const cadeia&) const; // cadeia>cadeia
	bool operator>(char*) const; // cadeia>string em C++
	friend bool operator>(char*, const cadeia&); //string em C++>cadeia
	bool operator>=(const cadeia&) const; // cadeia>=cadeia
	bool operator>=(char*) const; // cadeia>=string em C++
	friend bool operator>=(char*, const cadeia&); //string em C++>=cadeia
	
	// operadores de concatenação
	cadeia operator+ (const cadeia&) const; //cadeia+cadeia
	cadeia operator+(char* )const; //cadeia+string em C++
	friend cadeia operator+(const char* , const cadeia&); //string + cadeia
	void operator+=(const cadeia&) ; //cadeia+=cadeia
	void operator+=(char* ); //cadeia+=string em C++
	
	// manipulação de cadeia
	int procura(char c , int inicio) const; // procura o caractere c a partir de inicio
	int encontra_ultima( char c) const; // encontra a ultima ocorrência de c
	cadeia subcadeia(int indice, int cont) const; // extrai uma subcadeia
	void insere(const cadeia& c, int indice ); //insere uma cadeia em outra
	void insere(char* c, int indice ); //insere uma string em uma cadeia
	void remove(int indice, int cont); // deleta uma subcadeia
	
	// indexação de cadeia
	char& operator[] (int n);
	
	// converte uma cadeia em uma string em C++
	operator char* (void) const;
	
	// E/S
	friend ostream& operator<<(ostream& , cadeia& );
	friend istream& operator>>(istream& , cadeia& );
	int lecadeia(istream& e=cin, char delimitador='\n'); // lê Caracteres até o delimitador
	// metodos adicionais
	int pega_tamanho( ) const {return (tamanho-1);}
	bool vazia( ) const { return (tamanho==1);}
	void limpa( void);
};

cadeia::cadeia(char *s)
{
	tamanho = strlen(s) +1; // inclui o \0
	cad = new char [tamanho]; // aloca espaço
	assert(cad);
	strcpy(cad,s);
}

cadeia::cadeia(char c)
{
  cad = new char[2];
  assert(cad);
  cad[0] = c;
  cad[1] = '\0';
  tamanho = 2;
}

cadeia::cadeia (const cadeia& s )
{	tamanho = s.tamanho;
	cad = new char [s.tamanho];
	assert (cad);
	strcpy(cad, s.cad);
}

//destrutor
cadeia::~cadeia(void)
{	delete[ ]cad; }

//cadeia=cadeia
cadeia& cadeia::operator=(const cadeia& s)
{	if (s.tamanho!= tamanho) // se os tamanhos são diferentes realoca
	{	delete[ ] cad;
		cad= new char [s.tamanho];
		assert(cad);
		tamanho = s.tamanho;
	}
	strcpy(cad, s.cad);
	return *this;
}

// cadeia=string em C++
cadeia& cadeia::operator=(char* s )
{	if ((strlen(s)+1)!=tamanho)
	{	delete[ ] cad;
		tamanho = strlen(s)+1;
		cad= new char [tamanho];
		assert(cad);
	}
	strcpy(cad,s);
	return *this;
}

// operadores relacionais
bool cadeia::operator==(const cadeia& c) const // cadeia=cadeia
{ return strcmp(cad,c.cad)==0;}

bool cadeia::operator==(char* c) const // cadeia=string em C++
{ return strcmp(cad,c) == 0; }

bool operator==(char* s, const cadeia& c) //string em C++=cadeia
{ return strcmp(s,c.cad) == 0; }

bool cadeia::operator!=(const cadeia& c) const // cadeia!=cadeia
{ return strcmp(cad,c.cad) != 0; }

bool cadeia::operator!=(char* c) const // cadeia!=string em C++
{ return strcmp(cad,c) != 0; }

bool operator!=(char* s, const cadeia& c) //string em C++=cadeia
{ return strcmp(s,c.cad)!= 0; }

bool cadeia::operator<(const cadeia& c) const // cadeia<cadeia
{ return strcmp(cad,c.cad) < 0; }

bool cadeia::operator<(char* c) const // cadeia<string em C++
{ return strcmp(cad,c) < 0; }

bool operator<(char* s, const cadeia& c) //string em C++<cadeia
{ return strcmp(s,c.cad) < 0; }

bool cadeia::operator<=(const cadeia& c) const // cadeia<=cadeia
{ return strcmp(cad,c.cad) <= 0; }

bool cadeia::operator<=(char* c) const // cadeia<=string em C++
{ return strcmp(cad,c) <= 0; }

bool operator<=(char* s, const cadeia& c) //string em C++<=cadeia
{ return strcmp(s,c.cad) <= 0; }

bool cadeia::operator>(const cadeia& c) const // cadeia>cadeia
{ return strcmp(cad,c.cad) > 0; }

bool cadeia::operator>(char* c) const // cadeia>string em C++
{ return strcmp(cad,c) > 0; }

bool operator>(char* s, const cadeia& c) //string em C++>cadeia
{ return strcmp(s,c.cad) > 0; }

bool cadeia::operator>=(const cadeia& c) const // cadeia>=cadeia
{ return strcmp(cad,c.cad) >= 0; }

bool cadeia::operator>=(char* c) const // cadeia>=string em C++
{ return strcmp(cad,c) >= 0; }

bool operator>=(char* s, const cadeia& c) //string C++>=cadeia
{ return strcmp(s,c) >= 0; }

// operadores de concatenação
//cadeia+cadeia
cadeia cadeia::operator+ (const cadeia& c) const
{	cadeia temp;
	int tam;
	delete[ ] temp.cad ;
	tam = tamanho + c.tamanho -1 ; // somente 1: \0
	temp.cad = new char [tam];
	assert(temp.cad);
	temp.tamanho = tam;
	strcpy(temp.cad,cad);
	strcat(temp.cad,c.cad);
	return temp;
}

//cadeia+string em C++
cadeia cadeia::operator+(char* c)const
{	cadeia temp;
	int tam;
	delete [] temp.cad;
	tam = tamanho + strlen(c);
	temp.cad = new char [tam];
	assert(temp.cad);
	temp.tamanho = tam;
	strcpy(temp.cad,cad);
	strcat(temp.cad, c);
	return temp;
}

//string em C++ + cadeia
cadeia operator+(const char* s , const cadeia& c)
{	cadeia temp;
	int tam;
	delete [] temp.cad;
	tam = strlen(s) + c.tamanho;
	temp.cad = new char [tam];
	assert(temp.cad);
	temp.tamanho = tam;
	strcpy(temp.cad,s);
	strcat(temp.cad, c.cad);
	return temp;
}

//cadeia+=cadeia
void cadeia::operator+=(const cadeia& c)
{	char *temp;
	int tam = tamanho + c.tamanho - 1;
	temp = new char [tam];
	assert(temp);
	strcpy(temp,cad);
	strcat(temp, c.cad);
	delete [] cad;
	cad = temp;
	tamanho = tam;
}

//cadeia+=string em C++
void cadeia::operator+=(char* c)
{	int tam;
	char *temp;
	tam = tamanho + strlen(c);
	temp = new char [tam];
	assert(temp);
	strcpy(temp,cad);
	strcat(temp, c);
	delete [] cad;
	cad = temp;
	tamanho = tam;
}

// manipulação de cadeia
// procura o caractere c a partir de inicio
int cadeia::procura(char c , int inicio) const
{	int retorno;
	char *p;
	p = strchr(&cad[inicio],c);
	if (p != 0)
		retorno = int(p-cad);
	else
		retorno = -1;
	return retorno;
}

// encontra a ultima ocorrência de c
int cadeia::encontra_ultima( char c) const
{	int retorno;
	char *p;
	p = strrchr(cad,c);
	if (p != 0)
		retorno = int(p-cad); // calcula o índice
	else
		retorno = -1;
	return retorno;
}

// extrai uma subcadeia
cadeia cadeia::subcadeia(int indice, int cont) const
{	int charesq = tamanho-indice-1,i; // numero de caracteres de indice ate o fim da cadeia
	cadeia temp; // constrói a subcadeia em temp
	char *p, *q;
	if (indice >= tamanho-1) // retorna cadeia nula se o indice for muito grande
		return temp; // temp é 0
	if (cont > charesq)
		cont = charesq;
	delete [] temp.cad; // deleta a cadeia nula criada na declaração de temp
	temp.cad = new char [cont+1]; // aloca memória para a subcadeia
	assert(temp.cad);
	for(i=0,p=temp.cad,q=&cad[indice];i < cont;i++)
		*p++ = *q++; // copia contadores de caracteres de cad para temp.cad
	*p = 0; // coloca final de cadeia
	temp.tamanho = cont+1;
	return temp;
}

//insere uma cadeia em outra
void cadeia::insere(const cadeia& c, int indice )
{	int novotamanho, tamanho_c = c.tamanho-1, i;
	char *novacadeia, *p, *q;
	novotamanho = tamanho + tamanho_c;
	novacadeia = new char [novotamanho];
	assert(novacadeia);
	for(i=0,p = novacadeia, q = cad;i <= indice-1;i++)
		*p++ = *q++;
	strcpy(p,c.cad);
	p += tamanho_c;
	strcpy(p,&cad[indice]);
	delete [] cad; // delete cadeia antiga
	tamanho = novotamanho; // novo tamanho da cadeia
	cad = novacadeia; // novo ponteiro para cadeia
}

//insere uma string C++ em uma cadeia
void cadeia::insere(char* c, int indice )
{	int novotamanho, tamanho_c = strlen(c), i;
	char *novacadeia, *p, *q;
	novotamanho = tamanho + tamanho_c;
	novacadeia = new char [novotamanho];
	assert(novacadeia);
	for(i=0,p = novacadeia, q = cad;i <= indice-1;i++)
		*p++ = *q++;
	strcpy(p,c);
	p += tamanho_c;
	strcpy(p,&cad[indice]);
	delete [] cad; // deleta a cadeia antiga
	tamanho = novotamanho; // novo tamanho para cadeia
	cad = novacadeia; // novo ponteiro para cadeia
}

// deleta uma subcadeia
void cadeia::remove(int indice, int cont)
{	int charesq = tamanho-indice-1, novotamanho, i;
	char *novacadeia, *p, *q;
	if (indice >= tamanho-1)
		return; // retorna se o índice for muito grande
	if (cont > charesq) // se cont > caracteres remanescentes, use esses caracteres
		cont = charesq;
	novotamanho = tamanho - cont;
	novacadeia = new char [novotamanho];
	assert(novacadeia);
	for(i=0,p=novacadeia,q=cad;i <= indice-1;i++)
       *p++ = *q++;
	q += cont;
	strcpy(p,q);
	delete [] cad;
	tamanho = novotamanho;
	cad = novacadeia;
}

// indexação de cadeia
char& cadeia::operator[ ] (int n)
{	if (n <0 || n >= tamanho-1)
	{	
		cout<<"Erro no indice da cadeia.";
      assert(0);
		exit(1);
	}
	return cad[n];
}

// converte uma cadeia em uma string em C++
cadeia::operator char* (void) const
{ return cad; }

// E/S
istream& operator>>(istream& e, cadeia& c)
{	char temp[256];
	if (e >> temp) // eof
	{	delete [] c.cad; // delete cad existente
		c.tamanho = strlen(temp) + 1;
		c.cad = new char [c.tamanho];
		assert(c.cad);
		strcpy(c.cad,temp);
	}
	return e;
}

ostream& operator<<(ostream& s, cadeia& c)
{ 
	s << c.cad;
	return s;
}

// lê caracteres até o delimitador
int cadeia::lecadeia(istream& e,char delimitador)
{	char temp[256]; // lê linha em temp
	// se não achar eof, lê uma linha de até 255 caracteres
	if (e.getline(temp, 256, delimitador))
	{	delete [] cad;
		tamanho = strlen(temp) + 1;
		cad = new char [tamanho];
		assert(cad);
		strcpy(cad,temp);
		return tamanho-1;
	}
	else
		return -1; // return -1 no fim de arquivo
}

// metodos adicionais
void cadeia::limpa( void)
{ 
	delete [ ] cad;
	tamanho = 1;
	cad = new char [tamanho];
	assert(cad);
	cad[0] = 0;
}

#endif
