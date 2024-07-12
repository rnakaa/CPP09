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


long long timeDiff(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
}





void PmergeMe::run(){
	struct timeval start, end;
	std::cout << "Before: " ;
	printVec(_vec);
	gettimeofday(&start, NULL);
	std::vector<p_vec> result = runMergeInsertionSort(_vec);
	gettimeofday(&end, NULL);
	std::cout << "After: " ;
	for (size_t i = 0; i < result.size()-1; i++){
		std::cout << result[i].num << " ";
	}
	std::cout << result[result.size() - 1].num << " " << std::endl;
	long long duration = timeDiff(start, end);
	std::cout << "Time to process a range of " << result.size() << " elements witch std::list : "<< duration << "us" << std::endl;
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
		vec.insert(vec.begin() + pos, value);
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

	vecFairing(vec);
	makePair(vec);

	runMergeInsertionSort(vec);

	std::vector<int> jacoblay = createJacobsthalSequence(static_cast<int>(vec.size()));

	size_t pairsize = vec[0].p_vecs.size();

	if (pairsize >= 1){
		vec.insert(vec.begin(),vec[0].p_vecs.back());
		vec[1].p_vecs.pop_back();
		for (size_t i = 1; i < jacoblay.size(); i++){
			int pos = jacoblay[i] - 1;
			int count = 0;
			for (size_t j = 0; j < vec.size(); j++){
				if (pairsize == vec[j].p_vecs.size())
					count++;
				if (count == pos && vec[j].p_vecs.size() != 0){
					insertSorted(vec, (vec[j].p_vecs).back(), j );
					break;
				}
			}
		}
		for ( size_t i = 0; i < vec.size(); i++){
			if (vec[i].p_vecs.size() == pairsize){
				vec[i].p_vecs.pop_back();
			}
		}
	}

	if(_amari[_kaisou -1].num != -1){
		insertSorted(vec, _amari[_kaisou-1], vec.size());
	}


	_kaisou--;
	return vec;
}

void PmergeMe::runList(){
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::list<p_lst> result = runMergeInsertionSortList(_lst);
	gettimeofday(&end, NULL);
//	for (std::list<p_lst>::iterator it = result.begin(); it != result.end(); ++it) {
//		std::cout << it->num << " ";
//	}
//	std::cout << std::endl;
	long long duration = timeDiff(start, end);
	std::cout << "Time to process a range of " << result.size() << " elements witch std::list : "<< duration << "us" << std::endl;
	std::cout << std::endl;
}

std::list<p_lst> PmergeMe::makePairList(std::list<p_lst>& lst){
	if (lst.size() < 2) return lst;

	for (size_t i = 1; i < lst.size(); i++){
		std::list<p_lst>::iterator current_it = lst.begin();
		std::advance(current_it, i);
		std::list<p_lst>::iterator prev_it = lst.begin();
		std::advance(prev_it, i - 1);

		if (prev_it->num >= current_it->num){
			prev_it->p_lsts.push_back(*current_it);
			current_it = lst.erase(current_it);
		}
		else if (prev_it->num < current_it->num){
			current_it->p_lsts.push_back(*prev_it);
			lst.erase(prev_it);
		}
	}

	return lst;
}

void PmergeMe::listFairing(std::list<p_lst>& lst){
	if (lst.size() % 2){
		_amari_list.pop_back();
		_amari_list.push_back(lst.back());
		lst.pop_back();
	}
}

std::list<int> PmergeMe::createJacobsthalSequenceList(int n) {
	n = n * 2;
	if (n == 0) return std::list<int>();
	if (n == 1) {
		std::list<int> result;
		result.push_back(1);
		return result;
	}

	std::list<int> jacobsthal;
	jacobsthal.push_back(1);
	jacobsthal.push_back(3);
	int next = 3;

	while (jacobsthal.size() < static_cast<size_t>(n)) {
		next = jacobsthal.back() + 2 * *(std::prev(jacobsthal.end(), 2));
		if (next > n) break;
		jacobsthal.push_back(next);
	}

	std::list<int> result;
	result.push_back(1);

	for (std::list<int>::iterator it = std::next(jacobsthal.begin()); it != jacobsthal.end(); ++it) {
		for (int j = *it; j > *std::prev(it); --j) {
			if (j <= n) result.push_back(j);
		}
	}

	n = n / 2;
	for (std::list<int>::iterator it = result.begin(); it != result.end();) {
		if (*it > n) {
			it = result.erase(it);
		} else {
			++it;
		}
	}

	return result;
}

void PmergeMe::insertSortedList(std::list<p_lst>& lst, p_lst value, size_t end) {
	try {
		std::list<p_lst>::iterator it = lst.begin();
		for (size_t i = 0; i < end && it != lst.end(); ++i) {
			it = std::next(it);
		}
		for (; it != lst.begin() && value < *std::prev(it); --it);
		lst.insert(it, value);
	} catch (const std::exception& e) {
		std::cerr << "Error in insertSortedList: " << e.what() << std::endl;
	}
}

std::list<p_lst> PmergeMe::runMergeInsertionSortList(std::list<p_lst>& lst){
	if (lst.size() < 2){
		return lst;
	}
	_kaisou++;
	p_lst amachan;
	amachan.num = -1;
	_amari_list.push_back(amachan);

	listFairing(lst);
//	printList(lst);
	makePairList(lst);

	runMergeInsertionSortList(lst);

	std::vector<int> jacoblay = createJacobsthalSequence(static_cast<int>(lst.size()));

	size_t pairsize = lst.front().p_lsts.size();

	if (pairsize >= 1){
		lst.push_front(lst.front().p_lsts.back());
		(std::next(lst.begin(), 1))->p_lsts.pop_back();
		for (size_t i = 1; i < jacoblay.size(); i++) {
			int pos = jacoblay[i] - 1;
			int count = 0;
			for (size_t j = 0; j < lst.size(); j++){
				std::list<p_lst>::iterator lit = lst.begin();
				std::advance(lit, j);

				if (pairsize == lit->p_lsts.size())
					count++;
				if (count == pos && lit->p_lsts.size() != 0){
					insertSortedList(lst, lit->p_lsts.back(), j);
					break;
				}
			}
		}
		for (size_t j = 0; j < lst.size(); j++){
		std::list<p_lst>::iterator lit = lst.begin();
		std::advance(lit, j);

		if (lit->p_lsts.size() == pairsize){
			lit->p_lsts.pop_back();
		}
	}
	}


//	printList(lst);
//	std::cout << "_amari[_kaisou-1] " << std::next(_amari_list.begin(), _kaisou -1)->num << std::endl;
//	std::cout << "print _amarilist" << std::endl;
//	printList(_amari_list);
	if (_amari_list.size() > static_cast<size_t> (_kaisou - 1)){
		if (std::next(_amari_list.begin(), _kaisou -1)->num != -1){
			insertSortedList(lst, *std::next(_amari_list.begin(), _kaisou-1), lst.size());
		}
	}
//	std::cout << "amari dainyuugo" << std::endl;
//	printList(lst);


_kaisou--;
return lst;
}

void PmergeMe::printList(std::list<p_lst>& lst){
	for (std::list<p_lst>::iterator it = lst.begin(); it != lst.end(); ++it) {
		std::cout << it->num << " ";
	}
	std::cout << std::endl;
}
