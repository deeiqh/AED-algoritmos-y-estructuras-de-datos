#include "dato.h"
#include "lista_doble.h"
#include <string>
#include <fstream>


using namespace std;

using DatoSUI = Dato<string, unsigned int>;

#define nombre_archivo "enfermedades.txt"

int main()
{
	//	INDEXAR
	ListaD<DatoSUI>* pLista = new ListaD<DatoSUI>;

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
			pLista->add_ordenado(dato);
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

    pLista->show();

    //LEER DESCRIPCIÓN DE ENFERMEDAD, TOMANDO DIRECCION DE LISTA 

    string enfermedad = "Parkinson";

    DatoSUI dato(enfermedad);
    NodoD<DatoSUI>* pNodo = new NodoD<DatoSUI>(dato);
    int poss;
    if(pLista->find(dato,pNodo)){
    	poss = pNodo->dato.pos;
    }

    arch.seekg(fstream::beg+poss);
    arch.read(c,1);
    cout << "\nDescripción de " << enfermedad << '\n';
	while(c[0] != '#'){
		cout << c;
		arch.read(c,1);
	}    
       
    //ELIMINAR ENFERMEDAD
    enfermedad = "Parkinson";
    cout << "\n\nAntes de eliminar "<< enfermedad <<":\n";
    pLista->show();    
    cout << "\nLuego de eliminar "<< enfermedad <<":\n";
    pLista->del(dato);
    arch.seekg(fstream::beg+poss-2); //eliminacion logica del archivo
    c[0]= '0';
    arch.write(c,1);
    pLista->show();

    
    //DESHACER ELIMINCACION
    pLista->add_ordenado(dato);
    arch.seekg(fstream::beg+poss-2); //eliminacion logica del archivo
    c[0]= '1';
    arch.write(c,1);

    arch.close();// Lista tiene destructor implementado

/*
    cout<<"----------Enfermedades--------\n"

    cout<<"First(0), Next(1), Prev(2), Last(-1)\n",
	int a;
	NodoD<DatoSUI>* pNodoV = pLista->first();
    cin >> a;
    switch(a){
    	case 0:
    		ventana(pLista->first);
    		pNodoV = pLista->first,
    		break;
    	case 1:
    		ventana(pNodoV->next);
    		pNodoV = pNodoV->next;
    	case 2:
    		ventana(pNodoV->prev);
    		pNodoV = pNodoV->prev;
    	case -1:
    		ventana(pNodoV->last);
    		pNodoV = pNodoV->last;
    }

*/

/*
	DatoSUI dato("a",1);
	DatoSUI dato2("b",2);

	if (dato.comp(dato2) == 0)
		cout << "compar \n";

	dato.show();

	NodoD<DatoSUI>* pNodo = new NodoD<DatoSUI>(dato);
	pNodo->dato.show();
	delete pNodo;

	ListaD<DatoSUI>* pLista = new ListaD<DatoSUI>;
	pLista->show();

	cout << "add \n";
	DatoSUI dato3("c",1);
	DatoSUI dato4("d",2);
	pLista->add_ordenado(dato4);	
	pLista->add_ordenado(dato3);
	pLista->add_ordenado(dato2);	
	pLista->add_ordenado(dato3);	
	pLista->add_ordenado(dato3);
	pLista->add_ordenado(dato);	
	pLista->add_ordenado(dato3);
	pLista->show();

	DatoSUI dato5("e",2);
	pLista->del(dato5);
	pLista->show();

	delete pLista;
*/
	return 0;
}