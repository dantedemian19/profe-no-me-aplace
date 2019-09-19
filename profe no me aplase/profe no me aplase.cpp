#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
int n = 0;// contador de nodos
int program = -1;// programa elegido

struct list {// definicion de la estructura
	int num = 0;
	struct list* sig = NULL;// apunta al nodo siguiente con valor mas alto
	struct list* ant = NULL;// apunta al nodo anterior con valor mas bajo
	int pos = n;
};
typedef struct list* node;//definicion del tipo

node start; // el primer nodo, el de valor num mas bajo
node last; //el ultimo nodo, el de valor num mas alto


void ordenar(node &liste, int valor) {// ordena la lista de menor a mayor
	bool ezet = true; // verifica si ya se encontro la posicion del nodo
	if (n == 2) {// el numero dos de la lista solo puede estar adelante o atras del ultimo, no en el medio
		node q = start; // el cabezal mas bajo
		node p = q->sig; // el cabezal mas alto, en este caso inutil, pero abajo es necesario
		if (valor < q->num) {// si va antes
			q->ant = liste;
			liste->ant = NULL;
			liste->sig = q;
			start = liste;
		}
		else {
			if (q->num < valor) {//si va despues
				q->sig = liste;
				liste->ant = q;
				liste->sig = NULL;
				ezet = false;
				last = liste;
			}
		}
	}
	if (n != 1 && n != 2) {
		node q = start; // lo mismo que arriba
		node p = q->sig; // lo mismo que arriba
		if (valor < q->num) {//si va primero
			q->ant = liste;
			liste->ant = NULL;
			liste->sig = q;
			start = liste;

		}
		else {
			while (ezet) {
				if (p->num >= valor && q->num < valor) {//si va en el medio de dos numeros
					liste->ant = q;
					liste->sig = p;
					p->ant = liste;
					q->sig = liste;
					ezet = false;
					last->sig = NULL;
					start->ant = NULL;

				}
				else {
					q = q->sig;
					p = p->sig;;
					if (p == NULL && ezet) {// si va ultimo
						q->sig = liste;
						liste->ant = q;
						liste->sig = NULL;
						ezet = false;
						last = liste;

					}

				}
			}
		}
	}
};

bool repetir(int valor) {
	node q = start;
	do{
		if (valor == q->num) {
			return true;
		}
		else {
			q = q->sig;
		}
	}while (q != NULL);
	if (q == NULL) {
		return false;
	}
};

