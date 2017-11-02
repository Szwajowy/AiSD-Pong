#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct elem {
	int dane;
	elem *nast;
};

void insert(int x, int i, elem *&lista) {
	elem* newElem = new elem;
	newElem->dane = x;
	if (i==1) {
		newElem->nast=lista;
		lista = newElem;
	} else {
		elem* poprz=lista;
		int licznik = 1;
		while(licznik != (i-1)) {
			licznik
		}
	}
}

int remove(int i, elem *&lista) {
	
}

int read(int i, elem *lista) {
	
}

int main(int argc, char** argv) {
	return 0;
}
