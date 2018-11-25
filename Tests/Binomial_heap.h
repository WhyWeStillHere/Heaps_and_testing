//
// Created by runb2 on 08/11/2018.
//

#ifndef HEAPS_AND_TESTING_BINOMIAL_HEAP_H
#define HEAPS_AND_TESTING_BINOMIAL_HEAP_H

#include "Dynamic_array.h"
#include <queue>


template <typename T>
class Binomial_heap {
public:
    class Pointer;

    struct Heap_node {
        T key;
        int degree = 0;
        Heap_node* child = nullptr;
        Heap_node* sibling = nullptr;
        Pointer* pointer;
        Heap_node(T key_): key(key_), degree(1) {};
        Heap_node() {};
    };

    class Pointer {
    public:
        T get_elem() {
            return elem->key;
        }
        void set_index(Heap_node* x) {
            elem = x;
            return;
        }
        Pointer(){};
        Pointer(Heap_node* x): elem(x) {};
    private:
        Heap_node* elem;
    };

    ~Binomial_heap() {
        while(root != nullptr) {
            Heap_node *nxt = root->sibling;
            delete_binomial_heap(root->child);
            delete root->pointer;
            delete root;
            root = nxt;
        }
    }

    bool is_empty() {
        if(root == nullptr) {
            return 1;
        } else {
            return 0;
        }
    }
    T get_min() {
        if(minimum == nullptr) {
            throw std::out_of_range("Binomial heap is empty");
        }
        return minimum->key;
    }
    void update_min(Heap_node* node) {
        minimum = nullptr;
        while(node != nullptr) {
            if(minimum == nullptr) {
                minimum = node;
            }
            if(node->key < minimum->key) {
                minimum = node;
            }
            node = node->sibling;
        }
        return;
    }

    Heap_node* get_root() {
        return root;
    }
    Pointer* insert(T x) {
        Heap_node* nw = new Heap_node(x);
        Pointer* p = new Pointer(nw);
        nw->pointer = p;
        merge(nw);
        return p;
    }

    Heap_node* merge_nodes(Heap_node* first, Heap_node* second) {
        if(first->key < second->key) {
            first->degree *= 2;
            first->sibling = second->sibling;
            second->sibling = first->child;
            first->child = second;
            return first;
        } else {
            second->degree *= 2;
            first->sibling = second->child;
            second->child = first;
            return second;
        }
    }
    void merge(Heap_node* heap2) {
        if(root == nullptr) {
            root = heap2;
            update_min(root);
            return;
        }
        if(heap2 == nullptr) {
            update_min(root);
            return;
        }
        Heap_node* nw_heap = nullptr;
        Heap_node* heap1 = root;
        Heap_node* carry = nullptr;
        Heap_node* nw_root = nullptr;
        while(heap2 != nullptr && heap1 != nullptr) {
            if(heap1->degree < heap2->degree) {
                if(nw_heap == nullptr) {
                    nw_heap = heap1;
                    nw_root = nw_heap;
                    heap1 = heap1->sibling;
                } else {
                    nw_heap->sibling = heap1;
                    heap1 = heap1->sibling;
                    nw_heap = nw_heap->sibling;
                }
            } else {
                if (nw_heap == nullptr) {
                    nw_heap = heap2;
                    nw_root = nw_heap;
                    heap2 = heap2->sibling;
                } else {
                    nw_heap->sibling = heap2;
                    heap2 = heap2->sibling;
                    nw_heap = nw_heap->sibling;
                }
            }
        }
        if(heap1 == nullptr) {
            if(nw_heap == nullptr) {
                nw_heap = heap2;
                nw_root = nw_heap;
            } else {
                nw_heap->sibling = heap2;
            }
        } else {
            if(nw_heap == nullptr) {
                nw_heap = heap1;
                nw_root = nw_heap;
            } else {
                nw_heap->sibling = heap1;
            }
        }
        nw_heap = nw_root;
        while(nw_heap->sibling != nullptr) {
            if(nw_heap->degree == nw_heap->sibling->degree) {
                if(nw_heap->sibling->sibling != nullptr &&
                   nw_heap->sibling->degree == nw_heap->sibling->sibling->degree){
                    nw_heap->sibling = merge_nodes(nw_heap->sibling, nw_heap->sibling->sibling);
                } else {
                    if(nw_heap == nw_root) {
                        nw_heap = merge_nodes(nw_heap, nw_heap->sibling);
                        nw_root = nw_heap;
                    } else {
                        nw_heap = merge_nodes(nw_heap, nw_heap->sibling);
                    }
                }
            } else {
                nw_heap = nw_heap->sibling;
            }
        }
        root = nw_root;
        update_min(root);
        /* print(root);
         std::cout << " @#$% \n";*/
    }

    T extract_min() {
        if(minimum == nullptr) {
            throw std::out_of_range("Binomial heap is empty");
        }
        Heap_node* node = minimum->child;
        Heap_node* change = root;
        T return_value = minimum->key;
        if(root == minimum) {
            root = root->sibling;
        }
        while(change->sibling != nullptr) {
            if(change->sibling == minimum) {
                change->sibling = minimum->sibling;
                break;
            }
            change = change->sibling;
        }
        delete minimum;
        node = reverse_list(node);
        merge(node);
        return return_value;
    }
    Heap_node* reverse_list(Heap_node* start) {
        if(start == nullptr) {
            return nullptr;
        }
        Heap_node* tmp = start->sibling;
        if(tmp == nullptr) {
            return start;
        }
        Heap_node* nw_start = reverse_list(start->sibling);
        tmp->sibling = start;
        start->sibling = nullptr;
        return nw_start;
    }

    void print(Heap_node* root_) {
        Heap_node* cur = root_;
        while(cur != nullptr) {
            std::cout << "!! ";
            std::cout << cur->key << " ";
            print_bfs(cur->child);
            cur = cur->sibling;
        }
        std::cout << "\n\n";
    }
    void print_node(Heap_node* node) {
        std::cout << node->key << " ";
        print_bfs(node->child);
    }
    void print_bfs(Heap_node* root) {
        std::queue<Heap_node*> bfs;
        bfs.push(root);
        while(bfs.size()) {
            Heap_node* nw = bfs.front();
            bfs.pop();
            while(nw != nullptr) {
                std:: cout << nw->key << " ";
                bfs.push(nw->child);
                nw = nw->sibling;
            }
        }
        std::cout << "\n";
    }

private:
    Heap_node* root = nullptr;
    Heap_node* minimum;
    void delete_binomial_heap(Heap_node* root_) {
        while(root_ != nullptr) {
            Heap_node* nxt = root_->sibling;
            delete_binomial_heap(root_->child);
            delete root_->pointer;
            delete root_;
            root_ = nxt;
        }
        return;
    }
};

#endif //HEAPS_AND_TESTING_BINOMIAL_HEAP_H