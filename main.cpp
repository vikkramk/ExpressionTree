/*Implementation of an Expression Tree
* Converts infix to postfix notation using Shunting Yard Algorithm
* Inputs into an expression tree
* Read out tree as infix, prefix, or
* Enter a line with spaces between infix
*/

#include <iostream>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <vector>

using namespace std;

struct TreeNode {
	TreeNode(string* value) {
		this->value = value;
		left = NULL;
		right = NULL;
	}
	
  string* value;
  TreeNode* left;
  TreeNode* right;
};

//Get the precedence for an operator from a lookup table
int opPrecedence(char c) {
	char operators[256] = {0};

	if (c > 256)
		return 0;

	operators['+'] = 1;
	operators['-'] = 1;
	operators['*'] = 2;
	operators['/'] = 2;
	operators['^'] = 3;

	return operators[c];
}

//Print an expression tree in prefix form
void printprefix(TreeNode* parent) {
	cout << *(parent->value) << " " << flush;
	if (parent->left != NULL)
		printprefix(parent->left);
	if (parent->right != NULL)
		printprefix(parent->right);
}

//Print an expression tree in infix form
void printinfix(TreeNode* parent) {
	cout << "(" << flush;
	if (parent->left != NULL)
		printinfix(parent->left);
	cout << *(parent->value) << flush;
	if (parent->right != NULL)
		printinfix(parent->right);
	cout << ")" << flush;
}

//Print an expression tree in postfix form
void printpostfix(TreeNode* parent) {
	if (parent->left != NULL)
		printpostfix(parent->left);
	if (parent->right != NULL)
		printpostfix(parent->right);
	cout << *(parent->value) << " " << flush;
}

int main() {
  vector<string*> opstack;	//Operative stack for shunting yard
  vector<string*> infix;	//Infix tokens
	vector<string*> postfix; //Postfix tokens
	vector<TreeNode*> tstack;	//Stack of trees for building expression tree
	TreeNode* exptree;	//Root of expression tree
  string input;	//Input from user
	int i; //Reused counter

	cout << "Enter infix expression with spaces between infix: " << flush;
  getline(cin, input);
	
	i = 0;
  while (i < input.length()) {
    string* token = new string();
    int j = i;
		while (input[j] != ' ' && j < input.length())
			j++;
		token = new string(input, i, j-i);
		infix.push_back(token);
		i = j + 1;
  }
	
	
  for (vector<string*>::iterator it = infix.begin(); it != infix.end(); ++it) {

    //Print numbers
		if (isdigit((*it)->at(0))) {
			postfix.push_back(*it);
		}
		//Deal with an operator
		else if (opPrecedence((*it)->at(0))!=0) {
			//Print all opstack on stack with a higher precedence
			while (!opstack.empty() && opPrecedence(opstack.back()->at(0)) > opPrecedence((*it)->at(0))) {
				postfix.push_back(opstack.back());
				opstack.pop_back();
			}
			//Push this operator
			opstack.push_back(*it);
		}
		//Push if a left paren
		if ((*it)->at(0) == '(') {
			opstack.push_back(*it);
		}
		//Deal with right paren
		if ((*it)->at(0) == ')') {
			//Pop all opstack until the left paren
			while (opstack.back()->at(0) != '(') {
				postfix.push_back(opstack.back());
				opstack.pop_back();
			}
			//Dispose of left paren
			opstack.pop_back();
		}
	}

	//Push rest of the ops on stack
	while (!opstack.empty()) {
		postfix.push_back(opstack.back());
		opstack.pop_back();
	}
	
	//Build the tree
	for (vector<string*>::iterator it = postfix.begin(); it != postfix.end(); ++it) {
		if (isdigit((*it)->at(0)))	//Push numbers
			tstack.push_back(new TreeNode(*it));
		else if (opPrecedence((*it)->at(0)) > 0) {	//Make tree from ops
			TreeNode* opnode = new TreeNode(*it);
			opnode->right = tstack.back();	//First is right because reading backwards
			tstack.pop_back();
			opnode->left = tstack.back();
			tstack.pop_back();
			tstack.push_back(opnode);
		}
	}
	
	exptree = tstack.back();
	
	cout << "Enter the form to output the expression as. (1:prefix, 2:infix, 3:postfix): " << flush;
	cin >> input;
	
	if (input == "1") {
		printprefix(exptree);
	}
	else if (input == "2") {
		printinfix(exptree);
	}
	else if (input == "3") {
		printpostfix(exptree);
	}
	else
		cout << "Get a life you idiot" << endl;
	
  return 0;

}
