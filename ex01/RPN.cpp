/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:25:17 by ycornamu          #+#    #+#             */
/*   Updated: 2023/07/13 13:07:28 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include "RPN.hpp"

void RPNCalc(std::string const &rpn)
{
	std::stack<int> st;
	std::istringstream iss(rpn);
	std::string word;

	while(std::getline(iss, word, ' '))
	{
		if (word.length() == 0)
			continue;
		else if (is_number(word))
		{
			if (std::atof(word.c_str()) > INT_MAX)
			{
				std::cout << "Error: number too high." << std::endl;
				return;
			}
			else if (std::atof(word.c_str()) < INT_MIN)
			{
				std::cout << "Error: number too low." << std::endl;
				return;
			}
			st.push(std::stoi(word));
			continue;
		}
		else if (is_operator(word))
		{
			if (st.size() < 2)
			{
				std::cout << "Error: not enough values" << std::endl;
				return;
			}
			int b = st.top(); st.pop();
			int a = st.top(); st.pop();
			if (word == "+")
				st.push(a + b);
			else if (word == "-")
				st.push(a - b);
			else if (word == "/")
			{
				if (b == 0)
				{
					std::cout << "Error: division by 0" << std::endl;
					return;
				}
				else
					st.push(a / b);
			}
			else if (word == "*")
				st.push(a * b);
		}
		else
		{
			std::cout << "Error: invalid character" << std::endl;
			return;
		}
	}
	if (st.size() != 1)
	{
		std::cout << "Error: too many values" << std::endl;
		return;
	}
	std::cout << st.top() << std::endl;
}

bool is_operator(std::string s)
{
	return (s == "+" || s == "-" || s == "*" || s == "/");
}

bool is_number(std::string s)
{
	size_t start = 0;
	if (s[0] == '-' && s.length() > 1)
		start++;
	for (size_t i = start; i < s.length(); i++)
		if (s[i] < '0' || s[i] > '9')
			return false;
	return true;
}
