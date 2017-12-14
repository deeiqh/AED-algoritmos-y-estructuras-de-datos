#ifndef KRUSKALL
#define KRUSKALL

#include <iostream>
#include "Grafo.h"
#include <list>
#include "fib_heap/Fib_heap.h"
#include <vector>
#include <climits>
#include <algorithm>
#include <set>

using D = int;
using W = int;
#define MAX 1000

Grafo<D, W> kruskall(const Grafo<D, W> &grafo);

#endif
