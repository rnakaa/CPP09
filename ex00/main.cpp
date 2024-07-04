#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
		return 1;
	}

	if (!BitcoinExchange::canOpenFiles(argv[1])) {
		return 1;
	}

	BitcoinExchange btcExchange;
	btcExchange.addCSVToMap();
	btcExchange.addInputToDeque(argv[1]);
	btcExchange.outputBitcoinExchange();

	return 0;
}
