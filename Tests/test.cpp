//
// Created by runb2 on 28/10/2018.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ntdef.h>
#include "Dynamic_array.h"
#include "Heap.h"
#include "Binomial_heap.h"
#include "Fibonacci_heap.h"

using testing::Eq;


TEST(Array_tests, init_test) {
    Dynamic_array<int> a;
    EXPECT_EQ(0, a.size());
    EXPECT_THROW(a.pop_back(), std::out_of_range);
}
TEST(Array_tests, push_test) {
    Dynamic_array<int> a;
    a.push_back(25);
    EXPECT_EQ(1, a.size());
    EXPECT_EQ(25, a[0]);
    EXPECT_THROW(a[a.size()], std::out_of_range);
    EXPECT_THROW(a[-1], std::out_of_range);
    a.push_back(26);
    EXPECT_EQ(25, a[0]);
    EXPECT_EQ(26, a[1]);
}
TEST(Array_tests, long_push_test) {
    Dynamic_array<int> a;
    for(int i = 0; i < 100000; i++) {
        a.push_back(i);
        EXPECT_EQ(i, a[i]);
        EXPECT_EQ(i + 1, a.size());
    }
    for(int i = 0; i < 100000; i++) {
        EXPECT_EQ(i, a[i]);
    }
}
TEST(Array_tests, pop_test) {
    Dynamic_array<int> a;
    for(int i = 0; i < 1000; i++) {
        a.push_back(i);
    }
    for(int i = 0; i < 1002; i++) {
        if(i >= 1000) {
            EXPECT_THROW(a.pop_back(), std::out_of_range);
        } else {
            a.pop_back();
            //std::cout << i << " " << a.size() << " " << a.max_size__() << " ! ";
        }
    }
    for(int i = 0; i < 100000; i++) {
        a.push_back(i);
        EXPECT_EQ(i, a[i]);
        EXPECT_EQ(i + 1, a.size());
    }
    for(int i = 0; i < 100000; i++) {
        EXPECT_EQ(i, a[i]);
    }
}
TEST(Array_tests, opetators_test) {
    Dynamic_array<int> a;
    a.push_back(5);
    int c = a[0];
    c = 25;
    EXPECT_EQ(a[0], 5);
    a[0] = 25;
    EXPECT_EQ(a[0], 25);
    a.push_back(1);
    EXPECT_EQ(a[1], 1);
    EXPECT_EQ(a[0], 25);
    std::swap(a[0], a[1]);
    EXPECT_EQ(a[1], 25);
    EXPECT_EQ(a[0], 1);
}


TEST(Heap_tests, init_test) {
    Heap<int> a;
    EXPECT_EQ(1, a.is_empty());
    EXPECT_THROW(a.extract_min(), std::out_of_range);
    EXPECT_THROW(a.get_min(), std::out_of_range);
}
TEST(Heap_tests, insert_test) {
    Heap<int> a;
    a.insert(2);
    EXPECT_EQ(2, a.get_min());
    a.insert(1);
    EXPECT_EQ(1, a.get_min());
    a.insert(4);
    EXPECT_EQ(1, a.get_min());
    a.insert(5);
    EXPECT_EQ(1, a.get_min());
    a.insert(-1);
    EXPECT_EQ(-1, a.get_min());
}
TEST(Heap_tests, extract_test) {
    Heap<int> a;
    a.insert(2);
    a.insert(1);
    a.insert(4);
    a.insert(5);
    a.insert(-1);
    int tmp = a.extract_min();
    EXPECT_EQ(tmp, -1);
    EXPECT_EQ(1, a.get_min());
    tmp = a.extract_min();
    EXPECT_EQ(tmp, 1);
    EXPECT_EQ(2, a.get_min());
    a.extract_min();
    EXPECT_EQ(4, a.get_min());
    a.extract_min();
    EXPECT_EQ(5, a.get_min());
    a.extract_min();
    EXPECT_THROW(a.extract_min(), std::out_of_range);
    EXPECT_THROW(a.get_min(), std::out_of_range);
    a.insert(2);
    a.insert(2);
    a.extract_min();
    EXPECT_EQ(2, a.get_min());
    a.insert(1);
    EXPECT_EQ(1, a.get_min());
    a.insert(4);
    EXPECT_EQ(1, a.get_min());
    a.insert(5);
    EXPECT_EQ(1, a.get_min());
    a.insert(-1);
    EXPECT_EQ(-1, a.get_min());
}
TEST(Heap_tests, extract_test_3kheap) {
    Heap<int> a(3);
    a.insert(2);
    a.insert(1);
    a.insert(5);
    a.insert(5);
    a.insert(-1);
    a.insert(7);
    a.insert(-2);
    a.insert(5);
    a.insert(12);
    a.insert(-10);
    int tmp = a.extract_min();
    EXPECT_EQ(tmp, -10);
    EXPECT_EQ(-2, a.get_min());
    tmp = a.extract_min();
    EXPECT_EQ(tmp, -2);
    a.extract_min();
    EXPECT_EQ(1, a.get_min());
    a.extract_min();
    EXPECT_EQ(2, a.get_min());
    a.extract_min();
    a.insert(2);
    a.insert(2);
    a.extract_min();
    EXPECT_EQ(2, a.get_min());
    a.insert(1);
    EXPECT_EQ(1, a.get_min());
    a.insert(4);
    EXPECT_EQ(1, a.get_min());
    a.insert(5);
    EXPECT_EQ(1, a.get_min());
    a.insert(-1);
    EXPECT_EQ(-1, a.get_min());
}

