#pragma once
#include <iostream>
using namespace std;
#include "MD5.hpp"
class String
{
public:
	static bool isIdValid(string& str);
	static bool isPasswordValid(string& str);
	static bool isNameValid(string& str);
	static void upperCase(string& str);
	static void lowerCase(string& str);
	static string hash(string& str);
};

