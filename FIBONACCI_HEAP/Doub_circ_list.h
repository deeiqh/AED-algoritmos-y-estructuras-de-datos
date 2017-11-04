#ifndef DOUB_CIRC_LIST
#define DOUB_CIRC_LIST

#include<iostream>
using namespace std;

template<class T>
class Doub_circ_list_node{
public:
    T data;
    Doub_circ_list_node* next = NULL;
    Doub_circ_list_node* prev = NULL;
public:
    Doub_circ_list_node(){};
    Doub_circ_list_node(T data):data(data){};
    ~Doub_circ_list_node(){};
};

template<class T>
void kick_node(Doub_circ_list_node<T> *node)
{	
	if(node != NULL){
		if( node->prev == node){//si solo hay un nodo en la lista
		}
		else{
			// los inmediatos se abren & se señalan
			node->prev->next = node->next;
			node->next->prev = node->prev;      
		}
		//puntero de node a NULL(solo es nodo, no es lista)
		node->next = NULL;
		node->prev = NULL;  
		
	}
}

template<class T>
void add_node(Doub_circ_list_node<T>* &punto,
			      Doub_circ_list_node<T>* node)
{
	//por compatibilidad con cormen se añade todo a la prev del punto.
	//se abre el punto y el de su prev & señalan a node
	if(node != NULL){
		if(punto == NULL){
			node->prev = node;
			node->next = node;
			punto = node;
		}
		else{  
			Doub_circ_list_node<T>* izquierdo = punto->prev;			
			punto->prev = node;
			izquierdo->next = node;
			//node se pone al dia
			node->next = punto;
			node->prev = izquierdo; 		
		} 	
	}
}	

template<class T>
//devuelce la primera lista, aunque ambas seran iguales
void push_list_into_list(
								Doub_circ_list_node<T>* &node_l,
								Doub_circ_list_node<T>* node_c)
{
	if(node_c != NULL && node_l != NULL){
		//romper un puntero de ambas listas & fusionarlos
		Doub_circ_list_node<T>* next_c = node_c->next;
		Doub_circ_list_node<T>* prev_l = node_l->prev;
	
		node_l->prev = node_c;		
		node_c->next = node_l;
	
		prev_l->next = next_c;
		next_c->prev = prev_l;
	}
	else{
		if(node_l == NULL){				
			node_c->next = node_c;
			node_c->prev = node_c;
			node_l = node_c;
		}
	}
}

template<class T>
void imprimir(Doub_circ_list_node<T>* node)
{
	if(node != NULL){
		Doub_circ_list_node<T>* n = node;
		do{
			//cout << node->data << ' ';
			cout << node->data.key << ' ';
			node = node->prev;
		}while(node != n && node != NULL);
		cout << '\n';
	}
	else
		cout << "NULL\n";
}
    

#endif
