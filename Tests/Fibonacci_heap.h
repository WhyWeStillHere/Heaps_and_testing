//
// Created by runb2 on 24/11/2018.
//

#ifndef HEAPS_AND_TESTING_FIBONACCI_HEAP_H
#define HEAPS_AND_TESTING_FIBONACCI_HEAP_H
#include "Dynamic_array.h"


template <typename T>
class Fibonacci_heap {
public:
    class Pointer;

    struct Heap_node {
        T key;
        int degree = 0;
        Heap_node* child = nullptr;
        Heap_node* right = nullptr;
        Heap_node* left = nullptr;
        Heap_node* parent = nullptr;
        Pointer* pointer;
        bool mark = false;
        Heap_node(T key_): key(key_), degree(0) {};
        Heap_node() {};
    };

    class Pointer {
    public:
        Heap_node* get_elem() {
            return elem;
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

    Fibonacci_heap() {};

    ~Fibonacci_heap() {
        if(root == nullptr) {
            return;
        }
        Heap_node* start_node = root;
        root = root->right;
        while(root != start_node) {
            Heap_node *next_node = root->right;
            delete_fibonacci_heap(root->child);
            delete root->pointer;
            delete root;
            root = next_node;
        }
        delete_fibonacci_heap(root->child);
        delete root->pointer;
        delete root;
        return;
    }
    void delete_fibonacci_heap(Heap_node* root_) {
        if(root_ == nullptr) {
            return;
        }
        Heap_node* start_node = root_;
        root_ = root_->right;
        while(root_ != start_node) {
            Heap_node* next_node = root_->right;
            delete_fibonacci_heap(root_->child);
            delete root_->pointer;
            delete root_;
            root_ = next_node;
        }
        delete_fibonacci_heap(root_->child);
        delete root_->pointer;
        delete root_;
        return;
    }

    Pointer* insert(T key) {
        Heap_node* new_element = new Heap_node(key);
        Pointer* new_elem_pointer = new Pointer(new_element);
        new_element->pointer = new_elem_pointer;
        if(root == nullptr) {
            root = new_element;
            root->left = root;
            root->right = root;
        } else {
            Heap_node* prev_right = root->right;
            root->right = new_element;
            new_element->left = root;
            new_element->right = prev_right;
            new_element->right->left = new_element;
            if(key < root->key) {
                root = new_element;
            }
        }
        size_++;
        return new_elem_pointer;
    }
    bool is_empty() {
        if(size_ == 0) {
            return 1;
        } else {
            return 0;
        }
    }
    T get_min() {
        if(root == nullptr) {
            throw std::out_of_range("Fibonacci heap is empty");
        }
        return root->key;
    }

    Heap_node* union_lists(Heap_node* first, Heap_node* second) {
        if(second == nullptr) {
            return first;
        }
        if(first == nullptr) {
            return second;
        }
        Heap_node* first_right = first->right;
        Heap_node* second_left = second->left;
        first->right = second;
        second->left = first;
        second_left->right = first_right;
        first_right->left = second_left;
        return first;
    }

    void merge(Fibonacci_heap* heap) {
        if(heap == nullptr || heap->size_ == 0) {
            return;
        }
        if(size_ == 0) {
            root = heap->root;
            size_ = heap->size_;
        } else {
            root = union_lists(root, heap->root);
            if(heap->root->key < root->key) {
                root = heap->root;
            }
            size_ += heap->size_;
        }
    }

    T extract_min() {
        if(root == nullptr) {
            throw std::out_of_range("Fibonacci heap is empty");
        }
        Heap_node* previous_root = root;
        T return_value = root->key;
        Heap_node* child_start = root->child;
        if(child_start != nullptr) {
            Heap_node* child_pointer = child_start->right;
            child_start->parent = nullptr;
            while(child_pointer != child_start) {
                child_pointer->parent = nullptr;
                child_pointer = child_pointer->right;
            }
        }
        root = union_lists(root, child_start);
        Heap_node* root_left = root->left;
        Heap_node* root_right = root->right;
        root_left->right = root_right;
        root_right->left = root_left;
        if(root == root->left) {
            delete root->pointer;
            delete root;
            root = nullptr;
            size_--;
            return return_value;
        }
        delete root->pointer;
        delete root;
        root = root_right;
        size_--;
        consolidate();
        return return_value;
    }

    void consolidate() { // Optimize Fibonacci heap structure
        Dynamic_array<Heap_node*> nodes_array(root->degree + 1, nullptr);
        nodes_array[root->degree] = root;
        Heap_node* current_node = root->right;
        while (current_node->degree >= nodes_array.size() || nodes_array[current_node->degree] != current_node) {
            while(current_node->degree >= nodes_array.size()) {
                nodes_array.push_back(0);
            }
            if(nodes_array[current_node->degree] == nullptr)  {
                nodes_array[current_node->degree] = current_node;
                if(root->key > current_node->key) {
                    root = current_node;
                }
                current_node = current_node->right;
            } else {
                Heap_node* carry = nodes_array[current_node->degree];
                Heap_node* add_to, *add;
                nodes_array[current_node->degree] = nullptr;
                if(carry->key < current_node->key) {
                    add_to = carry;
                    add = current_node;
                } else {
                    add_to = current_node;
                    add = carry;
                }
                add_to->child = union_lists(add_to->child, add);
                add->parent = add_to;
                ++add_to->degree;
                current_node = add_to;
                if(root->key > current_node->key) {
                    root = current_node;
                }
            }
        }
    }

    void decrease_key(Pointer* heap_node_pointer, T new_key) {
        Heap_node* current_node = heap_node_pointer->get_elem();
        if(current_node->parent == nullptr || current_node->parent->key < new_key) {
            current_node->key = new_key;
            if(current_node->parent == nullptr && root->key > new_key) {
                root = current_node;
            }
            return;
        }
        Heap_node* node_parent = current_node->parent;
        current_node->key = new_key;
        cut(current_node);
        cascading_cut(node_parent);
    }

    void cut(Heap_node* current_node) {
        Heap_node* node_left = current_node->left;
        Heap_node* node_right = current_node->right;
        Heap_node* node_parent = current_node->parent;
        node_right->left = node_left;
        node_left->right = node_right;
        current_node->left = current_node;
        current_node->right = current_node;
        if(node_parent != nullptr) {
            --node_parent->degree;
            node_parent->mark = 1;
        }
        if(node_parent != nullptr && node_parent->child == current_node) {
            if(node_left == current_node) {
                node_parent->child = nullptr;
            } else {
                node_parent->child = node_right;
            }
        }
        current_node->parent = nullptr;
        current_node->mark = 0;
        root = union_lists(root, current_node);
        if(root != current_node && root->key > current_node->key) {
            root = current_node;
        }
        return;
    }

    void print_roots() {
        if(root == nullptr) {
            return;
        }
        Heap_node* move = root->right;
        std::cout << root->key << " ";
        while(move != root) {
            std::cout << move->key << " ";
            move = move->right;
        }
        std::cout << "\n";
    }

    void cascading_cut(Heap_node* current_node) {
        while(current_node != nullptr && current_node->mark == true) {
            Heap_node* node_parent = current_node->parent;
            cut(current_node);
            current_node = node_parent;
        }
        if(current_node != nullptr) {
            current_node->mark = false;
        }
        return;
    }

    int size() {
        return size_;
    }

private:
    Heap_node* root = nullptr;
    int size_ = 0;
};

#endif //HEAPS_AND_TESTING_FIBONACCI_HEAP_H
