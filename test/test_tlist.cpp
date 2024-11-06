#include "list.h"

#include <gtest.h>

TEST(List, can_create_empty_list) {
    ASSERT_NO_THROW(List<int> l);
}

TEST(List, can_create_list_with_initial_size) {
    ASSERT_NO_THROW(List<int> l(5));
}

TEST(List, can_insert_value_at_front) {
    List<int> l;
    l.insert_front(10);
    EXPECT_EQ(l.get_first()->data, 10);
}

TEST(List, can_insert_multiple_values_at_front) {
    List<int> l;
    l.insert_front(10);
    l.insert_front(20);
    EXPECT_EQ(l.get_first()->data, 20);
    EXPECT_EQ(l.get_first()->next->data, 10);
}

TEST(List, can_erase_front) {
    List<int> l;
    l.insert_front(10);
    l.insert_front(20);
    l.erase_front();
    EXPECT_EQ(l.get_first()->data, 10);
}

TEST(List, can_erase_front_from_single_element) {
    List<int> l;
    l.insert_front(10);
    l.erase_front();
    EXPECT_EQ(l.size(), 0);
}

TEST(List, can_find_existing_value) {
    List<int> l;
    l.insert_front(10);
    l.insert_front(20);
    EXPECT_NE(l.find(10), nullptr);
}

TEST(List, cannot_find_non_existing_value) {
    List<int> l;
    l.insert_front(10);
    EXPECT_EQ(l.find(20), nullptr);
}

TEST(List, can_get_size_of_list) {
    List<int> l;
    l.insert_front(10);
    l.insert_front(20);
    EXPECT_EQ(l.size(), 2);
}

TEST(List, can_copy_list) {
    List<int> l;
    l.insert_front(10);
    l.insert_front(20);

    List<int> l2 = l;
    EXPECT_EQ(l2.get_first()->data, 20);
    EXPECT_EQ(l2.get_first()->next->data, 10);
}

TEST(List, copied_list_is_independent) {
    List<int> l;
    l.insert_front(10);
    List<int> l2 = l;
    l2.insert_front(20);

    EXPECT_NE(l2.get_first()->data, l.get_first()->data);
}

TEST(List, can_assign_list) {
    List<int> l1;
    l1.insert_front(10);
    List<int> l2;
    l2 = l1;
    EXPECT_EQ(l2.get_first()->data, 10);
}

TEST(List, can_access_element_by_index) {
    List<int> l;
    l.insert_front(10);
    l.insert_front(20);
    EXPECT_EQ(l[0], 20);
    EXPECT_EQ(l[1], 10);
}

TEST(List, throws_when_accessing_out_of_range_index) {
    List<int> l;
    l.insert_front(10);
    ASSERT_ANY_THROW(l[2]);
}

TEST(List, throws_when_erase_invalid_node) {
    List<int> l;
    l.insert_front(10);
    ASSERT_ANY_THROW(l.erase(nullptr));
}

TEST(List, can_find_first_node) {
    List<int> l;
    l.insert_front(10);
    l.insert_front(20);
    EXPECT_EQ(l.get_first()->data, 20);
}

TEST(List, can_destroy_list_and_free_memory) {
    {
        List<int> l;
        l.insert_front(10);
        l.insert_front(20);
    }
}

TEST(List, can_insert_after_specific_node) {
    List<int> l;
    l.insert_front(10);
    l.insert_front(20);
    auto secondNode = l.get_first()->next;
    l.insert(15, secondNode);
    EXPECT_EQ(secondNode->next->data, 15);
}

TEST(List, throws_when_erase_front_from_empty_list) {
    List<int> l;
    ASSERT_ANY_THROW(l.erase_front());
}

TEST(List, can_insert_into_empty_list) {
    List<int> l;
    ASSERT_EQ(l.size(), 0);

    l.insert_front(10);
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.get_first()->data, 10);
    EXPECT_EQ(l.get_first()->next, nullptr);
}

TEST(List, throwss_when_erase_front_from_empty_list) {
    List<int> l;

    ASSERT_ANY_THROW(l.erase_front());
}

TEST(Iterator, can_create_iterator)
{
    List<int> list(3);
    ASSERT_NO_THROW(List<int>::iterator it = list.begin());
}

TEST(Iterator, begin_points_to_first_element)
{
    List<int> list(3);
    list.insert_front(1);
    list.insert_front(2);
    list.insert_front(3);
    EXPECT_EQ(*list.begin(), 3);
}

TEST(Iterator, end_points_to_nullptr)
{
    List<int> list(3);
    EXPECT_EQ(list.end(), List<int>::iterator(nullptr));
}

TEST(Iterator, can_increment_iterator_prefix)
{
    List<int> list(3);
    list.insert_front(1);
    list.insert_front(2);
    list.insert_front(3);

    List<int>::iterator it = list.begin();
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(Iterator, can_increment_iterator_postfix)
{
    List<int> list(3);
    list.insert_front(1);
    list.insert_front(2);
    list.insert_front(3);

    List<int>::iterator it = list.begin();
    it++;
    EXPECT_EQ(*it, 2);
}

TEST(Iterator, can_compare_iterators_with_equal_operator)
{
    List<int> list(3);
    list.insert_front(1);

    List<int>::iterator it1 = list.begin();
    List<int>::iterator it2 = list.begin();
    EXPECT_TRUE(it1 == it2);
}

TEST(Iterator, can_compare_iterators_with_not_equal_operator)
{
    List<int> list(3);
    list.insert_front(1);

    List<int>::iterator it1 = list.begin();
    List<int>::iterator it2 = list.end();
    EXPECT_TRUE(it1 != it2);
}

TEST(Iterator, can_access_data_using_dereference_operator)
{
    List<int> list(1);
    list.insert_front(10);
    List<int>::iterator it = list.begin();
    EXPECT_EQ(*it, 10);
}

TEST(Iterator, iterator_initialized_to_nullptr_with_end)
{
    List<int> list;
    List<int>::iterator it = list.end();
    EXPECT_EQ(it, List<int>::iterator(nullptr));
}

TEST(Iterator, iterator_reaches_end_after_single_element)
{
    List<int> list;
    list.insert_front(42);
    List<int>::iterator it = list.begin();
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(Iterator, can_access_data_using_arrow_operator)
{
    List<int> list;
    list.insert_front(5);
    List<int>::iterator it = list.begin();
    EXPECT_EQ(*it, 5); 
}

TEST(List, insert_into_empty_ordered_list) {
    List<int> list;
    list.insert_ordered(5);

    // Проверяем, что единственный элемент списка равен 5
    EXPECT_EQ(list.get_first()->data, 5);
    // Проверяем, что размер списка 1
    EXPECT_EQ(list.size(), 1);
}

TEST(List, insert_smaller_element) {
    List<int> list;
    list.insert_ordered(10); 
    list.insert_ordered(5);  

    // Проверяем порядок элементов
    EXPECT_EQ(list.get_first()->data, 5);
    EXPECT_EQ(list.get_first()->next->data, 10);
}