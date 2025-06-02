/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 01:07:59 by cmakario          #+#    #+#             */
/*   Updated: 2025/06/03 00:19:20 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


int main(int argc, char** argv) {
	try {
		// Create Ford-Johnson sorting algorithm instance!
		PmergeMe sorter;
		
		// Parse input
		sorter.parseInput(argc, argv);
		
		// Sort and compare performance
		sorter.sortAndCompare();
		
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}
