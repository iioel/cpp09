/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:01:19 by ycornamu          #+#    #+#             */
/*   Updated: 2023/07/13 13:41:59 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>

int main(int ac, char **av)
{
	if (ac <= 2)
	{
		std::cerr << "Error: please give at least 2 postitive integers or more." << std::endl;
		return (1);
	}
	PmergeMe pm;
	for (int i = 1; i < ac; i++)
	{
		for (int j = 0; av[i][j]; j++)
		{
			if (!std::isdigit(av[i][j]))
			{
				std::cerr << "Error: please give only postitive integers." << std::endl;
				return (1);
			}
		}
		if (std::atof(av[i]) > INT_MAX)
		{
			std::cerr << "Error: number too high." << std::endl;
			return (1);
		}
		pm.push_back(std::atoi(av[i]));
	}

	pm.sort();
	
	return (0);
} 
