/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:21:22 by cmakario          #+#    #+#             */
/*   Updated: 2025/06/03 23:33:23 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>		// std::vector
# include <deque>		// std::deque
# include <string>		// std::string, std::stoi ,std::stol
# include <limits>		// std::numeric_limits<int>::max()

class PmergeMe {
private:
	std::vector<int> _vectorData;
	std::deque<int> _dequeData;

	// Jacobsthal sequence generator
	static int getJacobsthal(int n);
	static std::vector<int> generateJacobsthalSequence(int size);

public:
	// Orthodox Canonical Form
	PmergeMe(); 											// Default constructor
	PmergeMe(const PmergeMe& other); 						// Copy constructor
	PmergeMe& operator=(const PmergeMe& other);				// Assignment operator
	~PmergeMe();											// Destructor

	// Main interface
	void parseInput(int argc, char** argv);
	void sortAndCompare();

	// Vector sorting functions
	void sortVector();
	std::vector<int> fordJohnsonVector(std::vector<int>& data);

	// Deque sorting functions
	void sortDeque();
	std::deque<int> fordJohnsonDeque(std::deque<int>& data);

	// Utility functions
	void validateInput(const std::string& str);
};

#endif // PMERGEME_HPP
