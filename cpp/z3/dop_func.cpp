#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "dop_func.h"

using namespace std;

void CREATE_PLAIN(const string name, vector<string>& plains_vec, vector<string>& towns_vec, map<string, vector<string>>& plains_map, map<string, vector<string>>& towns_map, const vector<string>& new_towns) {
	bool exists = false;

	for (size_t i = 0; i < plains_vec.size(); i++) {
		if (plains_vec[i] == name) {
			exists = true;
			break;
		}
	}

	if (!exists) {
		plains_vec.push_back(name);
		plains_map[name] = {};
	}

	for (size_t i = 0; i < new_towns.size(); i++) {
		bool town_exists = false;

		for (size_t j = 0; j < towns_vec.size(); j++) {
			if (towns_vec[j] == new_towns[i]) {
				town_exists = true;
				break;
			}
		}

		if (!town_exists) {
			towns_vec.push_back(new_towns[i]);
			towns_map[new_towns[i]] = {};
		}

		towns_map[new_towns[i]].push_back(name);
		plains_map[name].push_back(new_towns[i]);
	}
	cout << "Самолет создан." << endl;

}

void PLAINS(vector<string>& plains_vec, vector<string>& towns_vec, map<string, vector<string>>& plains_map, map<string, vector<string>>& towns_map) {
	for (size_t i = 0; i < plains_vec.size(); i++) {
		TOWNS_FOR_PLAIN(plains_vec[i], plains_vec, towns_vec, plains_map, towns_map);
		cout << endl;
	}
}

void PLAINS_FOR_TOWN(string name, vector<string>& plains_vec, vector<string>& towns_vec, map<string, vector<string>>& plains_map, map<string, vector<string>>& towns_map) {
	bool exists = false;


	for (size_t i = 0; i < towns_vec.size(); i++) {
		if (towns_vec[i] == name) {
			exists = true;
		}
	}
	if (exists) {
		cout << "Самолеты для города " << name << ": ";

		for (size_t i = 0; i < towns_map[name].size(); i++) {
			cout << towns_map[name][i] << ' ';
		}

		cout << endl;
	}
	else cout << "Такого города не указано." << endl;
}

void TOWNS_FOR_PLAIN(string name, vector<string>& plains_vec, vector<string>& towns_vec, map<string, vector<string>>& plains_map, map<string, vector<string>>& towns_map) {
	bool exists = false;


	for (size_t i = 0; i < plains_vec.size(); i++) {
		if (plains_vec[i] == name) {
			exists = true;
		}
	}
	if (exists) {
		cout << "Города для самолета " << name << ": " << endl;

		for (size_t i = 0; i < plains_map[name].size(); i++) {
			PLAINS_FOR_TOWN(plains_map[name][i], plains_vec, towns_vec, plains_map, towns_map);
		}

		cout << endl;
	}
	else cout << "Такого самолета не указано." << endl;
}