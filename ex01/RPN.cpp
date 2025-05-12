/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:19:32 by cmakario          #+#    #+#             */
/*   Updated: 2025/05/12 13:10:14 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>


// v.1
int RPN::evaluate(const std::string &input) {
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
	}
	if (stack.size() != 1) {
		throw std::runtime_error("Invalid RPN expression");
	}
	return stack.top();
}

