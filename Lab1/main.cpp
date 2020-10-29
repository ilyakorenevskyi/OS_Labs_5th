#include <boost/process.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>

int f_func(int test_case) {
	switch (test_case) {
	case 0: {
		std::this_thread::sleep_for(std::chrono::seconds(2));
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
int main(int argc, char** argv) {
    namespace bp = boost::process;
    std::error_code ec;
    if (argc == 1) {
        bp::child f(argv[0], "f_func", bp::std_in = stdin,
            bp::std_out = stdout, bp::std_err = stderr);
        bp::child g(argv[0], "g_func", bp::std_in = stdin,
            bp::std_out = stdout, bp::std_err = stderr);
        f.wait();
        g.wait();
		std::cout << f.exit_code() + g.exit_code();
    }
    else if ((std::string)(argv[argc - 1]) == "f_func"){
        std::cout << "Child process f" << std::endl;
		return f_func(0);
    }
    else {
        std::cout << "Child process g" << std::endl;
		return g_func(0);
    }
    
}