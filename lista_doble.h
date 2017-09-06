#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include "dato.h"
#include "lista_doble.h"
#include <string>
#include <fstream>

using namespace std;

using DatoSUI = Dato<string, unsigned int>;

#define nombre_archivo "enfermedades.txt"

template <class T>
class NodoD{
public:
	T dato;
	NodoD* next;
	NodoD* prev;
public:
	NodoD(): next(NULL), prev(NULL) {};
	NodoD(T dato): dato(dato) {};
};

template <class T>
class ListaD{
public:
	NodoD<T>* head;
	NodoD<T>* last;
public:
	ListaD(): head(NULL), last(NULL) {};
	~ListaD(){
		NodoD<T>* temp1 = head;
		NodoD<T>* temp2 = head;
		while(temp1 != NULL){
			temp2 = temp1->next;
			delete temp1;
			temp1 = temp2;
		}
	}

	void show(){
		NodoD<T>* temp = head;
		while(temp != NULL){
			temp->dato.show();
			cout << " -> ";
			temp = temp->next;
		}
		cout << "NULL" << '\n';
	}

	bool find(T dato, NodoD<T>* &pNodo){
		pNodo = head;		
		while( pNodo != NULL && ((pNodo->dato).comp(dato) < 0 ) ){
			pNodo = pNodo->next;
		}
		if( pNodo != NULL && ((pNodo->dato).comp(dato) == 0) ){
			return true;
		}
		return false;
	}

	void add_ordenado(T dato){
		NodoD<T>* pNodo;
		if(!find(dato, pNodo)){
			NodoD<T>* pNodo2 = new NodoD<T>(dato);
			pNodo2->next = pNodo;
			if(pNodo == NULL){
				if(head == NULL){
					head = pNodo2;
					last = pNodo2;
				}
				else{
					pNodo2 -> prev = last;
					last->next = pNodo2;
					last = pNodo2;
				}
			}else{
				if(pNodo == head){
					head->prev = pNodo2;
					head = pNodo2;
				}
				else{
					pNodo2->prev = pNodo->prev;
					pNodo->prev = pNodo2;
					pNodo2->prev->next = pNodo2;
				}
			}

		}
	}

	void del(T dato){
		NodoD<T>* pNodo;
		if(find(dato, pNodo)){
			if(pNodo != NULL){
				if(head == last){
					delete pNodo;
					head = NULL;
					last = NULL;
				}
				else{
					if(pNodo == head){					
						head = pNodo->next;
						head->prev = NULL;
						delete pNodo;
					}
					else{
						if(pNodo == last){
							last = pNodo->prev;
							last->next = NULL;
							delete pNodo;
						}		
						else{
							pNodo->prev->next = pNodo->next;
							pNodo->next->prev = pNodo->prev;
							delete pNodo;
						}
					}
				}
			}
		}
	}

	NodoD<T>* first(){
		return head;
	}

	NodoD<T>* lastt(){
		return last;
	}

	NodoD<T>* next(NodoD<T>* pNodo){
		return pNodo->next;
	}

	NodoD<T>* prev(NodoD<T>* pNodo){
		return pNodo->prev;
	}

	void indexar(){
		string nombre="";
		char c[1];
		unsigned int pos=0;
		bool flag = true;

		fstream arch; 
	    arch.open(nombre_archivo, fstream::in | fstream::out); 
	    arch.read(c,1);
	    pos++;
	    while(c[0] != '~'){    	    //lee mucho de disco, esta para corregir	
	    	while(c[0] != '#'){
	    		nombre += c[0];
	    		arch.read(c,1);
	    		pos++;
	    	}
	    	arch.read(c,1);
	    	pos++;    
	    	if(c[0] == '0')	
	    		flag = false;
	    	arch.read(c,1);
	    	pos++;
	    	if(flag){
				DatoSUI dato(nombre,pos);			
				add_ordenado(dato);
			}
			nombre = "";
			while(c[0] != '@'){
	    		arch.read(c,1);
	    		pos++;
	    	}
	    	arch.read(c,1);
	    	pos++;
	    	flag = true;
    	}
    	arch.close();
	}

	string leer_enfermedad(){
		string enfermedad = "Parkinson";
		string res="";
	    DatoSUI dato(enfermedad);
	    NodoD<DatoSUI>* pNodo = new NodoD<DatoSUI>(dato);
	    int poss;
	    if(find(dato,pNodo)){
	    	poss = pNodo->dato.pos;
	    }
	    fstream arch; 
	    arch.open(nombre_archivo, fstream::in | fstream::out); 
	    arch.seekg(fstream::beg+poss);
	    char c[1];
	    arch.read(c,1);
	    cout << "\nDescripción de " << enfermedad << '\n';
		while(c[0] != '#'){
			res += c;
			arch.read(c,1);
		}   
		arch.close();
		return res; 

	}

};


#endif