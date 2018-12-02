//
// Created by runb2 on 03/11/2018.
//

#ifndef HEAPS_AND_TESTING_HEAP_H
#define HEAPS_AND_TESTING_HEAP_H

#include "Dynamic_array.h"

template <typename T>
class Heap {
public:
    Heap() {};
    template<class Iterator>
    Heap(Iterator begin, Iterator end, const int number_of_children): number_of_children_(number_of_children) {
        if(number_of_children <= 0) {
            throw std::logic_error("Number of children in heap is less then 1");
        }
        Iterator current_iterator = begin;
        while(current_iterator != end) {
            heap_storage.push_back(*current_iterator);
            Pointer* nw = new Pointer(heap_storage.size() - 1);
            rev_pointers_storage.push_back(nw);
        }
        build_heap();
    }
    template<class Iterator>
    Heap(Iterator begin, Iterator end): number_of_children_(2){
        while(begin != end) {
            heap_storage.push_back(*begin);
            Pointer* nw = new Pointer(heap_storage.size() - 1);
            rev_pointers_storage.push_back(nw);
            ++begin;
        }
        build_heap();
    }
    void build_heap() {
        for(int i = heap_storage.size() / number_of_children_; i >= 0; i--) {
            sift_down(i);
        }
        if(!is_empty()) {
            minimum = heap_storage[0];
        }
    }

    Heap(const int number_of_children): number_of_children_(number_of_children) {
        if(number_of_children <= 0) {
            throw std::logic_error("Number of children in heap is less then 1");
        }
    };
    ~Heap() {
        for(int i = 0; i < rev_pointers_storage.size(); i++) {
            delete rev_pointers_storage[i];
        }
    }
    class Pointer  {
    public:
        int get_index() {
            return ind;
        }
        void set_index(int i) {
            ind = i;
            return;
        }
        Pointer(){};
        Pointer(int x): ind(x) {};
    private:
        int ind;
    };

    void optimize(int insert_count, int extract_count) {
        if(!is_empty()) {
            throw std::logic_error("Heap is not empty");
        }
        number_of_children_ = std::max(2, insert_count / extract_count);
    }

    void pointer_check(Pointer* p) {
        if(p == nullptr) {
            throw std::logic_error("Invalid pointer");
        }
        if(p->get_index() >= heap_storage.size() || p->get_index() < 0) {
            throw std::logic_error("Invalid pointer");
        }
        return;
    }
    T get_element(Pointer* p) {
        pointer_check(p);
        return heap_storage[p->get_index()];
    }
    void swap_with_pointers(int first, int second) {
        std::swap(heap_storage[first], heap_storage[second]);
        std::swap(rev_pointers_storage[first], rev_pointers_storage[second]);
        rev_pointers_storage[first]->set_index(first);
        rev_pointers_storage[second]->set_index(second);
        return;
    }

    Pointer* sift_up(int pos) {
        while(heap_storage[(pos - 1) / number_of_children_] > heap_storage[pos]) { // При i = 0 условие всегда неверно
            swap_with_pointers((pos - 1) / number_of_children_, pos);
            pos = (pos - 1) / number_of_children_;
        }
        return rev_pointers_storage[pos];
    }
    void sift_down(int pos) {
        while(pos * number_of_children_ + 1 < heap_storage.size()) {
            int j = pos * number_of_children_ + 1;
            for(int i = 2; i <= number_of_children_ && pos * number_of_children_ + i < heap_storage.size(); i++) {
                if(heap_storage[pos * number_of_children_ + i] < heap_storage[j]) {
                    j = pos * number_of_children_ + i;
                }
            }
            if (heap_storage[pos] < heap_storage[j]) {
                break;
            }
            swap_with_pointers(pos, j);
            pos = j;
        }
        return;
    }
    Pointer* insert(T key) {
        if(is_empty() || minimum > key) {
            minimum = key;
        }
        heap_storage.push_back(key);
        Pointer* nw = new Pointer(heap_storage.size() - 1);
        rev_pointers_storage.push_back(nw);
        Pointer* valid_pointer = sift_up(heap_storage.size() - 1);
        return valid_pointer;
    }
    T get_min() {
        if(is_empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return minimum;
    }
    T extract_min() {
        if(is_empty()) {
            throw std::out_of_range("Heap is empty");
        }
        T tmp = heap_storage[0];
        swap_with_pointers(0, heap_storage.size() - 1);
        heap_storage.pop_back();
        delete rev_pointers_storage[rev_pointers_storage.size() - 1];
        rev_pointers_storage.pop_back();
        sift_down(0);
        if(!is_empty()) {
            minimum = heap_storage[0];
        }
        return tmp;
    }
    bool is_empty() {
        if(heap_storage.size() == 0) {
            return 1;
        } else {
            return 0;
        }
    }

    void change(Pointer* p, T val) {
        pointer_check(p);
        int pos = p->get_index();
        heap_storage[pos] = val;
        if(val < heap_storage[(pos - 1) / number_of_children_]) {
            sift_up(pos);
        } else {
            sift_down(pos);
        }
        minimum = heap_storage[0];
        return;
    }
    void delete_element(Pointer* p) {
        pointer_check(p);
        if(is_empty()) {
            throw std::out_of_range("Heap is empty");
        }
        int pos = p->get_index();
        T tmp = heap_storage[pos];
        swap_with_pointers(pos, heap_storage.size() - 1);
        heap_storage.pop_back();
        delete rev_pointers_storage[rev_pointers_storage.size() - 1];
        rev_pointers_storage.pop_back();
        sift_down(pos);
        if(!is_empty()) {
            minimum = heap_storage[0];
        }
        return;
    }
    void print() {
        for(int i = 0; i < heap_storage.size(); i++) {
            std::cout << heap_storage[i] << " ";
        }
        std::cout << "\n";
    }

private:
    Dynamic_array<T> heap_storage;
    Dynamic_array<Pointer*> rev_pointers_storage;
    int number_of_children_ = 2;
    T minimum;
};

#endif //HEAPS_AND_TESTING_HEAP_H
