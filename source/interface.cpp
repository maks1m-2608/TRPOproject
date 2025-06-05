#include "interface.h"

#include <iostream>         // для работы с потоками ввода / вывода
#include <conio.h>          // для работы с _getch()
#include <filesystem>       // для работы с файловой системой
#include <fstream>          // для работы с файлами
#include <regex>            // для работы с регулярными выражениями

Interface::Interface(Map& my_map) : my_map_(my_map) {}

int Interface::NumberSelection(int a, int b, int c) {
    int num(0); // для хранения кода символа
    while (1)
    {
        num = _getch();
        // выбор нажатой клавиши из диапазона / доп клавиши
        if (num >= a && num <= b || num == c)
        {
            break;
        }
    }
    return num;
}

void Interface::Realization() {
    // подключение русскоязычной раскладки
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // создание папок
    using std::filesystem::path;
    std::error_code err;
    path input_folder = path("Input");
    path output_folder = path("Output");
    std::filesystem::create_directories(input_folder, err);
    std::filesystem::create_directories(output_folder, err);
    StartMenu();
}

void Interface::StartMenu() {
    system("cls");
    std::cout << "     МЕНЮ ПРОГРАММЫ:     \n\n"
        << "Эта программа моделирует работу словаря с помощью бинарного дерева \n"
        << "Файлы, содержащие входные данные, должны быть расположены в папке \"Input\" \n"
        << "Файлы с выходными данными будут расположены в папке \"Output\" \n\n"
        << "Папки автоматически создаются в текущей директории программы. \n\n";

    system("pause");
    WorkMenu();
}

void Interface::WorkMenu()
{
    bool stop = false;      // флаг для работы цикла
    while (stop == false) {
        system("cls");
        int key,             // для хранения кода символа
            save;            // для хранения кода символа
        std::string time;    // для хранения текущего времени и даты

        std::cout << "Выберите дальнейшие действия, нажав соответствующую клавишу: \n"
            << "1   - добавить данные в словарь \n"
            << "2   - удалить данные из словаря \n"
            << "3   - узнать размер словаря \n"
            << "4   - вывести текущие данные словаря в консоль \n"
            << "5   - сохранить данные словаря в файл \n"
            << "esc - закрыть программу \n";

        key = NumberSelection('1', '5', 27);

        switch (key) {
        case '1':
            system("cls");
            AddMenu();
            break;
        case '2':
            system("cls");
            if (my_map_.Empty()) {
                std::cout << "Словарь пуст, нет данных для удаления!\n\n";
                system("pause");
            }
            else {
                DeleteMenu();
            }
            break;
        case '3':
            system("cls");
            std::cout << "Текущий размер словаря - " << my_map_.Size() << " элементов\n\n";
            system("pause");
            break;
        case '4':
            system("cls");
            if (my_map_.Empty()) {
                std::cout << "Словарь пуст! \n\n";
            }
            else {
                std::cout << "Данные выведены в формате - <key> <value>\n\n";
                my_map_.OutMapData(std::cout, false);
            }
            std::cout << std::endl;
            system("pause");
            break;
        case '5':
            system("cls");
            if (my_map_.Empty()) {
                std::cout << "Словарь пуст! \n\n";
            }
            else {
                SaveInFile();
            }
            system("pause");
            break;
        case 27:
            if (my_map_.CheckSaveData() == false && my_map_.Empty() != true) {
                system("cls");
                std::cout << "Вы не сохранили данные, сохранить данные в файл?\n"
                    << "1   - да \n"
                    << "2   - нет - в этом случае все данные будут утеряны \n";
                save = NumberSelection('1', '2');
                switch (save) {
                case '1':
                    SaveInFile();
                    break;
                case '2':
                    break;
                }
            }
            stop = true;
            break;
        }
    }
}

