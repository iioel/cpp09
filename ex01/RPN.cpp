/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:25:17 by ycornamu          #+#    #+#             */
/*   Updated: 2023/07/11 15:25:23 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <stack>
#include <iostream>
#include "RPN.hpp"

void RPNCalc(std::string const &rpn)
{
	std::stack<int> st;

	for (size_t i = 0; i < rpn.length(); i++)
	{
		if(rpn[i] == ' ')
			continue;
		else if (rpn[i] <= '9' && rpn[i] >= '0')
		{
			st.push(rpn[i] - '0');
			continue;
		}
		else if (rpn[i] == '+' || rpn[i] == '-' || rpn[i] == '/' || rpn[i] == '*')
		{
			if (st.size() < 2)
			{
				std::cout << "Error: not enough values" << std::endl;
				return;
			}
			int b = st.top(); st.pop();
			int a = st.top(); st.pop();
			if (rpn[i] == '+')
				st.push(a + b);
			else if (rpn[i] == '-')
				st.push(a - b);
			else if (rpn[i] == '/')
				st.push(a / b);
			else if (rpn[i] == '*')
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
