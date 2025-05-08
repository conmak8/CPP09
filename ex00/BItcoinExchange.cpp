/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BItcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:49:19 by cmakario          #+#    #+#             */
/*   Updated: 2025/05/09 01:03:10 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>

bool BitcoinExchange::loadDatabase(const std::string &filename) {
	
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "❌ Error: exchange rated could not be opened." << std::endl;
		return false;
	}

	std::string line;
	std::getline(file, line);							// ? could or should i skip the header? how?
	if (line != "date,exchange_rate") {					// i check if the header is correct at first ?need it?
		std::cerr << "❌ Error: Invalid header format in database." << std::endl;
		return false;
	}
	
	// v1:	approach
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date, valueStr;
		
		if (line.empty()) {
			std::cerr << "❌ Error: Empty line found in database." << std::endl;
			return false;
		}
		if (!(iss >> date >> valueStr)) {												// ? will understand the comma?
			std::cerr << "❌ Error: Invalid data format in database." << std::endl;
			return false;
		}
		double rate = std::stod(valueStr);
		if (rate < 0) {
			std::cerr << "❌ Error: Negative exchange rate found." << std::endl;
			return false;
		}
		_dataBase[date] = rate;
	}

	// v2:	approach
/* 	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date, valueStr;
		
		if (std::getline(iss, date, ',') && std::getline(iss, valueStr)) {
			try {
				double rate = std::stod(valueStr);
				if (rate < 0) {
					std::cerr << "❌ Error: Negative exchange rate found." << std::endl;
					return false;
				}
				_dataBase[date] = rate;
			} catch (...) {
				std::cerr << "❌ Error: Invalid data format in database." << std::endl;
				return false;
			}	
		}
	} */
	
	file.close(); 													// ? do i close it or not?
	return true;
}