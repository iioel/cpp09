/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:58:27 by ycornamu          #+#    #+#             */
/*   Updated: 2023/07/13 11:45:22 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

BitcoinExchange::BitcoinExchange(void) 
{
	;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& btce) : _file(btce._file), _database_file("data.csv"), _database(btce._database)
{
	;
}

BitcoinExchange::~BitcoinExchange(void)
{
	;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& btce)
{
	this->_file 			= btce._file;
	this->_database_file 	= btce._database_file;
	this->_database 		= btce._database;
	return *this;
}

BitcoinExchange::BitcoinExchange(std::string file) : _file(file), _database_file("data.csv")
{
	_database = getCsvLines(_database_file, ",");
}

void BitcoinExchange::run(void)
{
	std::ifstream f;

	f.open(_file.c_str(), std::ios::in);
	if (f.fail())
	{
		std::cerr << "Error: could not open file: " << _file << std::endl;
		exit (1);
	}

	std::string line, date_str, price_str;
	int			date, day, month, year;
	double		price;

	while (std::getline(f, line))
	{
		if (line.find("date") != std::string::npos)
			continue;
		if ((date_str = line.substr(0, line.find(" | "))).length() != 10)
		{
			std::cerr << "Error: date bad input => " << date_str << std::endl;
			continue;
		}
		day = std::atoi(date_str.substr(8, 2).c_str());
		month = std::atoi(date_str.substr(5, 2).c_str());
		year = std::atoi(date_str.substr(0, 4).c_str());

		if ((price_str = line.substr(line.find(" | ") + 3, line.length())).empty())
		{
			std::cerr << "Error: price bad input => " << price_str << std::endl;
			continue;
		}
		price = std::atof(price_str.c_str());
		if (price > 2147483647)
		{
			std::cerr << "Error: too large number." << std::endl;
			continue;
		}
		if (price < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		
		date = year*10000 + month*100 + day;
		if (! checkDate(date))
		{
			std::cerr << "Error: date not valid => " << date_str << std::endl;
			continue;
		}
		if (findValue(_database, date) == NULL)
		{
			std::cerr << "Error: no date not found => " << date_str << std::endl;
			continue;
		}
		std::cout << *findValue(_database, date) * price << std::endl;
	}
}

std::map<int, double> getCsvLines(std::string file, std::string sep)
{
	std::map<int, double> data;
	std::ifstream datafile;

	std::string	line, date_str, price_str;
	int		date, day, month, year;

	datafile.open(file.c_str(), std::ios::in);
	if (datafile.fail())
	{
		std::cerr << "Error: could not open file: " << file << std::endl;
		exit (1);
	}

	while (std::getline(datafile, line))
	{
		date_str = line.substr(0, line.find(sep));
		if (date_str == "date")
			continue;
		day = std::atoi(date_str.substr(8, 2).c_str());
		month = std::atoi(date_str.substr(5, 2).c_str());
		year = std::atoi(date_str.substr(0, 4).c_str());
		date = year*10000 + month*100 + day;
		if (! checkDate(date))
		{
			std::cerr << "Error: date not valid => " << date_str << std::endl;
			continue;
		}
		price_str = line.substr(line.find(sep) + 1, line.length());
		data[date] = std::atof(price_str.c_str());
	}
	return data;
}

double* findValue(std::map<int, double> data, int date)
{
	std::map<int, double>::iterator it = data.begin();
	while (it != data.end())
	{
		if (it->first > date)
			break;
		it++;
	}
	if (it->first != date && it != data.begin())
		it--;
	else if (it->first != date && it == data.begin())
		return NULL;
	return &(it->second);
}

bool checkDate(int date)
{
	int day, month, year;

	day = date % 100;
	month = (date / 100) % 100;
	year = date / 10000;
	if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 0 && day <= 31)
		return true;
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 0 && day <= 30)
		return true;
	else if (month == 2 && day > 0 && day <= 28)
		return true;
	else if (month == 2 && day == 29 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
		return true;
	else
	return false;
}
