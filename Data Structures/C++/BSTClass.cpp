#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#define GAP 10
using namespace std;

class Node {
	public:
	int value;
	Node *left, *right;

	Node() {
		value = 0;
		left = NULL;
		right = NULL;
	}

	Node(int value) {
		value = value;
		left = NULL;
		right = NULL;
	}
};

class BST {
	public:
	Node *root;

	BST() {
		root = NULL;
	}
	/*Returns true if the root of a Node is Empty*/
	bool isEmpty() {
		if(root == NULL) return true;
		else return false;
	}
	/*Inserts a Node*/
	void insert(Node *node) {
		if(root == NULL) {
			root = node;
			std::cout << "Inserted node to root" << endl << "\n";
		}
		else {
			Node *rt = root;

			while(rt != NULL) {
				if(rt->value == node->value) {
					std::cout << "Duplicate Value, enter a different one bro" << endl << "\n";
					//No Duplicate values allowed
					return;
				}
				else if((rt->value < node->value) && (rt->right == NULL)){
					rt->right = node;
					std::cout << "Inserted the node to the right child" << endl << "\n";
					break;
				}
				else if(rt->value < node->value) {
					rt = rt->right;
					std::cout << "Shfted Node to the Right" << endl << "\n";
					//The right child of RT is not null, we need to shift right
				}
				else if((node->value < rt->value) && (rt->left == NULL)){
					rt->left = node;
					std::cout << "Inserted the node to the left child" << endl << "\n";
					break;
				}
				else if(node->value < rt->value) {
					rt = rt->left;
					std::cout << "Shfted Node to the Left" << endl << "\n";
					//The left child of RT is not null, we need to shift left
				}
				else {
					//I guess this is just a defensive statement but there's really no need for it ever
					std::cout << "Some invalid error type of situation happened while Inserting I guess.." << endl << "\n";
				}
			}
		}
	}
	/*Find the Node with the Minimum Value in the BST*/
	Node *minNode(Node *node) {
		Node *curr = node;
		while (curr->left != NULL) {
		curr = curr->left;
		}
		return curr;
	}
	/*Deleting a Node from a BST*/
	Node *deleteNode(Node *rt, int value) {
		if (rt == NULL) return NULL;
		else if (value > rt->value) rt->right = deleteNode(rt->right, value);
		else if (value < rt->value) rt->left = deleteNode(rt->left, value);
		else {
			if (rt->left == NULL) {
				Node *n = rt->right;
				delete rt;
				return n;
			} else if (rt->right == NULL) {
				Node *n = rt->left;
				delete rt;
				return n;
			} else {
				Node *n = minNode(rt->right);
				rt->value = n->value;
				rt->right = deleteNode(rt->right, n->value);
			}
   		}
    return rt;
  }
	/*Returns a Pointer to a Node*/ //NON RECURSIVE WAY JUST PICK WHICHEVER YOU WANT - If you can fix the Segmentation Faults caused by the recursive method then go ahead 
	Node *search(int value) {
		if(root == NULL) return root;
		else {
			Node *rt = root;
			while(rt != NULL) {
				//If it's the root value then return root
				if(value == rt->value) return rt;
				//If its less than the root value then look in the Left Node
				else if(value < rt->value) {
					rt = rt->left;
				//If its greater than the root value then look in the Right Node
				} else if(value > rt->value) {
					rt = rt->right;
				} else {
					//I guess this is just a defensive statement but there's really no need for it ever
					std::cout << "Some invalid error type of situation happened while Searching I guess.." << endl << "\n";
				}
			}
			//Couldn't Find the value we were looking for - return NULL
			return NULL;
		}
	}
	/*Returns a Pointer to a Node*/ //Found a recursive way to search afterwards my b bro BUT for some reason was giving segmentation FAULTS
	Node *Search(Node *rt, int value) {
		if(rt->value == value || rt == NULL) return rt;
		else if(value > rt->value) return Search(rt->right, value);
		else if(value < rt->value) return Search(rt->left, value);
		else std::cout << "Some invalid error type of situation happened while Searching I guess.." << endl << "\n";
	}
	/*Preorder Printing of the BST - Root/Left/Right*/
	void preorder(Node *n) {
		if(n == NULL) return;
		//Print the Node's value
		std::cout << n->value << " ";
		//Recursive call to the Left of each Node
		preorder(n->left);
		//Recursive call to the Right of each Node
		preorder(n->right);
	}
	/*Preorder Printing of the BST - Left/Right/Root*/
	void postorder(Node *n) {
		if(n == NULL) return;
		//Recursive call to the Left of each Node
		postorder(n->left);
		//Recursive call to the Right of each Node
		postorder(n->right);
		//Print the Node's value
		std::cout << n->value << " ";
	}
	/*Inorder Printing of the BST - Left/Root/Right*/
	void inorder(Node *n) {
		if(n == NULL) return;
		//Recursive call to the Left of each Node
		inorder(n->left);
		//Print the Node's value
		std::cout << n->value << " ";
		//Recursive call to the Right of each Node
		inorder(n->right);
	}
	/*Print a 2D (Shifted 90 degrees) version of the Tree*/
	void printTree(Node *r, int distance) {
		if(r == NULL) return;
		//Spastd::cing out the levels correctly
		distance += GAP;
		//Recursive call to the Right Child
		printTree(r->right, distance);
		std::cout << endl;
		//Print the required amount of spaces
		for(int i = GAP; i < distance; i++) {
			std::cout << " ";
		}
		//Print value of Node
		std::cout << r->value << "\n";
		//Recursive call to the Left Child
		printTree(r->left, distance);
	}
};

