#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
    : _kaisou(0), _vec()
    , _lst(),_amari()
		{
    // std::cout << "Default Constructor Called" << std::endl;
}

PmergeMe::~PmergeMe() {
    // std::cout << "Destructor Called" << std::endl;
}



void PmergeMe::checkArgs(const int argc, char **str) {
    for (int i = 1; i < argc; ++i) {
        for (size_t j = 0; str[i][j]; ++j) {
            if (!std::isdigit(str[i][j]) && str[i][j] != ' ') {
                throw std::logic_error("not correct argument");
            }
        }
    }
}


void PmergeMe::setVectorAndList(const int argc, char **argv) {
	for (int i = 1; i < argc; ++i) {
		const char* arg = argv[i];
		char* end;
		long num = std::strtol(arg, &end, 10);

		if (end == arg || *end != '\0' || num <= 0) {
			throw std::invalid_argument("Invalid input: " + std::string(arg));
		}

		if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min()) {
			throw std::out_of_range("out of range");
		}

		p_vec vec;
		vec.num = num;
		_vec.push_back(vec);

		p_lst lst;
		lst.num = num;
		_lst.push_back(lst);
	}
}


void PmergeMe::createJacobsthalVector(std::vector<unsigned int>& vec, const size_t max_num) {
	unsigned int j_prev = 0, j_curr = 1;

	vec.push_back(j_prev);

	if (max_num == 0) {
		return;
	}

	while (true) {
		vec.push_back(j_curr);
		if (j_curr >= max_num) {
			break;
		}
		unsigned int j_next = j_curr + 2 * j_prev;
		j_prev = j_curr;
		j_curr = j_next;
	}
	if (vec.back() > max_num) {
		vec.pop_back();
		vec.push_back(max_num);
	}
}


void PmergeMe::createJacobsthalList(std::list<unsigned int>& lst, const size_t max_num) {
	unsigned int j_prev = 0, j_curr = 1;

	lst.push_back(j_prev);

	if (max_num == 0) {
		return;
	}

	while (true) {
		lst.push_back(j_curr);
		if (j_curr >= max_num) {
			break;
		}
		unsigned int j_next = j_curr + 2 * j_prev;
		j_prev = j_curr;
		j_curr = j_next;
	}
	if (lst.back() > max_num) {
		lst.pop_back();
		lst.push_back(max_num);
	}
}




void PmergeMe::run(){
		std::vector<p_vec> result = runMergeInsertionSort(_vec);
		for (size_t i = 0; i < result.size()-1; i++){
			std::cout << result[i].num << " ";
		}
		std::cout << result[result.size() - 1].num << " " << std::endl;
}















std::vector<p_vec> PmergeMe::makePair(std::vector<p_vec>& vec){
		for ( size_t i = 1; i < vec.size(); i++){
			if (vec[i-1].num>=vec[i].num){
				vec[i-1].p_vecs.push_back(vec[i]);
				vec.erase(vec.begin() + i);
			}
			else if (vec[i-1].num<vec[i].num){
				vec[i].p_vecs.push_back(vec[i-1]);
				vec.erase(vec.begin() + i - 1);
			}
		}
		return vec;
	
}



void PmergeMe::vecFairing(std::vector<p_vec>& vec){
		if (vec.size() % 2){
			_amari.pop_back();
			_amari.push_back(vec.back());
			vec.pop_back();
		}
}

std::vector<int>  PmergeMe::createJacobsthalSequence(int n) {
		n = n*2;
    if (n == 0) return std::vector<int>();
    if (n == 1) {
        std::vector<int> result;
        result.push_back(1);
        return result;
    }

    std::vector<int> jacobsthal;
    jacobsthal.push_back(1);
    jacobsthal.push_back(3);
    int next = 3;

    while (jacobsthal.size() < static_cast<size_t>(n)) {
        next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
        if (next > n) break;
        jacobsthal.push_back(next);
    }

    std::vector<int> result;
    result.push_back(1);

    for (size_t i = 1; i < jacobsthal.size(); ++i) {
        for (int j = jacobsthal[i]; j > jacobsthal[i-1]; --j) {
            if (j <= n) result.push_back(j);
        }
    }

		n = n/2;
		for (size_t i = 0; i < result.size();++i){
			if ( result[i] > n){
				result.erase(result.begin() + i);
				i--;
			}
		}

    return result;
}

size_t binarySearchInsertPosition(const std::vector<p_vec>& vec, const p_vec& value, size_t end) {
    size_t left = 0;
    size_t right = end;
		std::cout << "binary Search " << value.num << std::endl;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (vec[mid].num < value.num) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}


void PmergeMe::insertSorted(std::vector<p_vec>& vec, p_vec value, size_t end) {
    try {
        if (end > vec.size()) {
            end = vec.size();
        }
        size_t pos = binarySearchInsertPosition(vec, value, end);
				std::cout << "insert number in fun" << value.num << std::endl;
        vec.insert(vec.begin() + pos, value);
				printVec(vec);
    } catch (const std::exception& e) {
        std::cerr << "Error in insertSorted: " << e.what() << std::endl;
    }
}

void PmergeMe::printVec(std::vector<p_vec> & vec){
		if (vec.size() == 0){
			return;
		}
		for (size_t i = 0; i < vec.size() - 1; i++){
			std::cout << vec[i].num << " ";
		}
		std::cout << vec[vec.size()-1].num << std::endl;
}

