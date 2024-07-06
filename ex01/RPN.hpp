#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <stack>
#include <deque>


class RPN {
	public :
		RPN(std::string str);
		~RPN();
		void checkStr();
		void strToDeque();
		void calculate();
		
	private:
		RPN();
		RPN(RPN const & cp);
		RPN const & operator=(RPN const & cp);
		std::stack <std::string> _stack;
		std::deque <std::string> _deque;
		std::string _str;
		ssize_t _result;
};

#endif
