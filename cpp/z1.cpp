#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <locale.h>

using namespace std;

extern double kol = 0;

class Stelazh {
public:
    vector<vector<vector<pair<string, int>>>> sekcii;

    void init(int vert, int polk) {
        for (int i = 0; i < vert; i++) {
            vector<vector<pair<string, int>>> polki;
            for (int j = 0; j < polk; j++) {
                polki.push_back({});
            }
            sekcii.push_back(polki);
        }
    }

    void add(string name, int count, int vert, int polk) {
        int kolich = 0;
        bool suzh = false;
        int ind = 0;

        for (size_t i = 0; i < sekcii[vert][polk].size(); i++) {
            kolich += sekcii[vert][polk][i].second;
            if (sekcii[vert][polk][i].first == name) {
                suzh = true;
                ind = i;
            }
        }

        if (kolich + count > 10) {
            cout << "Не достаточно места в ячейке" << endl;
        }
        else {
            if (suzh){
                sekcii[vert][polk][ind].second += count;
                kol += count;
            }
            else {
                sekcii[vert][polk].push_back(make_pair(name, count));
                kol += count;
            }
            cout << "Добавлено " << count << ' ' << name << endl;
        }
    }

    void rem(string name, int count, int vert, int polk) {
        bool suzh = false;

        for (size_t i = 0; i < sekcii[vert][polk].size(); i++) {
            if (sekcii[vert][polk][i].first == name && sekcii[vert][polk][i].second != 0) {
                suzh = true;
                if (sekcii[vert][polk][i].second >= count) {
                    sekcii[vert][polk][i].second -= count;
                    kol -= count;
                    cout << "Удалено " << count << ' ' << name << endl;
                }
                else {
                    cout << "Недостаточно товара для удаления" << endl;
                }
                break;
            }
        }
        if (!suzh) {
            cout << "Указанного товара нет в ячейке" << endl;
        }
    }
};

void geting_input(map<char, vector<Stelazh>>& zonez) {
    string input;

    while(true) {
        cin >> input;

        if (input == "ADD" || input == "REMOVE") {
            string name;
            int count;
            string yach;

            cin >> name;
            cin >> count;
            cin >> yach;

            char zone;
            int stel_id;
            int vert;
            int polk;

            int konec = 0;

            zone = yach[konec++];
            stel_id = yach[konec++] - '0';
            vert = yach[konec++] - '0';
            polk = yach[konec++] - '0';

            if (count > 0) {

                if ('A' <= zone && 'D' >= zone && stel_id <= 8 && stel_id > 0 && vert <= 2 && vert > 0 && polk == 1) {
                    if (input == "ADD") zonez[zone][stel_id - 1].add(name, count, vert - 1, polk - 1);
                    if (input == "REMOVE") zonez[zone][stel_id - 1].rem(name, count, vert - 1, polk - 1);
                }
                else {
                    cout << "Не существует такой ячейки" << endl;
                }
            }
            else {
                cout << "Некорректное значение количества" << endl;
            }
        }
        else if (input == "INFO") {
            cout << "Склад заполнен на " << kol / 640 * 100 << '%' << endl; // ADD Orange 8 B421
            vector<char> zonez_chars = { 'A', 'B', 'C', 'D' };
            for (size_t i = 0; i < zonez_chars.size(); i++) {
                double kolich = 0;

                cout << "Зона " << zonez_chars[i] << ':' << endl;

                for (int j = 0; j < 8; j++) {

                    for (size_t vert = 0; vert < 2; vert++) {
                        size_t g = 0;
                        int podschet = 0;

                        cout << "Ячейка " << zonez_chars[i] << j + 1 << vert + 1 << 1 << ": ";

                        for (g = 0; g < zonez[zonez_chars[i]][j].sekcii[vert][0].size(); g++) {
                            podschet++;
                            if (zonez[zonez_chars[i]][j].sekcii[vert][0][g].second != 0) {
                                kolich += zonez[zonez_chars[i]][j].sekcii[vert][0][g].second;
                                cout << zonez[zonez_chars[i]][j].sekcii[vert][0][g].first << ' ' << zonez[zonez_chars[i]][j].sekcii[vert][0][g].second << ' ';
                            }
                        }
                        while (podschet++ < 1) {
                            cout << "Пуста" << ' ';
                        }
                        cout << endl;
                    }

                }
                cout << "Заполненность зоны " << zonez_chars[i] << " - " << kolich / (640 / 4) * 100 << '%' << endl;
            }
        }
        else if (input == "END") {
            break;
        }
        else {
            cout << "Неизвестная команда" << endl;
        }
    }
    
}

int main() {
    setlocale(LC_ALL, "russian");

    map<char, vector<vector<int>>> main_map;
    int vert = 2, polk = 1, kol_stel = 8, kol_zone = 4;

    map<char, vector<Stelazh>> zonez;

    vector<char> zonez_chars = { 'A', 'B', 'C', 'D' };

    for (int i = 0; i < kol_zone; i++) {
        vector<Stelazh> stelazhi;
        for (int j = 0; j < kol_stel; j++) {
            Stelazh new_stelazh;
            new_stelazh.init(vert, polk);
            stelazhi.push_back(new_stelazh);
        }
        zonez[zonez_chars[i]] = stelazhi;
    }
    
    geting_input(zonez);
}