std::vector<p_vec> PmergeMe::runMergeInsertionSort(std::vector<p_vec>& vec){
		if ( vec.size() < 2){
			return vec;
		}
		_kaisou++;
		p_vec amachan;
		amachan.num = -1;
		_amari.push_back(amachan);
		//main_chainを整形、個数を偶数にする



		//std::cout << "vector 表示します makePair前" << std::endl;
		//for (size_t i = 0; i < vec.size(); i++){
		//	std::cout << vec[i].num << " ";
		//}
//		std::cout << std::endl;
		vecFairing(vec);
		makePair(vec);

		//std::cout << "vector 表示します" << std::endl;
		//for (size_t i = 0; i < vec.size(); i++){
		//	std::cout << vec[i].num  << " ";
		//}
		//std::cout << std::endl;
		//std::cout << std::endl;
		//for (size_t i = 0; i < vec.size() ; i++){
		//	std::cout << std::endl << vec[i].num << std::endl;

		//	if (vec[i].p_vecs.size())
		//		printVec(vec[i].p_vecs);	
		//	for (size_t j = 0; j < vec[i].p_vecs.size() ; j++){
		//		std::cout << std::endl << vec[i].p_vecs[j].num << std::endl;
		//		if (vec[i].p_vecs[j].p_vecs.size())
		//			printVec(vec[i].p_vecs[j].p_vecs);	
		//	}
		//	std::cout <<"-------------" << std::endl;
		//}


		runMergeInsertionSort(vec);

//�編
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << BLUE << "ようこそ、Welcome!"  << RESET<< std::endl;
		printVec(vec);



		for (size_t i = 0; i < vec.size() ; i++){
			std::cout << std::endl << vec[i].num << std::endl;

			if (vec[i].p_vecs.size())
				printVec(vec[i].p_vecs);	
			for (size_t j = 0; j < vec[i].p_vecs.size() ; j++){
				std::cout << std::endl << vec[i].p_vecs[j].num << std::endl;
				if (vec[i].p_vecs[j].p_vecs.size())
					printVec(vec[i].p_vecs[j].p_vecs);	
			}
			std::cout <<"-------------" << std::endl;
		}






		std::vector<int> jacoblay = createJacobsthalSequence(static_cast<int>(vec.size()));

		size_t pairsize = vec[0].p_vecs.size();
		std::vector<int> stock;

		if (vec[0].p_vecs.size() >= 1){
			vec.insert(vec.begin(),vec[0].p_vecs.back()); vec[1].p_vecs.pop_back();
			std::cout << "jacoblay size = " << jacoblay.size() << std::endl;
			for (size_t i = 1; i < jacoblay.size(); i++){
				//std::cout  << std::endl << "i = " << i << std::endl;
				printVec(vec);
				int pos = jacoblay[i] - 1;
				int count = 0;
				//				std::cout << "pos " << jacoblay[i] - 1 << std::endl;
				for (size_t j = 0; j < vec.size(); j++){
					//std::cout << "if (pairsize == vec[" << j << "].p_vecs.size())" << std::endl;
					//	std::cout << "vec[j] " << vec[j].num << std::endl;
					//	std::cout << "vec[j].size() " << vec[j].p_vecs.size() << std::endl;
					if (pairsize == vec[j].p_vecs.size())
						count++;
					//	std::cout << "count " << count << std::endl;
					if (count == pos && vec[j].p_vecs.size() != 0){
						std::cout << "jacoblay[i] " << jacoblay[i] << std::endl;
						std::cout << "j " << j << std::endl;
						std::cout << "vec[j] "<< vec[j].num << std::endl;
						std::cout << "insert number "<< (vec[j].p_vecs).back().num << std::endl<<std::endl;


						//		std::cout << "vec[" << j << "].p_vecs" << std::endl;
						//		printVec(vec[j].p_vecs);
						insertSorted(vec, (vec[j].p_vecs).back(), j );

						for (size_t i = 0; i < vec.size() ; i++){
							std::cout << std::endl << vec[i].num << std::endl;

							if (vec[i].p_vecs.size())
								printVec(vec[i].p_vecs);	
							for (size_t j = 0; j < vec[i].p_vecs.size() ; j++){
								std::cout << std::endl << vec[i].p_vecs[j].num << std::endl;
								if (vec[i].p_vecs[j].p_vecs.size())
									printVec(vec[i].p_vecs[j].p_vecs);	
							}
							std::cout <<"-------------" << std::endl;
						}
						std::cout << "inserted" << std::endl;
						printVec(vec);
						//		std::cout << "koko4" << std::endl;
						//printVec(vec);
						//vec[j].p_vecs.pop_back();
						break;
					}
				}
			}
			for ( size_t i = 0; i < vec.size(); i++){
				if (vec[i].p_vecs.size() == pairsize){
					vec[i].p_vecs.pop_back();
				}
			}
			//		std::cout << "sortdone"<< std::endl;
		}





		if(_amari[_kaisou-1].num != -1){
			insertSorted(vec, _amari[_kaisou-1], vec.size());
		}

//		printVec(vec);


//		for (size_t i = 0; i < vec.size() ; i++){
//			std::cout << std::endl << vec[i].num << std::endl;
//			if (vec[i].p_vecs.size())
//				printVec(vec[i].p_vecs);	
//		}
//
		for (size_t i = 0; i < vec.size() ; i++){
			std::cout << std::endl << vec[i].num << std::endl;

			if (vec[i].p_vecs.size())
				printVec(vec[i].p_vecs);	
			for (size_t j = 0; j < vec[i].p_vecs.size() ; j++){
				std::cout << std::endl << vec[i].p_vecs[j].num << std::endl;
				if (vec[i].p_vecs[j].p_vecs.size())
					printVec(vec[i].p_vecs[j].p_vecs);	
			}
			std::cout <<"-------------" << std::endl;
		}




		_kaisou--;
		return vec;
}
