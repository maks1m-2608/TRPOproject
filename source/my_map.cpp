#include "my_map.h"

// Реализация методов структуры Element

// Реализация методов структуры Element
Element::Element() {}

Element::Element(const Element& other) {
    key = other.key;
    value = other.value;
}

Element::Element(std::string key_, std::string value_) {
    key = key_;
    value = value_;
}

Element* Element::Next() const {
    const Element* current = this;
    if (current->right_son) {
        current = current->right_son;
        while (current->left_son) {
            current = current->left_son;
        }
        return const_cast<Element*>(current);
    }
    while (current->parent && current == current->parent->right_son) {
        current = current->parent;
    }
    return const_cast<Element*>(current->parent);
}

Element* Element::First(Element* root) {
    if (!root) return nullptr;
    Element* current = root;
    while (current->left_son) {
        current = current->left_son;
    }
    return current;
}

// Реализация методов структуры Pair

Pair::Pair(const std::string& key, const std::string& value) : key_(key), value_(value) {}

Pair::Pair() : key_(), value_() {}

// Реализация методов класса Map::Iterator

Map::Iterator::Iterator(Element* current) : current_(current) {}

Pair Map::Iterator::operator*() const {
    if (!current_) return Pair();
    return Pair(current_->key, current_->value);
}

Map::Iterator& Map::Iterator::operator++() {
    if (current_) {
        current_ = current_->Next();
    }
    return *this;
}

Map::Iterator Map::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

bool Map::Iterator::operator==(const Iterator& other) const {
    return current_ == other.current_;
}

bool Map::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

// Реализация методов класса Map::ConstIterator

Map::ConstIterator::ConstIterator(const Element* current) : current_(current) {}

Pair Map::ConstIterator::operator*() const {
    if (!current_) return Pair();
    return Pair(current_->key, current_->value);
}

Map::ConstIterator& Map::ConstIterator::operator++() {
    if (current_) {
        current_ = current_->Next();
    }
    return *this;
}

Map::ConstIterator Map::ConstIterator::operator++(int) {
    ConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

bool Map::ConstIterator::operator==(const ConstIterator& other) const {
    return current_ == other.current_;
}

bool Map::ConstIterator::operator!=(const ConstIterator& other) const {
    return !(*this == other);
}

// Реализация методов класса Map

Map::Map() : root_(nullptr), size_(0), check_save_(true) { }

bool Map::Empty() const {
    return size_ == 0;
}

Element* Map::InsertInMap(Element* elem, Element*& node) {
    if (root_ == nullptr && root_ == node) {
        root_ = elem;
        return nullptr;
    }

    Element* left = node->left_son;
    Element* right = node->right_son;

    if (left == nullptr && elem->key <= node->key) {
        if (elem->key == node->key) {
            node->value = elem->value;
            return node;
        }
        else {
            node->left_son = elem;
            node->left_son->parent = node;
            return node->left_son;
        }
    }
    else if (right == nullptr && elem->key >= node->key) {
        if (elem->key == node->key) {
            node->value = elem->value;
            return node;
        }
        else {
            node->right_son = elem;
            node->right_son->parent = node;
            return node->right_son;
        }
    }
    else if (left != nullptr && elem->key < node->key) {
        return InsertInMap(elem, node->left_son);
    }
    else if (right != nullptr && elem->key > node->key) {
        return InsertInMap(elem, node->right_son);
    }
    return nullptr;
}

Element* Map::Insert(const Element& element) {
    Element* elem = new Element(element);
    check_save_ = false;
    if (Find(elem->key) == nullptr) {
        ++size_;
    }
    return InsertInMap(elem, root_);
}

Element* Map::FindInMap(const std::string& key, Element* node) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->key == key) {
        return node;
    }
    if (node->key > key) {
        return FindInMap(key, node->left_son);
    }
    else {
        return FindInMap(key, node->right_son);
    }
}

Element* Map::Find(const std::string& key) {
    return FindInMap(key, root_);
}

Element* Map::Find(const std::string& key) const {
    return FindInMap(key, root_);
}

std::string Map::At(const std::string& key) const {
    auto result = Find(key);
    if (result == nullptr) {
        return "";
    }
    return result->value;
}

