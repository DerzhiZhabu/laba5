#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

void PLAINS_FOR_TOWN(string name, vector<string>& plains_vec, vector<string>& towns_vec, map<string, vector<string>>& plains_map, map<string, vector<string>>& towns_map);
void CREATE_PLAIN(const string name, vector<string>& plains_vec, vector<string>& towns_vec, map<string, vector<string>>& plains_map, map<string, vector<string>>& towns_map, const vector<string>& new_towns);
void PLAINS(vector<string>& plains_vec, vector<string>& towns_vec, map<string, vector<string>>& plains_map, map<string, vector<string>>& towns_map);
void TOWNS_FOR_PLAIN(string name, vector<string>& plains_vec, vector<string>& towns_vec, map<string, vector<string>>& plains_map, map<string, vector<string>>& towns_map);
