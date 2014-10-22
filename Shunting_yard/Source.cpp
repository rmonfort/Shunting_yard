#include <iostream>
#include <string>
#include <cctype>
#include <queue>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::queue;
using std::stack;

// Checks if string is not empty
bool is_not_empty(const string& string_to_check)
{
	return string_to_check != "";
}

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

int set_precedence(const char& math_operator)
{
	switch (math_operator)
	{
	case '^':
		return 4;
		break;
	case '*':
		return 3;
		break;
	case '/':
		return 3;
		break;
	case '+':
		return 2;
		break;
	case '-':
		return 2;
		break;
	default:
		return 0;
		break;
	}
}



int main(){
	cout << "Please enter an mathematical expression:" << endl;
	string mathematical_expression;
	getline(cin, mathematical_expression);

	string number;
	queue<string>  output_queue_in_RPN;
	stack<char> operator_stack;

	for (const auto& character : mathematical_expression)
	{
		if (isdigit(character))
		{
			number += character;
		}
		else
		{
			if (is_not_empty(number))
			{
				output_queue_in_RPN.push(number);
				number = "";
			}
			if (is_operator(character))
			{
				if (operator_stack.empty())
				{
					operator_stack.push(character);
				}
				else
				{
					int precedence_of_character = set_precedence(character);
					int precedence_of_operator_on_top_of_stack = set_precedence(operator_stack.top());
					while (precedence_of_character <= precedence_of_operator_on_top_of_stack)
					{
						string temp(1, operator_stack.top());
						operator_stack.pop();
						output_queue_in_RPN.push(temp);
						if (operator_stack.empty())
						{
							break;
						}
						precedence_of_operator_on_top_of_stack = set_precedence(operator_stack.top());
					}
					operator_stack.push(character);
				}
				
			}
		}
	}
	if (is_not_empty(number))
	{
		output_queue_in_RPN.push(number);
		number = "";
	}

	// Print Queue
	while (!output_queue_in_RPN.empty())
	{
		cout << output_queue_in_RPN.front() << " ";
		output_queue_in_RPN.pop();
	}

	// Print Stack
	while (!operator_stack.empty())
	{
		cout << operator_stack.top() << " ";
		operator_stack.pop();
	}
	cout << endl;
	return 0;
}