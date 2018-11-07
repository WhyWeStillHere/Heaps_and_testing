//
// Created by runb2 on 03/11/2018.
//

#ifndef HEAPS_AND_TESTING_DYNAMIC_ARRAY_H
#define HEAPS_AND_TESTING_DYNAMIC_ARRAY_H

#include <c++/4.8.3/stdexcept>
#include <gtest/gtest.h>

template <typename T>
class Dynamic_array {
public:
    Dynamic_array() {
        size_ = 0;
        max_size = 1;
        array = new T[1];
    }
    ~Dynamic_array() {
        delete[] array;
    }
    int size() {
        return size_;
    }
    T& operator[](const int& ind) {
        if(ind >= size_ || ind < 0) {
            throw std::out_of_range("Out of range in dynamic array");
        }
        return *(array + ind);
    }
    const T& operator[](const int& ind) const {
        if(ind >= size_ || ind < 0) {
            throw std::out_of_range("Out of range in dynamic array");
        }
        return *(array + ind);
    }
    void expand() {
        T* new_array = new T[max_size * 2];
        for(int i = 0; i < max_size; i++) {
            *(new_array + i) = *(array + i);
        }
        max_size *= 2;
        delete[] array;
        array = new_array;
        return;
    }
    void reduce() {
        T* new_array = new T[max_size / 2];
        for(int i = 0; i < size_; i++) {
            *(new_array + i) = *(array + i);
        }
        max_size /= 2;
        delete[] array;
        array = new_array;
        return;
    }
    void push_back(T key) {
        array[size_] = key;
        size_++;
        if(size_ == max_size) {
            expand();
        }
        return;
    }
    T pop_back() {
        if(size_ == 0) {
            throw std::out_of_range("Pop_back in the zero sized array");
        }
        T elem = *(array + size_ - 1);
        size_--;
        if(size_ < max_size / 4) {
            reduce();
        }
        return elem;
    }
private:
    int size_;
    int max_size;
    T* array;
};


#endif //HEAPS_AND_TESTING_DYNAMIC_ARRAY_H
