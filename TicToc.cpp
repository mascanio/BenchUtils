#include "TicToc.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

#ifdef _WIN32
void TicToc::tic()
{
	QueryPerformanceCounter(&start);
}

void TicToc::toc()
{
	QueryPerformanceCounter(&stop);
	elapsed_u.QuadPart = stop.QuadPart - start.QuadPart;
	elapsed_u.QuadPart *= 1000000;
	elapsed_u.QuadPart /= frequency.QuadPart;
}

int TicToc::getUsecsRaw() const
{
	return elapsed_u.QuadPart;
}

string TicToc::getUsecsFormatted() const
{
	string s;
	std::stringstream ss;
	ss << setw(6) << setfill('0') << elapsed_u.QuadPart;
	s = ss.str();
	for (int i = s.size() - 3; i > 0; i -= 3) {
		s.insert(s.begin() + i, ',');
	}

	return s;
}

int TicToc::getMillisRaw() const
{
	return getUsecsRaw() / 1000;
}

string TicToc::getMillisFormatted() const
{
	return string();
}

int TicToc::getSecsRaw() const
{
	return getMillisRaw() / 1000;
}

string TicToc::getSecsFormatted() const
{
	return string();
}

#else
std::ostream& operator<<(std::ostream& out, const TicToc& f) {
	string s;
	std::stringstream ss;
	ss << setw(9) << setfill('0') << f.nsec;
	s = ss.str();
	for (int i = s.size() - 3; i > 0; i -= 3) {
		s.insert(s.begin() + i, ',');
	}

	return out << "Secs: " << f.sec << " Nsecs: " << setw(11) << s;
}

inline void TicToc::tic() {
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
}

inline void TicToc::toc() {
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	diff();
}

void TicToc::getNsecsRaw(long& sec, long& nsec) const {
	sec = this->sec;
	nsec = this->nsec;
}

std::string TicToc::getNsecsFormatted() const {

}

long TicToc::getUsecsRaw() const {
	return sec * 1000000 + nsec / 1000;
}

std::string TicToc::getUsecsFormatted() const {

}

long TicToc::getMillisRaw() const {
	return sec * 1000 + nsec / 1000000;
}
std::string TicToc::getMillisFormatted() const {

}

long TicToc::getSecsRaw() const {
	return this->sec;
}

std::string TicToc::getSecsFormatted() const {
	string s;
	std::stringstream ss;
	ss << setw(6) << setfill('0') << this->sec;
	s = ss.str();
	for (int i = s.size() - 3; i > 0; i -= 3) {
		s.insert(s.begin() + i, ',');
	}

	return s;
}

void TicToc::diff() {
	if ((end.tv_nsec - start.tv_nsec) < 0) {
		sec = end.tv_sec - start.tv_sec - 1;
		nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	} else {
		sec = end.tv_sec - start.tv_sec;
		nsec = end.tv_nsec - start.tv_nsec;
	}
}
#endif

