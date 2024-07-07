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
		runMergeInsertionSort(_vec);
}















// vectorからPairを作成し、vector_chainを更新
// 大きい数字の下に小さい数字を入れ、vector_chainから小さい数字を削除する
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



std::vector<p_vec> PmergeMe::runMergeInsertionSort(std::vector<p_vec>& vec){
		if ( vec.size() < 2){
			return vec;
		}
		std::cout << "~~~ようこそkaisou = " << _kaisou<< " へ~~~"<< std::endl;
		_kaisou++;
		p_vec amachan;
		amachan.num = -1;
		_amari.push_back(amachan);
		//main_chainを整形、個数を偶数にする



		std::cout << "vector 表示します makePair前" << std::endl;
		for (size_t i = 0; i < vec.size(); i++){
			std::cout << vec[i].num << std::endl;
		}

//  以下では、main_vectorをペアに分けて、一つのvectorにする
		makePair(vec);

		std::cout << "vector 表示します" << std::endl;
		for (size_t i = 0; i < vec.size(); i++){
			std::cout << vec[i].num << std::endl;
		}


		runMergeInsertionSort(vec);

//帰還編
		std::cout << "ようこそ、Welcome!" << std::endl;

// もしmain_chainメンツに子供がいなかったら、(_kaisou == 0で実装できそうだが...)return vec;
//
//
//







		std::vector<p_vec> lay2;
	for (size_t i = 0; i < vec.size() ;i++){
		lay2.push_back(vec[i].p_vecs.back());
		vec[i].p_vecs.pop_back();
	}
//	if(_amari[_kaisou].num != -1){
//		lay2.push_back(_amari[_kaisou]);
//	}
		std::cout << "vector 表示します " << std::endl;
		for (size_t i = 0; i < vec.size(); i++){
			std::cout << vec[i].num << std::endl;
		}


		std::cout << "vector 表示します lay2" << std::endl;
		for (size_t i = 0; i < lay2.size(); i++){
			std::cout << lay2[i].num << std::endl;
		}


		_kaisou--;
		return vec;
		
}