TEST(Heap_tests, building_heap) {
    Dynamic_array<int> inp;
    inp.push_back(2);
    inp.push_back(1);
    inp.push_back(5);
    inp.push_back(5);
    inp.push_back(-1);
    inp.push_back(7);
    inp.push_back(-2);
    inp.push_back(5);
    inp.push_back(12);
    inp.push_back(-10);
    Heap<int> a(inp.begin(), inp.end());
    int tmp = a.extract_min();
    EXPECT_EQ(tmp, -10);
    EXPECT_EQ(-2, a.get_min());
    tmp = a.extract_min();
    EXPECT_EQ(tmp, -2);
    a.extract_min();
    EXPECT_EQ(1, a.get_min());
    a.extract_min();
    EXPECT_EQ(2, a.get_min());
    a.extract_min();
    a.insert(2);
    a.insert(2);
    a.extract_min();
    EXPECT_EQ(2, a.get_min());
    a.insert(1);
    EXPECT_EQ(1, a.get_min());
    a.insert(4);
    EXPECT_EQ(1, a.get_min());
    a.insert(5);
    EXPECT_EQ(1, a.get_min());
    a.insert(-1);
    EXPECT_EQ(-1, a.get_min());
}
TEST(Heap_tests, optimize_test) {
    Heap<int> a;
    int number_of_children;
    number_of_children = a.optimize(100, 10);
    EXPECT_EQ(number_of_children, 10);
    for(int i = 0, j = 300; i < 100; i++, j-= 3) {
        a.insert(j);
    }
    EXPECT_THROW(a.optimize(0, 10), std::logic_error);
    EXPECT_EQ(a.get_min(), 3);
    for(int i = 0, j = 6; i < 10; i++, j+=3) {
        a.extract_min();
        EXPECT_EQ(a.get_min(), j);
    }
}

