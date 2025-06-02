/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:31:27 by cmakario          #+#    #+#             */
/*   Updated: 2025/06/03 01:34:28 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// =================OCF================== //
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) 
	: _vectorData(other._vectorData), _dequeData(other._dequeData) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vectorData = other._vectorData;
		_dequeData = other._dequeData;
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
	if (num <= 0 || num > std::numeric_limits<int>::max()) {
		throw std::invalid_argument("Number out of valid range: " + str);
	}
}

// ================Parse command line arguments ================= //
void PmergeMe::parseInput(int argc, char** argv) {
	if (argc < 2) {
		throw std::invalid_argument("Usage: ./PmergeMe [numbers...]");
	}

	for (int i = 1; i < argc; ++i) {
		std::string arg(argv[i]);

		validateInput(arg);
		int num = std::stoi(arg);

		_vectorData.push_back(num);
		_dequeData.push_back(num);
	}

	// if (_vectorData.empty()) {
	// 	throw std::invalid_argument("No valid numbers provided");
	// }
}

// ===================Sort and Compare ==================== //
void PmergeMe::sortAndCompare() {
	// Initialize time variables
	double vectorTime = 0.0;
	double dequeTime  = 0.0;
	
	// DIsplay initial data
	std::cout << "⏳ Initial Vector: ";
	for (size_t i = 0; i < _vectorData.size() && i <= 20; ++i) {
		std::cout << _vectorData[i] << " ";
	}
	if (_vectorData.size() > 20) {
		std::cout << "[...]";
	}
	std::cout << std::endl;
	
	// Time vector sorting
	auto vecStart = std::chrono::high_resolution_clock::now();
	sortVector();
	auto vecEnd = std::chrono::high_resolution_clock::now();
	vectorTime = std::chrono::duration<double, std::micro>(vecEnd - vecStart).count(); // microseconds
	
	// Time deque sorting
	auto deqStart = std::chrono::high_resolution_clock::now();
	sortDeque();
	auto deqEnd = std::chrono::high_resolution_clock::now();
	dequeTime = std::chrono::duration<double, std::micro>(deqEnd - deqStart).count(); // microseconds
	
	
	// Display sorted sequence
	std::cout << "✅ After: ";
	for (size_t i = 0; i < _vectorData.size() && i <= 20; ++i) {
		std::cout << _vectorData[i] << " ";
	}
	if (_vectorData.size() > 20) {
		std::cout << "[...]";
	}
	std::cout << std::endl;
	
	// Display time taken
	
	std::cout << std::fixed << std::setprecision(6);
	std::cout << "Time to process a range of " << _vectorData.size() 
			<< " elements with std::vector : " << vectorTime/1000 << " ms" << std::endl;
	std::cout << "Time to process a range of " << _dequeData.size() 
			<< " elements with std::deque : " << dequeTime/1000 << " ms" << std::endl;
}

// ===================Sort Vector ==================== //
void PmergeMe::sortVector() {
	_vectorData = fordJohnsonVector(_vectorData);
}

std::vector<int> PmergeMe::fordJohnsonVector(std::vector<int>& data) {
	
	// Base cases
	if (data.size() <= 1) {
		return data;
	}
	if (data.size() == 2) {
		if (data[0] > data[1]) {
			std::swap(data[0], data[1]);
		}
		return data;
	}

	// Step 1: Create pairs and sort them
	std::vector<std::pair<int, int> > pairs;
	bool hasOdd = (data.size() % 2 == 1);
	int oddElement = hasOdd ? data.back() : -1;

	// Create pairs from neighbohr elements
	for (size_t i = 0; i < data.size() - (hasOdd ? 1 : 0); i += 2) {
		int first = data[i];
		int second = data[i + 1];

		// Sort the pair so larger element is first (winner)
		if (first < second) {
			pairs.push_back(std::make_pair(second, first));
		} else {
			pairs.push_back(std::make_pair(first, second));
		}

	}


	// Step 2: Extract winners and pendings and recursively sort them
	std::vector<int> winners;
	std::vector<int> pendings;

	for (const auto& pair : pairs) {
		winners.push_back(pair.first);   // Winner (larger element)
		pendings.push_back(pair.second); // Pending (smaller element)
	}

	// v.2 Step 1: Create pairs and sort them & Step 2: Extract winners and pendings and recursively sort them
/* 	std::vector<int> winners, pendings;
	bool hasOdd = (data.size() % 2 == 1);
	int oddElement = hasOdd ? data.back() : -1;
	// Create pairs from neighbor elements
	for (size_t i = 0; i < data.size() - hasOdd; i += 2) {
	int a = data[i], b = data[i+1];
	// Sort the pair so larger element is first (winner)
		if (a > b) {
			winners.push_back(a);
			pendings.push_back(b);
		} else {
			winners.push_back(b);
			pendings.push_back(a);
		}
	} */

	// Recursively sort winners
	if (winners.size() > 1) {
		winners = fordJohnsonVector(winners);
	}
	
	// Step 3: Create main chain from winners starting with the smallest pending
	std::vector<int> mainChain;

	if (!pendings.empty()) {
		mainChain.push_back(pendings[0]); // First pending is always smallest
	}

	// Add all winners to main chain
	for (int winner : winners) {
		mainChain.push_back(winner);
	}

	// Step 4: Insert remaining pendings using Jacobsthal sequence
	if (pendings.size() > 1) {
		std::vector<int> jacobsthalSeq = generateJacobsthalSequence(pendings.size());
		std::vector<bool> inserted(pendings.size(), false);
		inserted[0] = true; // First pending is already in main chain
	
		// Step 4:Insert pendings according to Jacobsthal order
		for (int jacobIndex : jacobsthalSeq) {
			if (jacobIndex < static_cast<int>(pendings.size()) && !inserted[jacobIndex]) {
				int elementToInsert = pendings[jacobIndex];
				
				// Binary search for insertion position
				auto insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), elementToInsert);
				mainChain.insert(insertPos, elementToInsert);
				inserted[jacobIndex] = true;
				
			}
		}
		
		// Insert any remaining pendings in order
		for (size_t i = 1; i < pendings.size(); ++i) {
			if (!inserted[i]) {
				int elementToInsert = pendings[i];
				auto insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), elementToInsert);
				mainChain.insert(insertPos, elementToInsert);
			}
		}
	}

	// Step 5: Handle odd element if present
	if (hasOdd) {
		auto insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), oddElement);
		mainChain.insert(insertPos, oddElement);
	}
	
	return mainChain;
}

