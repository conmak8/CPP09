/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:59:44 by cmakario          #+#    #+#             */
/*   Updated: 2025/06/03 22:46:40 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream> // std::cerr, std::cout
#include <limits> // for std::numeric_limits


int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "❌ Error: Wrong amount of arguments given." << std::endl;
		std::cout << "📘 Usage: ./btc <filename>" << std::endl;
		return 1;
	}

	BitcoinExchange btc;

	// ========== Interactive Menu ==========
	int choice = -1;
	while (choice != 1 && choice != 2 && choice != 0) {
		std::cout << "\n📦 Bitcoin Exchange Loader\n";
		std::cout << "1. Load exchange rate database (data.csv)\n";
		std::cout << "2. Skip loading (default rate = 0)\n";
		std::cout << "0. Exit\n";
		std::cout << "Enter your choice: ";

		if (!(std::cin >> choice)) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "❌ Please enter a valid number (0, 1, or 2)." << std::endl;
			choice = -1; // Reset choice to invalid
			continue;
		}

		if (choice == 1) {
			if (!btc.loadDatabase("data.csv")) {
				std::cerr << "❌ Error: \"data.csv\" file cannot be opened." << std::endl;
				return 1;
			}
			std::cout << "✅ Database loaded successfully!\n";
		} else if (choice == 2) {
			std::cout << "⚠️ No database loaded. All exchange rates will default to 0.\n";
		} else if (choice == 0) {
			std::cout << "👋 Exiting program. See you later!\n";
			return 0;
		} else {
			std::cerr << "❌ Invalid choice. Please enter 0, 1, or 2.\n";
			choice = -1;
		}
	}
	// ========== End of Menu ==========

	// std::cout << choice <<"  ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️\n";
	btc.processInput(argv[1]);
	std::cout << "✅ File processed successfully." << std::endl;
	return 0;
}




// int main(int argc, char **argv) {
// 	if (argc != 2) {
// 		std::cerr << "❌ Error: Wrong amoung of arguments given." << std::endl;
// 		std::cout << "Usage: ./btc <filename>" << std::endl;
// 		return 1;
// 	}

// 	BitcoinExchange btc;
// 	if (!btc.loadDatabase("data.csv")) {									// had to be hardcoded...
// 		std::cerr << "❌ Error: \"data.csv\" file cannot be opened." << std::endl;
// 		return 1;
// 	}

// 	btc.processInput(argv[1]);
	
// 	std::cout << "✅ File processed successfully." << std::endl;
// 	return 0;
// }

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

 