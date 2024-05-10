#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <locale.h>
#include "dop_func.h"

using namespace std;

enum class Commands {
	NOTHING,
	CREATE_PLAIN,
	PLAINS_FOR_TOWN,
	TOWNS_FOR_PLAIN,
	PLAINS
};

class Program {
private:
	Commands state = Commands::NOTHING;
	vector<string> plains_vec;
	vector<string> towns_vec;

	map<string, vector<string>> plains_map;
	map<string, vector<string>> towns_map;

public:

	void change_state(string new_state) {
		if (new_state == "CREATE_PLAIN") state = Commands::CREATE_PLAIN;
		else if (new_state == "PLAINS_FOR_TOWN") state = Commands::PLAINS_FOR_TOWN;
		else if (new_state == "TOWNS_FOR_PLAIN") state = Commands::TOWNS_FOR_PLAIN;
		else if (new_state == "PLAINS") state = Commands::PLAINS;
		else state = Commands::NOTHING;
	}

	void run() {
		string name;
		vector<string> new_towns;
		string town_name;
		int towns_count;


		switch (state) {
		case Commands::CREATE_PLAIN:
			cin >> name;

			cin >> towns_count;

			for (int i = 0; i < towns_count; i++) {
				cin >> town_name;
				bool exists = false;
				for (size_t j = 0; j < new_towns.size(); j++) {
					if (new_towns[j] == town_name) {
						exists = true;
						break;
					}
				}
				if (!exists) {
					new_towns.push_back(town_name);
				}
			}

			CREATE_PLAIN(name, plains_vec, towns_vec, plains_map, towns_map, new_towns);
			change_state("NOTHING");

			break;
		case Commands::PLAINS:
			PLAINS(plains_vec, towns_vec, plains_map, towns_map);
			change_state("NOTHING");
			break;
		case Commands::PLAINS_FOR_TOWN:
			cin >> name;
			PLAINS_FOR_TOWN(name, plains_vec, towns_vec, plains_map, towns_map);
			change_state("NOTHING");
			break;
		case Commands::TOWNS_FOR_PLAIN:
			cin >> name;
			TOWNS_FOR_PLAIN(name, plains_vec, towns_vec, plains_map, towns_map);
			change_state("NOTHING");
			break;
		}
	}

};


int main() {
	setlocale(LC_ALL, "russian");

	Program handler;
	string command;
	

	while (true) {
		cin >> command;
		handler.change_state(command);
		handler.run();
	}
}