/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PMergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:31:27 by cmakario          #+#    #+#             */
/*   Updated: 2025/06/01 01:32:24 by cmakario         ###   ########.fr       */
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