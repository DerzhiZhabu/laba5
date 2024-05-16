import sys

# Функция для добавления занятия в расписание
def add_class(day, name, month, university, days):
    exists = False  # Флаг, указывающий, существует ли указанный день в месяце
    for i in range(len(days[month])):
        if days[month][i] == day:
            exists = True
            break

    if exists:
        predm_exists = False  # Флаг, указывающий, существует ли уже такое занятие в расписании

        for i in range(len(university[month][day])):
            if university[month][day][i] == name:
                predm_exists = True
                break
        if not predm_exists:
            university[month][day].append(name)  # Добавление занятия в расписание, если оно еще не существует
    else:
        university[month][day] = [name]  # Создание нового дня в месяце и добавление занятия
        days[month].append(day)

# Функция для перехода к следующему месяцу
def next_month(month, monthes, university, days):
    month += 1  # Увеличение номера месяца
    if month > 12:
        month = 1  # Если месяц больше 12, то устанавливаем 1

    month_exists = False  # Флаг, указывающий, существует ли уже такой месяц в списке
    for i in range(len(monthes)):
        if monthes[i] == month:
            month_exists = True
            break

    if not month_exists:
        university[month] = {}  # Создание нового месяца в расписании
        days[month] = []

# Функция для просмотра расписания на определенный день
def view(day, month, university, days):
    exists = False  # Флаг, указывающий, существует ли указанный день в месяце

    for i in range(len(days[month])):
        if days[month][i] == day:
            exists = True
            break

    if exists:
        print(f"In {day} day {len(university[month][day])} classes in university: ", end="")  # Вывод количества занятий в университете
        for i in range(len(university[month][day])):
            print(university[month][day][i], end=" ")  # Вывод названий занятий
        print()
    else:
        print(f"In {day} day We are free!")  # Вывод сообщения о том, что день свободен
        print()

def main():
    month = 1  # Начальный месяц
    monthes = [1]  # Список месяцев
    university = {month: {}}  # Расписание занятий в университете
    days = {month: []}  # Список дней в месяцах

    while True:
        command = input()  # Ввод команды
        if command == "CLASS":
            day = int(input())  # Ввод дня
            name = input()  # Ввод названия занятия
            add_class(day, name, month, university, days)  # Добавление занятия в расписание
        elif command == "NEXT":
            next_month(month, monthes, university, days)  # Переход к следующему месяцу
        elif command == "VIEW":
            day = int(input())  # Ввод дня для просмотра расписания
            view(day, month, university, days)  # Просмотр расписания на указанный день

if __name__ == "__main__":
    main()