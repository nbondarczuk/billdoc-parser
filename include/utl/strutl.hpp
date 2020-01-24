#ifndef __STRUTL_HPP__
#define __STRUTL_HPP__

#include "string.h"

#define STREQ(a, b) (0 == strcmp(a, b))
#define STREQN(a, b, n) (0 == strncmp(a, b, n))

inline const char* Decode(const char* value, const char* arg, const char* r1, const char* r2) {
	if (STREQ(value, arg)) {
		return r1;
	}

	return r2;
}	

template <int MAX>
std::vector<std::string> split(const char *str, const char c = ' ') {
	std::vector<std::string> result;
	int i = 0;
    do
    {
        const char *begin = str;
        while(*str != c && *str)
            str++;
        result.push_back(std::string(begin, str));
    } while (0 != *str++ && i++ < MAX);

    return result;
}

template <int N>
std::string join(std::vector<std::string>& arg, const char c = ' ') {
	std::string rv;
	for (int i = 0; i < N; ++i) {
		rv += arg[i];
		if (i < N - 1) {
			rv += c;
		}
	}
	return rv;
}	

#endif // __STRUTL_HPP__
