#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iomanip>

const double PI = 3.14159265358979323846;

void printHelp() {
	std::cout << "Использование: calculator -o <операция> [--deg|--rad] <число>\n";
	std::cout << "Доступные операции:\n";
	std::cout << "  arcsin   - арксинус\n";
	std::cout << "  arccos   - арккосинус\n";
	std::cout << "Флаги:\n";
    	std::cout << "  --deg    - режим градусов (по умолчанию радианы)\n";
    	std::cout << "  --rad    - режим радиан\n";
    	std::cout << "Пример: calculator --operation arcsin --deg 0.5\n";
}

int main(int argc, char* argv[]) {
    	if (argc < 2) {
        	printHelp();
        	return 0;
    	}

    	std::string operation;
    	bool useDegrees = false;
    	std::vector<double> numbers;

    	for (int i = 1; i < argc; ++i) {
        	std::string arg = argv[i];

        	if (arg == "-o" || arg == "--operation") {
            		if (i + 1 < argc) {
                		operation = argv[++i];
            		} else {
                		std::cerr << "Ошибка: не указана операция после " << arg << "\n";
                		return 1;
            		}
        	} else if (arg == "--deg") {
            		useDegrees = true;
        	} else if (arg == "--rad") {
            		useDegrees = false;
        	} else {
            		try {
                		numbers.push_back(std::stod(arg));
            		} catch (...) {
                		std::cerr << "Ошибка: '" << arg << "' не является числом.\n";
                		return 1;
            		}
        	}
    	}

    	if (operation.empty()) {
        	std::cerr << "Ошибка: не задана операция (-o или --operation).\n";
        	printHelp();
        	return 1;
    	}

    	if (numbers.size() != 1) {
        	std::cerr << "Ошибка: для операции '" << operation << "' требуется ровно одно число.\n";
        	return 1;
    	}

    	double x = numbers[0];
    	double result = 0.0;

    	if (x < -1.0 || x > 1.0) {
        	std::cerr << "Ошибка: аргумент должен быть в диапазоне [-1, 1].\n";
        	return 1;
    	}

    	if (operation == "arcsin") {
        	result = std::asin(x);
    	} else if (operation == "arccos") {
        	result = std::acos(x);
    	} else {
        	std::cerr << "Ошибка: неизвестная операция '" << operation << "'.\n";
        	return 1;
    	}

    	if (useDegrees) {
        	result = result * 180.0 / PI;
    	}

    	std::cout << std::fixed << std::setprecision(4);
    	std::cout << "Результат: " << result;
    	if (useDegrees) {
        	std::cout << " градусов";
    	} else {
        	std::cout << " радиан";
    	}
    	std::cout << std::endl;

    	return 0;
}
