#include <iostream>
#include "RPN.hpp"

int main(int argc, char ** argv){
	if (argc != 2){
		std::cerr << "ERROR: Not collect number of inputs" << std::endl;
		return 1;
	}
	RPN rpn(argv[1]);
	try{
		rpn.checkStr();
		rpn.strToDeque();
		rpn.calculate();

	}
	catch(std::logic_error & e){
		std::cerr << e.what() << std::endl;
	}

}
