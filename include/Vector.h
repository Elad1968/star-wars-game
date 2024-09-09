#ifndef HW03_VECTOR_H
#define HW03_VECTOR_H

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

/**
 * Vector class to represent mathematical vectors.
 * @tparam Type The type of the elements.
 * @tparam size The dimension of the vector.
 */
template<class Type, size_t size>
class Vector {
public:
    using Iterator = typename std::array<Type, size>::iterator;
    using ConstIterator = typename std::array<Type, size>::const_iterator;
    static constexpr Type epsilon = 1e-10;
    /**
     * Constructs vector from elements.
     * @tparam Args Element types. Must be convertible to T.
     * @param args The elements in sequential order.
     */
    template<class ...Args>
    Vector(Args &&...args) : array() { // NOLINT(*-explicit-constructor)
        init<0>(std::forward<Args>(args)...);
    }
    /**
     * Copy constructor.
     * @param vector The vector to copy.
     */
    Vector(const Vector<Type, size> &vector) : array(vector.array) {

    }
    /**
     * Move constructor.
     * @param vector The vector to move.
     */
    Vector(Vector<Type, size> &&vector) noexcept : array(std::move(vector.array)) {

    }
    /**
     * Destructor.
     */
    ~Vector() = default;
    /**
     * Copy assignment.
     * @param vector The vector to copy.
     * @return this.
     */
    Vector<Type, size> &operator=(const Vector<Type, size> &vector) {
        if (&vector == this) return *this;
        array = vector.array;
        return *this;
    }
    /**
     * Move assignment.
     * @param vector The vector to move.
     * @return this.
     */
    Vector<Type, size> &operator=(Vector<Type, size> &&vector) noexcept {
        if (&vector == this) return *this;
        array = std::move(vector.array);
        return *this;
    }
    /**
     * Concatenates two vectors.
     * @tparam Type2 Type of the other vector's elements. Must be convertible to T.
     * @tparam size2 The setSize of the other vector.
     * @param vector The vector to concatenate to this.
     * @return The concatenation of this and vector.
     */
    template<class Type2, size_t size2>
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
    /**
     * Calculate the norm of the vector.
     * @return The setSize of the vector.
     */
    Type norm() const {
        return sqrt((*this).dot(*this));
    }
    /**
     * Get an iterator to the first element.
     * @return An iterator to the first element.
     */
    ConstIterator begin() const {
        return array.begin();
    }
    /**
     * Get an iterator past the last element.
     * @return An iterator past the last element.
     */
    ConstIterator end() const {
        return array.end();
    }
    /**
     * Checks if the vector is the zero vector.
     * @return true if this is the zero vector, false otherwise.
     */
    bool operator!() const {
        return std::all_of(begin(), end(), [](const Type &type) -> bool {
            return type == 0;
        });
    }
    /**
     * Checks if not the vector is the zero vector.
     * @return true if this is not the zero vector, false otherwise.
     */
    explicit operator bool() const {
        return std::any_of(begin(), end(), [](const Type &type) -> bool {
            return type != 0;
        });
    }
    /**
     * Get a string representation of the vector.
     * @return std::string that represents the vector.
     */
    std::string toString() const {
        std::string result = "[";
        const char *separator = "";
        for (const auto &element: *this) {
            result += separator;
            result += std::to_string(element);
            separator = ", ";
        }
        return result;
    }
    /**
     * Get the element in the index position.
     * @param index The index to get.
     * @return A const reference to the element at the index position.
     * @throw std::out_of_range if index >= setSize.
     */
    const Type &operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index " + std::to_string(index) + " is out of range for dimension " + std::to_string(size));
        return array[index];
    }
    /**
     * Add scalar to every element in this.
     * @param scalar The scalar to add.
     * @return A new calculated vector.
     */
    Vector<Type, size> operator+(const Type &scalar) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] + scalar;
        }
        return result;
    }
    /**
     * Subtract scalar from every element in this.
     * @param scalar The scalar to subtract.
     * @return A new calculated vector.
     */
    Vector<Type, size> operator-(const Type &scalar) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] - scalar;
        }
        return result;
    }
    /**
     * Multiply scalar with every element in this.
     * @param scalar The scalar to multiply with.
     * @return A new calculated vector.
     */
    Vector<Type, size> operator*(const Type &scalar) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] * scalar;
        }
        return result;
    }
    /**
     * Divide every element in this with a scalar.
     * @param scalar The scalar to divide.
     * @return A new calculated vector.
     */
    Vector<Type, size> operator/(const Type &scalar) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] / scalar;
        }
        return result;
    }
    /**
     * Check if two vectors are the same.
     * @param vector The other vector to check.
     * @return true if they are the same, false otherwise.
     */
    bool operator==(const Vector<Type, size> &vector) const {
        for (size_t i = 0; i < size; ++i) {
            if ((*this)[i] != vector[i]) return false;
        }
        return true;
    }
    /**
     * Check if two vectors are not the same.
     * @param vector The other vector to check.
     * @return true if they are not the same, false otherwise.
     */
    bool operator!=(const Vector<Type, size> &vector) const {
        return !(*this == vector);
    }
    /**
     * Add vector to this.
     * @param vector The vector to add.
     * @return A new calculated vector.
     */
    Vector<Type, size> operator+(const Vector<Type, size> &vector) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] + vector[i];
        }
        return result;
    }
    /**
     * Subtract vector from this.
     * @param vector The vector to subtract.
     * @return A new calculated vector.
     */
    Vector<Type, size> operator-(const Vector<Type, size> &vector) const {
        Vector<Type, size> result;
        for (size_t i = 0; i < size; ++i) {
            result[i] = (*this)[i] - vector[i];
        }
        return result;
    }
    /**
     * Calculate the do operator between this and vector.
     * @param vector The vector to calculate with.
     * @return A new calculated vector.
     */
    Type dot(const Vector<Type, size> &vector) const {
        Type result = 0;
        for (size_t i = 0; i < size; ++i) {
            result += (*this)[i] * vector[i];
        }
        return result;
    }
    /**
     *
     * @param vector
     * @return
     */
    Type distance(const Vector<Type, size> &vector) const {
        return (*this - vector).norm();
    }
    /**
     * Get an iterator to the first element.
     * @return An iterator to the first element.
     */
    Iterator begin() {
        return array.begin();
    }
    /**
     * Get an iterator past the last element.
     * @return An iterator past the last element.
     */
    Iterator end() {
        return array.end();
    }
    /**
     * Get the element in the index position.
     * @param index The index to get.
     * @return A reference to the element at the index position.
     * @throw std::out_of_range if index >= setSize.
     */
    Type &operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index " + std::to_string(index) + " is out of range for dimension " + std::to_string(size));
        return array[index];
    }
    /**
     * Add a scalar to the vector in place.
     * @param scalar The scalar to add.
     * @return A reference to the vector itself.
     */
    Vector<Type, size> &operator+=(const Type &scalar) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] += scalar;
        }
        return *this;
    }
    /**
     * Subtract the vector by a scalar in place.
     * @param scalar The scalar to subtract by.
     * @return A reference to the vector itself.
     */
    Vector<Type, size> &operator-=(const Type &scalar) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] -= scalar;
        }
        return *this;
    }
    /**
     * Multiply the vector by a scalar in place.
     * @param scalar The scalar to multiply by.
     * @return A reference to the vector itself.
     */
    Vector<Type, size> &operator*=(const Type &scalar) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] *= scalar;
        }
        return *this;
    }
    /**
     * Divide the vector by a scalar in place.
     * @param scalar The scalar to divide by.
     * @return A reference to the vector itself.
     */
    Vector<Type, size> &operator/=(const Type &scalar) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] /= scalar;
        }
        return *this;
    }
    /**
     * Add a vector to the vector in place.
     * @param vector The vector to add.
     * @return A reference to the vector itself.
     */
    Vector<Type, size> &operator+=(const Vector<Type, size> &vector) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] += vector[i];
        }
        return *this;
    }
    /**
     * Subtract the vector by another vector in place.
     * @param vector The vector to subtract by.
     * @return A reference to the vector itself.
     */
    Vector<Type, size> &operator-=(const Vector<Type, size> &vector) {
        for (size_t i = 0; i < size; ++i) {
            (*this)[i] -= vector[i];
        }
        return *this;
    }
    /**
     * Normalize the vector.
     * @return A reference to the vector itself.
     */
    Vector<Type, size> &normalize() {
        return (*this) /= (*this).norm();
    }
