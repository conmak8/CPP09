/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:31:27 by cmakario          #+#    #+#             */
/*   Updated: 2025/06/01 14:21:21 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// =================OCF================== //
PmergeMe::PmergeMe() : _debugMode(false) {}

PmergeMe::PmergeMe(const PmergeMe& other) 
	: _vectorData(other._vectorData), _dequeData(other._dequeData), _debugMode(other._debugMode) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vectorData = other._vectorData;
		_dequeData = other._dequeData;
		_debugMode = other._debugMode;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// ====================Jacobsthat Nummer Calculation ==================== //
int PmergeMe::getJacobsthal(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;

	// J(n) = J(n-1) + 2*J(n-2)
	int prev2 = 0, prev1 = 1;
	for (int i = 2; i <= n; ++i) {
		int current = prev1 + 2 * prev2;
		prev2 = prev1;
		prev1 = current;
	}
	return prev1;
}

std::vector<int> PmergeMe::generateJacobsthalSequence(int size) {
	std::vector<int> sequence;

	// Generate Jacobsthal numbers less than size
	for (int i = 1; getJacobsthal(i) < size; ++i) {
		sequence.push_back(getJacobsthal(i));
	}

	return sequence;
}

// ====================Debug Helper Functions==================== //
void PmergeMe::printDebug(const std::string& message) const {
	if (_debugMode) {
		std::cout << "🔧 " << message << std::endl;
	}
}

void PmergeMe::setDebugMode(bool debug) {
	_debugMode = debug;
}


// ===================Parse command argumentss==================== //
void PmergeMe::validateInput(const std:: string& str) {
	if (str.empty()) {
		throw std::invalid_argument("Empty input");
	}

	// check if we have positive integers only
	for (size_t i = 0; i < str.length(); ++i) {
		if (!std::isdigit(str[i])) {
			throw std::invalid_argument("Invalid character in number: " + str);
		}
	}

	// Convert to long and check its rangee
	long num = std::stol(str);
	if (num < 0 || num > std::numeric_limits<int>::max()) {
		throw std::invalid_argument("Number out of valid range: " + str);
	}
}


void PmergeMe::parseInput(int argc, char** argv) {
	if (argc < 2) {
		throw std::invalid_argument("Usage: ./PmergeMe [numbers...] [--debug]");
	}

	for (int i = 1; i < argc; ++i) {
		std::string arg(argv[i]);

		if (arg == "--debug") {
			setDebugMode(true);
			continue;
		}

		validateInput(arg);
		int num = std::stoi(arg);

		_vectorData.push_back(num);
		_dequeData.push_back(num);
	}

	if (_vectorData.empty()) {
		throw std::invalid_argument("No valid numbers provided");
	}

	printDebug("✅ Input parsed successfully!");
	printContainer("Original Vector", _vectorData);
	printContainer("Original Deque", _dequeData);
}