TEST(Heap_pointers_tests, validation_test) {
    Heap<int> a;
    Heap<int>::Pointer* pointer = a.insert(5);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-1);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(2);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-3);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-5);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(6);
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(6, a.get_min());
}
TEST(Heap_pointers_tests, change_test) {
    Heap<int> a;
    Heap<int>::Pointer* pointer1 = a.insert(8);
    EXPECT_EQ(8, a.get_element(pointer1));
    a.insert(-1);
    Heap<int>::Pointer* pointer2 = a.insert(-2);
    a.insert(7);
    EXPECT_EQ(8, a.get_element(pointer1));
    EXPECT_EQ(-2, a.get_element(pointer2));
    a.insert(-3);
    a.insert(4);
    a.insert(3);
    EXPECT_EQ(8, a.get_element(pointer1));
    EXPECT_EQ(-2, a.get_element(pointer2));
    EXPECT_EQ(-3, a.get_min());
    a.change(pointer1, -8);
    EXPECT_EQ(-8, a.get_element(pointer1));
    EXPECT_EQ(-2, a.get_element(pointer2));
    EXPECT_EQ(-8, a.get_min());
    a.change(pointer1, 100);
    EXPECT_EQ(100, a.get_element(pointer1));
    EXPECT_EQ(-2, a.get_element(pointer2));
    EXPECT_EQ(-3, a.get_min());
    a.change(pointer2, -4);
    EXPECT_EQ(100, a.get_element(pointer1));
    EXPECT_EQ(-4, a.get_element(pointer2));
    EXPECT_EQ(-4, a.get_min());
}
TEST(Heap_pointers_tests, delete_element_test) {
    Heap<int> a;
    Heap<int>::Pointer* pointer1 = a.insert(8);
    EXPECT_EQ(8, a.get_element(pointer1));
    a.insert(-1);
    Heap<int>::Pointer* pointer2 = a.insert(-2);
    a.insert(7);
    EXPECT_EQ(8, a.get_element(pointer1));
    EXPECT_EQ(-2, a.get_element(pointer2));
    a.insert(-3);
    a.insert(4);
    a.insert(3);
    EXPECT_EQ(-3, a.get_min());
    a.delete_element(pointer2);
    EXPECT_EQ(-3, a.get_min());
    a.extract_min();
    EXPECT_EQ(-1, a.get_min());
}

TEST(Binomial_heap_tests, init_test) {
    Binomial_heap<int> a;
    EXPECT_EQ(1, a.is_empty());
    EXPECT_THROW(a.extract_min(), std::out_of_range);
    EXPECT_THROW(a.get_min(), std::out_of_range);
}
TEST(Binomial_heap_tests, merge_test) {
    Binomial_heap<int> f, s;
    for(int i = 0, j = 0; i < 100; i++, j+=2) {
        f.insert(j);
    }
    for(int i = 0, j = 1; i < 100; i++, j+=2) {
        s.insert(j);
    }
    EXPECT_EQ(f.get_min(), 0);
    EXPECT_EQ(s.get_min(), 1);
    f.merge(s.get_root());
    for(int i = 0; i < 200; i++) {
        EXPECT_EQ(f.get_min(), i);
        f.extract_min();
    }
    EXPECT_THROW(f.extract_min(), std::out_of_range);
    EXPECT_THROW(f.get_min(), std::out_of_range);
    EXPECT_EQ(f.is_empty(), 1);
}
TEST(Binomial_heap_tests, insert_test) {
    Binomial_heap<int> kek;
    int minim;
    kek.insert(0);
    minim = 0;
    for(int i = 0; i <  100000; i++) {
        EXPECT_EQ(kek.get_min(), minim);
        int t = rand();
        kek.insert(t);
        minim = std::min(t, minim);
    }
}
TEST(Binomial_heap_tests, extract_test) {
    Binomial_heap<int> a;
    a.insert(5);
    a.insert(7);
    a.insert(9);
    a.insert(-2);
    a.insert(-5);
    a.insert(100);
    EXPECT_EQ(a.get_min(), -5);
    a.extract_min();
    EXPECT_EQ(a.get_min(), -2);
    a.extract_min();
    EXPECT_EQ(a.get_min(), 5);
    a.extract_min();
    EXPECT_EQ(a.get_min(), 7);
    a.extract_min();
    EXPECT_EQ(a.get_min(), 9);
    a.extract_min();
    EXPECT_EQ(a.get_min(), 100);
    a.extract_min();
    EXPECT_THROW(a.get_min(), std::out_of_range);
    EXPECT_THROW(a.extract_min(), std::out_of_range);

    a.insert(2);
    a.insert(1);
    a.insert(4);
    a.insert(5);
    a.insert(-1);
    int tmp = a.extract_min();
    EXPECT_EQ(tmp, -1);
    EXPECT_EQ(1, a.get_min());
    tmp = a.extract_min();
    EXPECT_EQ(tmp, 1);
    EXPECT_EQ(2, a.get_min());
    a.extract_min();
    EXPECT_EQ(4, a.get_min());
    a.extract_min();
    EXPECT_EQ(5, a.get_min());
    a.extract_min();
    EXPECT_THROW(a.extract_min(), std::out_of_range);
    EXPECT_THROW(a.get_min(), std::out_of_range);
    a.insert(2);
    a.insert(2);
    a.extract_min();
    EXPECT_EQ(2, a.get_min());
    a.insert(1);
    EXPECT_EQ(1, a.get_min());
    a.insert(4);
    EXPECT_EQ(1, a.get_min());
    a.insert(5);
    EXPECT_EQ(1, a.get_min());
    a.insert(-1);
    EXPECT_EQ(-1, a.get_min());
}

