#include <iostream>
#include <string>
#include <cctype>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stack;

// Checks if character is an operator
bool is_operator(const char& character_to_check)
{
	switch (character_to_check)
	{
	case '^':
	case '*':
	case '/':
	case '+':
	case '-':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

// Checks if operator is left associative
bool is_left_associative(const char& operator_to_check)
{
	switch (operator_to_check)
	{
	case '*':
	case '/':
	case '+':
	case '-':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

// Returns precedence value of an operator
int set_precedence(const char& operation)
{
	switch (operation)
	{
	case '^':
		return 4;
		break;
	case '*':
	case '/':
		return 3;
		break;
	case '+':
	case '-':
		return 2;
		break;
	default:
		return 0;
		break;
	}
}

// Checks if a character is a left parenthesis
bool is_left_parenthesis(const char& character_to_check)
{
	return character_to_check == '(' ? 1 : 0;
}

// Checks if a character is a right parenthesis
bool is_right_parenthesis(const char& character_to_check)
{
	return character_to_check == ')' ? 1 : 0;
}

// Checks if a parentehsis exists in stack
bool a_parenthesis_exists_in_stack(stack<char> stack_to_check)
{
	while (!stack_to_check.empty())
	{
		if (is_left_parenthesis(stack_to_check.top()) || is_right_parenthesis(stack_to_check.top()))
		{
			return 1;
		}
		stack_to_check.pop();
	}
	return 0;
}

int main()
{
	cout << "Please enter a mathematical expression: " << endl;
	string mathematical_expression;
	getline(cin, mathematical_expression);

	string number;
	stack<char> operator_stack;
	for (const auto& character : mathematical_expression)
	{
		// Skip blank characters
		if (isblank(character))
		{
			continue;
		}

		
		if (isdigit(character)) // If character is a digit, append to number
		{
			number += character;
			continue;
		}
		else if (is_operator(character)) 
		{
			if (number != "") // If number isn't empty, output it
			{
				cout << number << " ";
				number = "";
			}
			while (!operator_stack.empty())
			{
				// Set precedence for character and operator on top of stack
				int precedence_of_character = set_precedence(character); 
				int precedence_of_operator_on_top_of_stack = set_precedence(operator_stack.top());

				// If character is left associative and its precedence is less than or equal to that of the operator on top of the stack
				// Or the character has less precedence than the operator
				// then output the operator and remove it from the stack
				if ((is_left_associative(character) && precedence_of_character <= precedence_of_operator_on_top_of_stack) || precedence_of_character < precedence_of_operator_on_top_of_stack)
				{
					cout << operator_stack.top() << " ";
					operator_stack.pop();
				}
				else
				{
					break;
				}
			}
			operator_stack.push(character);
		}
		else if (is_left_parenthesis(character))
		{
			if (number != "")
			{
				cout << number << " ";
				number = "";
			}
			operator_stack.push(character);
		}
		else if (is_right_parenthesis(character))
		{
			if (number != "")
			{
				cout << number << " ";
				number = "";
			}
			while (!is_left_parenthesis(operator_stack.top())) // Cycle through stack and search for matching parenthesis
			{
				cout << operator_stack.top() << " ";
				operator_stack.pop();
				if (operator_stack.empty()) // If a matching parenthesis isn't found output and error message 
				{
					cout << "Error: Mismatched parentheses" << endl;
					return 1;
				}
			}
			operator_stack.pop();
		}
	}
	if (number != "") 
	{
		cout << number << " ";
		number = "";
	}

	if (a_parenthesis_exists_in_stack(operator_stack)) // Checks stack for mismatched parenthesis
	{
		cout << "Error: Mismatched parentheses" << endl;
		return 1;
	}

	while (!operator_stack.empty())
	{
		cout << operator_stack.top() << " ";
		operator_stack.pop();
	}
	cout << endl;

	return 0;
}