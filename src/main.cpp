#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <map>

std::map<int, std::string> swi;
std::mutex border;

void swimming(std::string name, float speed, std::map<int, std::string> tablo) {
	
	float distance = 0;
	int time = 0;
	do {
		time += 1;
		distance += speed;
		if (distance > 100) { distance = 100; };
		std::cout << "\t--" << name << " проплыл " << distance << " метров!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (distance < 100);
	
	tablo.insert(std::pair<int, std::string>(time, name));
	
}



int main() {
	setlocale(LC_ALL, "rus");
	std::string swim1, swim2/*, swim3, swim4, swim5, swim6*/;
	float speed1, speed2/*, speed3, speed4, speed5, speed6*/ ;

	std::cout << "Введите имена шести спортсменов разеляя их пробелом! " << std::endl;
	std::cin >> swim1 >> swim2/* >> swimmer3 >> swimmer4 >> swimmer5 >> swimmer6*/;
	std::cout << "Введите скорость каждого спортсмена, так же через пробел! " << std::endl;
	std::cin >> speed1 >> speed2/* >> speed3 >> speed4 >> speed5 >> speed6*/;

	std::thread swimmer1(swimming, swim1, speed1, std::ref(swi));
	std::thread swimmer2(swimming, swim2, speed2, std::ref(swi));
	swimmer1.join();
	swimmer2.join();
	return 0;
}