Element* Map::FindMax(Element* node) {
    Element* max_number = nullptr;
    while (node != nullptr) {
        max_number = node;
        node = node->right_son;
    }
    return max_number;
}

void Map::EraseElem(const std::string& key, Element*& node) {
    if (node == nullptr) {
        std::cout << "Удаляемый элемент не найден\n";
        return;
    }
    if (node->key == key) {
        Element* erase_elem = node;

        if (erase_elem->left_son != nullptr && erase_elem->right_son == nullptr) {
            if (erase_elem == root_) {
                node = node->left_son;
                node->parent = nullptr;
            }
            else if (erase_elem->parent->key > erase_elem->key) {
                node->parent->left_son = node->left_son;
                node->left_son->parent = erase_elem->parent;
            }
            else {
                node->parent->right_son = node->left_son;
                node->left_son->parent = erase_elem->parent;
            }
        }
        else if (erase_elem->left_son == nullptr && erase_elem->right_son != nullptr) {
            if (erase_elem == root_) {
                node = node->right_son;
                node->parent = nullptr;
            }
            else if (node->parent->key > node->key) {
                node->parent->left_son = node->right_son;
                node->right_son->parent = erase_elem->parent;
            }
            else {
                node->parent->right_son = node->right_son;
                node->right_son->parent = erase_elem->parent;
            }
        }
        else if (node->left_son == nullptr && node->right_son == nullptr) {
            if (erase_elem == root_) {
                node = nullptr;
            }
            else if (node->parent->key > node->key) {
                node->parent->left_son = nullptr;
            }
            else {
                node->parent->right_son = nullptr;
            }
        }
        else {
            Element* max_num = FindMax(node->left_son);

            if (erase_elem == root_) {
                node = max_num;
                node->right_son = erase_elem->right_son;
                if (node == erase_elem->left_son) {
                    node->left_son = nullptr;
                }
                node->parent = erase_elem->parent;
                delete erase_elem;
                std::cout << "Данные успешно удалены!\n";
                return;
            }
            else if (node->parent->key > node->key) {
                node->parent->left_son = max_num;
            }
            else {
                node->parent->right_son = max_num;
            }

            node->right_son = erase_elem->right_son;
            if (node == erase_elem->left_son) {
                node->left_son = nullptr;
            }
            node->parent = erase_elem->parent;
        }
        delete erase_elem;
        std::cout << "Данные успешно удалены!\n";
        return;
    }

    if (node->key > key) {
        EraseElem(key, node->left_son);
    }
    else {
        EraseElem(key, node->right_son);
    }
}

void Map::Erase(std::string key) {
    EraseElem(key, root_);
    --size_;
    check_save_ = false;
}

size_t Map::Size() const {
    return size_;
}

Element* Map::ClearMap(Element*& node) {
    if (node == nullptr) {
        return nullptr;
    }
    node->left_son = ClearMap(node->left_son);
    node->right_son = ClearMap(node->right_son);
    delete node;
    return nullptr;
}

void Map::Clear() {
    ClearMap(root_);
    root_ = nullptr;
    size_ = 0;
    check_save_ = true;
}

std::string& Map::operator[](std::string key) {
    auto it = Find(key);
    if (it != nullptr) {
        return it->value;
    }
    std::string str;
    return Insert({ key, str })->value;
}

Map::iterator Map::begin() {
    return iterator(Element::First(root_));
}

Map::iterator Map::end() {
    return iterator(nullptr);
}

Map::const_iterator Map::begin() const {
    return const_iterator(Element::First(root_));
}

Map::const_iterator Map::end() const {
    return const_iterator(nullptr);
}

void Map::OutMapData(std::ostream& out, bool check) {
    OutData(out, root_);
    if (check == true) {
        check_save_ = true;
    }
}

void Map::OutData(std::ostream& out, Element* node) const {
    if (node == nullptr) {
        return;
    }
    OutData(out, node->left_son);
    out << "\"" << node->key << "\"" << " " << "\"" << node->value << "\"" << std::endl;  // вывод данных в файл
    OutData(out, node->right_son);
}

bool Map::CheckSaveData() const {
    return check_save_;
}