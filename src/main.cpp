#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <map>

std::map<int, std::string> swi;
std::mutex border;

void swimming(std::string name, float speed, std::map<int, std::string> &tablo) {
	
	
	float distance = 0;
	int time = 0;
	border.lock();
	do {
		time += 1;
		distance += speed;
		if (distance > 100) { distance = 100; };
		std::cout << "\t--" << name << " проплыл " << distance << " метров!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (distance < 100);
	
	if (tablo.count(time)) {
		tablo.find(time)->second += " " + name;
	}
	else {
		tablo.insert(std::pair<int, std::string>(time, name));
	}
	border.unlock();
}



int main() {
	setlocale(LC_ALL, "rus");
	std::string swim1, swim2, swim3, swim4, swim5, swim6;
	float speed1, speed2, speed3, speed4, speed5, speed6 ;

	std::cout << "¬ведите имена шести спортсменов разел€€ их пробелом! " << std::endl;
	std::cin >> swim1 >> swim2 >> swim3 >> swim4 >> swim5 >> swim6;
	std::cout << "¬ведите скорость каждого спортсмена, так же через пробел! " << std::endl;
	std::cin >> speed1 >> speed2 >> speed3 >> speed4 >> speed5 >> speed6;

	std::thread swimmer1(swimming, swim1, speed1, std::ref(swi));
	std::thread swimmer2(swimming, swim2, speed2, std::ref(swi));
	std::thread swimmer3(swimming, swim3, speed3, std::ref(swi));
	std::thread swimmer4(swimming, swim4, speed4, std::ref(swi));
	std::thread swimmer5(swimming, swim5, speed5, std::ref(swi));
	std::thread swimmer6(swimming, swim6, speed6, std::ref(swi));
	swimmer1.join();
	swimmer2.join();
	swimmer3.join();
	swimmer4.join();
	swimmer5.join();
	swimmer6.join();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	std::cout << "\n\n";

	for (std::map<int, std::string>::iterator it = swi.begin(); it != swi.end(); it++) {
		std::cout << "\t--«а врем€ " << it->first << " секунд , пловец(вцы) " << it->second << " проплыл(и) стометровку!" << std::endl;
	}
	
	
	return 0;
}