void Interface::AddMenu() {
    int key;            // для хранения кода символа
    bool stop = false;  // флаг для работы цикла

    while (stop == false) {
        system("cls");
        std::cout << "Выберите способ ввода информации, нажав соответствующую клавишу: \n"
            << "1   - с клавиатуры \n"
            << "2   - из файла \n"
            << "esc - вернуться в главное меню \n";

        key = NumberSelection('1', '2', 27);

        switch (key) {
        case '1':
            InputKeyboard();
            break;
        case '2':
            FindFileForInput();
            break;
        case 27:
            stop = true;
            break;
        }
    }
}

void Interface::InputKeyboard() {
    bool stop = false,          // флаги для работы циклов
        stop_key = false,
        stop_value = false;
    std::string key;            // ключ
    std::string value;          // значение
    std::string str;            // строка

    while (stop == false) {
        system("cls");
        std::cout << "Введите данные в формате <key> <value>\n\n";
        stop_key = false;
        stop_value = false;

        while (stop_key == false) {
            std::cout << "Введите ключ (для выхода - exit) - ";
            std::getline(std::cin, key);
            if (!key.empty()) {
                stop_key = true;
            }
        }

        if (key == "exit") {
            stop = true;
            continue;
        }

        while (stop_value == false) {
            std::cout << "Введите значение (для выхода - exit) - ";
            std::getline(std::cin, value);
            if (!value.empty()) {
                stop_value = true;
            }
        }

        if (value == "exit") {
            stop = true;
            continue;
        }

        my_map_.Insert({ key, value });
        std::cout << "\nданные успешно добавлены: key - " << key << " value - " << value << std::endl;
        system("pause");
    }
}

void Interface::FindFileForInput() {
    using std::filesystem::path;
    path cur_path = std::filesystem::current_path();     // путь к текущей директории
    path input_path;    // входной путь
    bool stop = false;  // флаг для работы цикла
    std::string str;

    while (stop == false) {
        system("cls");

        bool check_cout = false;
        input_path = cur_path / path("Input");

        // перебор всей директории
        for (auto it : std::filesystem::directory_iterator(input_path)) {
            if (check_cout == false) {
                std::cout << "Список файлов в папке Input: " << std::endl;
                check_cout = true;
            }
            auto status = std::filesystem::status(it);
            path file_path(it);

            // если it - это файл - вывести его в консоль
            if (status.type() == std::filesystem::file_type::regular) {
                std::cout << file_path.filename().string() << std::endl;
            }
        }

        std::cout << "\nВведите название файла, для выхода введите - exit: \n";

        std::getline(std::cin, str);

        if (str == "exit") {
            return;
        }
        if (str.empty()) {
            std::cout << "Вы ничего не ввели, попробуйте еще раз\n\n";
            system("pause");
            continue;
        }

        input_path = input_path / path(str);

        if (std::filesystem::exists(input_path) == false) {
            std::cout << "Данный файл не найден, попробуйте еще раз \n\n";
            system("pause");
            continue;
        }
        else {
            std::cout << "Вы открыли файл " << input_path.filename().string() << std::endl
                << "Путь к файлу: " << input_path.string() << std::endl << std::endl;
            stop = true;
            system("pause");
            InputFromFile(input_path.string());
            system("pause");
        }
    }
}

void Interface::InputFromFile(std::string name) {
    system("cls");

    std::string str;
    std::string key;
    std::string value;
    std::fstream file;
    file.open(name, std::fstream::in);
    int pos1 = 0, 
        pos2 = 0;

    std::cout << "В словарь добавлены данные в формате <key> <value>:\n\n";

    while (!file.eof()) {
        key.clear();
        value.clear();
        pos1 = 0;
        pos2 = 0;

        std::getline(file, str);

        if (str.empty()) {
            continue;
        }

        pos1 = str.find("\"");
        pos2 = str.find("\"", pos1 + 1);
        key.append(str, pos1 + 1, pos2 - pos1 - 1);

        pos1 = str.find("\"", pos2 + 1);
        pos2 = str.find("\"", pos1 + 1);
        value.append(str, pos1 + 1, pos2 - pos1 - 1);

        my_map_.Insert({ key, value });
        std::cout << "\"" << key << "\" " << "\"" << value << "\"" << std::endl;
    }
    std::cout << std::endl;
}

