/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BItcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:49:19 by cmakario          #+#    #+#             */
/*   Updated: 2025/05/11 15:31:52 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream> // std::cerr, std::cout
#include <fstream> // std::ifstream
#include <sstream> // std::istringstream, std::ostringstream
#include <ctime> // std::time, std::localtime


//---------------OCF------------------//
BitcoinExchange::BitcoinExchange() {											// Default constructor
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {					// Copy constructor
	*this = src;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {		// Copy assignment operator
	if (this != &rhs) {
		this->_dataBase = rhs._dataBase;
	}
	return *this;
}
BitcoinExchange::~BitcoinExchange() {											// Destructor
}

// v2.approach
/* BitcoinExchange::BitcoinExchange() = default;
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) = default;
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) = default;
BitcoinExchange::~BitcoinExchange() = default; */
//---------------Methods------------------//

namespace {
	bool isValidDate(const std::string &date) {
		if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
			return false;
		}
		// v2: approach
		int y, m, d;
		char dash1, dash2;
		std::istringstream iss(date);
		if (!(iss >> y >> dash1 >> m >> dash2 >> d) || dash1 != '-' || dash2 != '-' || !iss.eof()) {
			return false;
		}
		if (m < 1 || m > 12 || d < 1 || d > 31) {
			return false;
		}
		if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) {
			return false;
		}
		if (m == 2) {
			bool isLeapyear = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
			if ((isLeapyear && d > 29) || (!isLeapyear && d > 28)) {
				return false;
			}
		}
		// check if the date is before 2009-01-02
		if (y < 2009 || (y == 2009 && m == 1 && d < 2)) {
			std::cerr << "❌ Error: Date => " << date << " is before 2009-01-02! There was NO bitcoin dumpy!" << std::endl;
			return false;
		}
		// check if the date is in the future
		std::time_t t = std::time(nullptr);
		std::tm *now = std::localtime(&t);
		int currY = now->tm_year + 1900;
		int currM = now->tm_mon + 1;
		int currD = now->tm_mday;

		if (y > currY || (y == currY && m > currM) || (y == currY && m == currM && d > currD)) {
			std::cerr << "❌ Error: Date is in the future => " << date  << " Are you wizard🧙 or what ?" << std::endl;
			return false;
		}
		
		return true;
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
			size_t pos;
			value = std::stod(valueStr, &pos);
			if (pos != valueStr.length()) {
				std::cerr << "❌ Error: Invalid character in value. => " << valueStr.substr(pos) << std::endl;
				return false;
			}
			if (value < 0) {
				std::cerr << "❌ Error: Value not a positive number." << std::endl;
				return false;
			} else if (value > 1000) {
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
}

bool BitcoinExchange::loadDatabase(const std::string &filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "❌ Error: exchange rated could not be opened." << std::endl;
		return false;
	}

	std::string line;
	std::getline(file, line);
	if (line != "date,exchange_rate") {
		std::cerr << "❌ Error: Invalid header format in database." << std::endl;
		return false;
	}
	
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string date, valueStr;
		
		if (std::getline(iss, date, ',') && std::getline(iss, valueStr)) {
			try {
				// std::cout << date << " => " << valueStr << std::endl;
				double rate = std::stod(valueStr);
				// std::cout << date << " => " << valueStr << std::endl;q
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
	}
	file.close(); 													// ? do i close it or not? ??
								// ! When it goes out of scope, the destructor is automatically called: ~ifstream() { close(); }
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
			std::cerr << "❌ Error: Invalid input => " << line << std::endl;
			continue;
		}

		std:: string date = line.substr(0, separator);
		std::string valueStr = line.substr(separator + 1);

		std::string whitespaces (" \t\f\v\n\r");
		
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
			// std::cerr << "❌ Error: Invalid date format => " << date << std::endl;
		} else if (!isValidValue(valueStr, value)) {
			// std::cerr << "❌ Error: Invalid value format => " << valueStr << std::endl;
		} else {
			std::string closestDate = findClosestDate(date);
			// std::cout << "Closest date: " << closestDate << " Data: " << _dataBase[closestDate] << std::endl;
			double rate = _dataBase[closestDate];
			std::cout << "\033[32m" << date << " => " << valueStr << " = " << value << " * " 
			<< rate << " = " << "\033[1m" << rate * value << "\033[0m" << std::endl;
		}
	}
	 file.close();
}

std::string BitcoinExchange::findClosestDate(const std::string &date) const {
	std::map<std::string, double>::const_iterator it = _dataBase.lower_bound(date);			// ? check if upper_bound is correct
	if (it == _dataBase.end() || it->first != date) {
		--it;
	}
	return it->first;
}
