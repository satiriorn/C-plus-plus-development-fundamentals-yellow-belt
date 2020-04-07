#include <sstream>
#include <stdexcept>

#include "phone_number.h"

using namespace std;

PhoneNumber::PhoneNumber(const string& international_number) {
	istringstream stream(international_number);
	char s = stream.get();
	getline(stream, country_code_, '-');
	getline(stream, city_code_, '-');
	getline(stream, local_number_, '\n');
	if (s != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty())
		throw invalid_argument("WRONG PHONE NUMBER: " + international_number);
}

string PhoneNumber::GetCountryCode() const {return country_code_;}

string PhoneNumber::GetCityCode() const {return city_code_;}

string PhoneNumber::GetLocalNumber() const {return local_number_;}

string PhoneNumber::GetInternationalNumber() const { return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);}