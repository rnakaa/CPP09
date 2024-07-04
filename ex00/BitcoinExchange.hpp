#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <deque>

#define CSV_FILE "data.csv"
#define FIRST_INPUT_LINE "date|value"
#define FIRST_CSV_LINE "date,exchange_rate"

class BitcoinExchange {
	public:
		//constructor
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		~BitcoinExchange();
		BitcoinExchange& operator=(const BitcoinExchange& other);



		//error
		static void printError(const std::string& error_message);

		//check
		static bool canOpenFiles(const char *arg_file);

		//add
		void addCSVToMap();
		void addInputToDeque(const char *file_name);

		//output
		void outputBitcoinExchange();
	private:
		bool checkValidDate(const std::string& date_key, const std::string& ex_rate_value);
		bool checkValidExRate(const std::string& value, double& ex_num);
		std::map<std::string, double>::iterator findClosestDate(const std::string& date_key);
		void processInputEntry(const std::string& key, const std::string& value);
		std::map<std::string, double> _data_map;
		std::deque<std::pair<std::string, std::string> > _input_deq;
};

#endif
