//Nicholas Deniz
//CS-300
//Project Two Course Planner
//ProjectTwo.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>  //for isspace and toupper

using namespace std;

//string helpers
//trim before/after spaces
string Trim(const string& s) {
	size_t start = 0;
	//start at non space
	while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) start++;

	size_t end = s.size();
	//move back over spaces
	while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) end--;

	//substring between start and end
	return s.substr(start, end - start);
}

//Makes an uppercase copy to compare course numbers
string ToUpper(const string& s) {
	string out = s;
	for (size_t i = 0; i < out.size(); ++i) {
		out[i] = static_cast<char>(toupper(static_cast<unsigned char>(out[i])));
	}
	return out;
}

//split csv line by commas
vector<string> SplitCSV(const string& line) {
	vector<string> parts;
	string token;
	stringstream ss(line);
	//read the tokens seperated by commas
	while (getline(ss, token, ',')) {
		parts.push_back(Trim(token)); //storing trim token
	}
	return parts;
}

//Course holds record from csv; number, name, and zero or more prerequisites
struct Course {
	string number; 
	string name;
	vector<string> prerequisites;
};

//node in BST stores course and left/right child pointers
struct Node {
	Course data;
	Node* left;
	Node* right;

	//constructor starts with null children
	Node(const Course& c) : data(c), left(NULL), right(NULL) {

	}
};

//BST Functions
//Create node with the correct Course
Node* CreateNode(const Course& c) {
	return new Node(c);
}

//insert a Course into BST, order by course number with should be alphanumeric
//if number already exits then replace the stored Course data
//return root pointer
Node* BST_Insert(Node* root, const Course& c) {
	if (root == NULL) { //if empty place here
		return CreateNode(c);
	}
	if (c.number < root->data.number) { //go left when less than
		root->left = BST_Insert(root->left, c);
	} else if (c.number > root->data.number) { //go right if greater than
		root->right = BST_Insert(root->right, c);
	}
	else {
		//if same course number replace
		root->data = c;
	}
	return root;
}

//search for course number in BST using ToUpper
//return pointer to Course if found else NULL
const Course* BST_Search(Node* root, const string& key) {
	string target = ToUpper(key); 
	Node* cur = root;
	while (cur != NULL) {
		if (target == cur->data.number) return &cur->data; //found exact number
		if (target < cur->data.number) cur = cur->left; //search left 
		else cur = cur->right;
	}
	return NULL; //if not found
}

//In order traversal prints nodes in aplanumeric by courseNumber
void BST_InOrderPrint(Node* root) {
	if (root == NULL) return;
	BST_InOrderPrint(root->left); //left
	cout << root->data.number << ", " << root->data.name << endl; //node
	BST_InOrderPrint(root->right); //right
}

//destroy rough post order delete
void DestroyTree(Node* root) {
	if (root == NULL) return;
	DestroyTree(root->left);
	DestroyTree(root->right);
	delete root;
}

//load csv into BST
//open file, read non empty line, split by comma
//build one Course per line, insert into BST
//return true if file opened
bool LoadCoursesIntoBST(const string& filePath, Node*& root) {
	ifstream in(filePath.c_str());
	if (!in.is_open()) {
		cout << "Error: could not open file \"" << filePath << "\"\n";
		return false; 
	}

	string line;
	int lineNo = 0;
	while (getline(in, line)) {
		lineNo++;
		line = Trim(line);
		if (line.empty()) continue; //skip blank line

		vector<string> parts = SplitCSV(line);
		if (parts.size() < 2) { //needs number and name
			cout << "Bad line " << lineNo << ", it needs a courseNumber and name\n";
			continue;
		}

		//Build Course from tokens
		Course c;
		c.number = ToUpper(parts[0]); //uppercase makes ordering consistent
		c.name = parts[1];

		//remaining tokens are prerequisites
		for (size_t i = 2; i < parts.size(); ++i) {
			string p = ToUpper(parts[i]);
			if (!p.empty()) c.prerequisites.push_back(p);
		}

		//Insert into BST
		root = BST_Insert(root, c);
	}
	return true;
}

//print one course, title and prerequisites
void PrintOneCourse_BST(Node* root, const string& target) {
	const Course* c = BST_Search(root, target);
	if (c == NULL) {
		cout << "Course not found." << endl;
		return;
	}

	//print course line
	cout << c->number << ", " << c->name << endl;

	//print prerequisites
	if (c->prerequisites.empty()) {
		cout << "Prerequisites: None" << endl;
	}
	else {
		cout << "Prerequisites: ";
		for (size_t i = 0; i < c->prerequisites.size(); ++i) {
			cout << c->prerequisites[i];
			if (i + 1 < c->prerequisites.size()) cout << ", ";
		}
		cout << endl;
	}
}

//main menu 1, 2, 3, 9
int main() {
	cout << "Welcome to the course planner.\n\n";

	Node* bstRoot = NULL; //start empty
	bool loaded = false; //track if loaded data correctly

	while (true) {
		cout << "  1. Load Data Structure.\n";
		cout << "  2. Print Course List.\n";
		cout << "  3. Print Course.\n";
		cout << "  9. Exit\n\n";
		cout << "What would you like to do? ";

		string choice;
		if (!getline(cin, choice)) break; //end on EOF
		choice = Trim(choice);

		if (choice == "1") {
			//1. Load Data
			cout << "Enter the name of the data file: ";
			string path;
			if (!getline(cin, path)) break;
			path = Trim(path);

			//If already have data clear before reloading
			DestroyTree(bstRoot);
			bstRoot = NULL;

			if (LoadCoursesIntoBST(path, bstRoot)) {
				if (bstRoot != NULL) {
					loaded = true;
					cout << "Completed load\n\n";
				}
				else {
					loaded = false;
					cout << "Courses not loaded as the file was empty.\n\n";
				}
			}
			else {
				loaded = false;
				cout << "Load failed.\n\n";
			}
		}
		else if (choice == "2") {
			//2. Print sorted list in order traversal
			if (!loaded || bstRoot == NULL) {
				cout << "No data loaded\n\n";
			}
			else {
				cout << "Here is a sample schedule:\n\n";
				BST_InOrderPrint(bstRoot); //prints alphanumeric by courseNumber
				cout << endl;  //new line after list
			}
		}
		else if (choice == "3") {
			//3. Print one course
			if (!loaded || bstRoot == NULL) {
				cout << "No data loaded\n\n";
			}
			else {
				cout << "What course do you want to know about? ";
				string code;
				if (!getline(cin, code)) break;
				code = Trim(code);
				PrintOneCourse_BST(bstRoot, code);
				cout << endl;
			}
		}
		else if (choice == "9") {
			//9. Exit
			cout << "Thank you for using the course planner!\n";
			break;
		}
		else {
			//any other input not valid
			cout << choice << " is not a valid option.\n\n";
		}
	}

	//clean up before exit
	DestroyTree(bstRoot);
	return 0;
}