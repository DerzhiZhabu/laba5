kol = 0  # Глобальная переменная kol типа double и ее инициализация значением 0

class Stelazh:  # Определение класса Stelazh
    def __init__(self):
        self.sekcii = []  # Вектор для хранения ячеек с товарами

    def init(self, vert, polk):  # Метод для инициализации секций стеллажа
        for i in range(vert):
            polki = []  # Вектор для хранения полок
            for j in range(polk):
                polki.append([])  # Добавление пустого вектора пар (название товара, количество) в вектор полок
            self.sekcii.append(polki)  # Добавление вектора полок в вектор секций

    def add(self, name, count, vert, polk):  # Метод для добавления товара в ячейку
        kolich = 0  # Переменная для хранения общего количества товаров в ячейке
        suzh = False  # Флаг, указывающий на наличие товара в ячейке
        ind = 0  # Индекс товара в ячейке

        for i in range(len(self.sekcii[vert][polk])):
            kolich += self.sekcii[vert][polk][i][1]  # Суммирование количества товаров в ячейке
            if self.sekcii[vert][polk][i][0] == name:
                suzh = True  # Установка флага, если товар найден
                ind = i  # Сохранение индекса найденного товара

        if kolich + count > 10:  # Проверка, достаточно ли места в ячейке
            print("Не достаточно места в ячейке")
        else:
            if suzh:
                self.sekcii[vert][polk][ind][1] += count  # Увеличение количества товара в ячейке
                global kol
                kol += count  # Увеличение общего количества товаров на складе
            else:
                self.sekcii[vert][polk].append([name, count])  # Добавление нового товара в ячейку
                kol += count  # Увеличение общего количества товаров на складе
            print(f"Добавлено {count} {name}")

    def rem(self, name, count, vert, polk):  # Метод для удаления товара из ячейки
        suzh = False  # Флаг, указывающий на наличие товара в ячейке

        for i in range(len(self.sekcii[vert][polk])):
            if self.sekcii[vert][polk][i][0] == name and self.sekcii[vert][polk][i][1] != 0:
                suzh = True  # Установка флага, если товар найден
                if self.sekcii[vert][polk][i][1] >= count:
                    self.sekcii[vert][polk][i][1] -= count  # Уменьшение количества товара в ячейке
                    global kol
                    kol -= count  # Уменьшение общего количества товаров на складе
                    print(f"Удалено {count} {name}")
                else:
                    print("Недостаточно товара для удаления")
                break
        if not suzh:
            print("Указанного товара нет в ячейке")

def geting_input(zonez):  # Функция для получения ввода от пользователя и выполнения команд
    while True:
        input_str = input()  # Чтение ввода пользователя

        if input_str == "ADD" or input_str == "REMOVE":  # Проверка на команду добавления или удаления товара
            name = input()  # Чтение названия товара
            count = int(input())  # Чтение количества товара
            yach = input()  # Чтение кода ячейки

            zone = yach[0]  # Чтение зоны из кода ячейки
            stel_id = int(yach[1])  # Чтение идентификатора стеллажа из кода ячейки
            vert = int(yach[2])  # Чтение вертикального индекса ячейки из кода ячейки
            polk = int(yach[3])  # Чтение горизонтального индекса ячейки из кода ячейки

            if count > 0:  # Проверка на корректное количество товара
                if 'A' <= zone <= 'D' and 1 <= stel_id <= 8 and 1 <= vert <= 2 and polk == 1:
                    # Проверка на существование ячейки
                    if input_str == "ADD":
                        zonez[zone][stel_id - 1].add(name, count, vert - 1, polk - 1)  # Вызов метода добавления товара
                    if input_str == "REMOVE":
                        zonez[zone][stel_id - 1].rem(name, count, vert - 1, polk - 1)  # Вызов метода удаления товара
                else:
                    print("Не существует такой ячейки")
            else:
                print("Некорректное значение количества")
        elif input_str == "INFO":  # Проверка на команду получения информации
            print(f"Склад заполнен на {kol / 640 * 100}%")  # Вывод заполненности склада в процентах
            zonez_chars = ['A', 'B', 'C', 'D']  # Вектор для хранения символов зон
            for i in range(len(zonez_chars)):
                kolich = 0  # Переменная для хранения заполненности зоны

                print(f"Зона {zonez_chars[i]}:")  # Вывод названия зоны

                for j in range(8):
                    for vert in range(2):
                        g = 0  # Переменная для итерации по товарам в ячейке
                        podschet = 0  # Переменная для подсчета количества товаров в ячейке

                        print(f"Ячейка {zonez_chars[i]}{j + 1}{vert + 1}1: ", end="")  # Вывод названия ячейки

                        for g in range(len(zonez[zonez_chars[i]][j].sekcii[vert][0])):
                            podschet += 1  # Увеличение счетчика товаров
                            if zonez[zonez_chars[i]][j].sekcii[vert][0][g][1] != 0:
                                kolich += zonez[zonez_chars[i]][j].sekcii[vert][0][g][1]  # Суммирование количества товаров в зоне
                                print(f"{zonez[zonez_chars[i]][j].sekcii[vert][0][g][0]} {zonez[zonez_chars[i]][j].sekcii[vert][0][g][1]}", end=" ")  # Вывод информации о товаре

                        while podschet < 1:
                            print("Пуста", end=" ")  # Вывод информации о пустой ячейке
                            podschet += 1
                        print()

                print(f"Заполненность зоны {zonez_chars[i]} - {kolich / (640 / 4) * 100}%")  # Вывод заполненности зоны в процентах
        elif input_str == "END":  # Проверка на команду завершения программы
            break  # Выход из цикла
        else:
            print("Неизвестная команда")  # Вывод сообщения об ошибке для неизвестных
def main():
    vert = 2  # Определение количества элементов
    polk = 1
    kol_stel = 8
    kol_zone = 4

    zonez = {}  # Объявление карты для хранения зон и стеллажей

    zonez_chars = ['A', 'B', 'C', 'D']  # Вектор для хранения символов зон

    for i in range(kol_zone):
        stelazhi = []  # Вектор для хранения стеллажей в зоне
        for j in range(kol_stel):
            new_stelazh = Stelazh()  # Создание нового стеллажа
            new_stelazh.init(vert, polk)  # Инициализация стеллажа
            stelazhi.append(new_stelazh)  # Добавление стеллажа в вектор
        zonez[zonez_chars[i]] = stelazhi  # Добавление вектора стеллажей в карту зон

    geting_input(zonez)  # Вызов функции для получения ввода от пользователя и выполнения команд

if __name__ == "__main__":
    main()