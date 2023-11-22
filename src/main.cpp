#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std::vector<std::string> tablo;
std::mutex border;

void swimming(std::string name, float speed, std::vector<std::string> &tablo) {
	float distance = 0;
	int time = 0;
	do {
		time += 1;
		distance += speed;
		if (distance > 100) { distance = 100; };
		std::cout << "\t--" << name << " swam " << distance << " meters!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (distance < 100);
	border.lock();
	tablo.push_back((std::to_string(time) + " \t " + name));
	border.unlock();
}



int main() {
	std::string swim1, swim2, swim3, swim4, swim5, swim6;
	float speed1, speed2, speed3, speed4, speed5, speed6 ;

	std::cout << "Enter the names of the six athletes separated by a space! " << std::endl;
	std::cin >> swim1 >> swim2 >> swim3 >> swim4 >> swim5 >> swim6;
	std::cout << "Enter the speed of each athlete, also separated by a space! " << std::endl;
	std::cin >> speed1 >> speed2 >> speed3 >> speed4 >> speed5 >> speed6;

	std::thread swimmer1(swimming, swim1, speed1, std::ref(tablo));
	std::thread swimmer2(swimming, swim2, speed2, std::ref(tablo));
	std::thread swimmer3(swimming, swim3, speed3, std::ref(tablo));
	std::thread swimmer4(swimming, swim4, speed4, std::ref(tablo));
	std::thread swimmer5(swimming, swim5, speed5, std::ref(tablo));
	std::thread swimmer6(swimming, swim6, speed6, std::ref(tablo));
	swimmer1.join();
	swimmer2.join();
	swimmer3.join();
	swimmer4.join();
	swimmer5.join();
	swimmer6.join();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	
	std::cout << "\n\n";
	std::cout << "Time \t Name" << std::endl;
	for (int t = 0; t < tablo.size(); t++) {
		std::cout << tablo[t] << std::endl;
	}
	
	
	return 0;
}
