#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

TEST(test_list_assignment_operator){
    List<int> L1;
    for (int i = 0; i < 5; ++i) {
        L1.push_back(i);
    }

    List<int> L2;
    for (int i = 5; i < 10; ++i) {
        L2.push_back(i);
    }
    L2 = L1;

    ASSERT_EQUAL(L2.size(), L1.size());

    auto it1 = L1.begin();
    auto it2 = L2.begin();
    while (it1 != L1.end() && it2 != L2.end()) {
        ASSERT_EQUAL(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_forward_traversal) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    int j = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }
    ASSERT_EQUAL(j, list.size());
}

TEST(test_backward_traversal) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    int j = list.size();
    List<int>::Iterator it = list.end();
    do {
        --it;
        --j;
        ASSERT_EQUAL(*it, j);
    }
    while(it != list.begin());
    ASSERT_EQUAL(j, 0);
}

TEST(test_list_empty_default_ctor) {
    List<int> L;
    ASSERT_TRUE(L.empty());
    ASSERT_EQUAL(L.size(), 0);
    ASSERT_TRUE(L.begin() == L.end());
}

TEST(test_single_push_front) {
    List<int> L;
    L.push_front(10);
    ASSERT_FALSE(L.empty());
    ASSERT_EQUAL(L.size(), 1);
    ASSERT_EQUAL(L.front(), 10);
    ASSERT_EQUAL(L.back(), 10);

    List<int>::Iterator it = L.begin();
    ASSERT_TRUE(it != L.end());
    ASSERT_EQUAL(*it, 10);
    ++it;
    ASSERT_TRUE(it == L.end());
}

TEST(test_single_push_back) {
    List<int> L;
    L.push_back(20);
    ASSERT_FALSE(L.empty());
    ASSERT_EQUAL(L.size(), 1);
    ASSERT_EQUAL(L.front(), 20);
    ASSERT_EQUAL(L.back(), 20);

    auto it = L.begin();
    ASSERT_EQUAL(*it, 20);
    ++it;
    ASSERT_TRUE(it == L.end());
}

TEST(test_insert_at_begin) {
    List<int> L;
    L.push_back(1);
    L.push_back(3);

    auto it = L.begin();
    auto inserted = L.insert(it, 0);  

    ASSERT_EQUAL(*inserted, 0);
    ASSERT_EQUAL(L.front(), 0);
    ASSERT_EQUAL(L.size(), 3);

    int expected[] = {0, 1, 3};
    int j = 0;
    for (auto t = L.begin(); t != L.end(); ++t, ++j) {
        ASSERT_EQUAL(*t, expected[j]);
    }
}

TEST(test_insert_in_middle) {
    List<int> L;
    L.push_back(1);
    L.push_back(3);

    auto it = L.begin();
    ++it;                     
    auto inserted = L.insert(it, 2);

    ASSERT_EQUAL(*inserted, 2);
    ASSERT_EQUAL(L.size(), 3);

    int expected[] = {1, 2, 3};
    int j = 0;
    for (auto t = L.begin(); t != L.end(); ++t, ++j) {
        ASSERT_EQUAL(*t, expected[j]);
    }
}

TEST(test_insert_at_end) {
    List<int> L;
    L.push_back(1);
    L.push_back(2);

    auto it = L.end();
    auto inserted = L.insert(it, 9);

    ASSERT_EQUAL(*inserted, 9);
    ASSERT_EQUAL(L.back(), 9);

    int expected[] = {1, 2, 9};
    int j = 0;
    for (auto t = L.begin(); t != L.end(); ++t, ++j) {
        ASSERT_EQUAL(*t, expected[j]);
    }
}

TEST(test_insert_into_empty_list) {
    List<int> L;
    auto inserted = L.insert(L.end(), 42);

    ASSERT_FALSE(L.empty());
    ASSERT_EQUAL(L.size(), 1);
    ASSERT_EQUAL(L.front(), 42);
    ASSERT_EQUAL(L.back(), 42);
    ASSERT_EQUAL(*inserted, 42);
    ASSERT_TRUE(++inserted == L.end());
}

TEST(test_erase_begin) {
    List<int> L;
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);

    auto it = L.begin();
    auto ret = L.erase(it);

    ASSERT_EQUAL(*ret, 2);
    ASSERT_EQUAL(L.front(), 2);
    ASSERT_EQUAL(L.size(), 2);

    int expected[] = {2, 3};
    int j = 0;
    for (auto t = L.begin(); t != L.end(); ++t, ++j) {
        ASSERT_EQUAL(*t, expected[j]);
    }
}

