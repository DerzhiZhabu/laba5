#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <locale.h>
#include <algorithm>

using namespace std;

#include <iostream>
#include <random>

int rn() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(100, 999);
    return distrib(gen);
}

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second;
}


int main() {
    setlocale(LC_ALL, "russian");
    int wind_count;
    string talon;


    vector<vector<int>> windows_queue;
    vector<int> time_in;
    vector<pair<int, int>> people;
    vector<int> talons;

    cout << "Введите количество окон" << endl;
    cin >> wind_count;

    for (int i = 0; i < wind_count; i++) {
        windows_queue.push_back({});
        time_in.push_back(0);
    }


    string input;

    while (true) {
        cin >> input;

        if (input == "DISTRIBUTE") {
            sort(people.begin(), people.end(), compare);

            for (size_t i = 0; i < people.size(); i++) {
                int min = time_in[0];
                size_t indexx = 0;
                for (size_t ind = 0; ind < time_in.size(); ind++) {
                    if (time_in[ind] < min) {
                        min = time_in[ind];
                        indexx = ind;
                    }
                }
                windows_queue[indexx].push_back(people[i].first);
                time_in[indexx] += people[i].second;
            }

            for (size_t i = 0; i < time_in.size(); i++) {
                cout << "Окно " << i + 1 << " (" << time_in[i] << " минут): ";
                for (size_t j = 0; j < windows_queue[i].size(); j++) {
                    cout << 'T' << windows_queue[i][j] << ' ';
                }
                cout << endl;
            }
            break;
        }
        else if (input == "ENQUEUE") {
            int time;
            int talon;

            cin >> time;

            while (true) {
                talon = rn();
                bool exists = false;

                for (size_t i = 0; i < talons.size(); i++) {
                    if (talons[i] == talon) {
                        exists = true;
                    }
                }
                if (!exists) {
                    break;
                }
            }
            cout << 'T' << talon << endl;

            people.push_back(make_pair(talon, time));
        }
        else {
            cout << "Неизвестная команда" << endl;
        }
    }
}


