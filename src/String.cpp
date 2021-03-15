#include "String.hpp"
bool String::isIdValid(string& str) {
	const char* _str = str.c_str();
	int i = 0;
	while (_str[i] != '\0') {
		if (!((_str[i] <= 57 && _str[i] >= 48) || (_str[i] <= 90 && _str[i] >= 65) || (_str[i] <= 122 && _str[i] >= 97))) {
			cout << "Invalid ID." << endl;
			return false;
		}
		i++;
	}
	return true;
}
bool String::isPasswordValid(string& str) {
	const char* _str = str.c_str();
	int i = 0;
	while (_str[i] != '\0') {
		if (!(_str[i] <= 126 && _str[i] >= 33)) {
			cout << "Invalid password." << endl;
			return false;
		}
		i++;
	}
	return true;
}
bool String::isNameValid(string& str) {
	const char* _str = str.c_str();
	int i = 0;
	while (_str[i] != '\0') {
		if (!((_str[i] <= 90 && _str[i] >= 65) || (_str[i] <= 122 && _str[i] >= 97))) {
			return false;
		}
		i++;
	}
	return true;
}
void String::upperCase(string& str) {
	char* _str = &str[0];
	int i = 0;
	while (_str[i] != '\0') {
		if (_str[i] <= 122 && _str[i] >= 97) {
			_str[i] -= 32;
		}
		i++;
	}
}
void String::lowerCase(string& str) {
	char* _str = &str[0];
	int i = 0;
	while (_str[i] != '\0') {
		if (_str[i] <= 90 && _str[i] >= 65) {
			_str[i] += 32;
		}
		i++;
	}
}
string String::hash(string& str) {
	return md5(md5(str));
}