TEST(Binomial_heap_pointers_tests, validation_test) {
    Binomial_heap<int> a;
    Binomial_heap<int>::Pointer* pointer = a.insert(5);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-1);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(2);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-3);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-5);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(6);
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(6, a.get_min());
}
TEST(Binomial_heap_pointers_tests, change_test) {
    Binomial_heap<int> a;
    Binomial_heap<int>::Pointer* pointer1 = a.insert(8);
    EXPECT_EQ(8, a.get_element(pointer1));
    a.insert(-1);
    Binomial_heap<int>::Pointer* pointer2 = a.insert(-2);
    a.insert(7);
    EXPECT_EQ(8, a.get_element(pointer1));
    EXPECT_EQ(-2, a.get_element(pointer2));
    a.insert(-3);
    a.insert(4);
    a.insert(3);
    EXPECT_EQ(8, a.get_element(pointer1));
    EXPECT_EQ(-2, a.get_element(pointer2));
    EXPECT_EQ(-3, a.get_min());
    a.change(pointer1, -8);
    EXPECT_EQ(-8, a.get_element(pointer1));
    EXPECT_EQ(-2, a.get_element(pointer2));
    EXPECT_EQ(-8, a.get_min());
    a.change(pointer1, 100);
    EXPECT_EQ(100, a.get_element(pointer1));
    EXPECT_EQ(-2, a.get_element(pointer2));
    EXPECT_EQ(-3, a.get_min());
    a.change(pointer2, -4);
    EXPECT_EQ(100, a.get_element(pointer1));
    EXPECT_EQ(-4, a.get_element(pointer2));
    EXPECT_EQ(-4, a.get_min());
}
TEST(Binomial_heap_pointers_tests, delete_element_test) {
    Binomial_heap<int> a;
    Binomial_heap<int>::Pointer* pointer1 = a.insert(8);
    EXPECT_EQ(8, a.get_element(pointer1));
    a.insert(-1);
    Binomial_heap<int>::Pointer* pointer2 = a.insert(-2);
    a.insert(7);
    EXPECT_EQ(8, a.get_element(pointer1));
    EXPECT_EQ(-2, a.get_element(pointer2));
    a.insert(-3);
    a.insert(4);
    a.insert(3);
    EXPECT_EQ(-3, a.get_min());
    a.delete_node(pointer2);
    EXPECT_EQ(-3, a.get_min());
    a.extract_min();
    EXPECT_EQ(-1, a.get_min());
}
TEST(Binomial_heap_pointers_tests, complex_pointer_test) {
    Binomial_heap<long long> a;
    for(int i = 0; i < 20; i++) {
        a.insert(i);
    }
    EXPECT_EQ(0, a.get_min());
    a.extract_min();
    EXPECT_EQ(1, a.get_min());
    Binomial_heap<long long>::Pointer *p;
    p = a.insert(-5);
    EXPECT_EQ(-5, a.get_min());
    a.change(p, 25);
    for(int i = 0; i < 19; i++) {
        EXPECT_EQ(i + 1, a.get_min());
        a.extract_min();
    }
    EXPECT_EQ(25, a.get_min());
    a.delete_node(p);
    EXPECT_EQ(1, a.is_empty());
}

