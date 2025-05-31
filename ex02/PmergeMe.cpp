/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PMergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:31:27 by cmakario          #+#    #+#             */
/*   Updated: 2025/06/01 01:35:51 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PMergeMe.hpp"

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

