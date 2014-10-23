#include <iostream>
#include <string>
#include <queue>
#include <cctype>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::queue;
using std::stack;

bool is_operator(const char& operator_to_check)
{
	switch (operator_to_check)
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

bool is_left_parenthesis(const char& character_to_check)
{
	return character_to_check == '(' ? 1 : 0;
}

bool is_right_parenthesis(const char& character_to_check)
{
	return character_to_check == ')' ? 1 : 0;
}

bool a_parenthesis_exists_in_stack(stack<char> operator_stack)
{
	while (!operator_stack.empty())
	{
		if (is_left_parenthesis(operator_stack.top()) || is_right_parenthesis(operator_stack.top()))
		{
			return 1;
		}
		operator_stack.pop();
	}
	return 0;
}

int main()
{
	cout << "Please enter a mathematical expression: " << endl;
	string mathematical_expression;
	getline(cin, mathematical_expression);

	string number;
	queue<string> output_queue;
	stack<char> operator_stack;
	for (const auto& character : mathematical_expression)
	{
		if (isblank(character))
		{
			continue;
		}

		if (isdigit(character))
		{
			number += character;
			continue;
		}
		else if (is_operator(character))
		{
			if (number != "")
			{
				output_queue.push(number);
				number = "";
			}
			while (!operator_stack.empty())
			{
				int precedence_of_character = set_precedence(character);
				int precedence_of_operator_on_top_of_stack = set_precedence(operator_stack.top());
				if ((is_left_associative(character) && precedence_of_character <= precedence_of_operator_on_top_of_stack) || precedence_of_character < precedence_of_operator_on_top_of_stack)
				{
					string top_of_operator_stack(1, operator_stack.top());
					output_queue.push(top_of_operator_stack);
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
				output_queue.push(number);
				number = "";
			}
			operator_stack.push(character);
		}
		else if (is_right_parenthesis(character))
		{
			if (number != "")
			{
				output_queue.push(number);
				number = "";
			}
			while (!is_left_parenthesis(operator_stack.top()))
			{
				string top_of_operator_stack(1, operator_stack.top());
				output_queue.push(top_of_operator_stack);
				operator_stack.pop();
				if (operator_stack.empty())
				{
					cout << "Error: Mismatched parentheses" << endl;
					return 1;
				}
			}
			operator_stack.pop();
		}

		/*cout << endl;*/
		//// Test
		//queue<string> queue_test(output_queue);
		//cout << "Output Queue: ";
		//while (!queue_test.empty())
		//{
		//	cout << queue_test.front() << " ";
		//	queue_test.pop();
		//}
		//cout << endl;

		//stack<char> stack_test(operator_stack);
		//cout << "Operator Stack: ";
		//while (!stack_test.empty())
		//{
		//	cout << stack_test.top() << " ";
		//	stack_test.pop();
		//}
		//cout << endl;
		
	}
	if (number != "")
	{
		output_queue.push(number);
		number = "";
	}

	if (a_parenthesis_exists_in_stack(operator_stack))
	{
		cout << "Error: Mismatched parentheses" << endl;
		return 1;
	}

	while (!output_queue.empty())
	{
		cout << output_queue.front() << " ";
		output_queue.pop();
	}

	while (!operator_stack.empty())
	{
		cout << operator_stack.top() << " ";
		operator_stack.pop();
	}
	cout << endl;

	return 0;
}