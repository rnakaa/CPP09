#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <ctime>
#include <algorithm>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

typedef struct s_vec {
	long num;
	std::vector<s_vec> p_vecs;
	bool operator<(const s_vec other) const {
		return num < (other).num;
	}
}p_vec;

typedef struct s_lst {
	long num;
	std::list<s_lst> p_lst;
}p_lst;


class PmergeMe {
public:
    PmergeMe();
    ~PmergeMe();


		void checkArgs(const int argc, char **str);

		void setVectorAndList(const int argc,char **argv);

		void createJacobsthalVector(std::vector<unsigned int>& jacobsthal_vec, const size_t max_num);
		void createJacobsthalList(std::list<unsigned int>& lst, const size_t max_num);

		std::vector<p_vec> runMergeInsertionSort(std::vector<p_vec>& vec);
		std::vector<p_vec> makePair(std::vector<p_vec>& vec);
		void vecFairing(std::vector<p_vec>& vec);
		void run();
		void insertSorted(std::vector<p_vec>& vec, p_vec target, size_t t);

		std::vector<int>  createJacobsthalSequence(int n);
		void printVec(std::vector<p_vec> & vec);





private:
		int _kaisou;
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    std::vector<p_vec> _vec;
    std::list<p_lst> _lst;
		std::vector<p_vec> _amari;


    void printFirstSecondLine(const std::string& str);

};

#endif // PMERGEME_HPP
//
