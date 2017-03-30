#pragma once

#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#include <string>

class TicToc {

private:
#ifdef _WIN32
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
	LARGE_INTEGER elapsed_u;

	LARGE_INTEGER frequency;
#else
	timespec start, end;

	time_t sec;
	long nsec;

	void diff();
#endif

public:
	TicToc() {
#ifdef _WIN32
		QueryPerformanceFrequency(&frequency);
#endif
	}

	void tic();
	void toc();

	void getNsecsRaw(long& sec, long& nsec) const;
	std::string getNsecsFormatted() const;

	long getUsecsRaw() const;
	std::string getUsecsFormatted() const;

	long getMillisRaw() const;
	std::string getMillisFormatted() const;

	long getSecsRaw() const;
	std::string getSecsFormatted() const;
};