void ingresar(node &liste, int valor) { //ingresa un valor nuevo al la lista
	//ingreso de un nodo nuevo a la lista
	node z = new(struct list);
	z->num = valor;
	if (n != 0) {
	
	}
	else {
		z->ant = NULL;
		start = z;
		last = z;
	}
		liste = z;
		n = n + 1;
	if (program == 1 || program == 2) {
		ordenar(liste, valor);// ordenamiento del programa 1 y 2;
	}
	
}
void ingresar7(node& liste, int valor) {// ingresa al final de la lista para el programa 7
	bool fal = repetir(valor);//verifica si el valor ingresado esta en la lista o no (programa 7)
	if (program == 7 && fal) {//el valor esta repetido y no se necesita ingresar el valor
		return;
	}
	if (program == 7 && !fal) {
		node z = new(struct list);
		z->num = valor;
		if (liste != NULL) liste->sig = z;
		z->ant = liste;
		liste = z;
		last = liste;
	}
};
void eleccion3_1(node &liste, node &z) {// deja decidir el orden en el que va el nuevo nodo del programa 3, cuando solo hay un valor en la lista
	int r = 0;
	node q = liste;
	while (r != 1 && r!=2) {
		cout << " ant:" << q->num << " \n";
		cout << " pulse 1 para ingresar antes \n";
		cout << " pulse 2 para ingresar despues \n";
		cin >> r;
		system("cls");
		switch (r) {
		case 1:// si va antes
			q->ant = z;
			z->sig = q;
			start = z;
			last = q;
			break;
		case 2: //si va despues
			q->sig = z;
			z->ant = q;
			last = z;
			start = q;
			break;
		default:
			cout << " Ingrese un numero valido \n";
			break;
		}
	}
};
void eleccion3_2(node &liste, node &z) {// deja decidir el lugar donde va el nodo nuevo del programa 3, cuando hay 2 nodos o mas en la lista ademas del nuevo
	int r = 0;
	node q = liste->ant; // el cabezal mas bajo
	node p = liste; // el cabezal mas alto, en este caso inutil, pero abajo es necesario
	while (r != 1) {
		if(q==NULL)cout << " ant:" << "NULL" << " \n";
		else cout << " ant:" << q->num << " \n";
		if (p == NULL)cout << " sig:" << "NULL" << " \n";
		else cout << " sig:" << p->num << " \n";
		cout << " pulse 1 para ingresar \n";
		cout << " pulse 2 para mover delante \n";
		cout << " pulse 3 para mover atras \n";
		cin >> r;
		system("cls");
		switch (r) {
		case 1:// ingresa el nodo entre los nodos serleccionados
			z->ant = q;
			z->sig = p;
			if (p != NULL) p->ant = z;
			if(q != NULL) q->sig = z;
			if(q==NULL){
				start = z;
			}
			if (p == NULL) {
				last = z;
			}
			break;

		case 2: //mover los cabezales adelante
			if (p != NULL) {
				if (q != NULL)q = q->sig;
				else q = start;
				p = p->sig;
			}else{
				cout << " no se puede mover hacia delante \n";
			}
			break;
		case 3: //mover los cabezales atras
				if (q != NULL){
					if (p != NULL)p = p->ant;
					else p = last;
					q = q->ant;
			}
			else {
				cout << " no se puede mover hacia atras \n";
			}
			break;
		default:
			cout << " Ingrese un numero valido \n";
			break;
		}
	}


};
void ingresar3(node &liste, int valor) { //ingresa un valor nuevo al la lista para el programa 3

	node z = new(struct list);
	z->num = valor;
	if (n != 0 && n != 1) {
		eleccion3_2(liste, z);
	}
	if (n == 0) {
			z->ant = NULL;
			start = z;
			last = z;
		}
	if (n == 1) {
			eleccion3_1(liste,z);
		}

	liste = z;
	n = n + 1;
};
int contadorpedorro() {// devuelve el numero de nodos que hay 
	node z = start;
	int i = 0;
	system("cls");
	while (z != NULL) {
		i += 1;
		z = z->sig;
	}
	return i;
};
void mostrarfifo(node liste) {// muestra desde el primer ingresado al ultimo
	node z = start;
	int i = 0;
	system("cls");
	cout << " nº" << "	|	" << "num	" << " \n";
	while (z != NULL) {
		cout << " " << i + 1 << "	|	" << z->num << "\n";
		i += 1;
		z = z->sig;
	}

};
void mostrarlifo(node liste) {// muestra desde el ultimo ingresado al primero
	node z = last;
	int i = 0;
	system("cls");
	cout << " nº" << "	|	" << "num	\n";
	while (z != NULL) {
		cout << " " << i + 1 << "	|	" << z->num << "\n";
		i += 1;
		z = z->ant;
	}

};
void eliminarnodo(node& liste) {// elimina un nodo de la lista
	int t = 0;
	node q = liste;
	node p = q->ant;
	node r = q->sig;
	while (t != 1) {
		if (p == NULL)cout << " ant:" << "NULL" << " \n";
		else cout << " ant:" << p->num << " \n";
		if (q == NULL)cout << " select:" << "NULL" << " \n";
		else cout << " select:" << q->num << " \n";
		if (r == NULL)cout << " sig:" << "NULL" << " \n";
		else cout << " sig:" << r->num << " \n";
		cout << " pulse 1 para eliminar \n";
		cout << " pulse 2 para mover delante \n";
		cout << " pulse 3 para mover atras \n";
		cin >> t;
		system("cls");
		switch (t) {
		case 1:// eliminar el nodo seleccionado
			n -= 1;
			if (p != NULL) p->sig = q->sig;
			else 

			break;

		case 2: //mover los cabezales adelante
			if (r != NULL) {
				if (p != NULL)p = p->sig;
				else p = q;
				q = q->sig;
				r = r->sig;
			}
			else {
				cout << " no se puede mover hacia delante \n";
			}
			break;
		case 3: //mover los cabezales atras
			if (p != NULL) {
				if (r != NULL)r = r->ant;
				else r = q;
				q = q->ant;
				p = p->ant;
			}
			else {
				cout << " no se puede mover hacia atras \n";
			}
			break;
		default:
			cout << " Ingrese un numero valido \n";
			break;
		}
	}
};
	
