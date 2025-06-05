#pragma once
#include <iostream>
#include <string>

// ���� ������, �������� ���� � ��������
struct Element {
    Element();
    Element(const Element& other);
    Element(std::string key_, std::string value_);

    std::string key;
    std::string value;
    Element* parent = nullptr;
    Element* left_son = nullptr;
    Element* right_son = nullptr;

    // ���������� ��������� ������� � ������� in-order
    Element* Next() const;
    // ���������� ������ (�����������) ������� � ���������
    static Element* First(Element* root);
};

// ���� ����-�������� ��� ���������
struct Pair {
    Pair(const std::string& key, const std::string& value);
    Pair();

    std::string key_;
    std::string value_;
};

// ������������� ������ �� ������ ��������� ������
class Map {
public:
    // �������� ��� ������ ��������� � ������� ����������� ������
    class Iterator {
    public:
        Iterator(Element* current);

        // �������� ������� ���� ����-��������
        Pair operator*() const;
        // ������� � ���������� �������� (���������� ���������)
        Iterator& operator++();
        // ������� � ���������� �������� (����������� ���������)
        Iterator operator++(int);
        // �������� �� ��������� ����������
        bool operator==(const Iterator& other) const;
        // �������� �� ����������� ����������
        bool operator!=(const Iterator& other) const;

    private:
        Element* current_ = nullptr;
    };

    class ConstIterator {
    public:
        ConstIterator(const Element* current);

        Pair operator*() const;
        ConstIterator& operator++();
        ConstIterator operator++(int);
        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        const Element* current_ = nullptr;
    };

    using iterator = Iterator;
    using const_iterator = ConstIterator;

    // ����������� �� ���������
    Map();
    // �������� �� ������� ����������
    bool Empty() const;
    // ������� ��������
    Element* Insert(const Element& element);
    // ����� �������� �� ����� (������������� ������)
    Element* Find(const std::string& key);
    // ����� �������� �� ����� (����������� ������)
    Element* Find(const std::string& key) const;
    // ��������� �������� �� ����� (� ���������)
    std::string At(const std::string& key) const;
    // �������� �������� �� �����
    void Erase(std::string key);
    // ������ �������
    size_t Size() const;
    // ������� ����������
    void Clear();
    // ������ � �������� �� ����� (� �������������� �������� ��� ����������)
    std::string& operator[](std::string key);
    // �������� �� ������ �������
    iterator begin();
    // �������� �� ������� ����� ���������� ��������
    iterator end();
    // ����������� �������� �� ������ �������
    const_iterator begin() const;
    // ����������� �������� �� ������� ����� ���������� ��������
    const_iterator end() const;
    // ����� ���� ������
    void OutMapData(std::ostream& out, bool check);
    // �������� ���������� ������
    bool CheckSaveData() const;

private:
    // ��������������� ������� ��� �������
    Element* InsertInMap(Element* elem, Element*& node);
    // ��������������� ������� ��� ������
    Element* FindInMap(const std::string& key, Element* node) const;
    // ��������������� ������� ��� ��������
    void EraseElem(const std::string& key, Element*& node);
    // ����� ������������� �������� � ���������
    Element* FindMax(Element* node);
    // ��������������� ������� ��� �������
    Element* ClearMap(Element*& node);
    // ��������������� ������� ��� ������ ������
    void OutData(std::ostream& out, Element* node) const;

    Element* root_ = nullptr;  // ������ ������
    size_t size_ = 0;          // ���������� ���������
    bool check_save_ = true;   // ���� ��������� ����������
};