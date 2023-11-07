/*
* Brian Cook
* CST-201 1pm
* Micharl Sarlo
* 11/8/2022
* My Own Work
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct BST {
public:
	struct Node {
	public:
		string data;
		struct Node* left;
		struct Node* right;

		Node() {
			data = "";
			left = NULL;
			right = NULL;
		}

		Node(string key) {
			data = key;
			left = NULL;
			right = NULL;
		}
	};

	// Create a root node for each tree
	Node* root = new Node();

	// Return the primary root for the tree
	Node* returnRoot() {
		return root;
	}

	// O(n) -- displays all elements in the tree
	void display(Node* head) {
		if (head != NULL) {
			display(head->left);
			cout << head->data << " : ";
			display(head->right);
		}
	}

	// Inserts element in order to tree given a tree head & data
	// O(logn)
	struct Node* insert(Node* head, string data) {
		if (head == NULL) {
			struct Node* temp = new(struct Node);
			temp->data = data;
			temp->left = NULL;
			temp->right = NULL;
			return temp;
		}
		else {
			if (data < head->data) {
				head->left = insert(head->left, data);
			}
			else {
				head->right = insert(head->right, data);
			}
			return head;
		}
	}
	// O(logn)
	string findMinVal(Node* root) {
		string minval = root->data;
		if (root->left == NULL) {
			return root->data;
		}
		findMinVal(root->left);
	}

	// Removes element from tree given a tree head & data
	// O(logn)
	struct Node* remove(Node* head, string key) {

		if (head == NULL) {
			cout << "Nothing to delete" << endl;
			return head;
		}

		if (head->data == key) {
			if (head->right == NULL) {
				head = head->left;
			}
			else if (head->left == NULL) {
				head = head->right;
			}
			else if (head->right == NULL && head->left == NULL) {
				head = NULL;
			}
			else if (head->right != NULL && head->left != NULL) {

				string newKey = findMinVal(head->right);;
				head->data = newKey;
				remove(head->right, newKey);
			}
			return head;
		}

		if (head->data > key) {
			head->left = remove(head->left, key);
		}
		else {
			head->right = remove(head->right, key);
		}

		return head;

	}
	// Counter for how many items we look at in the tree to find an item
	int searchCt = 0;
	// search a tree top down by passing a root or head and a key O(logn)
	struct Node* search(Node* head, string key) {

		searchCt++;

		if (head == NULL) {
			cout << "\n\n" << key << " not found in the dataset\n";
			searchCt = 0;
		}
		else if (head->data == key) {
			cout << "\n\nKey '" << key << "' found after looking at " << searchCt << " items.\n";
			searchCt = 0;
		}
		if (key > head->data) {
			search(head->right, key);
		}
		else if (key < head->data) {
			search(head->left, key);
		}
		return head;
	}
};

int main() {

	ifstream textIn("TextIn.txt");
	if (!textIn) {
		cout << "File not found";
		exit(10);
	}

	BST tree;

	string str;
	while (textIn >> str) {
		cout << str << endl;
		tree.insert(tree.returnRoot(), str);
	}

	tree.display(tree.returnRoot());

	string input;

	while (true) {
		cout << "\nEnter string to search for or (-1) to quit:  ";
		cin >> input;
		if (input == "-1") {
			break;
		}
		tree.search(tree.returnRoot()->right, input);
	}

	while (true) {
		cout << "\nEnter string to remove or (-1) to quit:  ";
		cin >> input;
		if (input == "-1") {
			break;
		}

		cout << "\n\nBefore Remove:\n";
		tree.display(tree.returnRoot());
		cout << "\nRemoving: " << input << "\n";

		cout << "\n\nAfter Remove:\n";
		tree.remove(tree.returnRoot(), input);
		tree.display(tree.returnRoot());
	}




	return 0;
}