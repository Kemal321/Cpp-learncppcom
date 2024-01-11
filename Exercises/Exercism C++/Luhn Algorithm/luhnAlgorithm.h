#ifndef LUHN_H
#define LUHN_H
#include <string>

namespace luhn {
	bool valid(std::string cardNumber);
	bool nonAscii(std::string cardNumber);
	bool luhnCalculator(std::string cardNumber);
}  // namespace luhn

#endif // LUHN_H