#include <iostream>
#include <fstream>
using namespace std;
int x;

struct usr {
	char name[50];
	usr* nx;
};

struct admin {
	char name[50];
	admin* nx;
};

struct cash {
	char name[50];
	cash* nx;
};

usr* inc, * aux, * fin = nullptr;
admin* incA, * auxA, * finA = nullptr;
cash* incC, * auxC, * finC = nullptr;




void usuario(usr* nuevo);
void usuario(admin* nuevo);
void usuario(cash* nuevo);
void showlist();
void mod(char nameUsr[50]);
void del(char nameUsr[50]);
void writebin();
void readbin();



int main()
{
	usr* nodeUsr = new usr;
	char nameUsr[50];
	int opt = 0, opt2 = 0;

	do
	{ 
	cout << "1.- Login" << endl;
	cout << "2.- Sign in" << endl;
	cin >> opt2;
	cin.ignore();
	} while (opt < 1 || opt > 5);
	

	do
	{
		system("CLS");
		cout << "Menu" << endl;
		cout << "1.- Agregar usuario." << endl;
		cout << "2.- Modificar nombre de usuario." << endl;
		cout << "3.- Mostrar lista." << endl;
		cout << "4.- Eliminar usuario." << endl;
		cout << "5.- Salir del programa." << endl;
		cin >> opt;
		cin.ignore();

		if (opt == 1)
		{
			cout << "Ingrese el nombre del usuario: ";
			cin.getline(nameUsr, 50);
			strcpy_s(nodeUsr->name, nameUsr);
			usuario(nodeUsr);

			opt = 0;
		}
		if (opt == 2)
		{
			cout << "Nombre del usuario a modificar: ";
			cin.getline(nameUsr, 50);
			mod(nameUsr);

			opt = 0;
		}
		if (opt == 3)
		{
			readbin();
			showlist();
			cin.ignore();
			opt = 0;
		}
		if (opt == 4)
		{

			cout << "Nombre de usuario a eliminar: ";
			cin.getline(nameUsr, 50);
			del(nameUsr);
			opt = 0;
		}
	} while (opt < 1 || opt > 5);
	writebin();
	system("PAUSE");
	return(0);
}
void usuario(usr* nuevo)
{

	if (inc == nullptr) {
		inc = new usr;
		aux = inc;

		aux->nx = nullptr;

		strcpy_s(aux->name, nuevo->name);

	}
	else {
		aux = inc;

		while (aux->nx != nullptr)
		{
			aux = aux->nx;
		}

		aux->nx = new usr;

		aux->nx->nx = nullptr;

		aux = aux->nx;
		fin = aux;

		strcpy_s(aux->name, nuevo->name);
	}
}
void usuario(admin* nuebo)
{

	if (incA == nullptr) {
		incA = new admin;
		auxA = incA;

		auxA->nx = nullptr;

		strcpy_s(auxA->name, nuebo->name);

	}
	else {
		auxA = incA;

		while (auxA->nx != nullptr)
		{
			auxA = auxA->nx;
		}

		auxA->nx = new admin;

		auxA->nx->nx = nullptr;

		auxA = auxA->nx;
		finA = auxA;

		strcpy_s(auxA->name, nuebo->name);
	}
}
void usuario(cash* nuebo)
{

	if (incC == nullptr) {
		incC = new cash;
		auxC = incC;

		auxC->nx = nullptr;

		strcpy_s(auxC->name, nuebo->name);

	}
	else {
		auxC = incC;

		while (auxC->nx != nullptr)
		{
			auxC = auxC->nx;
		}

		auxC->nx = new cash;

		auxC->nx->nx = nullptr;

		auxC = auxC->nx;
		finC = auxC;

		strcpy_s(auxA->name, nuebo->name);
	}
}
void showlist()
{
	system("cls");
	if (inc == nullptr)
	{

		cout << "\n";
		cout << "La lista esta vacia. Agregue canciones";

	}
	else
	{
		aux = inc;

		while (aux != nullptr)
		{
			cout << "Usuario: " << aux->name << endl;
			aux = aux->nx;
		}

	}
}
void mod(char nameMod[50]) {
	aux = inc;
	char newNom[50];

	if (aux == nullptr)
	{
		cout << "La lista esta vacia. Agregue canciones" << endl;
	}
	else {
		while (aux != nullptr && strcmp(aux->name, nameMod) != 0) {

			aux = aux->nx;

		}
		if (aux == nullptr) {
			cout << "Usuario no encontrado" << endl;
		}
		else {

			cout << "Nombre del usuario: " << aux->name << endl;
			cout << "Nuevo nombre: ";
			cin.getline(newNom, 50);
			strcpy_s(aux->name, newNom);
			cout << "Usuario modificado" << endl;

		}
	}

	system("PAUSE");
}
void del(char nameDel[50])
{
	aux = inc;
	usr* anterior = nullptr;

	if (aux == nullptr)
	{
		cout << "La lista esta vacia, agrege usuarios" << endl;
	}
	else {

		while (aux != nullptr) {

			if (strcmp(aux->name, nameDel) != 0) {
				anterior = aux;
				aux = aux->nx;
			}
			else {

				if (aux == inc) {

					cout << "Nombre de usuario: " << aux->name << endl;

					inc = aux->nx;

					delete aux;

					aux = inc;

					cout << "Usuario eliminado" << endl;

				}
				else {
					cout << "Nombre de usuario: " << aux->name << endl;

					anterior->nx = aux->nx;

					delete aux;

					aux = inc;

					cout << "Usuario eliminado" << endl;

				}
			}
		}

		if (aux == nullptr) {
			cout << "Usuario no encontrado" << endl;
		}


		system("PAUSE");
	}
}
void writebin()
{
	aux = inc;

	ofstream archivo;
	archivo.open("usuarios.bin", ios::out | ios::binary | ios::trunc);

	if (archivo.is_open()) {
		while (aux != nullptr)
		{
			archivo.write((char*)aux, sizeof(usr));
			aux = aux->nx;
		}

		archivo.close();
	}
	else
	{
		cout << "No se pudo abrir el archivo.";
		system("PAUSE");
	}
}
void readbin() {

	ifstream archivo;
	archivo.open("usuarios.bin", ios::in | ios::binary);

	aux = inc;
	if (archivo.is_open()) {

		usr* usread = new usr;

		while (!archivo.read((char*)usread, sizeof(usr)).eof()) {

			while (aux != nullptr && aux->nx != nullptr)
			{
				aux = aux->nx;
			}
			if (aux == nullptr) {
				inc = usread;
				inc->nx = nullptr;
				aux = inc;
			}
			else {
				aux->nx = usread;
				aux->nx->nx = nullptr;
				fin = aux->nx;
			}

			usread = new usr;
		}
		archivo.close();
	}
	else {
		cout << "No es posible abrir el archivo.";
		system("PAUSE");
	}
}