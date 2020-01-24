#ifndef __DATEUTL_HPP__
#define __DATEUTL_HPP__

#include <time.h>

#include <string>

// YYYYMMDD -> DD.MM.YYYY
inline std::string FormatDate(std::string d) {
	std::string nd;
	nd.resize(8);
	nd[0] = d[6];
	nd[1] = d[7];
	nd[2] = '.';
	nd[3] = d[4];
	nd[4] = d[5];
	nd[5] = '.';
	nd[6] = d[2];
	nd[7] = d[3];
	return nd;
}

// get formatted file creation timestamp
inline char* FileTimeStamp()
{
	time_t now;
	time (&now);
	const struct tm *timeptr = localtime(&now);
	
	static const char wday_name[][4] = {
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};
	static const char mon_name[][4] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};
	static char result[26];
	sprintf(result, "%.3s %d %.3s%3d %.2d:%.2d:%.2d",
			wday_name[timeptr->tm_wday],
			1900 + timeptr->tm_year,
			mon_name[timeptr->tm_mon],
			timeptr->tm_mday,
			timeptr->tm_hour,
			timeptr->tm_min,
			timeptr->tm_sec);
	
	return result;
}

#endif // __DATEUTL_HPP__