int getChoice() {
	int choice = 0;
	std::cin >> std::setw(1) >> choice;
	//Error Checking
	while(!std::cin.good()) {
		//Report the Error
		std::cout << "ERROR: Faulty Input! Try again..." << endl  << "\n";
		//Clear the Stream of any Bad Input
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		//Get the Input from User again
		std::cout << "Enter a Valid Input: ";
		std::cin >> choice;
	}
	//Clear the Stream of any Bad Input
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	return choice;
}

/*Menu for the Print Tree Options Selection*/
void printMenu(BST bst) {
	std::cout << "Option 4 selected" << endl;
	int choice;
	while(choice != 5) {
		std::cout << "Choose how you want to Print your BST (1-5):" << endl << "Select '0' to Exit" << endl << "\n" << "PRINTING OPTIONS" << endl;
		std::cout << "0. Exit the Application to be Executed" << endl;
		std::cout << "1. Preorder" << endl;
		std::cout << "2. Postorder" << endl;
		std::cout << "3. Inorder" << endl;
		std::cout << "4. Graphical Representation" << endl;
		std::cout << "5. Return to previous MENU" << endl  << "\n";
		choice = getChoice();
		std::cout << "\n";
		switch(choice) {
			case 0:
				std::cout << "Option 0 selected" << endl;
				std::cout << "Exiting...(The Application to be Executed)" << endl << "\n";
				exit(0);
			case 1:
				std::cout << "Printing BST..." << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				std::cout << "Preorder: ";
				bst.preorder(bst.root);
				std::cout << endl  << "\n";
				break;
			case 2:
				std::cout << "Printing BST..." << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				std::cout << "Postorder: ";
				bst.postorder(bst.root);
				std::cout << endl  << "\n";
				break;
			case 3:
				std::cout << "Printing BST..." << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				std::cout << "Inorder:  ";
				bst.inorder(bst.root);
				std::cout << endl  << "\n";
				break;
			case 4:
				std::cout << "Printing BST..." << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				std::cout << "2D 90 degree Shifted Graphical Representation:" << endl;
				bst.printTree(bst.root, 5);
				std::cout << "\n";
				break;
			case 5:
				std::cout << "Returning to previous MENU..." << endl  << "\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				break;
			default:
				std::cout << "Choose a Valid Option!!" << endl << "\n";
				break;
		}
	}
}
/*Main Display Menu*/
void mainMenu() {
	/*Create the BST object*/
	BST bst;
	//value = value of the node to be inserted, option = option chosen from Menu for operation
	int value, option;

	while(option != 5) {
		std::cout << "Select a choice from the Menu (1-5):" << endl << "\n" << "MENU OPTIONS" << endl;
		std::cout << "1. Insert a Node" << endl;
		std::cout << "2. Search for a Node" << endl;
		std::cout << "3. Delete a Node" << endl;
		//std::cout << "4. Clear Screen" << endl;
		std::cout << "4. Print BST" << endl;
		std::cout << "5. Exit the Application to be Executed" << endl << "\n";

		option = getChoice();
		std::cout << "\n";
		//Create a Node
		Node *node = new Node();

		switch(option) {
			case 1:
				std::cout << "Option 1 selected" << endl;
				std::cout << "Enter a value to Insert: ";
				//std::cin >> value;
				value = getChoice();
				std::cout << "\n";
				//Store the value into the Node
				node->value = value;
				std::cout << "Inserting... " << endl << value << " into BST" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				//Insert a Node into the BST
				bst.insert(node);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				break;
			case 2:
				std::cout << "Option 2 selected" << endl;
				std::cout << "Enter a value to Search: ";
				//std::cin >> value;
				value = getChoice();
				std::cout << "\n";
				std::cout << "Searching..." << endl << "Looking for the value "<< value << " in the BST" << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				//Search for the Value in the Tree
				//node = bst.Search(bst.root, value);
				node = bst.search(value);
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				if(node != NULL) std::cout << "The value " << value << " exists in the Tree" << endl << "\n";
				else std::cout << value <<" DOES NOT exist in the Tree currently" << endl << "\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				break;
			case 3:
				std::cout << "Option 3 selected" << endl;
				std::cout << "Enter a value to Delete: ";
				//std::cin >> value;
				value = getChoice();
				std::cout << "\n";
				node = bst.search(value);
				if(node != NULL) {
					std::cout << "Deleting..." << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					std::cout << "Binary Search Tree before Deleting element " << value << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					bst.printTree(bst.root, 5);
					std::cout << "\n";
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					bst.deleteNode(bst.root, value);
					std::cout << "The value " << value << " was Deleted from the BST" << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
					std::cout << "Binary Search Tree after Deleting element " << value << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
					bst.printTree(bst.root, 5);
					std::cout << "\n";
				} else std::cout << "The value " << value << " DOES NOT exist in the Tree" << endl << "\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
				break;
				/* I couldnt get the Clearing Screen to work so might as well just delete this bro
			case 4:
				std::cout << "Option 4 selected" << endl;
				std::cout << "Clearing Screen" << endl;
				system("cls");
				break;
				*/
			case 4:			
				printMenu(bst);
				break;
			case 5:
				std::cout << "Option 5 selected" << endl;
				std::cout << "Exiting...(The Application to be Executed)" << endl << "\n";
				exit(0);
			default:
				std::cout << "Choose a Valid Option!!" << endl << "\n";
		}
	}
}
int main()
{ 
	mainMenu();	
	return 0;
}