private:
    /**
     * Initializes the index element in the vector.
     * @tparam index The index to initialize.
     * @tparam Type2 The type of the element.
     * @tparam Args The types of the rest of the elements.
     * @param x The element to insert in the index position.
     * @param args The rest of the elements.
     */
    template<size_t index, class Type2, class ...Args>
    void init(Type2 &&x, Args &&...args) {
        static_assert(index < size, "Too many arguments provided.");
        array[index] = std::forward<Type2>(x);
        init<index + 1>(std::forward<Args>(args)...);
    }
    /**
     * Done initializing.
     * @tparam index A placeholder index to work with the former init method.
     */
    template<size_t index>
    void init() const {

    }
    /**
     * Holds the elements.
     */
    std::array<Type, size> array;
};

/**
 * Print the vector to an output stream.
 * @tparam Type The type of the elements.
 * @tparam size The dimension of the vector.
 * @param stream The stream to print to.
 * @param vector The vector to print.
 * @return stream.
 */
template<class Type, size_t size>
std::ostream &operator<<(std::ostream &stream, const Vector<Type, size> &vector) {
    stream << "[";
    const char *space = "";
    for (const Type &t : vector) {
        std::cout << space << t;
        space = ", ";
    }
    return stream << "]";
}

#endif //HW03_VECTOR_H
