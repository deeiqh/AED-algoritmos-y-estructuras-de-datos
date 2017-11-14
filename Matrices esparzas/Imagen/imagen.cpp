//g++ -std=c++11 *.cpp -o i -lpthread -lX11

#include <CImg.h>
#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace cimg_library;
using namespace std;
using size_type = short int;//2B
#define Negro true
#define Blanco false

CImg<bool> binarizar(CImg<double> imagen, int umbral);
void poner_a_buffer(size_type numero, char* buffer, int& indice);
size_type sacar_de_buffer(char* buffer,int& indice);

int main(int argc, char *argv[])
{
	map<size_type, map<size_type, bool>> matriz;
	
	// iimagen: input_imagen
	const char* input = cimg_option("-i", "pernu.jpg", "iimagen");
    int umbral = cimg_option("-u", 100.0, "iimagen");
    
	//oimagen: imagen output
    string oimagen = "BN_pernu.jpg";
    
    //lectura de la imagen
    CImg<double> iimagen(input);
    
    //binarización de la imagen
   	CImg<bool> imagen_binaria = binarizar(iimagen, umbral);

   	//guardamos en matriz esparza
	for (int f = 0; f != imagen_binaria.height(); f++ ) {
        for (int c = 0; c != imagen_binaria.width(); c++ ) {            
            if (imagen_binaria(c,f) == Blanco) {
            	matriz[f][c] = Blanco;
            }
        }
    }
    
    //guardamos en archivo la matriz esparza
    //	el archivo es binario y guarda en bloques de dos bytes los
    //	datos de la matriz, pues con 2 bytes se logra mas de 
    //	65000 filas o columnas. Se ha usado operadores de bits
  	// 	tiene la sgte estructura:
  	//	----
  	//	numFilas | numColumas | FilasNetas(de la matriz)
  	//	fila iesima de la matriz | ColNetas(de la matriz) | Columnas iesimas
  	//	fila iesima de la matriz | ColNetas(de la matriz) | Columnas iesimas
  	//	----
    fstream arch;
    arch.open("arch.bin", fstream:: out | fstream::binary);
    char* buffer = new char[imagen_binaria.width()*imagen_binaria.height()];
    int indice = 0;
    size_type nf, nc;
    unsigned int st = sizeof(size_type);
    nf = imagen_binaria.height();
    nc = imagen_binaria.width();
    
    poner_a_buffer(nf, buffer, indice);
    poner_a_buffer(nc, buffer, indice);   
    poner_a_buffer(matriz.size(), buffer, indice);//num de filas netas

    arch.write(buffer, 3*st);
    indice = 0;
    
    for(auto itf=matriz.begin(); itf != matriz.end(); itf++){
    	poner_a_buffer(itf->first, buffer, indice);
    	poner_a_buffer(itf->second.size(), buffer, indice);
    	for(auto itc=itf->second.begin(); itc!=itf->second.end(); itc++){
    		poner_a_buffer(itc->first, buffer, indice);
    	}
    	arch.write(buffer, indice);
    	indice = 0;
    }

    arch.close();
    
    //detalle del tamaño de un archivo que no use una matriz esparza
    cerr << "Si no se usa una matriz esparza el archivo arch.bin pesaría ";
    cerr << (3 + 2*nf + nf*nc)*st/1024 << " kB\n";
    
    //levantamos el archivo en matriz2
    map<size_type, map<size_type, bool>> matriz2;
    size_type f_netas, c_netas;
    arch.open("arch.bin", fstream:: in);  	
	arch.seekg (0, fstream::beg);
	
	
	arch.read(buffer,3*(st)); // nf, nc, f_netas	
	indice = 0; // posicion del siguiente dato a sacar	
	
	nf = sacar_de_buffer(buffer, indice);
	nc = sacar_de_buffer(buffer, indice);
	f_netas = sacar_de_buffer(buffer, indice);

	for(int i = 0; i != f_netas; i++){		
		//leer a buffer la fila y col netas
		arch.read(buffer,st*2);
		indice = 0;
		//sacar de buffer c_netas
		size_type fila = sacar_de_buffer(buffer, indice);
		matriz2[fila];
		c_netas = sacar_de_buffer(buffer, indice);
		//leer a buffer las columnas
		arch.read(buffer, c_netas*st);	
		indice = 0;	
		size_type columna;
		//escribir todo el buffer en la matriz2: las columnas de fila
		for(int i = 0; i != c_netas; i++){
			columna = sacar_de_buffer(buffer, indice);
			matriz2[fila][columna] = Negro;
		}
	}
	
    arch.close();
    
    //leemos matriz2 y generamos la imagen_binaria2
    CImg<bool> imagen_binaria2(nc, nf, 1, 1, 0);
    cimg_forXY(imagen_binaria2, x, y) {
		    if (matriz2[y][x])
		        imagen_binaria2(x,y) = Blanco;
		    else
		        imagen_binaria2(x,y) = Negro;
    }
    
    //mostramos imagen de matriz2
    CImgDisplay main_disp(imagen_binaria2,"Peru-NuevaZelanda");
    while(1){
      if(main_disp.is_closed()){break;}
      main_disp.wait(10);
   }
}


CImg<bool> binarizar(CImg<double> imagen, int umbral) {
    CImg<bool> imagen_binaria(imagen.width(), imagen.height(), 1, 1, 0);
    //por cada pixel escribimos true o false
    cimg_forXY(imagen, x, y) {
        if (imagen(x,y) > umbral)
            imagen_binaria(x,y) = Negro;
        else
        	imagen_binaria(x,y) = Blanco;
    }
    return imagen_binaria;
}

void poner_a_buffer(size_type numero, char* buffer, int& indice){
	buffer[indice] = numero >> (sizeof(size_type)-1)*8;
	size_type n;
	n = 255;
    buffer[indice+1] = numero & n;
	indice += 2;
}

size_type sacar_de_buffer(char* buffer,int& indice){
	size_type numero, n,m;
	n = 255;	
	numero = buffer[indice] & n;
	numero = numero << (sizeof(size_type)-1)*8;
	m = buffer[indice+1] & n;
	numero = numero | m;
	indice += 2;	
	return numero;
}

