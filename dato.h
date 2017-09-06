#ifndef DATO_H
#define DATO_H

#include <iostream>
#include <string>

using namespace std;

template <class T, class U>
class Dato{
public:
	T id;
	U pos;
public:
	Dato();
	Dato(T id, U pos = -1):id(id), pos(pos) {};
	void show(){
		cout << id << ' ' << pos;
	}

	int comp(const Dato<string,U> &b){
		return ((this->id).compare(b.id));
	}
};

#endif