#include <boost/process.hpp>
#include <string>
#include <iostream>
#include <Windows.h>
#include "demofuncs"
#include "functions.h"

int binaryOperation(int a, int b) {
	if (a == 0 || b == 0) {
		return 0;
	}
	if (a == MININT || b == MININT) {
		return MININT;
	}
	return a * b;
}

bool checkCancelation() {
	return GetKeyState('C') && GetKeyState(VK_CONTROL);
}



void manager(char* process) {
	namespace bp = boost::process;
	bp::opstream f_in, g_in;
	bp::ipstream f_out, g_out;
	bp::group func;
	bp::child f(process, "f_func", bp::std_in < f_in,
		bp::std_out > f_out , bp::std_err = stderr, func);
	bp::child g(process, "g_func", bp::std_in < g_in,
		bp::std_out > g_out, bp::std_err = stderr, func);
	int test_num;
	std::cout << "Enter test case number or -1 to exit\n";
	std::cout << "0 f finishes before g with non-zero value\n";
	std::cout << "1 g finishes before f with non-zero value\n";
	std::cout << "2 f finishes with zero value, g hangs\n";
	std::cout << "3 g finishes with zero value, f hangs\n";
	std::cout << "4 f finishes with non-zero value, g hangs\n";
	std::cout << "5 g finishes with non-zero value, f hangs\n";
	std::cin >> test_num;
	f_in << test_num << std::endl;
	g_in << test_num << std::endl;

	int f_res = -1,
		g_res = -1;
	int a = MININT;
	
	while (f.running() && g.running()) {
		if (checkCancelation()) {
			func.terminate();
			std::cout << "f was terminated" << std::endl;
			std::cout << "g was terminated" << std::endl;
			f_res = MININT;
			g_res = MININT;
		}
	}

	if (f_res != MININT && g_res != MININT) {
		
		if (!(f.running())) {
			f_out >> f_res;
			std::cout << "f ended with " << f_res << std::endl;
			while (g.running()) {
				if (checkCancelation()) {
					g.terminate();
					g_res = MININT;
					std::cout << "g was terminated" << std::endl;
				}
			}
			if (g_res != MININT) {
				g_out >> g_res;
				std::cout << "g ended with " << g_res << std::endl;
			}
		}
		else {
			g_out >> g_res;
			std::cout << "g ended with " << g_res << std::endl;
			while (f.running()) {
				if (checkCancelation()) {
					f.terminate();
					f_res = MININT;
					std::cout << "f was terminated" << std::endl;
				}
			}
			if (f_res != MININT) {
				f_out >> f_res;
				std::cout << "f ended with " << f_res << std::endl;
			}
		}
	}
	int result = binaryOperation(f_res, g_res);
	if (result  == MININT) {
		std::cout << "f(x)*g(x) cant be calculated" << std::endl;
	}
	else {
		std::cout << "f(x)*g(x) equals " << result << std::endl;
	}
}

int main(int argc, char** argv) {
	namespace bp = boost::process;
    std::error_code ec;
    if (argc == 1) {
		manager(argv[0]);
    }
    else if ((std::string)(argv[argc - 1]) == "f_func"){
 		int data;
		std::cin >> data;
		std::cout << spos::lab1::demo::f_func<spos::lab1::demo::INT>(data);
		return 0;
		/*return f_func(0);*/
    }
    else {
		int data;
		std::cin >> data;
		std::cout << spos::lab1::demo::g_func<spos::lab1::demo::INT>(data);
		return 0;
		/*return g_func(0);*/
		
    }
	return 0;
}