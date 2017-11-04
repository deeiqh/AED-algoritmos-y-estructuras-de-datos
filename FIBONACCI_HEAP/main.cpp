#include <iostream>
#include "Doub_circ_list.h"
#include "Fib_heap.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	Fib_heap<int> fib_heap;
		
	fib_heap.insert(23);	
	fib_heap.insert(7);
	Doub_circ_list_node<Fib_node<int>>* node = fib_heap.insert(21);
	fib_heap.insert(3);
	fib_heap.insert(17);
	fib_heap.insert(24);
	
	fib_heap.extract_min();
	
	fib_heap.decrease_key(node, 5);
	
	fib_heap.delete_node(node);
	
	fib_heap.draw();
	/*
		Fib_heap<int> fib_heap;
	map< pair< int,Doub_circ_list_node<Fib_node<int>>* >> map;
	Doub_circ_list_node<Fib_node<int>>* n;
	pair<int,Doub_circ_list_node<Fib_node<int>>*> par;
	int key,a,b;

	int opcion;
	do{
		cout << "Fibonacci heaps:\n\n";
		cout << "0) Dibujar heap.\n";
		cout << "1) Insertar nodo.\n";
		cout << "2) Extraer mínimo.\n";
		cout << "3) Decrease key.\n";
		cout << "4) Delete node.\n";
		cout << "Elija...\n\n";
		
		cin >> opcion;
		
		switch opcion{
			case 0:
				fib_heap.draw();
				cout << "Dibujado.\n";
				break;
			case 1:
				cout << "Valor de key: ";
				cin << key;
				while(map.find(key != map.end())){					
					n = fib_heap.insert(key);
					par = (key,n);
					map.insert(par);
				}
				cout << "Insertado.\n";
				break;
			case 2:
				n = fib_heap.extract_min();
				cout << "Valor mínimo: "<< n->data.key << " \n";
				map.erase(n->data.key);
				break;
			case 3:
				cout << "Valor del nodo a decrecer: ";
				cin << a;
				cout << "Valor nuevo, menor: ";
				cin << b;
				fib_heap.decrease_key(map[a],b);
				cout << "LLave decrementada.\n";
				break;
			case 4:
				cout << "Valor del nodo a eliminar: ";
				cin << a;
				fib_heap.delete_node(map[a]);
				break;
		}
		
	}while()
	*/
	
	return 0;
}

	/*
	Fib_node<int> f1(1);
	Doub_circ_list_node<Fib_node<int>> node1(f1);
	Fib_node<int> f2(2);
	Doub_circ_list_node<Fib_node<int>> node2(f2);
	Fib_node<int> f3(3);
	Doub_circ_list_node<Fib_node<int>> node3(f3);
	Fib_node<int> f4(4);
	Doub_circ_list_node<Fib_node<int>> node4(f4);
	Fib_node<int> f5(5);
	Doub_circ_list_node<Fib_node<int>> node5(f5);
	Fib_node<int> f6(6);
	Doub_circ_list_node<Fib_node<int>> node6(f6);
	Fib_node<int> f7(7);
	Doub_circ_list_node<Fib_node<int>> node7(f7);
	Fib_node<int> f8(8);
	Doub_circ_list_node<Fib_node<int>> node8(f8);
	Fib_node<int> f9(9);
	Doub_circ_list_node<Fib_node<int>> node9(f9);
	Fib_node<int> f10(10);
	Doub_circ_list_node<Fib_node<int>> node10(f10);
	Fib_node<int> f11(11);
	Doub_circ_list_node<Fib_node<int>> node11(f11);
	Fib_node<int> f12(12);
	Doub_circ_list_node<Fib_node<int>> node12(f12);
	Fib_node<int> f13(13);
	Doub_circ_list_node<Fib_node<int>> node13(f13);
	
	
	Doub_circ_list<Fib_node<int>> list1;
	Doub_circ_list<Fib_node<int>> list2;
	Doub_circ_list<Fib_node<int>> list3;
	Doub_circ_list<Fib_node<int>> list4;
	Doub_circ_list<Fib_node<int>> list5;
	Doub_circ_list<Fib_node<int>> list6;
	
	list1.add_node(list1.fantasma, &node1);
	list1.add_node(list1.fantasma, &node2);
	list1.add_node(list1.fantasma, &node3);
	list1.add_node(list1.fantasma, &node4);
	
	list2.add_node(list2.fantasma, &node5);
	list2.add_node(list2.fantasma, &node6);
	
	list3.add_node(list3.fantasma, &node7);
	
	list4.add_node(list4.fantasma, &node8);
	list4.add_node(list4.fantasma, &node9);
	list4.add_node(list4.fantasma, &node10);
	
	list5.add_node(list5.fantasma, &node11);
	list5.add_node(list5.fantasma, &node12);
	
	list6.add_node(list6.fantasma, &node13);
	
	list1.imprimir(list1.fantasma);
	list2.imprimir(list2.fantasma);
	list3.imprimir(list3.fantasma);
	list4.imprimir(list4.fantasma);
	list5.imprimir(list5.fantasma);
	list6.imprimir(list6.fantasma);
	
	Doub_circ_list_node<Fib_node<int>> *min = &node3;
	Doub_circ_list<Fib_node<int>> roots = list1;
	
	node3.data.children = &node5;
	node4.data.children = &node7;
	node5.data.parent = &node3;
	node5.data.children = &node8;
	node6.data.parent = &node3;	
	node7.data.parent = &node4;
	node7.data.children = &node11;
	node8.data.parent = &node5;
	node9.data.parent = &node5;
	node10.data.parent = &node5;
	node11.data.parent = &node7;
	node12.data.parent = &node7;
	node12.data.children = &node13;
	node13.data.parent = &node12;	
	
	Fib_heap<int> fib_heap;	
	fib_heap.min = &node3;
	fib_heap.roots = list1;
	fib_heap.n = 13;
	
		
	fib_heap.extract_min();
	
	fib_heap.draw();
	
	*/
/*
void draw(
		Doub_circ_list_node<Fib_node<int>>* min,
		Doub_circ_list<Fib_node<int>> roots)
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
	
	
	arch.close();
}
*/
	/*
	Doub_circ_list_node<Fib_node<int>> node2(2);
	Doub_circ_list_node<Fib_node<int>> node3(3);
	Doub_circ_list_node<Fib_node<int>> node4(4);

	
	Doub_circ_list<int> list1;

	
	list1.add_node(list1.fantasma, &node1);
	
	list1.add_node(list1.fantasma, &node2);
	
	
	list1.add_node(list1.fantasma, &node3);
	
	Doub_circ_list<int> list2;
	
	list2.add_node(list2.fantasma, &node7);

	
	list2.add_node(list2.fantasma, &node8);
	
	
	list2.add_node(list2.fantasma, &node9);
	
	list1.imprimir(list1.fantasma);
	list1.imprimir(list2.fantasma);
	
	list1.push_children_into_list(list1.fantasma, &list2, &node7);
	cout << '\n';
	list1.imprimir(list1.fantasma);
	list1.imprimir(list2.fantasma);
	
	cout << '\n';
	list1.kick_node_from_list(&node1);
	list1.imprimir(&node1);
	
	*/