void Interface::DeleteMenu() {
    int key;            // для хранения кода символа
    bool stop = false;  // флаг для работы цикла

    while (stop == false) {
        system("cls");
        std::cout << "Выберите информацию, которую нужно удалить: \n"
            << "1   - удалить элемент из словаря \n"
            << "2   - очистить словарь \n"
            << "esc - вернуться в главное меню \n";

        key = NumberSelection('1', '2', 27);

        switch (key) {
        case '1':
            if (my_map_.Empty()) {
                std::cout << "Словарь пуст, нет данных для удаления!\n\n";
                system("pause");
            }
            else {
                DeleteElem();
            }
            break;
        case '2':
            if (my_map_.Empty()) {
                std::cout << "Словарь пуст, нет данных для удаления!\n\n";
                system("pause");
            }
            else {
                DeleteAllData();
            }
            break;
        case 27:
            stop = true;
            break;
        }
    }
}

void Interface::DeleteElem() {
    bool stop = false;
    std::string key;
    while (stop == false) {
        system("cls");
        std::cout << "Текущие элементы словаря в формате <key> <value>\n\n";
        my_map_.OutMapData(std::cout, false);
        std::cout << "\nВведите ключ элемента, который нужно удалить (для выхода - exit): \n";
        std::getline(std::cin, key);
        if (key.empty()) {
            continue;
        }
        if (key == "exit") {
            stop = true;
            continue;
        }
        if (my_map_.Find(key) == nullptr) {
            std::cout << "Удаляемый элемент не найден!\n";
        }
        else {
            my_map_.Erase(key);
            std::cout << "Элемент с ключом - " << key << " удален из словаря\n\n";
        }
        system("pause");
    }
}

void Interface::DeleteAllData() {
    system("cls");

    int key;         // для хранения кода символа
    std::cout << "Вы точно хотите безвозвратно удалить всю информацию из дерева? \n"
        << "1   - да, удалить все данные \n"
        << "esc - вернуться в главное меню \n";

    key = NumberSelection('1', '1', 27);

    switch (key) {
    case '1':
        my_map_.Clear();
        std::cout << "\nДанные успешно удалены!\n\n";
        system("pause");
        break;
    case 27:
        break;
    }

}

std::string Interface::FindTime() {
    std::string date_now;     // строка для записи данных

    // определение текущего времени
    time_t now;
    tm date;
    time(&now);
    localtime_s(&date, &now);

    date_now.append(" ");

    if (date.tm_mday < 10) { date_now.append("0"); }
    date_now.append(std::to_string(date.tm_mday).append("."));

    if (date.tm_mon + 1 < 10) { date_now.append("0"); }
    date_now.append(std::to_string(date.tm_mon + 1).append("."));

    date_now.append(std::to_string(date.tm_year + 1900).append(" "));

    date_now.append(std::to_string(date.tm_hour).append("."));

    if (date.tm_min < 10) { date_now.append("0"); }
    date_now.append(std::to_string(date.tm_min).append("."));

    if (date.tm_sec < 10) { date_now.append("0"); }
    date_now.append(std::to_string(date.tm_sec));

    return date_now;
}

void Interface::SaveInFile() {
    system("cls");
    using std::filesystem::path;

    std::string time = FindTime();

    // путь к текущей директории программы
    path cur_path = std::filesystem::current_path();
    // путь к выходному файлу с данными
    cur_path = cur_path / path("Output") / path("result by" + time + ".txt");

    std::fstream file;
    file.open(cur_path, std::fstream::out);
    my_map_.OutMapData(file, true);
    file.close();

    std::cout << "Данные сохранены в файл: " << cur_path.filename().string() << std::endl
        << "Путь к файлу: " << cur_path.string() << std::endl << std::endl;
}
