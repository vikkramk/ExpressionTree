/*Implementation of an Expression Tree
* Converts infix to postfix notation using Shunting Yard Algorithm
* Inputs into an expression tree
* Read out tree as infix, prefix, or
* Enter a line with spaces between tokens
*/

#include <iostream>
#include <cctype>
#include <cstddef>
#include <cstring>

using namespace std;

struct TreeNode {
  string* value;
  TreeNode* left;
  TreeNode* right;
};

class TreeStack {
private:
  TreeNode* stack[80];
  int stackpos;
public:
  TreeStack() { stackpos = 0; }
  void push(TreeNode* tn) { stack[++stackpos] = tn; }
  TreeNode* peek() { return stack[stackpos]; }
  TreeNode* pop() { return stack[stackpos--]; }
};

class StringStack {
private:
  string* stack[80];
  int stackpos;
public:
  StringStack() {stackpos = 0;}
  void push(string* tn) { stack[++stackpos] = tn; }
  string* peek() { return stack[stackpos]; }
  string* pop() { if (stackpos == 0) return NULL; return stack[stackpos--]; }
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

int main() {
  StringStack opstack;
  StringStack tokens;
  string* input = new string();

  cin >> *input;
  tokens.push(input);
  while (cin.rdbuf( )->in_avail( )) {
    input = new string();
    cin >> *input;
    tokens.push(input);
  }

  while (tokens.peek() != NULL) {
    string* token = tokens.pop();

    //Print numbers
		if (isdigit(token->at(0))) {
			std::cout << token << std::flush;
		}
		//Deal with an operator
		else if (opPrecedence(token->at(0))!=0) {
			//Print all opstack on stack with a higher precedence
			while (opPrecedence(opstack.peek()->at(0)) > opPrecedence(token->at(0))) {
				std::cout << opstack.pop() << std::flush;
			}
			//Push this operator
			opstack.push(token);
		}
		//Push if a left paren
		if (token->at(0) == '(') {
			opstack.push(token);
		}
		//Deal with right paren
		if (token->at(0) == ')') {
			//Pop all opstack until the left paren
			while (opstack.peek()->at(0) != '(')
				std::cout << opstack.pop() << std::flush;
			//Dispose of left paren
			opstack.pop();
		}

		//Space the tokens
		std::cout << " " << std::flush;
	}

	//Print rest of the opstack of stack
	while (opstack.peek() != '\0') {
		std::cout << opstack.pop() << " " << std::flush;
	}

  return 0;

}
