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
        begin_ = new Iterator(0, this);
        end_ = new Iterator(0, this);
    }
    Dynamic_array(int n, T key) {
        size_ = 0;
        max_size = 1;
        array = new T[1];
        while(size_ != n) {
            push_back(key);
        }
    }
    class Iterator {
    public:
        T& operator*() {
            T& data = (*array)[index];
            return data;
        }
        Iterator operator++() {
            ++index;
            return *this;
        }
        Iterator operator--() {
            --index;
            return *this;
        }
        Iterator operator++(int) {
            Iterator* old = new Iterator(this);
            ++(*this);
            return *old;
        }
        Iterator operator--(int) {
            Iterator* old = new Iterator(this);
            --(*this);
            return *old;
        }
        bool operator!=(Iterator second) {
            int second_index = second.get_index();
            Dynamic_array<T>* second_array = second.get_array();
            return index != second_index || array != second_array;
        }
        bool operator==(Iterator second) {
            return !(this != second);
        }
        int get_index() {
            return index;
        }
        Dynamic_array<T>* get_array() {
            return array;
        }
        Iterator(int index_, Dynamic_array<T>* array_): index(index_), array(array_) {};
        Iterator(Iterator* iterator) {
            if(iterator == nullptr) {
                throw std::logic_error("nullptr pointer in the constructor");
            }
            index = iterator->get_index();
            array = iterator->get_array();
        }
    private:
        int index;
        Dynamic_array<T>* array;
    };


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
    void push_back(T key) {
        ++(*end_);
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
        --(*end_);
        T elem = *(array + size_ - 1);
        size_--;
        if(size_ < max_size / 4) {
            reduce();
        }
        return elem;
    }
    Iterator begin() {
        return *begin_;
    }
    Iterator end() {
        return *end_;
    }
private:
    int size_;
    int max_size;
    T* array;
    Iterator* begin_;
    Iterator* end_;
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
};


#endif //HEAPS_AND_TESTING_DYNAMIC_ARRAY_H