TEST(test_erase_end) {
    List<int> L;
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);

    auto it = L.end();
    --it;                    
    auto ret = L.erase(it);

    ASSERT_TRUE(ret == L.end());
    ASSERT_EQUAL(L.back(), 2);
    ASSERT_EQUAL(L.size(), 2);

    int expected[] = {1, 2};
    int j = 0;
    for (auto t = L.begin(); t != L.end(); ++t, ++j) {
        ASSERT_EQUAL(*t, expected[j]);
    }
}

TEST(test_erase_middle) {
    List<int> L;
    L.push_back(10);
    L.push_back(20);
    L.push_back(30);

    auto it = L.begin();
    ++it;     // points to 20
    auto ret = L.erase(it);

    ASSERT_EQUAL(*ret, 30);
    ASSERT_EQUAL(L.size(), 2);

    int expected[] = {10, 30};
    int j = 0;
    for (auto t = L.begin(); t != L.end(); ++t, ++j) {
        ASSERT_EQUAL(*t, expected[j]);
    }
}

TEST(test_erase_all_via_loop) {
    List<int> L;
    for (int i = 0; i < 5; ++i) L.push_back(i);

    auto it = L.begin();
    while (it != L.end()) {
        it = L.erase(it);    
    }

    ASSERT_TRUE(L.empty());
    ASSERT_EQUAL(L.size(), 0);
    ASSERT_TRUE(L.begin() == L.end());
}

TEST(test_clear) {
    List<int> L;
    for (int i = 0; i < 10; ++i) L.push_back(i);

    L.clear();

    ASSERT_TRUE(L.empty());
    ASSERT_EQUAL(L.size(), 0);
    ASSERT_TRUE(L.begin() == L.end());

    L.push_back(99);
    ASSERT_EQUAL(L.front(), 99);
    ASSERT_EQUAL(L.back(), 99);
    ASSERT_EQUAL(L.size(), 1);
}


TEST(test_iterator_default_ctor_not_equal_begin_or_end) {
    List<int> L;
    L.push_back(1);

    List<int>::Iterator it_default;
    ASSERT_TRUE(it_default != L.begin());
    ASSERT_TRUE(it_default != L.end());
}

TEST(test_assignment_into_nonempty_nodes) {
    List<int> L1;
    for (int i = 0; i < 3; ++i) L1.push_back(i);
    List<int> L2;
    for (int i = 10; i < 13; ++i) L2.push_back(i);
    L2 = L1;
    ASSERT_EQUAL(L2.size(), 3);

    auto a = L1.begin();
    auto b = L2.begin();
    for (; a != L1.end(); ++a, ++b) {
        ASSERT_EQUAL(*a, *b);
        ASSERT_TRUE(&(*a) != &(*b));
    }
    auto it = L2.begin();
    *it = 999;
    ASSERT_EQUAL(L1.front(), 0);
    ASSERT_EQUAL(L2.front(), 999);
}

TEST(test_assignment_into_empty_list) {
    List<int> L1;
    for (int i = 0; i < 4; ++i) L1.push_back(i);
    List<int> L2;
    L2 = L1;
    ASSERT_EQUAL(L2.size(), 4);

    auto a = L1.begin();
    auto b = L2.begin();
    for (; a != L1.end(); ++a, ++b) {
        ASSERT_EQUAL(*a, *b);
    }
}

TEST(test_self_assignment) {
    List<int> L;
    for (int i = 0; i < 5; ++i) L.push_back(i);
    L = L;
    ASSERT_EQUAL(L.size(), 5);
    int expected = 0;
    for (auto it = L.begin(); it != L.end(); ++it, ++expected) {
        ASSERT_EQUAL(*it, expected);
    }
}

TEST(test_insert_before_begin) {
    List<int> L;
    L.push_back(5);
    auto it = L.begin();
    auto inserted = L.insert(it, 99);
    ASSERT_EQUAL(L.size(), 2);
    ASSERT_EQUAL(L.front(), 99);
    ASSERT_EQUAL(*inserted, 99);
    it = L.begin();
    ASSERT_EQUAL(*it, 99);
    ++it;
    ASSERT_EQUAL(*it, 5);
    ++it;
    ASSERT_TRUE(it == L.end());
}


TEST_MAIN()
