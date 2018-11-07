//
// Created by runb2 on 28/10/2018.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Dynamic_array.h"
#include "Heap.h"

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