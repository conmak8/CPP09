/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:19:29 by cmakario          #+#    #+#             */
/*   Updated: 2025/05/12 11:42:58 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>


int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "❌ Usage: " << argv[0] << " <expression>" << std::endl;
		return 1;
	}
	try {
		RPN rpn;
		int result = rpn.evaluate(argv[1]);
		std::cout << "✅ Result: " << result << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "❌ Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
