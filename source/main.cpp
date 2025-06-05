#include "my_map.h"
#include "interface.h"
#include <fstream>

#include <iostream>

using namespace std;

void Tests() {
    {
        cout << "тест на правильную работу словаря - добавление и лексикографическое упорядочение данных" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        cout << "ключи добавляемых элементов - 111, 333, 222" << endl;
        cout << "Данные в упорядоченном виде:" << endl;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        mp.OutMapData(cout, false);
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }

    {
        cout << "тест на корректную работу оператора []" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        cout << "Данные до изменения:" << endl;
        mp.OutMapData(cout, false);
        cout << "Изменение значения элемента с ключом - [111], было - 111, стало - 999: " << endl;
        cout << "Данные после изменения:" << endl;
        mp["111"] = "999";
        mp.OutMapData(cout, false);
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }

    {
        cout << "тест на работу итераторов №1" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        cout << "вывод данных с помощью цикла for с использованием итераторов:" << endl;
        for (auto [key, value] : mp) {
            cout << key << " " << value << endl;
        }
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }

    {
        cout << "тест на работу итераторов №2" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        cout << "данные в словаре:" << endl;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        mp.OutMapData(cout, false);
        cout << "используя итератор на начало словаря - begin(), выведем информацию о первом элемента словаря:" << endl;
        auto it = *mp.begin();
        cout << it.key_ << " " << it.value_ << endl;
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }

    {
        cout << "тест на работу функции удаления данных из словаря" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        cout << "данные в словаре до удаления элемента:" << endl;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        mp.OutMapData(cout, false);
        cout << "удалим элемент с ключом - [222]:" << endl;
        mp.Erase("222");
        cout << "данные в словаре после удаления элемента:" << endl;
        mp.OutMapData(cout, false);
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }

    {
        cout << "тест на безопасный доступ к значению" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        cout << "данные в словаре до взятия значения:" << endl;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        mp.OutMapData(cout, false);
        cout << "с помощью фукнции at() возьмем значение элемента с ключом - [333] и выведем его:" << endl;
        cout << "-------------------" << endl;
        cout << mp.At("333") << endl;
        cout << "-------------------" << endl;
        cout << "данные в словаре после взятия значения:" << endl;
        mp.OutMapData(cout, false);
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    Tests();
    system("pause");

    Map my_map;
    Interface interface(my_map);
    interface.Realization();
}