#pragma once
#include <thread>
#include <chrono>

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
	default: {
		return 0;
		break;
	}
	}
}