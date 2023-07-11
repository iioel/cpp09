/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:10:32 by ycornamu          #+#    #+#             */
/*   Updated: 2023/07/11 17:10:34 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <sys/time.h>

void PmergeMe::sort()
{
	_straggler = -1;

	std::cout << "Before: ";
	for (PmergeMe::iterator it = this->begin(); it != this->end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	createPairs();

	timeval start1, end1;
	gettimeofday(&start1, NULL);
	{ // first container to be used std::list< std::pair<int, int> >
		sortPairs();
		_pairs.sort();
	}
	gettimeofday(&end1, NULL);

	
	for (std::list< std::pair<int, int> >::iterator it = _pairs.begin(); it != _pairs.end(); it++)
	{
		_sorted.push_back(it->first);
	    _pending.push_back(it->second);
	}
	if (_straggler != -1)
		_pending.push_back(_straggler);

	timeval start2, end2;
	gettimeofday(&start2, NULL);
	{ // second container to be used std::vector<int>
		for (std::vector<int>::iterator it = _pending.begin(); it != _pending.end(); it++)
			binaryInsertion(*it);
	}
	gettimeofday(&end2, NULL);

	this->clear();
	for (std::vector<int>::iterator it = _sorted.begin(); it != _sorted.end(); it++)
		this->push_back(*it);
	std::cout << "After: ";
	for (PmergeMe::iterator it = this->begin(); it != this->end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	long long int diff1 = (end1.tv_sec - start1.tv_sec) * 1000000 + (end1.tv_usec - start1.tv_usec);
	long long int diff2 = (end2.tv_sec - start2.tv_sec) * 1000000 + (end2.tv_usec - start2.tv_usec);
	std::cout << "Time for std::list< std::pair<int, int> >: " << diff1 << " us" << std::endl;
	std::cout << "Time for std::vector<int> " << diff2 << " us" << std::endl;
}

void PmergeMe::createPairs()
{
	PmergeMe::iterator it = this->begin();
	while (it != this->end())
	{
		PmergeMe::iterator it2 = it;
		if (++it2 == this->end())
			_straggler = *it;
		else
			_pairs.push_back(std::make_pair(*it, *it2));
		if (it2 != this->end())
			++it;
		++it;
	}
}

void PmergeMe::sortPairs()
{
	for (std::list< std::pair<int, int> >::iterator it = _pairs.begin(); it != _pairs.end(); it++)
		it->first < it->second ? swapPair(it->first, it->second) : 0;
}

int PmergeMe::swapPair(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
	return 0;
}

void PmergeMe::binaryInsertion(int value)
{
	int pos = 0;
	int size = _sorted.size();
	int min = 0;
	int max = size - 1;
	int mid = (min + max) / 2;

	if (size == 0)
	{
		_sorted.push_back(value);
		return;
	}
	else if (value < _sorted.front())
	{
		_sorted.insert(_sorted.begin(), value);
		return;
	}
	else if (value > _sorted.back())
	{
		_sorted.push_back(value);
		return;
	}
	while (min <= max)
	{
		if (value < _sorted[mid])
			max = mid - 1;
		else if (value > _sorted[mid])
			min = mid + 1;
		else
			break;
		mid = (min + max) / 2;
	}
	if (value < _sorted[mid])
		pos = mid;
	else
		pos = mid + 1;
	_sorted.insert(_sorted.begin() + pos, value);
}
