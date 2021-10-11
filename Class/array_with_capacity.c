#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef double element_type;
typedef int size_type;

struct array
{
    element_type* start;
    size_type size;
    size_type capacity;
};

size_type array_size(struct array* o)
{
    return o->size;
}

size_type array_capacity(struct array* o)
{
    return o->capacity;
}

int array_empty(struct array* o)
{
    return (o->size == 0);
}

size_type array_max_size(struct array* o)
{
    return INT_MAX;
}

element_type array_access(struct array* o, size_type index)
{
    assert(index >= 0);
    assert(index < o->size);
    return o->start[index];
}

void array_modify(struct array* o, size_type index, element_type value)
{
    assert(index >= 0);
    assert(index < o->size);
    o->start[index] = value;
}

struct array* array_create(size_type size, element_type default_value,
                           size_type capacity)
{
    assert(size <= capacity);
    struct array* a = (struct array*)malloc(sizeof(struct array));
    a->start = (element_type*)malloc(sizeof(element_type) * capacity);
    a->capacity = capacity;
    a->size = size;
    int i = 0;
    for (i = 0; i < size; ++i) {
        a->start[i] = default_value;
    }
    return a;
}

void array_insert(struct array* a, size_type pos, element_type value)
{
    assert(pos >= 0);
    assert(pos < a->size);
    int i = 0;
    if (a->size == a->capacity) {
        element_type nc = 2 * a->capacity;
        element_type* el = (element_type*)malloc(sizeof(element_type) * nc);
        for (i = 0; i < a->size; ++i) {
            el[i] = a->start[i];
        }
        free(a->start);
        a->start = el;
        a->capacity = nc;
    }
    for (i = a->size - 1; i >= pos; --i) {
        a->start[i + 1] = a->start[i];
    }
    a->start[pos] = value;
    a->size = a->size + 1;
}

void array_remove(struct array* o, element_type pos)
{
    assert(pos >= 0);
    assert(pos < o->size);
    // TODO
}

void array_set_capacity(struct array* a, size_type new_capacity)
{
    assert(a->size <= new_capacity);
    // TODO
}

size_type array_get_index_of_largest_value(struct array* a, size_type b, size_type e)
{
    assert(b >= 0);
    assert(e >= 0);
    assert(e < array_size(a));
    assert(b <= e);
    size_type result = b;
    for (size_type i = b + 1; i <= e; ++i) {
        if (array_access(a, result) < array_access(a, i)) {
            result = i;
        }
    }
    return result;
}

void array_swap(struct array* a, size_type f, size_type s)
{
    assert(f >= 0);
    assert(s >= 0);
    assert(f < array_size(a));
    assert(s < array_size(a));
    element_type tmp = a->start[f];
    a->start[f] = a->start[s];
    a->start[s] = tmp;
}


/* 1. Select largest item
 * 2. Swap the largest item with the last item (moving it to the end)
 * 3. Ignoring the last (largest) item, search the rest of the array for largest item
 * 4. Swap the largest item with the last item (next-to-last in the original array)
 * 5. Continue until n-1 items are selected and swapped (the remaining item on the first place is in its proper position)
 */
void array_selection_sort(struct array* a)
{
     size_type n = array_size(a);
     for (size_type i = n - 1; i > 0; --i) {
        size_type l = array_get_index_of_largest_value(a, 0, i);
        if (l != i) {
            array_swap(a, l, i);
        }
     }
}

/*
 * At the first step let us set the Array[0]
 * as the sorted part of the array and Array[1] – Array [n – 1]
 * as not sorted part of the array
 * Take the first item from the not sorted array and
 * find its proper place in the sorted part
 *
 * While looking for the proper position for the item, move each item in the
 * sorted array to the right, thus making a room to insert the target item.
 */
void array_insertion_sort(struct array* a)
{
     size_type n = array_size(a);
     for (size_type i = 0; i < n; ++i) {
     }
}

