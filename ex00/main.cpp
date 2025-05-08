/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:59:44 by cmakario          #+#    #+#             */
/*   Updated: 2025/05/08 18:09:02 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "❌ Error: Wrong amoung of arguments given." << std::endl;
		std::cout << "Usage: ./btc <filename>" << std::endl;
		return 1;
	}

	BitcoinExchange btc;
	if (!btc.loadDB(argv[1])) {
		std::cerr << "❌ Error: File cannot be opened." << std::endl;
		return 1;
	}

	btc.processInput(argv[1]);
	
	std::cout << "✅ File processed successfully." << std::endl;
	return 0;
}