/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:59:44 by cmakario          #+#    #+#             */
/*   Updated: 2025/05/11 15:15:47 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream> // std::cerr, std::cout


int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "❌ Error: Wrong amoung of arguments given." << std::endl;
		std::cout << "Usage: ./btc <filename>" << std::endl;
		return 1;
	}

	BitcoinExchange btc;
	if (!btc.loadDatabase("data.csv")) {									// had to be hardcoded...
		std::cerr << "❌ Error: \"data.csv\" file cannot be opened." << std::endl;
		return 1;
	}

	btc.processInput(argv[1]);
	
	std::cout << "✅ File processed successfully." << std::endl;
	return 0;
}

//  if i wanted to use the database file as an argument, i would have to change the code in the main function
/* int main(int argc, char **argv) {
    if (argc != 2 && argc != 3) {
        std::cerr << "Usage: ./btc <input_file> [database_file]" << std::endl;
        return 1;
    }

    std::string dbFile = (argc == 3) ? argv[2] : "data.csv";
    
    BitcoinExchange btc;
    if (!btc.loadDatabase(dbFile))
        return 1;

    btc.processInput(argv[1]);
    return 0;
}
 */