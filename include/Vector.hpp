#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

template <class Type, size_t size> class Vector {
public:
    using Iterator = typename std::array<Type, size>::iterator;
    using ConstIterator = typename std::array<Type, size>::const_iterator;
    static constexpr Type epsilon = 1e-10;

    template <class... Args>
    Vector(Args &&...args)
        : array() {
        init<0>(std::forward<Args>(args)...);
    }
    Vector(const Vector<Type, size> &vector)
        : array(vector.array) {
    }
    Vector(Vector<Type, size> &&vector) noexcept
        : array(std::move(vector.array)) {
    }
    ~Vector() = default;
    Vector<Type, size> &operator=(const Vector<Type, size> &vector) {
        if (&vector == this) return *this;
        array = vector.array;
        return *this;
    }
    Vector<Type, size> &operator=(Vector<Type, size> &&vector) noexcept {
        if (&vector == this) return *this;
        array = std::move(vector.array);
        return *this;
    }
    template <class Type2, size_t size2>
    Vector<Type, size + size2> operator,(const Vector<Type2, size2> &vector) const {
        Vector<Type, size + size2> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i];
        }
        for (size_t i = size; i < size2 + size; ++i) {
            result[i] = (vector)[i - size];
        }
        return result;
    };
    Type norm() const {
        return sqrt((*this).dot(*this));
    }
    ConstIterator begin() const {
        return array.begin();
    }
    ConstIterator end() const {
        return array.end();
    }
    bool operator!() const {
        return std::all_of(begin(), end(), [](const Type &type) -> bool {
            return type == 0;
        });
    }
    explicit operator bool() const {
        return std::any_of(begin(), end(), [](const Type &type) -> bool {
            return type != 0;
        });
    }
    std::string toString() const {
        std::string result = "[";
        const char *separator = "";
        for (const auto &element : *this) {
            result += separator;
            result += std::to_string(element);
            separator = ", ";
        }
        return result;
    }
    const Type &operator[](size_t index) const {
        if (index >= size)
            throw std::out_of_range("Index " + std::to_string(index) + " is out of range for dimension " +
                                    std::to_string(size));
        return array[index];
    }
    Vector<Type, size> operator+(const Type &scalar) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] + scalar;
        }
        return result;
    }
    Vector<Type, size> operator-(const Type &scalar) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] - scalar;
        }
        return result;
    }
    Vector<Type, size> operator*(const Type &scalar) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] * scalar;
        }
        return result;
    }
    Vector<Type, size> operator/(const Type &scalar) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] / scalar;
        }
        return result;
    }
    bool operator==(const Vector<Type, size> &vector) const {
        for (size_t i = 0; i < size; ++i) {
            if ((*this)[i] != vector[i]) return false;
        }
        return true;
    }
    bool operator!=(const Vector<Type, size> &vector) const {
        return !(*this == vector);
    }
    Vector<Type, size> operator+(const Vector<Type, size> &vector) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] + vector[i];
        }
        return result;
    }
    Vector<Type, size> operator-(const Vector<Type, size> &vector) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] - vector[i];
        }
        return result;
    }
    Type dot(const Vector<Type, size> &vector) const {
        Type result = 0;
        for (size_t i = 0; i < size; ++i) {
            result += (*this)[i] * vector[i];
        }
        return result;
    }
    Type distance(const Vector<Type, size> &vector) const {
        return (*this - vector).norm();
    }
    Iterator begin() {
        return array.begin();
    }
    Iterator end() {
        return array.end();
    }
    Type &operator[](size_t index) {
        if (index >= size)
            throw std::out_of_range("Index " + std::to_string(index) + " is out of range for dimension " +
                                    std::to_string(size));
        return array[index];
    }
    Vector<Type, size> &operator+=(const Type &scalar) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] += scalar;
        }
        return *this;
    }
    Vector<Type, size> &operator-=(const Type &scalar) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] -= scalar;
        }
        return *this;
    }
    Vector<Type, size> &operator*=(const Type &scalar) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] *= scalar;
        }
        return *this;
    }
    Vector<Type, size> &operator/=(const Type &scalar) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] /= scalar;
        }
        return *this;
    }
    Vector<Type, size> &operator+=(const Vector<Type, size> &vector) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] += vector[i];
        }
        return *this;
    }
    Vector<Type, size> &operator-=(const Vector<Type, size> &vector) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] -= vector[i];
        }
        return *this;
    }
    Vector<Type, size> &normalize() {
        return (*this) /= (*this).norm();
    }
private:
    template <size_t index, class Type2, class... Args> void init(Type2 &&x, Args &&...args) {
        static_assert(index < size, "Too many arguments provided.");
        array[index] = std::forward<Type2>(x);
        init<index + 1>(std::forward<Args>(args)...);
    }
    template <size_t index> void init() const {
    }
    std::array<Type, size> array;
};

template <class Type, size_t size> std::ostream &operator<<(std::ostream &stream, const Vector<Type, size> &vector) {
    stream << "[";
    const char *space = "";
    for (const Type &t : vector) {
        std::cout << space << t;
        space = ", ";
    }
    return stream << "]";
}
