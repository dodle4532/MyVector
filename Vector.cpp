#include <iostream>
#include <cstdlib>
#include "Vector.h"



Vector::Vector(const Value* rawArray, const size_t size, float coef) {
    _data = new Value [size];
    for (int i = 0; i < size; ++i) {
        _data[i] = rawArray[i];
    }
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;
}

Vector::Vector(const Vector& other) {
    this->_data = new Value [other._size];
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other._size;
    this->_capacity = other._capacity;
    this->_capacity = this->_size * this->_multiplicativeCoef;
    for (int i = 0; i < other._size; ++i) {
        this->_data[i] = other._data[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete [] this->_data;
        this->_data = new Value [other._size];
        this->_size = other._size;
        this->_capacity = other._capacity;
        this->_multiplicativeCoef = other._multiplicativeCoef;
        this->_capacity = this->_size * this->_multiplicativeCoef;
        for (int i = 0; i < other._size; ++i) {
            this->_data[i] = other._data[i];
        }
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept 
    : _data(nullptr)
    , _size(0)
    , _capacity(1)
{
//     if (other._size == 0) {
//         delete [] this->_data;
//         this->_data = nullptr;
//         this->_size = 0;
//         this->_capacity = 0;
//         return;
//     }
//     delete [] this->_data;
//     this->_data = nullptr;
//     this->_size = other._size;
// //    this->_capacity = this->_size * this->_multiplicativeCoef;
//     this->_capacity = other._capacity;
//     this->_multiplicativeCoef = other._multiplicativeCoef;
//         this->_data = new Value [other._size];
//         for (int i = 0; i < other._size; ++i) {
//             this->_data[i] = other._data[i];
//         }
//         delete [] other._data;
//         other._data = nullptr;
//         other._capacity = 0;
//         other._size = 0;
    this->_data = other._data;
    this->_size = other._size;
    this->_capacity = other._capacity;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

Vector& Vector::operator=(Vector&& other) noexcept {
    if (this != &other) { 
        delete [] this->_data;
        this->_data = other._data;
        this->_size = other._size;
        this->_capacity = other._capacity;

        delete [] other._data;
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

Vector::~Vector() {
    delete [] _data;
}

void Vector::pushBack(const Value& value) {
    if (_capacity > _size) {
        _size++;
        _data[_size - 1] = value;
        return;
    }
    Value* tmp = new Value [_size];
    for (int i = 0; i < _size; ++i) {
        tmp[i] = _data[i];
    }
    delete [] _data;
    _size++;
    _capacity = _size * _multiplicativeCoef;
    _data = new Value [_capacity];
    for (int i = 0; i < _size - 1; ++i) {
        _data[i] = tmp[i];
    }
    _data[_size - 1] = value;
    delete [] tmp;
    return;
}

void Vector::pushFront(const Value& value) {
    if (_capacity > _size) {
        _size++;
        for (int i = _size - 1; i > 0; i--) {
            _data[i] = _data[i -1];
        }
        _data[0] = value;
        return;
    }
    Value* tmp = new Value [_size];
    for (int i = 0; i < _size; ++i) {
        tmp[i] = _data[i];
    }
    delete [] _data;
    _size++;
    _capacity = _size * _multiplicativeCoef;
    _data = new Value [_capacity];
    _data[0] = value;
    for (int i = 1; i < _size; ++i) {
        _data[i] = tmp[i - 1];
    }
    delete [] tmp;
    return;
}

void Vector::insert(const Value& value, size_t pos) {
    if (_size == _capacity) {
        pushBack(0);
    }
    else {
        _size++;
    }
    for (int i = _size - 1; i > pos; --i) {
        _data[i] = _data[i-1];
    }
    _data[pos] = value;
    return;
}

void Vector::insert(const Value* values, size_t size, size_t pos) {
    if (values == nullptr) {
        return;
    }
    for (int i = 0; i < size; ++i) {
        insert(values[i], pos);
        pos++;
    }
}

void Vector::insert(const Vector& vector, size_t pos) {
    if (vector._size == 0) {
        return;
    }
    insert(vector._data, vector._size, pos);
}

void Vector::popBack() {
    if (_size == 0) {
        throw("ERROR");
        return;
    }
    _size--;
    return;
}

void Vector::popFront() {
    if (_size == 0) {
        throw("ERROR");
        return;
    }
    _size--;
    for (int i = 0; i < _size; ++i) {
        _data[i] = _data[i+1];
    }
    return;
}

void Vector::erase(size_t pos, size_t count) {
    if (count == 0) {
        return;
    }
    if (pos + count > _size) {
        count = _size - pos;
    }
    _size = _size - count;
    for (int i = pos; i < pos + count; ++i) {
        _data[i] = _data[i + count];
    }
    return;

}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    this->erase(beginPos - 1, endPos - beginPos + 1);
    return;
}

size_t Vector::size() const {
    return _size;
}

size_t Vector::capacity() const {
    return _capacity;
}


Value& Vector::operator[](size_t idx) {
    return _data[idx];
}

const Value& Vector::operator[](size_t idx) const {
    return _data[idx];
}

long long Vector::find(const Value& value) const {
    for (int i = 0; i < _size; ++i)
    {
        if (_data[i] == value)
        {
            return i;
        }
    }
    std::cout << "Not found" << std::endl;
    std::exit(0);
}

void Vector::reserve(size_t capacity) {
    if (capacity <= _capacity) {
        return;
    }
    Value* tmp = new Value [_size];
    for (int i = 0; i < _size; ++i) {
        tmp[i] = _data[i];
    }
    delete [] this->_data;
//    _capacity = capacity * _multiplicativeCoef;
    _capacity = capacity;
    this->_data = new Value [_capacity];
    for (int i = 0; i < _size; ++i) {
        _data[i] = tmp[i];
    }
    delete [] tmp;
    return;
}

void Vector::shrinkToFit() {
    Value* tmp = new Value [_size];
    for (int i = 0; i < _size; ++i) {
        tmp[i] = _data[i];
    }
    delete [] _data;
    _data = new Value [_size];
    for (int i = 0; i < _size; ++i) {
        _data[i] = tmp[i];
    }
    _capacity = _size;
    delete [] tmp;
    // _capacity = _size;
    // if (_capacity == 0) {
    //     _capacity = ;
    // }
    // Value* ptr = new Value [_size];
    // for (int i = 0; i < _size; ++i) {
    //     ptr[i] = _data[i];
    // }
    // delete [] _data;
    // _data = new Value [_size];
    // for (int i = 0; i < _size - 1; ++i) {
    //     _data[i] = ptr[i];
    // }
    // delete [] ptr;
    return;
}

Vector::Iterator::Iterator(Value* ptr) {
    _ptr = ptr;
}
Value& Vector::Iterator::operator*() {
    return *_ptr;
}
    
const Value& Vector::Iterator::operator*() const {
    return *_ptr;
}
    
Value* Vector::Iterator::operator->() {
    return _ptr;
}
    
const Value* Vector::Iterator::operator->() const {
    return _ptr;
}
    
Vector::Iterator Vector::Iterator::operator++() {
     ++_ptr;
     return *this;
 }
    
Vector::Iterator Vector::Iterator::operator++(int) {
    _ptr++;
    return *this;
}
    
bool  Vector::Iterator::operator==(const Iterator& other) const {
    return this->_ptr == other._ptr;
}
    
bool  Vector::Iterator::operator!=(const Iterator& other) const {
    return this->_ptr != other._ptr;
}

Vector::Iterator Vector::begin() {
    Vector::Iterator A(&_data[0]);
    return A;
}

Vector::Iterator Vector::end() {
    Vector::Iterator A(&_data[_size - 1]);
    return A;
}