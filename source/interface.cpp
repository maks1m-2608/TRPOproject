#include "interface.h"

#include <iostream>         // ˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜ / ˜˜˜˜˜˜
#include <conio.h>          // ˜˜˜ ˜˜˜˜˜˜ ˜ _getch()
#include <filesystem>       // ˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜
#include <fstream>          // ˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜
#include <regex>            // ˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜
#include <Windows.h>        // ˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜

Interface::Interface(Map& my_map) : my_map_(my_map) {}

int Interface::NumberSelection(int a, int b, int c) {
    int num(0); // ˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜
    while (1)
    {
        num = _getch();
        // ˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜ / ˜˜˜ ˜˜˜˜˜˜˜
        if (num >= a && num <= b || num == c)
        {
            break;
        }
    }
    return num;
}

void Interface::Realization() {
    // ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ˜˜˜˜˜˜˜˜ ˜˜˜˜˜
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
    std::cout << "     ˜˜˜˜ ˜˜˜˜˜˜˜˜˜:     \n\n"
        << "˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ \n"
        << "˜˜˜˜˜, ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜, ˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜ \"Input\" \n"
        << "˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜ \"Output\" \n\n"
        << "˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜. \n\n";

    system("pause");
    WorkMenu();
}

void Interface::WorkMenu()
{
    bool stop = false;      // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜
    while (stop == false) {
        system("cls");
        int key,             // ˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜
            save;            // ˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜
        std::string time;    // ˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜

        std::cout << "˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜, ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜: \n"
            << "1   - ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ \n"
            << "2   - ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜ \n"
            << "3   - ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜ \n"
            << "4   - ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ \n"
            << "5   - ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜ \n"
            << "esc - ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ \n";

        key = NumberSelection('1', '5', 27);

        switch (key) {
        case '1':
            system("cls");
            AddMenu();
            break;
        case '2':
            system("cls");
            if (my_map_.Empty()) {
                std::cout << "˜˜˜˜˜˜˜ ˜˜˜˜, ˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜!\n\n";
                system("pause");
            }
            else {
                DeleteMenu();
            }
            break;
        case '3':
            system("cls");
            std::cout << "˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜ - " << my_map_.Size() << " ˜˜˜˜˜˜˜˜˜\n\n";
            system("pause");
            break;
        case '4':
            system("cls");
            if (my_map_.Empty()) {
                std::cout << "˜˜˜˜˜˜˜ ˜˜˜˜! \n\n";
            }
            else {
                std::cout << "˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ - <key> <value>\n\n";
                my_map_.OutMapData(std::cout, false);
            }
            std::cout << std::endl;
            system("pause");
            break;
        case '5':
            system("cls");
            if (my_map_.Empty()) {
                std::cout << "˜˜˜˜˜˜˜ ˜˜˜˜! \n\n";
            }
            else {
                SaveInFile();
            }
            system("pause");
            break;
        case 27:
            if (my_map_.CheckSaveData() == false && my_map_.Empty() != true) {
                system("cls");
                std::cout << "˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜, ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜?\n"
                    << "1   - ˜˜ \n"
                    << "2   - ˜˜˜ - ˜ ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜ \n";
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
    int key;            // ˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜
    bool stop = false;  // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜

    while (stop == false) {
        system("cls");
        std::cout << "˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜, ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜: \n"
            << "1   - ˜ ˜˜˜˜˜˜˜˜˜˜ \n"
            << "2   - ˜˜ ˜˜˜˜˜ \n"
            << "esc - ˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜ \n";

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
    bool stop = false,          // ˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜
        stop_key = false,
        stop_value = false;
    std::string key;            // ˜˜˜˜
    std::string value;          // ˜˜˜˜˜˜˜˜
    std::string str;            // ˜˜˜˜˜˜

    while (stop == false) {
        system("cls");
        std::cout << "˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ <key> <value>\n\n";
        stop_key = false;
        stop_value = false;

        while (stop_key == false) {
            std::cout << "˜˜˜˜˜˜˜ ˜˜˜˜ (˜˜˜ ˜˜˜˜˜˜ - exit) - ";
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
            std::cout << "˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ (˜˜˜ ˜˜˜˜˜˜ - exit) - ";
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
        std::cout << "\n˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜: key - " << key << " value - " << value << std::endl;
        system("pause");
    }
}

void Interface::FindFileForInput() {
    using std::filesystem::path;
    path cur_path = std::filesystem::current_path();     // ˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜
    path input_path;    // ˜˜˜˜˜˜˜ ˜˜˜˜
    bool stop = false;  // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜
    std::string str;

    while (stop == false) {
        system("cls");

        bool check_cout = false;
        input_path = cur_path / path("Input");

        // ˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜
        for (auto it : std::filesystem::directory_iterator(input_path)) {
            if (check_cout == false) {
                std::cout << "˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜ Input: " << std::endl;
                check_cout = true;
            }
            auto status = std::filesystem::status(it);
            path file_path(it);

            // ˜˜˜˜ it - ˜˜˜ ˜˜˜˜ - ˜˜˜˜˜˜˜ ˜˜˜ ˜ ˜˜˜˜˜˜˜
            if (status.type() == std::filesystem::file_type::regular) {
                std::cout << file_path.filename().string() << std::endl;
            }
        }

        std::cout << "\n˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜, ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜ - exit: \n";

        std::getline(std::cin, str);

        if (str == "exit") {
            return;
        }
        if (str.empty()) {
            std::cout << "˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜, ˜˜˜˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜\n\n";
            system("pause");
            continue;
        }

        input_path = input_path / path(str);

        if (std::filesystem::exists(input_path) == false) {
            std::cout << "˜˜˜˜˜˜ ˜˜˜˜ ˜˜ ˜˜˜˜˜˜, ˜˜˜˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜ \n\n";
            system("pause");
            continue;
        }
        else {
            std::cout << "˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜ " << input_path.filename().string() << std::endl
                << "˜˜˜˜ ˜ ˜˜˜˜˜: " << input_path.string() << std::endl << std::endl;
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

    std::cout << "˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ <key> <value>:\n\n";

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
    int key;            // ˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜
    bool stop = false;  // ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜

    while (stop == false) {
        system("cls");
        std::cout << "˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜, ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜: \n"
            << "1   - ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜ \n"
            << "2   - ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ \n"
            << "esc - ˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜ \n";

        key = NumberSelection('1', '2', 27);

        switch (key) {
        case '1':
            if (my_map_.Empty()) {
                std::cout << "˜˜˜˜˜˜˜ ˜˜˜˜, ˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜!\n\n";
                system("pause");
            }
            else {
                DeleteElem();
            }
            break;
        case '2':
            if (my_map_.Empty()) {
                std::cout << "˜˜˜˜˜˜˜ ˜˜˜˜, ˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜!\n\n";
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
        std::cout << "˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ <key> <value>\n\n";
        my_map_.OutMapData(std::cout, false);
        std::cout << "\n˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜˜, ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜ (˜˜˜ ˜˜˜˜˜˜ - exit): \n";
        std::getline(std::cin, key);
        if (key.empty()) {
            continue;
        }
        if (key == "exit") {
            stop = true;
            continue;
        }
        if (my_map_.Find(key) == nullptr) {
            std::cout << "˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜!\n";
        }
        else {
            my_map_.Erase(key);
            std::cout << "˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜ - " << key << " ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜\n\n";
        }
        system("pause");
    }
}

void Interface::DeleteAllData() {
    system("cls");

    int key;         // ˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜
    std::cout << "˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜? \n"
        << "1   - ˜˜, ˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ \n"
        << "esc - ˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜ \n";

    key = NumberSelection('1', '1', 27);

    switch (key) {
    case '1':
        my_map_.Clear();
        std::cout << "\n˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜!\n\n";
        system("pause");
        break;
    case 27:
        break;
    }

}

std::string Interface::FindTime() {
    std::string date_now;     // ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜

    // ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜
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

    // ˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
    path cur_path = std::filesystem::current_path();
    // ˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜
    cur_path = cur_path / path("Output") / path("result by" + time + ".txt");

    std::fstream file;
    file.open(cur_path, std::fstream::out);
    my_map_.OutMapData(file, true);
    file.close();

    std::cout << "˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜: " << cur_path.filename().string() << std::endl
        << "˜˜˜˜ ˜ ˜˜˜˜˜: " << cur_path.string() << std::endl << std::endl;
}
