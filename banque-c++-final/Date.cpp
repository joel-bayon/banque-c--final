#include "Date.h"

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;


Date::Date() : date(time(nullptr))
{
	cout << "instanciation d'une Date() ... " << endl;
	struct tm * timeinfo= localtime(&date);
	ss << std::put_time(timeinfo,"%d/%m/%Y"); //C++11
}

Date::Date(const std::string& str_date) : ss(str_date){
	cout << "instanciation d'une Date(const std::string&) ... " << endl;
	struct std::tm timeinfo;
	ss >> std::get_time(&timeinfo,"%d/%m/%Y"); //C++11
	if (ss.fail()) std::cout << "Error reading time\n";
	else date = mktime(&timeinfo);
}


Date::Date(const Date & date) {
	cout << "instanciation d'une Date(const Date &)" << endl;
	this->date = date.date;
	ss << date.ss.str();
}

Date& Date::operator = (const Date & date) {
	cout << "Date::operator = (const Date &)" << endl;
	this->date = date.date;
	ss.str("");
	ss << date.ss.str();
	return *this;
}

Date::Date(Date&& date) :date(date.date), ss(move(date.ss)){
	cout << "instanciation d'une Date(Date &&)" << endl;
}

Date& Date::operator = (Date && date) {
	cout << "Date::operator = (Date &&)" << endl;
	this->date = date.date;
	this->ss = std::move(date.ss);
	return *this;
}


Date::~Date()
{
	cout << "destruction d'une Date ... " << endl;

}

/*int main(int argc, char **argv) {
	Date now;
	cout << now.toString() << endl;
	Date other(now);
	cout << other.toString() << endl;
	other = Date("12/12/2017");
	cout << other.toString()  << " " << now.toString() <<endl;
	swap(now, other);
	cout << other.toString() << " " << now.toString() <<endl;
}*/




