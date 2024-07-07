#include "PmergeMe.hpp"
#include <iostream>
#include <stdexcept>

void printVector(const std::vector<unsigned int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void printList(const std::list<unsigned int>& lst) {
    for (std::list<unsigned int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <positive integer sequence>" << std::endl;
		return 1;
	}

	PmergeMe sorter;

	try {

		std::list<unsigned int> lst;
		std::vector<unsigned int> vec;
		sorter.checkArgs(argc,argv);
		sorter.setVectorAndList(argc,argv);
		sorter.run();

//		sorter.createJacobsthalList(lst, 24);//
//		sorter.createJacobsthalVector(vec, 24);//
//		std::cout << "vec";//
//		printVector(vec);//
//		std::cout << "lst";//
//		printList(lst);//
		


	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

