#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Room {
	int id;
	string name;
	string description;
};
class NodeItem {
public:
	int ID;
	NodeItem* left;
	NodeItem* right;
	NodeItem(int id) {
		ID = id;
		left = nullptr;
		right = nullptr;
	}
};
NodeItem* insert(NodeItem* root, int newID) {
	if (root == nullptr) {
		return new NodeItem(newID);
	}
	if (newID < root->ID) {
		root->left = insert(root->left, newID);
	}
	else if (newID > root->ID) {
		root->right = insert(root->right, newID);
	}
	return root;
}

bool search(NodeItem* root, int targetID) {
	if (root == nullptr) {
		return false;
	}
	if (targetID == root->ID) {
		return true;
	}
	if (targetID < root->ID) {
		return search(root->left, targetID);
	}
	else{
		return search(root->right, targetID);
	}
}


int main() {
	NodeItem* inventory = nullptr;
	int roomactually = 0;
	bool playing = true;
	vector<Room> dungeon = {
		{0, "Entrada de la Mazmorra", "Se siente un aire frio y humedo."},
		{1, "Armeria Vieja", "Hay espadas oxidadas por el suelo."},
		{2, "Sala del Tesoro", "Ves un cofre brillando al fondo!"}
	};
	int paths[3][3] = {
		{0, 1, 0},{1, 0, 1},{0, 1, 0}
	};

	while (playing) {
		cout << "========================================" << endl;
		cout << "Estas en: " << dungeon[roomactually].name << endl;
		cout << dungeon[roomactually].description << endl;
		cout << "========================================" << endl;
		cout << "========================================" << endl;
		if (search(inventory, 50) == true) {
			cout << "[Inventario]: Llevas la Llave Dorada (ID: 50)" << endl;
		}
		else {
			cout << "[Inventario]: Vacio" << endl;
		}
		cout << "========================================" << endl;
		cout << "A donde quieres ir (Digita el ID o -1 para salir)" << endl;
		int nextRoom;
		cin >> nextRoom;
		if (nextRoom == -1) {
			playing = false;
			cout << "Gracias por jugar" << endl;
			break;
		}
		if (nextRoom >= 0 && nextRoom < 3 && paths[roomactually][nextRoom] == 1) {
			roomactually = nextRoom;
			cout << "Te mueves de sala" << endl;
			if (roomactually == 2) {
				if (search(inventory, 50) == false) {
					cout << "\n[EVENTO] Encuentras una 'Llave Dorada' antigua en el cofre." << endl;
					cout << "Guardando item con ID [50] en tu inventario BST...\n" << endl;
					inventory = insert(inventory, 50);
				}
				else {
					cout << "\nEl cofre de la sala ya esta vacio. Ya tienes la 'Llave Dorada'.\n" << endl;
				}
			}
		}
		else {
			cout << "Intenta otra ruta" << endl;
		}
	}

	return 0;
}