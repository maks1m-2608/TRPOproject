#pragma once
#include <iostream>
#include <string>

// Узел дерева, хранящий ключ и значение
struct Element {
    Element();
    Element(const Element& other);
    Element(std::string key_, std::string value_);

    std::string key;
    std::string value;
    Element* parent = nullptr;
    Element* left_son = nullptr;
    Element* right_son = nullptr;

    // Возвращает следующий элемент в порядке in-order
    Element* Next() const;
    // Возвращает первый (минимальный) элемент в поддереве
    static Element* First(Element* root);
};

// Пара ключ-значение для итератора
struct Pair {
    Pair(const std::string& key, const std::string& value);
    Pair();

    std::string key_;
    std::string value_;
};

// Ассоциативный массив на основе бинарного дерева
class Map {
public:
    // Итератор для обхода элементов в порядке возрастания ключей
    class Iterator {
    public:
        Iterator(Element* current);

        // Получить текущую пару ключ-значение
        Pair operator*() const;
        // Перейти к следующему элементу (префиксный инкремент)
        Iterator& operator++();
        // Перейти к следующему элементу (постфиксный инкремент)
        Iterator operator++(int);
        // Проверка на равенство итераторов
        bool operator==(const Iterator& other) const;
        // Проверка на неравенство итераторов
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

    // Конструктор по умолчанию
    Map();
    // Проверка на пустоту контейнера
    bool Empty() const;
    // Вставка элемента
    Element* Insert(const Element& element);
    // Поиск элемента по ключу (неконстантная версия)
    Element* Find(const std::string& key);
    // Поиск элемента по ключу (константная версия)
    Element* Find(const std::string& key) const;
    // Получение значения по ключу (с проверкой)
    std::string At(const std::string& key) const;
    // Удаление элемента по ключу
    void Erase(std::string key);
    // Размер словаря
    size_t Size() const;
    // Очистка контейнера
    void Clear();
    // Доступ к значению по ключу (с автоматической вставкой при отсутствии)
    std::string& operator[](std::string key);
    // Итератор на первый элемент
    iterator begin();
    // Итератор на позицию после последнего элемента
    iterator end();
    // Константный итератор на первый элемент
    const_iterator begin() const;
    // Константный итератор на позицию после последнего элемента
    const_iterator end() const;
    // вывод всех данных
    void OutMapData(std::ostream& out, bool check);
    // проверка сохранения данных
    bool CheckSaveData() const;

private:
    // Вспомогательная функция для вставки
    Element* InsertInMap(Element* elem, Element*& node);
    // Вспомогательная функция для поиска
    Element* FindInMap(const std::string& key, Element* node) const;
    // Вспомогательная функция для удаления
    void EraseElem(const std::string& key, Element*& node);
    // Поиск максимального элемента в поддереве
    Element* FindMax(Element* node);
    // Вспомогательная функция для очистки
    Element* ClearMap(Element*& node);
    // Вспомогательная функция для вывода данных
    void OutData(std::ostream& out, Element* node) const;

    Element* root_ = nullptr;  // Корень дерева
    size_t size_ = 0;          // Количество элементов
    bool check_save_ = true;   // Флаг изменения контейнера
};