/*
 * 1. Divide the array into halves
 * 2. Sort each half (here the recursion comes: halves are sorted by the same
 * Merge Sort algorithm)
 * 3. Merge the sorted halves
 *      - Compare the first item in one half with the first item in the other
 *      half
 *      - Move the smaller item to temporary array
 *      - Repeat until there is no more item is left in one of the halves
 *      - Move the remaining items in the other half to the array
 */
void array_merge_sort(struct array* a)
{
    size_type n = array_size(a);
    if (n == 1) {
        return;
    }
    size_type n1 = n/2;
    size_type n2 = n - n1;
    struct array* a1 = array_create(n1, 0, n1);
    struct array* a2 = array_create(n2, 0, n2);
    for (int i = 0, i<n1, i++){
    	array_modify(a1, i, array_access(a, i));
    }
    for (int j = n1+1, j<n, j++){
	array_modify(a2, j, array_access(a, j));
    }
    array_merge_sort(a1);
    array_merge_sort(a2);
    array_merge(a1, a2, a);
}



void array_print(struct array* a)
{
    int i = 0;
    printf("array size=%d capacity=%d\n", array_size(a), array_capacity(a));
    for (i = 0; i < array_size(a); ++i) {
        printf("array[%d]=%f\n", i, array_access(a, i));
    }
}

void array_test()
{
    int i = 0;
    struct array* a = array_create(4, 5, 9);
    array_print(a);
    int number = 6;
    for (i = 0; i < number; ++i) {
        array_insert(a, 0, i);
        // array_print(a);
    }
    assert(array_size(a) == 10);
    array_print(a);
    number = 5;
    for (i = 0; i < number; ++i) {
        array_remove(a, 0);
    }
    array_print(a);
}

void selection_sort_test()
{
    struct array* a = array_create(10, 0, 10);
    array_modify(a, 0, 2);
    array_modify(a, 1, 6);
    array_modify(a, 2, 10);
    array_modify(a, 3, 3);
    array_modify(a, 4, 2);
    array_modify(a, 5, 3);
    array_modify(a, 6, 11);
    array_modify(a, 7, 48);
    array_modify(a, 8, 5);
    array_modify(a, 9, 4);
    // array_print(a);
    assert(array_size(a) == 10);
    array_selection_sort(a);
    assert(array_access(a, 0) == 2.0);
    assert(array_access(a, 1) == 2.0);
    assert(array_access(a, 2) == 3.0);
    assert(array_access(a, 3) == 3.0);
    assert(array_access(a, 4) == 4.0);
    assert(array_access(a, 5) == 5.0);
    assert(array_access(a, 6) == 6.0);
    assert(array_access(a, 7) == 10.0);
    assert(array_access(a, 8) == 11.0);
    assert(array_access(a, 9) == 48.0);
    // array_print(a);
}

void merge_sort_test()
{
    struct array* a = array_create(10, 0, 10);
    array_modify(a, 0, 2);
    array_modify(a, 1, 6);
    array_modify(a, 2, 10);
    array_modify(a, 3, 3);
    array_modify(a, 4, 2);
    array_modify(a, 5, 3);
    array_modify(a, 6, 11);
    array_modify(a, 7, 48);
    array_modify(a, 8, 5);
    array_modify(a, 9, 4);
    array_print(a);
    assert(array_size(a) == 10);
    array_merge_sort(a);
    assert(array_access(a, 0) == 2);
    assert(array_access(a, 1) == 2);
    assert(array_access(a, 2) == 3);
    assert(array_access(a, 3) == 3);
    assert(array_access(a, 4) == 4);
    assert(array_access(a, 5) == 5);
    assert(array_access(a, 6) == 6);
    assert(array_access(a, 7) == 10);
    assert(array_access(a, 8) == 11);
    assert(array_access(a, 9) == 48);
    array_print(a);
}

int main()
{
    // array_test();
    selection_sort_test();
    merge_sort_test();
    return 0;
}
