#include "mylib.h"

class Timer {
private:
	// panaudojame using
	std::chrono::time_point<hrClock> start;
public:
	Timer() : start{ hrClock::now() } {}
	void reset() {
		start = hrClock::now();
	}
	double elapsed() const {
		return durationDouble(hrClock::now() - start).count();
	}
};