void control1(){ //menu del programa 1
	node liste = NULL;
	int w = 0;
	int valor = 0;
	while (w != 3) {
		cout << " Programa: " << program << "\n";
		cout << " pulse 1 para ingresar un nuevo nodo \n";
		cout << " pulse 2 para ver los nodos ordenados \n";
		cout << " pulse 3 para salir \n";
		cin >> w;
		system("cls");
		switch (w) {
		case 1:
			cout << "ingrese el valor del nodo: ";
			cin >> valor;
			ingresar(liste, valor);
			system("cls");
			break;
		case 2:
			mostrarfifo(liste);
			system("pause");
			system("cls");
			break;
		case 3:
			break;
		default:
			cout << "ingrese un numero valido \n";
			system("pause");
			break;
		}
	}
};
void control2(){//menu del programa 2
	node liste = NULL;
	int w = 0;
	int valor = 0;
	while (w != 3) {
		cout << " Programa: " << program << "\n";
		cout << " pulse 1 para ingresar un nuevo nodo \n";
		cout << " pulse 2 para ver los nodos ordenados \n";
		cout << " pulse 3 para salir \n";
		cin >> w;
		system("cls");
		switch (w) {
		case 1:
			cout << "ingrese el valor del nodo: ";
			cin >> valor;
			ingresar(liste, valor);
			system("cls");
			break;
		case 2:
			mostrarlifo(liste);
			system("pause");
			system("cls");
			break;
		case 3:
			break;
		default:
			cout << "ingrese un numero valido \n";
			system("pause");
			break;
		}
	}
};
void control3(){//menu del programa 3
	node liste = NULL;
	int w = 0;
	int valor = 0;
	while (w != 3) {
		cout << " Programa: " << program << "\n";
		cout << " pulse 1 para ingresar un nuevo nodo \n";
		cout << " pulse 2 para ver los nodos \n";
		cout << " pulse 3 para salir \n";
		cin >> w;
		system("cls");
		switch (w) {
		case 1:
			cout << "ingrese el valor del nodo: ";
			cin >> valor;
			ingresar3(liste, valor);
			system("cls");
			break;
		case 2:
			mostrarfifo(liste);
			system("pause");
			system("cls");
			break;
		case 3:

			break;
		default:
			cout << "ingrese un numero valido \n";
			system("pause");
			break;
		}
	}
};

void control7() {
	node liste = NULL;
	int w = 0;
	int valor = 0;
	while (w != 3) {
		cout << " Programa: " << program << "\n";
		cout << " pulse 1 para ingresar un nuevo nodo \n";
		cout << " pulse 2 para ver los nodos \n";
		cout << " pulse 3 para salir \n";
		cin >> w;
		system("cls");
		switch (w) {
		case 1:
			cout << "ingrese el valor del nodo: ";
			cin >> valor;
			ingresar3(liste, valor);
			system("cls");
			break;
		case 2:
			mostrarfifo(liste);
			system("pause");
			system("cls");
			break;
		case 3:

			break;
		default:
			cout << "ingrese un numero valido \n";
			system("pause");
			break;
		}
	}
};
void selection() { // menu de seleccion de programas
	bool tru = true;
	while (tru) {
		system("cls");
		start = NULL;
		last = NULL;
		cout << " pulse 1 para ingresar al programa 1 \n";
		cout << " pulse 2 para ingresar al programa 2 \n";
		cout << " pulse 3 para ingresar al programa 3 \n";
		cout << " pulse 4 para ingresar al programa 7 \n";
		cout << " pulse 5 para ingresar al programa 8 \n";
		cout << " pulse 6 para ingresar al programa 9 \n";
		cout << " pulse 7 para ingresar al programa 10 \n";
		cout << " pulse 8 para ingresar al programa 11 \n";
		cout << " pulse 9 para salir \n";
		cin >> program;
		system("cls");
		switch (program) {
		case 1:
			program = 1;
			system("pause");
			system("cls");
			control1();
			break;
		case 2:
			program = 2;
			system("pause");
			system("cls");
			control2();
			break;
		case 3:
			program = 3;
			system("pause");
			system("cls");
			control3();
			break;
		case 4:
			program = 7;
			system("pause");
			system("cls");
			control7();
			break;
		case 5:
			cout << "on working....\n";
			system("pause");
			break;
		case 6:
			cout << "on working....\n";
			system("pause");
			break;
		case 7:
			cout << "its done....\n";
			system("pause");
			break;
		case 8:
			cout << "on working....\n";
			system("pause");
			break;
		case 9:
			cout << "loading \n";
			Sleep(6000);
			system("exit");
			break;
		default:
			cout << "ingrese un numero valido";
			break;
		}
	}
};
int main() {
	selection();
}