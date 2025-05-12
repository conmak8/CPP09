/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmakario <cmakario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:19:36 by cmakario          #+#    #+#             */
/*   Updated: 2025/05/12 11:10:55 by cmakario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>


class RPN {
private:
	bool isOperator(char c);
	void applyOperator(char op, std::stack<int> &s);
public:
//-------------OCF-----------------//
	RPN();
	RPN(const RPN& src);
	RPN &operator=(const RPN& rhs);
	~RPN();
//---------Member functions-------//
	int evaluate(const std::string &input);
};

#endif // ! RPN_HPP
