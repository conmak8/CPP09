/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:19:32 by cmakario          #+#    #+#             */
/*   Updated: 2025/05/13 10:43:14 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream> // for std::istringstream
#include <stdexcept> // for std::invalid_argument and std::runtime_error
#include <cctype> // for std::isdigit
// #include <iostream> // for debugging


bool RPN::isOperator(char c) const {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void RPN::applyOperator(char op, std::stack<int> &stack) {
	if (stack.size() < 2) {
		throw std::runtime_error("❌ Error: Not enough operands on the stack.");
	}
	
	int right = stack.top();
	stack.pop();
	int left = stack.top();
	stack.pop();
	int result = 0;
	
	switch (op) {
		case '+':
			result = left + right;
			break;
		case '-':
			result = left - right;
			break;
		case '*':
			result = left * right;
			break;
		case '/':
			if (right == 0) {
				throw std::runtime_error("❌ Error: Division by zero.");
			}
			result = left / right;
			break;
		default:
			throw std::invalid_argument("❌ Error: Unknown operator");
		}
		
	stack.push(result);
}


// v.1
/* int RPN::evaluate(const std::string &input) {
	std::stack<int> stack;
	for (char c : input) {
		if (std::isspace(c)) {
			continue;
		}
		if (std::isdigit(c)) {
			stack.push(c - '0');
		} else if (isOperator(c)) {
			applyOperator(c, stack);
		} else {
			throw std::invalid_argument("Invalid character in expression");
		}
		// std::cout << "❌ " << stack.size() << std::endl;
	}
	if (stack.size() != 1) {
		// std::cout << "❌ Error: " << stack.size() << std::endl;
		throw std::runtime_error("Invalid RPN expression");
	}
	return stack.top();
} */

// v.2 with the use of std::istringstream
/* int RPN::evaluate(const std::string &input) {
	std::stack<int> stack;
	std::istringstream iss(input);
	std::string token;

	while (iss >> token) {
		if (std::isdigit(token[0])) {
			stack.push(std::stoi(token));
		} else if (isOperator(token[0])) {
			applyOperator(token[0], stack);
		} else {
			throw std::invalid_argument("Invalid token in expression");
		}
	}
	if (stack.size() != 1) {
		throw std::runtime_error("Invalid RPN expression");
	}
	return stack.top();
}
 */

// v.2.1
int RPN::evaluate(const std::string &input) {
	if (input.empty())
		throw std::invalid_argument("❌ Error: Expression is empty.");
		
	std::stack<int> stack;
	std::istringstream iss(input);
	std::string token;

	while (iss >> token) {
		if (token.length() == 1 && std::isdigit(token[0])) {
			int num = token[0] - '0';
			stack.push(num);
		} else if (token.length() == 1 && isOperator(token[0])) {
				applyOperator(token[0], stack);
		} else if (std::isdigit(token[0]) && token.length() > 1) {
			throw std::invalid_argument("❌ Error: Multi-digit numbers are not allowed: \"" + token + "\"");
		} else {
			 throw std::invalid_argument("❌ Error: Invalid token: \"" + token + "\"");
		}
	}

	if (stack.size() != 1) {
		throw std::runtime_error("❌ Error: Invalid expression (stack size != 1)");
	}
	return stack.top();
}

