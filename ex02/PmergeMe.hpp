/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:09:36 by ycornamu          #+#    #+#             */
/*   Updated: 2023/07/11 17:09:40 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <list>
# include <utility>

// Create a class that inherits from List and that we can use the push_back() and insert() methods

class PmergeMe : public std::vector<int>
{
	public:
		// Inherit from std::list<int>

		void sort();
		
	private:
		// Stuff to do here
		std::list< std::pair<int, int> >	_pairs;
		int									_straggler;
		std::vector< int > 					_sorted;
		std::vector< int >					_pending;

		void createPairs();
		void sortPairs();
		int swapPair(int &a, int &b);
		void binaryInsertion(int value);
};


#endif
