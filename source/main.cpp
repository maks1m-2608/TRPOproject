#include "my_map.h"
#include "interface.h"
#include <fstream>

#include <iostream>

using namespace std;

void Tests() {
    {
        cout << "���� �� ���������� ������ ������� - ���������� � ������������������ ������������ ������" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        cout << "����� ����������� ��������� - 111, 333, 222" << endl;
        cout << "������ � ������������� ����:" << endl;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        mp.OutMapData(cout, false);
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }

    {
        cout << "���� �� ���������� ������ ��������� []" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        cout << "������ �� ���������:" << endl;
        mp.OutMapData(cout, false);
        cout << "��������� �������� �������� � ������ - [111], ���� - 111, ����� - 999: " << endl;
        cout << "������ ����� ���������:" << endl;
        mp["111"] = "999";
        mp.OutMapData(cout, false);
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }

    {
        cout << "���� �� ������ ���������� �1" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        cout << "����� ������ � ������� ����� for � �������������� ����������:" << endl;
        for (auto [key, value] : mp) {
            cout << key << " " << value << endl;
        }
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }

    {
        cout << "���� �� ������ ���������� �2" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        cout << "������ � �������:" << endl;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        mp.OutMapData(cout, false);
        cout << "��������� �������� �� ������ ������� - begin(), ������� ���������� � ������ �������� �������:" << endl;
        auto it = *mp.begin();
        cout << it.key_ << " " << it.value_ << endl;
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }

    {
        cout << "���� �� ������ ������� �������� ������ �� �������" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        cout << "������ � ������� �� �������� ��������:" << endl;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        mp.OutMapData(cout, false);
        cout << "������ ������� � ������ - [222]:" << endl;
        mp.Erase("222");
        cout << "������ � ������� ����� �������� ��������:" << endl;
        mp.OutMapData(cout, false);
        cout << "------------------------------" << endl;
        cout << endl << endl;
    }

    {
        cout << "���� �� ���������� ������ � ��������" << endl;
        cout << "------------------------------" << endl;
        Map mp;
        cout << "������ � ������� �� ������ ��������:" << endl;
        mp.Insert({ "111", "111" });
        mp.Insert({ "333", "111" });
        mp.Insert({ "222", "111" });
        mp.OutMapData(cout, false);
        cout << "� ������� ������� at() ������� �������� �������� � ������ - [333] � ������� ���:" << endl;
        cout << "-------------------" << endl;
        cout << mp.At("333") << endl;
        cout << "-------------------" << endl;
        cout << "������ � ������� ����� ������ ��������:" << endl;
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