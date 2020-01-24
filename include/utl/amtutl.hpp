#ifndef __AMTUTL_HPP__
#define __AMTUTL_HPP__

#include <stdio.h>
#include <stdlib.h>

#include <string>

template <int N>
std::string FormatDecimalAmount(std::string a) {
	std::string amount(a);
	amount[a.size() - (N + 1)] = ',';
	return amount;
}

template <int N>
std::string FormatDecimalRate(std::string r) {
	std::string rate(r);
	rate[r.size() - (N + 1)] = ',';
	return rate.substr(0, rate.size() - (N + 1));
}

template <int N>
long GetDecimalAmount(std::string a) {
	std::string amount(a.substr(0, a.size() - (N + 1)));
	amount += a.substr(a.size() - N, N);
	return atol(amount.c_str());
}

template <int N>
std::string PutDecimalAmount(long a) {
	char buffer[256];
	std::string sign;
	if (a == 0) {
		return "0,00";
	} else if (a < 0) {
		sign.assign("-");
		a *= -1;
	}
	sprintf(buffer, "%03ld", a);
	std::string fract(buffer + strlen(buffer) - N);
	buffer[strlen(buffer) - N] = 0x00;
	std::string amount(buffer);
	return sign + amount + std::string(",") + fract;
}

#endif // __AMTUTL_HPP__
