﻿#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
int n = 0;// contador de nodos
int program = -1;// programa elegido

struct list {// definicion de la estructura
	int num = 0;//valor del nodo
	struct list* sig = NULL;// apunta al nodo siguiente con valor mas alto
	struct list* ant = NULL;// apunta al nodo anterior con valor mas bajo
};
typedef struct list* node;//definicion del tipo

node start; // el primer nodo, el de valor num mas bajo
node last; //el ultimo nodo, el de valor num mas alto

void wait() {
	cout << "loading \n";
	Sleep(2000);
	system("cls");
};
void borrar() {// borra toda la lista
	node q = start;
	node p = q;
	while (q != NULL) {
		delete q;
		q = p;
		if (p != NULL) p->sig;
	}
};
void crear(node& liste) {// resetea la lista
	n = 0;
	liste = NULL;
	last = NULL;
	start = NULL;
	cout << " se creo una nueva lista \n";
	system("pause");
	system("cls");
};
void borrarn(node& p, node& q, node& r) {// borra un nodo 
	n -= 1;
	delete q;
	if (p != NULL) p->sig = r;
	else start = r;
	if (r != NULL) r->ant = p;
	else last = p;
};
void ordenar(node& liste, int valor) {// ordena la lista de menor a mayor
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
void ordenarevez(node& liste, int valor) {// ordena la lista de menor a mayor
	bool ezet = true; // verifica si ya se encontro la posicion del nodo
	if (n == 2) {// el numero dos de la lista solo puede estar adelante o atras del ultimo, no en el medio
		node q = start; // el cabezal mas bajo
		node p = q->sig; // el cabezal mas alto, en este caso inutil, pero abajo es necesario
		if (valor > q->num) {// si va antes
			q->ant = liste;
			liste->ant = NULL;
			liste->sig = q;
			start = liste;
		}
		else {
			if (q->num > valor) {//si va despues
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
		if (valor > q->num) {//si va primero
			q->ant = liste;
			liste->ant = NULL;
			liste->sig = q;
			start = liste;

		}
		else {
			while (ezet) {
				if (p->num <= valor && q->num > valor) {//si va en el medio de dos numeros
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
float promediolist() { // saca el promedio de los valores de la lista
	node z = start;
	float prom = 0;
	int i = 0;
	system("cls");
	while (z != NULL) {
		i += 1;
		prom += z->num;
		z = z->sig;
	}
	prom /= i;
	return prom;
};
bool repetir(int valor) { // devuelve true en caso de que el valor ingresado ya exista en la lista
	node q = start;
	do {
		if (valor == q->num) {// si ya existe
			return true;
		}
		else {
			q = q->sig;
		}
	} while (q != NULL);
	if (q == NULL) {// si no existe
		return false;
	}
	return false;
};
void ingresar(node& liste, int valor) { //ingresa un valor nuevo al la lista
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
void ingresar7(node& liste, int valor) {// ingresa al final de la lista 
	node z = new(struct list);
	z->num = valor;
	if (start == NULL) start = z;
	if (last != NULL) last->sig = z;
	z->ant = last;
	liste = z;
	last = liste;
};
void ingresarpri(node liste, int valor) {// ingresa al principio de la lista
	node z = new(struct list);
	z->num = valor;
	if (last == NULL) last = z;
	if (start != NULL) start->ant = z;
	z->sig = start;
	liste = z;
	start = liste;
};
void eleccion3_1(node& liste, node& z) {// deja decidir el orden en el que va el nuevo nodo del programa 3, cuando solo hay un valor en la lista
	int r = 0;// eleccion del usuario
	node q = liste;// el unico nodo que hay en la lista
	while (r != 1 && r != 2) {
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
void eleccion3_2(node& liste, node& z) {// deja decidir el lugar donde va el nodo nuevo del programa 3, cuando hay 2 nodos o mas en la lista ademas del nuevo
	int r = 0;// eleccion del usuario
	node q = liste->ant; // el cabezal mas bajo
	node p = liste; // el cabezal mas alto, en este caso inutil, pero abajo es necesario
	while (r != 1) {
		if (q == NULL)cout << " ant:" << "NULL" << " \n";
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
			if (q != NULL) q->sig = z;
			if (q == NULL) {
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
			}
			else {
				cout << " no se puede mover hacia delante \n";
			}
			break;
		case 3: //mover los cabezales atras
			if (q != NULL) {
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
void ingresar3(node& liste, int valor) { //ingresa un valor nuevo al la lista para el programa 3
	node z = new(struct list);
	z->num = valor;
	if (n != 0 && n != 1) {// si hay mas de dos nodos en la lista
		eleccion3_2(liste, z);
	}
	if (n == 0) {// si no hay nodos en la lista
		z->ant = NULL;
		start = z;
		last = z;
	}
	if (n == 1) {// si hay un solo nodo en la lista
		eleccion3_1(liste, z);
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
	cout << " nº" << "    |    " << "num    " << " \n";
	while (z != NULL) {
		cout << " " << i + 1 << "    |    " << z->num << "\n";
		i += 1;
		z = z->sig;
	}
};
void mostrarfifo8(node listis) {// muestra desde el primer ingresado al ultimo desde el inicio de una lista seleccionada
	node z = listis;
	int i = 0;
	system("cls");
	cout << " nº" << "    |    " << "num    " << " \n";
	while (z != NULL) {
		cout << " " << i + 1 << "    |    " << z->num << "\n";
		i += 1;
		z = z->sig;
	}
};
void mostrarlifo(node liste) {// muestra desde el ultimo ingresado al primero
	node z = last;
	int i = 0;
	system("cls");
	cout << " nº" << "    |    " << "num    \n";
	while (z != NULL) {
		cout << " " << i + 1 << "    |    " << z->num << "\n";
		i += 1;
		z = z->ant;
	}
};
void eliminarnodo(node& liste) {// elimina un nodo de la lista
	int t = 0;
	if (liste != NULL) {
		node q = liste;// nodo seleccionado
		node p = q->ant;// nodo anterior
		node r = q->sig;// nodo siguiente
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
				borrarn(p, q, r);
				break;
			case 2: //mover los cabezales adelante
				if (r != NULL) {
					p = q;
					q = r;
					r = r->sig;
				}
				else {
					cout << " no se puede mover hacia delante \n";
				}
				break;
			case 3: //mover los cabezales atras
				if (p != NULL) {
					r = q;
					q = p;
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
	}
	else {
		cout << " no hay nodos en la lista \n";
		system("pause");
	}
};
void guardado_impar() {
	node aux;// auxiuliar del pasaje
	node listis = NULL;// inicio de la nueva lista
	node listif = NULL;// final de la nueva lista
	node normal = start;// cabezal de seleccion
	while (normal != NULL) {
		if (normal != NULL && normal->num % 2 != 0 && listis != NULL) listis = normal;
		if (normal->num % 2 != 0) {
			aux = new(struct list);
			aux->num = normal->num;
			aux->sig = NULL;
			aux->ant = listif;
			if (listif != NULL) {
				listif->sig = aux;
			}
			else {
				listis = aux;
			}
			listif = aux;
		}
		normal = normal->sig;
	}
	mostrarfifo8(listis);
};
void saveprom() {//guarda en una lista los valores superiores al promedio de la lista
	float prom = promediolist();// valor del promedio de la lista inicial
	node aux;// auxiuliar del pasaje
	node listjf = NULL;// final de la nueva lista
	node listjs = NULL;// inicio de la nueva lista
	node normal = start;// cabezal de seleccion
	while (normal != NULL) {
		if (normal->num > prom) {
			aux = new(struct list);
			aux->num = normal->num;
			aux->sig = NULL;
			aux->ant = listjf;
			if (listjf != NULL) {
				listjf->sig = aux;
			}
			else {
				listjs = aux;
			}
			listjf = aux;
		}
		normal = normal->sig;
	}
	mostrarfifo8(listjs);
};
void control1() { //menu del programa 1
	node liste = NULL;// ultimo nodo ingresado
	int w = 0;// decision del usuario
	int valor = 0;// valor del ultimo nodo ingresado o del que se esta ingresando
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
			wait();
			break;
		default:
			cout << "ingrese un numero valido \n";
			system("pause");
			break;
		}
	}
};
void control2() {//menu del programa 2
	node liste = NULL;// ultimo nodo ingresado
	int w = 0;// decision del usuario
	int valor = 0;// valor del ultimo nodo ingresado o del que se esta ingresando
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
			wait();
			break;
		default:
			cout << "ingrese un numero valido \n";
			system("pause");
			system("cls");
			break;
		}
	}
};
void control3() {//menu del programa 3
	node liste = NULL;// ultimo nodo ingresado
	int w = 0;// decision del usuario
	int valor = 0;// valor del ultimo nodo ingresado o del que se esta ingresando
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
			wait();
			break;
		default:
			cout << "ingrese un numero valido \n";
			system("pause");
			break;
		}
	}
};
void control7() {// menu del programa 7
	node liste = NULL;// ultimo nodo ingresado
	int w = 0;// decision del usuario
	int valor = 0;// valor del ultimo nodo ingresado o del que se esta ingresando
	bool fal = false;
	while (w != 7) {
		bool fal = false;
		cout << " Programa: " << program << "\n";
		cout << " pulse 1 para crear una nueva lista \n";
		cout << " pulse 2 para ingresar un nuevo nodo al final de la lista \n";
		cout << " pulse 3 para ingresar un nuevo nodo en una posicion \n";
		cout << " pulse 4 para eliminar un nuevo nodo de una posicion \n";
		cout << " pulse 5 para mostar la lista \n";
		cout << " pulse 6 para saber cuantos nodos tiene la lista \n";
		cout << " pulse 7 para salir \n";
		cin >> w;
		system("cls");
		switch (w) {
		case 1:
			borrar();
			crear(liste);
			system("cls");
			break;
		case 2:
			while (!fal) {
				cout << "ingrese el valor del nodo: ";
				cin >> valor;
				fal = repetir(valor);
				if (fal != true) {
					cout << " el valor esta repetido, ingrese otro";
				}
			}
			ingresar7(liste, valor);
			system("cls");
			break;
		case 3:
			while (!fal) {
				cout << "ingrese el valor del nodo: ";
				cin >> valor;
				fal = repetir(valor);
				if (fal != true) {
					cout << " el valor esta repetido, ingrese otro";
				}
			}
			ingresar3(liste, valor);
			system("cls");
			break;
		case 4:
			eliminarnodo(liste);
			system("cls");
			break;
		case 5:
			mostrarfifo(liste);
			system("cls");
			break;
		case 6:
			cout << " en la lista hay " << contadorpedorro() << " nodo/s \n";
			system("pause");
			system("cls");
			break;
		case 7:
			wait();
			break;
		default:
			cout << "ingrese un numero valido \n";
			system("pause");
			break;
		}
	}
};
void control8() {// menu del programa 8 y 9 (en proceso)
	node liste = NULL;// ultimo nodo ingresado
	int w = 0;// decision del usuario
	int valor = 0;// valor del ultimo nodo ingresado o del que se esta ingresando
	while (w != 7) {
		cout << " Programa: " << program << "\n";
		cout << " pulse 1 para ingresar un nodo \n";
		cout << " pulse 2 para mostrar una lista con los datos impares de la lista \n";
		cout << " pulse 3 para mostrar una lista con los datos mayores del promedio \n";
		cout << " pulse 4 para eliminar un nodo \n";
		cout << " pulse 5 para mostrar la lista \n";
		cout << " pulse 6 para mostrar la cantidad de nodos que hay en la lista \n";
		cout << " pulse 7 para salir \n";
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
			guardado_impar();
			system("pause");
			system("cls");
			break;
		case 3:
			saveprom();
			system("pause");
			system("cls");
			break;
		case 4:
			eliminarnodo(liste);
			system("cls");
			break;
		case 5:
			mostrarfifo(liste);
			system("cls");
			break;
		case 6:
			cout << " en la lista hay " << contadorpedorro() << " nodo/s \n";
			system("pause");
			system("cls");
			break;
		case 7:
			wait();
			break;
		default:
			cout << "ingrese un numero valido \n";
			system("pause");
			break;
		}
	}
};
void control11() {// menu del programa 11 (en proceso)
	node liste = NULL;// ultimo ingresado
	node listi = NULL;// ultimo ingresado de la lista i
	node listj = NULL;// ultimo ingresado de la lista j
	node listis = NULL;// primer nodo de la lista i
	node listif = NULL; // ultimo nodo de la lista i
	node listjs = NULL;// primer nodo de la lista j
	node listjf = NULL;// ultimo nodo de la lista j
	int w = 0;
	int l = 0;
	int valor = 0;
	while (w != 7) {
		cout << " Programa: " << program << "\n";
		cout << " pulse 1 para ingresar un nodo al final\n";
		cout << " pulse 2 para ingresar un nodo al principio \n";
		cout << " pulse 3 para eliminar un nodo \n";
		cout << " pulse 4 para insertar una lista en orden asendente \n";
		cout << " pulse 5 para insertar una lista en orden decendente \n";
		cout << " pulse 6 para mostrar una lista\n";
		cout << " pulse 7 para salir \n";
		cin >> w;
		system("cls");
		switch (w) {
		case 1:
			cout << "ingrese el valor del nodo: ";
			cin >> valor;
			ingresar7(liste,valor);
			system("cls");
			break;
		case 2:
			cout << "ingrese el valor del nodo: ";
			cin >> valor;
			ingresarpri(liste,valor);
			system("cls");
			break;
		case 3:
			eliminarnodo(liste);
			system("cls");
			break;
		case 4:
			cout << "ingrese el valor del nodo: ";
			cin >> valor;
			ingresar(liste,valor);
			ordenar(liste,valor);
			system("cls");
			break;
		case 5:
			cout << "ingrese el valor del nodo: ";
			cin >> valor;
			ingresar(liste, valor);
			ordenarevez(liste, valor);
			system("cls");
			break;
		case 6:
			l = 0;
			while (l != 1 && l != 2 && l != 3) {
				cout << " Programa: " << program << "\n";
				cout << " pulse 1 para ver la lista normal \n";
				cout << " pulse 2 para ver la lista asendente \n";
				cout << " pulse 3 para ver la lista decendente\n";
				cin >> l;
				switch (l)
				{
				case 1:
					mostrarfifo(liste);
					break;
				case 2:
					mostrarfifo8(listis);
					break;
				case 3:
					mostrarfifo8(listjs);
					break;
				default:
					cout<<" ingresé una opción válida ";
					break;
				}
			}
			system("pause");
			system("cls");
			break;
		case 7:
			wait();
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
		n = 0;
		if (program != 0) {
			cout << " se han borrado todos los datos con exito \n";
			system("pause");
		}
		cout << " pulse 1 para ingresar al programa 1 \n";
		cout << " pulse 2 para ingresar al programa 2 \n";
		cout << " pulse 3 para ingresar al programa 3 \n";
		cout << " pulse 4 para ingresar al programa 7 \n";
		cout << " pulse 5 para ingresar al programa (8 y 9) \n";
		cout << " pulse 6 para ingresar al programa 11 \n";
		cout << " pulse 7 para salir \n";
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
			program = 8;
			system("pause");
			system("cls");
			control8();
			break;
		case 6:
			program = 11;
			system("pause");
			system("cls");
			control11();
			break;
		case 7:
			wait();
			tru = false;
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
