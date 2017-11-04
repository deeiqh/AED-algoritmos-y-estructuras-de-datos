#include <iostream>
#include "Doub_circ_list.h"
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <climits>

using namespace std;
using Colour = bool;
#define White false
#define Black true

template <class T>
class Fib_node{
public:
	Doub_circ_list_node<Fib_node>* parent = NULL;
	Doub_circ_list_node<Fib_node>* children = NULL;
	int degree = -1;
	Colour mark = White;
	T key;
public:
	Fib_node(){};
	Fib_node(T key):key(key){};
	~Fib_node(){};	
};

template <class T>
class Fib_heap{
public:
	Doub_circ_list_node<Fib_node<T>>* min = NULL;
	int n = 0;
public:
	
	Doub_circ_list_node<Fib_node<T>>* insert(T x)
	{
		Fib_node<T> f(x);
		Doub_circ_list_node<Fib_node<T>>* new_node = 
								new Doub_circ_list_node<Fib_node<T>>(f);
		add_node(min, new_node);
		if(min != NULL){
			if((new_node->data).key < (min->data).key){
				min = new_node;
			}
		}			
		n++;
		(new_node->data).degree = 0;
		new_node->data.parent = (min->data).parent;
		return new_node;
	}
	
	void extract_min()
	{
		if(min != NULL){
			if(min->next == min){//si hay solo 1 elemento
				kick_node(min);
				min = NULL;
				n--;
			} 
			else{
				//kick min & children to root
												
				Doub_circ_list_node<Fib_node<T>>* temp = min->next;
				kick_node(min);					
				n--;
				push_list_into_list(temp,(min->data).children);	
				min = temp;
				//merge
				vector<Doub_circ_list_node<Fib_node<T>>*> v(
									(1+static_cast<T>(ceil(log2(n)))));
				for(auto itv = v.begin();itv != v.end();itv++){
		        	*itv = NULL;
		    	}

				Doub_circ_list_node<Fib_node<T>>* it = NULL;
				Doub_circ_list_node<Fib_node<T>>* menor = NULL;
				Doub_circ_list_node<Fib_node<T>>* mayor = NULL;			

				it = min; 
				while(true){
					if(v[(it->data).degree] == NULL){
						v[(it->data).degree] = it;
					}
					else{
						//se detiene si el root que se está recorriendo es
						//es el mismo que el punero almacenado en el vector
						if(it == v[(it->data).degree]){
							break;
						}
						else{
							do{
								if((it->data).key < 
										(v[(it->data).degree]->data).key){
									menor = it;	
									mayor = v[(it->data).degree];
								}else{
									menor = v[(it->data).degree];	
									mayor = it;
								}
								v[(it->data).degree] = NULL;
								it = menor;
								(it->data).degree += 1;
								min = it;
								kick_node(mayor);
								
								mayor->data.parent = it; 
								add_node((it->data).children,mayor);
								
							}while(v[(it->data).degree] != NULL);
							
							v[(it->data).degree] = it;
						}
					}
					it = it->next;	
					min = it;			
				}
				//actualizamos el min			
				Doub_circ_list_node<Fib_node<T>>* n = min;
				Doub_circ_list_node<Fib_node<T>>* t = min;
				do{
					if((n->data).key < (min->data).key){
						min = n;
					}
					n = n->prev;
				}while(n != t && n != NULL);
			}
		}
		
	}
	
	void decrease_key(Doub_circ_list_node<Fib_node<T>>* node, T k)
	{
		Doub_circ_list_node<Fib_node<T>>* p;		
		node->data.key = k;
		p = node->data.parent;	
		if(p != NULL && (node->data.key < p->data.key)){
			//pasar a root, cortar
			tratamiento(node, p);
			cascada(p);
		}
		if(node->data.key < min->data.key){
			min = node;
		}		
	}
	
	void tratamiento(Doub_circ_list_node<Fib_node<T>>* node,
						Doub_circ_list_node<Fib_node<T>>* p){
		Doub_circ_list_node<Fib_node<T>>* temp = node->next;
		if(temp == node){
			temp = NULL;
		}else
			temp = node->next;
		kick_node(node);
		p->data.children = temp;
		p->data.degree--;
		node->data.parent = NULL;
		add_node(min,node);
		node->data.mark = White;
	}
	
	void cascada(Doub_circ_list_node<Fib_node<T>>* p){
		Doub_circ_list_node<Fib_node<T>>* pp;
		pp = p->data.parent;
		if(pp != NULL){
			if(p->data.mark == White){
				p->data.mark = Black;
			}
			else{
				tratamiento(p, pp);
				cascada(pp);
			}
		}
	}
	
	void delete_node(Doub_circ_list_node<Fib_node<T>>* node)
	{
		decrease_key(node,INT_MIN);
		extract_min();
	}
	
	void draw()
	{
		fstream arch;
		arch.open("fib_heap.dot", fstream::out);
		string cad("");
	
		arch << "graph fib_heap{\n\trankdir=TB\n\tstyle=invis\n\n";	
		arch << "\tsubgraph cluster_0{\n";
		arch << "\t\tmin[shape = none]\n";
		arch << "\t\tmin\n";
		arch <<	"\t}\n";
	
		arch << "\tsubgraph cluster_1{\n";
		arch << "\t\tedge [style=dashed]\n";
		arch <<	"\t\t{rank=same ";
		if(min != NULL){
			//imprimo root & inicializo el vector de padres
			Doub_circ_list_node<Fib_node<int>>* r_node = min;
			vector<Doub_circ_list_node<Fib_node<int>>*> v;
			do{
				if((r_node->data).children != NULL){
					v.push_back(r_node);				
				}
				arch << (r_node->data).key << ' ';
				cad = cad + to_string((r_node->data).key) + "--";
				r_node = r_node->next;
			}while(r_node != min);		
			arch << "}\n";
			cad.erase(cad.end()-2,cad.end());
			arch << "\t\t"+cad << '\n';
			arch << "\t}\n\n";		
			arch << "\tmin--"<<(min->data).key<<"[style=dotted]\n\n";
		
			//ya impreso root, imprimimos lo demás
			int i = 2;
			Doub_circ_list_node<Fib_node<int>>* a;
			Doub_circ_list_node<Fib_node<int>>* b;
			Doub_circ_list_node<Fib_node<int>>* r;
			Doub_circ_list_node<Fib_node<int>>* s;
			string str("");
			while(!v.empty()){
				//se imprimen los hijos y los enlaces
				arch << "\tsubgraph cluster_"<<i<<"{\n";
				arch << "\t\t{rank=same ";				
				a = v[0];
				if (a != NULL){
					r = a;
					do{
						b = (r->data).children;					
						s = b;
						if(b != NULL){					
							do{
								arch << (s->data).key << ' ';
								if((s->data).mark == Black){
									arch << "[style=filled fillcolor=black fontcolor=white] ";
								}
								str = str + to_string((r->data).key) +
										"--"+to_string((s->data).key)+' ';
								if((s->data).children != NULL){
									v.push_back(s);
								}
								s = s->next;
							}while(s != b);
							v.erase(v.begin());
						}
						r = r->next;					
					}while(r != a);
					arch << "}\n\t}\n\n\t" + str + "\n\n";
					str = "";
				}
				i++;
			}
			arch << "}\n";
		}
		else{
			arch << "}\n\t}\n\n";
			arch << "}\n";
		}
		arch.close();
	}

};
