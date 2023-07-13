/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 18:05:29 by ycornamu          #+#    #+#             */
/*   Updated: 2023/07/13 11:42:34 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE
# define BITCOINEXCHANGE

# include <string>
# include <map>

class BitcoinExchange
{
	private:
		std::string	_file;
		std::string _database_file;

		std::map<int, double> _database;

		BitcoinExchange(void);

	public:
		BitcoinExchange(const BitcoinExchange& btce);
		~BitcoinExchange(void);
		BitcoinExchange& operator=(const BitcoinExchange& btce);

		BitcoinExchange(std::string file);
		void run(void);
};

std::map<int, double>	getCsvLines(std::string file, std::string sep);
double * 				findValue(std::map<int, double> data, int date);
bool 					checkDate(int date);

#endif
