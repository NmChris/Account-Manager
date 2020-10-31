#include "Encryption.h"

std::string Encryption::encrpyt(std::string input) {
	std::string result = input;
	char keys[] = { 'L', 'J', 'Y', 'T' };
	for (int i = 0; i < input.size(); i++) {
		for (const char& key : keys)
			result[i] = result[i] ^ key;
	}
	return result;
}

std::string Encryption::decrypt(std::string input) {
	return encrpyt(input);
}