TEST(Fibonacci_heap_tests, init_test) {
    Fibonacci_heap<int> a;
    EXPECT_EQ(1, a.is_empty());
    EXPECT_THROW(a.extract_min(), std::out_of_range);
    EXPECT_THROW(a.get_min(), std::out_of_range);
}
TEST(Fibonacci_heap_tests, merge_test) {
    Fibonacci_heap<int> f, s;
    for(int i = 0, j = 0; i < 100; i++, j+=2) {
        f.insert(j);
    }
    for(int i = 0, j = 1; i < 100; i++, j+=2) {
        s.insert(j);
    }
    EXPECT_EQ(f.get_min(), 0);
    EXPECT_EQ(s.get_min(), 1);
    f.merge(&s);
    for(int i = 0; i < 200; i++) {
        EXPECT_EQ(f.get_min(), i);
        f.extract_min();
    }
    EXPECT_THROW(f.extract_min(), std::out_of_range);
    EXPECT_THROW(f.get_min(), std::out_of_range);
    EXPECT_EQ(f.is_empty(), 1);
}
TEST(Fibonacci_heap_tests, insert_test) {
    Fibonacci_heap<int> kek;
    int minim;
    kek.insert(0);
    minim = 0;
    for(int i = 0; i <  100000; i++) {
        EXPECT_EQ(kek.get_min(), minim);
        int t = rand();
        kek.insert(t);
        minim = std::min(t, minim);
    }
}
TEST(Fibonacci_heap_tests, extract_test) {
    Fibonacci_heap<int> a;
    a.insert(5);
    a.insert(7);
    a.insert(9);
    a.insert(-2);
    a.insert(-5);
    a.insert(100);
    EXPECT_EQ(a.get_min(), -5);
    a.extract_min();
    EXPECT_EQ(a.get_min(), -2);
    a.extract_min();
    EXPECT_EQ(a.get_min(), 5);
    a.extract_min();
    EXPECT_EQ(a.get_min(), 7);
    a.extract_min();
    EXPECT_EQ(a.get_min(), 9);
    a.extract_min();
    EXPECT_EQ(a.get_min(), 100);
    a.extract_min();
    EXPECT_THROW(a.get_min(), std::out_of_range);
    EXPECT_THROW(a.extract_min(), std::out_of_range);

    a.insert(2);
    a.insert(1);
    a.insert(4);
    a.insert(5);
    a.insert(-1);
    int tmp = a.extract_min();
    EXPECT_EQ(tmp, -1);
    EXPECT_EQ(1, a.get_min());
    tmp = a.extract_min();
    EXPECT_EQ(tmp, 1);
    EXPECT_EQ(2, a.get_min());
    a.extract_min();
    EXPECT_EQ(4, a.get_min());
    a.extract_min();
    EXPECT_EQ(5, a.get_min());
    a.extract_min();
    EXPECT_THROW(a.extract_min(), std::out_of_range);
    EXPECT_THROW(a.get_min(), std::out_of_range);
    a.insert(2);
    a.insert(2);
    a.extract_min();
    EXPECT_EQ(2, a.get_min());
    a.insert(1);
    EXPECT_EQ(1, a.get_min());
    a.insert(4);
    EXPECT_EQ(1, a.get_min());
    a.insert(5);
    EXPECT_EQ(1, a.get_min());
    a.insert(-1);
    EXPECT_EQ(-1, a.get_min());
}
TEST(Fibonacci_heap_tests, validation_test) {
    Fibonacci_heap<int> a;
    Fibonacci_heap<int>::Pointer* pointer = a.insert(5);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-1);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(2);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-3);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-5);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(6);
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(6, a.get_min());
}
TEST(Fibonacci_heap_tests, decrease_test) {
    Fibonacci_heap<int> a;
    Fibonacci_heap<int>::Pointer *p1, *p2, *p3, *p4;
    p1 = a.insert(-5);
    p2 = a.insert(100);
    p3 = a.insert(8);
    a.insert(-2);
    p4 = a.insert(50);
    a.insert(0);
    EXPECT_EQ(-5, a.get_min());
    a.decrease_key(p3, -10);
    EXPECT_EQ(-10, a.get_min());
    EXPECT_EQ(p1->get_elem()->key, -5);
    EXPECT_EQ(p2->get_elem()->key, 100);
    EXPECT_EQ(p3->get_elem()->key, -10);
    EXPECT_EQ(p4->get_elem()->key, 50);
    EXPECT_EQ(a.size(), 6);
    a.extract_min();
    EXPECT_EQ(-5, a.get_min());
    EXPECT_EQ(a.size(), 5);
    EXPECT_EQ(p1->get_elem()->key, -5);
    EXPECT_EQ(p2->get_elem()->key, 100);
    EXPECT_EQ(p4->get_elem()->key, 50);
    a.decrease_key(p4, 25);
    EXPECT_EQ(-5, a.get_min());
    EXPECT_EQ(a.size(), 5);
    EXPECT_EQ(p1->get_elem()->key, -5);
    EXPECT_EQ(p2->get_elem()->key, 100);
    EXPECT_EQ(p4->get_elem()->key, 25);
    a.decrease_key(p4, 20);
    EXPECT_EQ(-5, a.get_min());
    EXPECT_EQ(a.size(), 5);
    a.decrease_key(p2, -6);
    EXPECT_EQ(p1->get_elem()->key, -5);
    EXPECT_EQ(p2->get_elem()->key, -6);
    EXPECT_EQ(p4->get_elem()->key, 20);
    EXPECT_EQ(-6, a.get_min());
    EXPECT_EQ(a.size(), 5);
    a.decrease_key(p2, -7);
    EXPECT_EQ(-7, a.get_min());
    EXPECT_EQ(a.size(), 5);
    a.extract_min();
    EXPECT_EQ(-5, a.get_min());
    EXPECT_EQ(a.size(), 4);
    a.extract_min();
    EXPECT_EQ(-2, a.get_min());
    EXPECT_EQ(a.size(), 3);
    a.extract_min();
    EXPECT_EQ(0, a.get_min());
    EXPECT_EQ(a.size(), 2);
    a.extract_min();
    EXPECT_EQ(20, a.get_min());
    EXPECT_EQ(a.size(), 1);
    a.extract_min();
    EXPECT_EQ(a.size(), 0);
    EXPECT_THROW(a.extract_min(), std::out_of_range);
    EXPECT_THROW(a.get_min(), std::out_of_range);
    EXPECT_EQ(a.is_empty(), 1);
}



