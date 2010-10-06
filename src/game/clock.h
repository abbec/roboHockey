#include <string>
#include <iostream>

class Clock
{
	public:
		Clock(int m, int s) : minutes(m), seconds(s) {}

		void tick();
		void reset();
		bool isEnd();
		std::string printTime();

	private:
		int minutes, seconds;
};