// ===================Deque sort ==================== //
void PmergeMe::sortDeque() {
	_dequeData = fordJohnsonDeque(_dequeData);
}

std::deque<int> PmergeMe::fordJohnsonDeque(std::deque<int>& data) {
	
	// Base cases
	if (data.size() <= 1) {
		return data;
	}
	if (data.size() == 2) {
		if (data[0] > data[1]) {
			std::swap(data[0], data[1]);
		}
		return data;
	}

	// Step 1: Create pairs and sort them
	std::vector<std::pair<int, int> > pairs;
	bool hasOdd = (data.size() % 2 == 1);
	int oddElement = hasOdd ? data.back() : -1;

	// Create pairs from neighbohr elements
	for (size_t i = 0; i < data.size() - (hasOdd ? 1 : 0); i += 2) {
		int first = data[i];
		int second = data[i + 1];

		// Sort the pair so larger element is first (winner)
		if (first < second) {
			pairs.push_back(std::make_pair(second, first));
		} else {
			pairs.push_back(std::make_pair(first, second));
		}
	}

	// Step 2: Extract winners and pendings and recursively sort them
	std::deque<int> winners;
	std::deque<int> pendings;

	for (const auto& pair : pairs) {
		winners.push_back(pair.first);   // Winner (larger element)
		pendings.push_back(pair.second); // Pending (smaller element)
	}

	// Recursively sort winners
	if (winners.size() > 1) {
		winners = fordJohnsonDeque(winners);
	}
	
	// Step 3: Create main chain from winners starting with the smallest pending
	std::deque<int> mainChain;

	if (!pendings.empty()) {
		mainChain.push_back(pendings[0]); // First pending is always smallest
	}

	// Add all winners to main chain
	for (int winner : winners) {
		mainChain.push_back(winner);
	}

	// Step 4: Insert remaining pendings using Jacobsthal sequence
	if (pendings.size() > 1) {
		std::vector<int> jacobsthalSeq = generateJacobsthalSequence(pendings.size());
		std::vector<bool> inserted(pendings.size(), false);
		inserted[0] = true; // First pending is already in main chain

		// Insert pendings according to Jacobsthal order
		for (int jacobIndex : jacobsthalSeq) {
			if (jacobIndex < static_cast<int>(pendings.size()) && !inserted[jacobIndex]) {
				int elementToInsert = pendings[jacobIndex];
			
				// Binary search for insertion position in deque
				auto insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), elementToInsert);
				mainChain.insert(insertPos, elementToInsert);
				inserted[jacobIndex] = true;
			}
		}
	
		// Insert any remaining pendings in order
		for (size_t i = 1; i < pendings.size(); ++i) {
			if (!inserted[i]) {
				int elementToInsert = pendings[i];
				auto insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), elementToInsert);
				mainChain.insert(insertPos, elementToInsert);
			}
		}
	}

	// Step 5: Handle odd element if present
	if (hasOdd) {
		auto insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), oddElement);
		mainChain.insert(insertPos, oddElement);
	}

	return mainChain;
}
