#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <locale.h>

using namespace std;

void add_class(const int day, const string name, const int& month, map<int, map<int, vector<string>>>& university, map<int, vector<int>>& days) {
	bool exists = false;
	for (size_t i = 0; i < days[month].size(); i++) {
		if (days[month][i] == day) {
			exists = true;
			break;
		}
	}

	if (exists) {
		bool predm_exists = false;

		for (size_t i = 0; i < university[month][day].size(); i++) {
			if (university[month][day][i] == name) {
				predm_exists = true;
				break;
			}
		}
		if (!predm_exists) {
			university[month][day].push_back(name);
		}
	}
	else {
		university[month][day] = { name };
		days[month].push_back(day);
	}
}

void next_month(int& month, vector<int>& monthes, map<int, map<int, vector<string>>>& university, map<int, vector<int>>& days) {
	month++;
	if (month > 12) {
		month = 1;
	}
	
	bool month_exists = false;
	for (size_t i = 0; i < monthes.size(); i++) {
		if (monthes[i] == month) {
			month_exists = true;
			break;
		}
	}

	if (!month_exists) {
		university[month] = {};
		days[month] = {};
	}
}

void view(const int day, const int& month, map<int, map<int, vector<string>>>& university, map<int, vector<int>>& days) {
	bool exists = false;

	for (size_t i = 0; i < days[month].size(); i++) {
		if (days[month][i] == day) {
			exists = true;
			break;
		}
	}

	if (exists) {
		cout << "In " << day << " day " << university[month][day].size() << " classes in university: ";
		for (size_t i = 0; i < university[month][day].size(); i++) {
			cout << university[month][day][i] << " ";
		}
		cout << endl;
	}
	else {
		cout << "In " << day << " day We are free!";
		cout << endl;
	}

}

int main() {
	setlocale(LC_ALL, "russian");

	int month = 1;
	vector<int> monthes = { 1 };
	map<int, map<int, vector<string>>> university;
	map<int, vector<int>> days;

	university[month] = {};
	days[month] = {};

	string command;

	while (true) {
		cin >> command;
		if (command == "CLASS") {
			int day;
			string name;

			cin >> day;
			cin >> name;
			add_class(day, name, month, university, days);
		}
		else if (command == "NEXT") {
			next_month(month, monthes, university, days);
		}
		else if (command == "VIEW") {
			int day;
			cin >> day;
			view(day, month, university, days);
		}
	}
}