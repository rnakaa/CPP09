#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _data_map(), _input_deq() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _data_map(other._data_map), _input_deq(other._input_deq) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		this->_data_map = other._data_map;
		this->_input_deq = other._input_deq;
	}
	return *this;
}


void BitcoinExchange::printError(const std::string& error_message){
	std::cerr << "ERROR: " << error_message << std::endl;
}

bool BitcoinExchange::canOpenFiles(const char * arg_file) {
	std::ifstream input_file(arg_file);
	std::ifstream csv_file(CSV_FILE);

	if (!input_file.is_open()){
		printError("could not open input file");
		return false;
	} else if (!csv_file.is_open()){
		printError("could not open csv file");
		return false;
	}
	return true;
}

bool BitcoinExchange::checkValidDate(const std::string & sdate, const std::string & srate){
	if (srate.empty()){
		return false;
	}
	else if (sdate.size() != 10 || sdate[4] != '-' || sdate[7] != '-'){
		return false;
	}

	for (std::size_t i = 0; i < sdate.size(); i++){
		if ((i != 4 && i != 7) && !std::isdigit(sdate[i])){
			return false;
		}
	}

	int month;
	int day;

	std::stringstream(sdate.substr(5,2)) >> month;
	std::stringstream(sdate.substr(8,2)) >> day;
	if (month < 1 || month > 12 || day < 1 || day > 31 || (month == 2 && day > 29) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 31))
		return false;

	return true;
}

bool BitcoinExchange::checkValidExRate(const std::string& value, double& n) {
	std::stringstream ss(value);
	ss >> n;
	if (ss.fail() || n < 0 || n > 1000) {
		printError("bad input => " + value);
		return false;
	}
	return true;
}



void BitcoinExchange::addCSVToMap(){
	std::ifstream csv_file(CSV_FILE);
	std::string line;

	while (std::getline(csv_file, line)) {
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());

		if (line == FIRST_CSV_LINE){
			continue;
		}

		std::size_t pos = line.find(',');
		if (pos != std::string::npos) {
			std::string sdate = line.substr(0, pos);
			std::string srate = line.substr(pos + 1);
			
			std::istringstream iss(srate);
			double rate;
			iss >> rate;
			if (iss.fail() || !checkValidDate(sdate,srate) || _data_map.find(sdate) != _data_map.end()){
				printError("bad input");
				throw std::exception();
			} else {
				_data_map[sdate] = rate;
			}
		}
	}
}

void BitcoinExchange::addInputToDeque(const char *file){
	std::ifstream ifile(file);
	std::string line;
	std::getline(ifile, line);
	while (std::getline(ifile, line)) {
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());

		if (line == FIRST_INPUT_LINE){
			continue;
		}

		std::size_t pos = line.find('|');

		std::string sdate;
		std::string srate;
		if (pos != std::string::npos) {
			sdate = line.substr(0, pos);
			srate = line.substr(pos + 1);
		} else {
			sdate = line;
			srate = "";
		}



		_input_deq.push_back(std::make_pair(sdate, srate));
	}
	ifile.close();
}

std::map<std::string, double>::iterator BitcoinExchange::findClosestDate(const std::string & key) {
	std::map<std::string, double>::iterator near = _data_map.end();

	for (std::map<std::string, double>::iterator it = _data_map.begin(); it != _data_map.end(); ++it) {
		if (it->first > key) {
			break;
		}
		near = it;
	}

	if (near == _data_map.end() || near->first > key){
		throw std::out_of_range("cannot find the closest past date");
	}
	return near;
}



void BitcoinExchange::processInputEntry(const std::string& key, const std::string& value){
	if (!checkValidDate(key, value)){
		printError("bad input");
		return ;
	}

	double n;
	if (!checkValidExRate(value, n)){
		return;
	}
	try {
		std::map<std::string, double>::iterator it= findClosestDate(key);
		std::cout << key << " => " << value << " = " << n * it->second << std::endl;
	} catch (const std::exception & e){
		printError("bad input =>" + key);
	}
}


void BitcoinExchange::outputBitcoinExchange() {
	for (std::deque<std::pair<std::string, std::string> >::const_iterator it = _input_deq.begin(); it != _input_deq.end(); ++it) {
		processInputEntry(it->first, it->second);
	}
}
