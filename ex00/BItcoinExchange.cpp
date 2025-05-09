/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BItcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:49:19 by cmakario          #+#    #+#             */
/*   Updated: 2025/05/09 21:25:37 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>


//---------------OCF------------------//
BitcoinExchange::BitcoinExchange() {
	// Default constructor
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
	// Copy constructor
	*this = src;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
	// Copy assignment operator
	if (this != &rhs) {
		this->_dataBase = rhs._dataBase;
	}
	return *this;
}
BitcoinExchange::~BitcoinExchange() {
	// Destructor
}
//---------------Methods------------------//




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

void BitcoinExchange::processInput(const std::string &filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "❌ Error: exchange rated could not be opened." << std::endl;
		return ;
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line)) {
		if (line.empty())
			continue;

		size_t separator = line.find('|');
		if (separator == std::string::npos) {
			std::cerr << "❌ Error: Invalid input" << line << std::endl;
			continue;
		}

		std:: string date = line.substr(0, separator);
		std::string valueStr = line.substr(separator + 1);

		std::string whitespaces (" \t\f\v\n\r");
		
		std::size_t found = date.find_first_not_of(whitespaces);
		// Trim leading  & trailing whitespace from date
		date.erase(0, date.find_first_not_of(whitespaces));
		date.erase(date.find_last_not_of(whitespaces) + 1);
		// Trim leading & trailing whitespace from valueStr
		valueStr.erase(0, valueStr.find_first_not_of(whitespaces));
		valueStr.erase(valueStr.find_last_not_of(whitespaces) + 1);
		
		if (date.empty()) {	
			std::cerr << "❌ Error: Date format in missing." << std::endl;
			date.clear();
		}
		if (valueStr.empty()) {
			std::cerr << "❌ Error: Value format in missing." << std::endl;
			valueStr.clear();
		}
		/* Validation of date and valueStr formats */
		double value = 0;
		if (!isValidDate(date)) {
			std::cerr << "❌ Error: Invalid date format => " << date << std::endl;
		} else if (!isValidValue(valueStr, value)) {
			std::cerr << "❌ Error: Invalid value format => " << valueStr << std::endl;
		} else {
			std::string closestDate = findClosestDate(date);
				}
			}
}
		
bool isValidDate(const std::string &date) {
	if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
		return false;
	}
	
	int year = std::stoi(date.substr(0, 4));
	int month = std::stoi(date.substr(5, 2));
	int day = std::stoi(date.substr(8, 2));

	if (month < 1 || month > 12 || day < 1 || day > 31) {
		return false;
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
		return false;
	}
	if (month == 2) {
		bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if ((isLeapYear && day > 29) || (!isLeapYear && day > 28)) {
			return false;
		}
	}
	return true;

	// v2: approach
/* 	int y, m, d;
	char dash1, dash2;
	std::istringstream iss(date);
	if (!(iss >> y >> dash1 >> m >> dash2 >> d) || dash1 != '-' || dash2 != '-') {
		return false;
	}
	if (m < 1 || m > 12 || d < 1 || d > 31) {
		return false;
	}
	return true; */
}

bool isValidValue(const std::string &valueStr, double &value) {
	// Check if the value is a valid number and within the range
	// v1: approach
/* 	if (valueStr.empty()) {
		return false;
	}
	
	for (char c : valueStr) {
		if (!std::isdigit(c) && c != '.' && c != '-') {
			return false;
		}
	} */
	// v2: approach Catch any exception with that
	if (valueStr.empty()) {
		return false;
	}
	try {
		value = std::stod(valueStr);
		if (value < 0) {
			std::cerr << "❌ Error: Value not a positive number." << std::endl;
			return false;
		} else if (value > 5000) {
			std::cerr << "❌ Error: Value is too high." << std::endl;
			return false;
		}
	} catch (const std::invalid_argument&) {
		std::cerr << "❌ Error: Invalid value." << std::endl;
		return false;
	} catch (const std::out_of_range&) {
		std::cerr << "❌ Error: Value out of range." << std::endl;
		return false;
	} catch (...) {
		std::cerr << "❌ Error: Unknown error." << std::endl;
		return false;
	}
	return true;
}
