/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:21:22 by cmakario          #+#    #+#             */
/*   Updated: 2025/06/01 19:57:05 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <iostream>
# include <sstream>
# include <chrono>
# include <algorithm>
# include <iomanip>

class PmergeMe {
private:
	std::vector<int> _vectorData;
	std::deque<int> _dequeData;
	bool _debugMode;

	// Jacobsthal sequence generator
	static int getJacobsthal(int n);
	static std::vector<int> generateJacobsthalSequence(int size);

	// Debug helpers
	void printDebug(const std::string& message) const;
	template<typename Container>
	void printContainer(const std::string& label, const Container& container) const;

public:
	// Orthodox Canonical Form
	PmergeMe(); 											// Default constructor
	PmergeMe(const PmergeMe& other); 						// Copy constructor
	PmergeMe& operator=(const PmergeMe& other);				// Assignment operator
	~PmergeMe();											// Destructor

	// Main interface
	void parseInput(int argc, char** argv);
	void sortAndCompare();
	void setDebugMode(bool debug);

	// Vector sorting functions (separate file)
	void sortVector();
	std::vector<int> fordJohnsonVector(std::vector<int>& data);

	// Utility functions
	void validateInput(const std::string& str);
	
};


#endif // PMERGEME_HPP