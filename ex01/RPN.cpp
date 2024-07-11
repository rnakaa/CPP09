#include "RPN.hpp"

RPN::RPN(std::string str):_str(str){}
RPN::~RPN(){}

void RPN::checkStr(){
	if (_str.size() < 1)
		throw std::logic_error("not enogh parameters");
	for (size_t i = 0; i < _str.size(); i++){
		if (!std::isdigit(_str[i]) && _str[i] != '+' && _str[i] != '*' && _str[i] != '/' && _str[i] != '-' && _str [i] != ' ')
			throw std::logic_error("not permit argument");
	}
}

void RPN::strToDeque(){
	for (size_t i = 0, n; i < _str.size(); i = n + 1) {
		n = _str.find_first_of(' ', i);
		if (n == std::string::npos) {
			n = _str.size();
		}
		_deque.push_front(_str.substr(i, n - i));
		if (_deque.front().size() >= 2)
			throw std::logic_error("not correct number");
	}
}

void RPN::calculate(){
	while (_deque.size() != 0){
		std::string arg = _deque.back();
		_deque.pop_back();
		if (!std::isdigit(arg[0])) {
			if (_stack.size() < 2) {
				throw std::logic_error("To calculate using Reverse Polish Notation, the order of operations must be different.");
			} else {
				int a = stoi(_stack.top());
				_stack.pop();
				int b = stoi(_stack.top());
				_stack.pop();
				if (arg[0] == '+'){
					_stack.push(std::to_string(a+b));
				}
				else if (arg[0] == '-'){
					_stack.push(std::to_string(b-a));
				}
				else if (arg[0] == '/'){
					if (a == 0)
						throw std::logic_error("Division by zero is mathematically undefined and must not be performed.");
					_stack.push(std::to_string(b/a));
				}
				else{
					_stack.push(std::to_string(a*b));
				}
			}
		}
		else{
			_stack.push(arg);
		}
	}
	if (_stack.size() != 1)
		throw std::logic_error("Error");
		
	std::cout << _stack.top()<< std::endl;
	
}
