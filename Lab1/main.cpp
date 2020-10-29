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

void manager(char* process) {
	namespace bp = boost::process;
	std::chrono::seconds hang_time(10);
	bp::child f(process, "f_func", bp::std_in = stdin,
		bp::std_out = stdout, bp::std_err = stderr);
	bp::child g(process, "g_func", bp::std_in = stdin,
		bp::std_out = stdout, bp::std_err = stderr);
	while (f.running() && g.running()) {

	}
	if (!(f.running())) {
		std::cout << "f ended with " << f.exit_code() << std::endl;
		if (!g.wait_for(hang_time)) {
			g.terminate();
			std::cout << "g was terminated because it hung on for too long" << std::endl;
		}
		else {
			std::cout << "g ended with " << g.exit_code() << std::endl;
		}
	}
	else {
		std::cout << "g ended with " << g.exit_code() << std::endl;
		if (!f.wait_for(hang_time)) {
			f.terminate();
			std::cout << "f was terminated because it hung on for too long" << std::endl;
		}
		else {
			std::cout << "f ended with " << f.exit_code() << std::endl;
		}
	}
}

int main(int argc, char** argv) {
	namespace bp = boost::process;
    std::error_code ec;
    if (argc == 1) {
		manager(argv[0]);
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