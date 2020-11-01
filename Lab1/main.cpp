#include <boost/process.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <Windows.h>
#include "demofuncs"

int binaryOperation(int a, int b) {
	if (a == 0 || b == 0) {
		return 0;
	}
	if (a == NULL || b == NULL) {
		return NULL;
	}
	return a * b;
}

bool checkCancelation() {
	return GetKeyState('C') && GetKeyState(VK_CONTROL);
}

int f_func(int test_case) {
	switch (test_case) {
	case 0: {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "Hello, f!";
		return 2;
		break;
	}
	case 1: {
		std::this_thread::sleep_for(std::chrono::seconds(5));
		return 2;
		break;
	}
	case 2: {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return 0;
		break;
	}
	case 3: {
		std::this_thread::sleep_for(std::chrono::seconds(100));
		return 0;
		break;
	}
	case 4: {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return 2;
		break;
	}
	case 5: {
		std::this_thread::sleep_for(std::chrono::seconds(100));
		return 0;
		break;
	}
	default: {
		return 0;
		break;
	}
	}
}

int g_func(int test_case) {
	switch (test_case) {
	case 0: {
		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout << "Hello, g!";
		return 3;
		break;
	}
	case 1: {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return 3;
		break;
	}
	case 2: {
		std::this_thread::sleep_for(std::chrono::seconds(600));
		return 0;
		break;
	}
	case 3: {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return 0;
		break;
	}
	case 4: {
		std::this_thread::sleep_for(std::chrono::seconds(600));
		return 0;
		break;
	}
	case 5: {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		return 2;
		break;
	}
	default:{
		return 0;
		break;
	}
	}
}

void manager(char* process) {
	namespace bp = boost::process;


	bp::opstream f_in, g_in;
	bp::ipstream f_out, g_out;


	bp::group func;
	bp::child f(process, "f_func", bp::std_in < f_in,
		bp::std_out > f_out, bp::std_err = stderr,func);
	bp::child g(process, "g_func", bp::std_in < g_in,
		bp::std_out > g_out, bp::std_err = stderr,func);

	int test_num;
	std::cout << "Enter test case number or -1 to exit\n";
	std::cin >> test_num;
	f_in << test_num << std::endl;
	g_in << test_num << std::endl;

	int f_res = -1,
		g_res = -1;

	while (f.running() && g.running()) {
		if (checkCancelation()) {
			func.terminate();
			std::cout << "f was terminated" << std::endl;
			std::cout << "g was terminated" << std::endl;
			f_res = NULL;
			g_res = NULL;
		}
	}

	if (f_res != NULL && g_res != NULL) {
		
		if (!(f.running())) {
			f_out >> f_res;
			std::cout << "f ended with " << f_res << std::endl;
			while (g.running()) {
				if (checkCancelation()) {
					g.terminate();
					g_res = NULL;
					std::cout << "g was terminated" << std::endl;
				}
			}
			if (g_res != NULL) {
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
					f_res = NULL;
					std::cout << "f was terminated" << std::endl;
				}
			}
			if (f_res != NULL) {
				f_out >> f_res;
				std::cout << "f ended with " << f_res << std::endl;
			}
		}
	}

	std::cout <<"f(x)*g(x) result is: " << binaryOperation(f_res,g_res);
}

int main(int argc, char** argv) {
	namespace bp = boost::process;
    std::error_code ec;
    if (argc == 1) {
		manager(argv[0]);
    }
    else if ((std::string)(argv[argc - 1]) == "f_func"){
		int a;
		std::cin >> a;
		std::cout << spos::lab1::demo::f_func<spos::lab1::demo::INT>(a);
		return 0;
		/*return f_func(0);*/
    }
    else {
		int a;
		std::cin >> a;
		std::cout << spos::lab1::demo::g_func<spos::lab1::demo::INT>(a);
		return 0;
		/*return g_func(0);*/
		
    }
	return 0;
}