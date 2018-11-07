//
// Created by runb2 on 03/11/2018.
//

#ifndef HEAPS_AND_TESTING_HEAP_H
#define HEAPS_AND_TESTING_HEAP_H

#include "Dynamic_array.h"

template <typename T>
class Heap {
public:
    Heap(const int number_of_childs): number_of_childs_(number_of_childs) {};
    Heap() {};
/*    class Pointer  {
    public:
        /*T get_value() {
            return *p;
        }
        T get_index() {
            return ind;
        }
        void set_index(int i) {
            ind = i;
            return;
        }
       /* void set_pointer(T* nw_p) {
            p = nw_p;
            return;
        }
        Pointer(int x): ind(x) {};
        //Pointer(T x, int i): p(&x), ind(i) {};
    private:
        //T* p;
        int ind;
    };

    void swap_with_pointers(int first, int second) {
        std::swap(heap_storage[first], heap_storage[second]);
        std::swap(pointers_storage[first], pointers_storage[second]);
        int tmp = pointers_storage[first].get_index();
        pointers_storage[first].set_index(pointers_storage[second].set_index());
        pointers_storage[second].set_index(tmp);
    }
*/
    void sift_up(int pos) {
        while(heap_storage[(pos - 1) / number_of_childs_] > heap_storage[pos]) { // При i = 0 условие всегда неверно
            std::swap(heap_storage[(pos - 1) / number_of_childs_], heap_storage[pos]);
            pos = (pos - 1) / number_of_childs_;
        }
        return;
    }
    void sift_down(int pos) {
        while(pos * number_of_childs_ + 1 < heap_storage.size()) {
            int j = pos * number_of_childs_ + 1;
            for(int i = 2; i <= number_of_childs_ && pos * number_of_childs_ + i < heap_storage.size(); i++) {
                if(heap_storage[pos * number_of_childs_ + i] < heap_storage[j]) {
                    j = pos * number_of_childs_ + i;
                }
            }
            if (heap_storage[pos] < heap_storage[j]) {
                break;
            }
            std::swap(heap_storage[pos], heap_storage[j]);
            pos = j;
        }
        return;
    }
    void print() {
        for(int i = 0; i < heap_storage.size(); i++) {
            std::cout << heap_storage[i] << " ";
        }
        std::cout << "\n";
    }
    bool is_empty() {
        if(heap_storage.size() == 0) {
            return 1;
        } else {
            return 0;
        }
    }
    void insert(T key) {
        heap_storage.push_back(key);
        sift_up(heap_storage.size() - 1);
        return;
    }
    T get_min() {
        if(is_empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap_storage[0];
    }
    T extract_min() {
        if(is_empty()) {
            throw std::out_of_range("Heap is empty");
        }
        T tmp = heap_storage[0];
        std::swap(heap_storage[0], heap_storage[heap_storage.size() - 1]);
        heap_storage.pop_back();
        sift_down(0);
        return tmp;
    }
private:
    Dynamic_array<T> heap_storage;
    //Dynamic_array<Pointer> pointers_storage;
    const int number_of_childs_ = 2;
};

#endif //HEAPS_AND_TESTING_HEAP_H
