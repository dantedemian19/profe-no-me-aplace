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

void ingresar(node &liste, int valor) { //ingresa un valor nuevo al la lista

	node z = new(struct list);
	z->num = valor;
	if (n != 0) {
	}
	else {
		z->ant = NULL;
		start = z;
		last = z;
	};
	liste = z;
	n = n + 1;
	if (program == 1 || program == 2) {
		ordenar(liste, valor);
	}

}
void eleccion3_1(node &liste, node &z) {
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
void eleccion3_2(node &liste, node &z) {
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
void ingresar3(node &liste, int valor) { //ingresa un valor nuevo al la lista

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
void eliminarnodo(int pos){
	node z = start;

};
void control1() { //menu del programa 1
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
void control2() {//menu del programa 2
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
void control3() {//menu del programa 3
	node liste = NULL;
	int w = 0;
	int valor = 0;
	while (w != 3) {
		cout<<n<<"\n";
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
		cout << " pulse 4 para ingresar al programa 4 \n";
		cout << " pulse 5 para ingresar al programa 5 \n";
		cout << " pulse 6 para ingresar al programa 6 \n";
		cout << " pulse 7 para ingresar al programa 7 \n";
		cout << " pulse 8 para ingresar al programa 8 \n";
		cout << " pulse 9 para ingresar al programa 9 \n";
		cout << " pulse 10 para ingresar al programa 10 \n";
		cout << " pulse 11 para ingresar al programa 11 \n";
		cout << " pulse 12 para salir \n";
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
			cout << "on working....\n";
			system("pause");
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
			cout << "on working....\n";
			system("pause");
			break;
		case 8:
			cout << "on working....\n";
			system("pause");
			break;
		case 9:
			cout << "on working....\n";
			system("pause");
			break;
		case 10:
			cout << "its done....\n";
			system("pause");
			break;
		case 11:
			cout << "on working....\n";
			system("pause");
			break;
		case 12:
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


