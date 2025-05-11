/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:31:41 by cmakario          #+#    #+#             */
/*   Updated: 2025/05/10 15:51:41 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map> // std::map
# include <string> // std::string


class BitcoinExchange {
private:
	std::map<std::string, double> _dataBase;
	std::string findClosestDate(const std::string &date) const;
public:
	//---------------OCF------------------//
	BitcoinExchange();										// Default constructor
	BitcoinExchange(const BitcoinExchange &src);			// Copy constructor	
	BitcoinExchange &operator=(const BitcoinExchange &rhs);	// Copy assignment operator
	~BitcoinExchange();										// Destructor
	//---------------Methods------------------//
	bool loadDatabase(const std::string &filename);
	void processInput(const std::string &filename);
};

#endif // !BITCOINEXCHANGE_HPP