TEST(Additional_tests, test_simple_heap) {
    Dynamic_array<long long> arr;
    for(int i = 0; i < 20; i++) {
        arr.push_back(i);
    }
    Heap<long long> a(arr.begin(), arr.end(), 4);
    EXPECT_EQ(0, a.get_min());
    a.extract_min();
    EXPECT_EQ(1, a.get_min());
    Heap<long long>::Pointer *p;
    p = a.insert(-5);
    EXPECT_EQ(-5, a.get_min());
    a.change(p, 25);
    for(int i = 0; i < 19; i++) {
        EXPECT_EQ(i + 1, a.get_min());
        a.extract_min();
    }
    EXPECT_EQ(25, a.get_min());
    a.delete_element(p);
    EXPECT_EQ(1, a.is_empty());
}
TEST(Additional_tests, test_binominal_heap) {
    Binomial_heap<long long> a;
    for(int i = 0; i < 20; i++) {
        a.insert(i);
    }
    EXPECT_EQ(0, a.get_min());
    a.extract_min();
    EXPECT_EQ(1, a.get_min());
    a.insert(25);
    for(int i = 0; i < 19; i++) {
        EXPECT_EQ(i + 1, a.get_min());
        a.extract_min();
    }
    EXPECT_EQ(25, a.get_min());
    a.extract_min();
    EXPECT_EQ(1, a.is_empty());
}
TEST(Additional_tests, test_fibonacci_heap) {
    Heap<int> a;
    Heap<int>::Pointer* pointer = a.insert(5);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-1);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(2);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-3);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(-5);
    EXPECT_EQ(5, a.get_element(pointer));
    a.insert(6);
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(5, a.get_element(pointer));
    a.extract_min();
    EXPECT_EQ(6, a.get_min());
}