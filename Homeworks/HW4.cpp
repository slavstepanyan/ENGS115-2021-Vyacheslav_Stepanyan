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
        a->start = el;
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
	for(int i = pos; i<= array_size(o); i++){
		o->start[i] = o->start[i+1];
	}
	o->size = o->size - 1;
}

void array_set_capacity(struct array* a, size_type new_capacity)
{   
    assert(a->size <= new_capacity);
	element_type* b = (element_type*)malloc(sizeof(element_type) * new_capacity);	
	for (int i = 0; i < a->size; i++){
		b[i] = a->start[i];
	}
	a->start = b;
	array_empty(a);
}


void array_print(struct array* a)
{
    int i = 0;
    printf("array size=%d capacity=%d\n", array_size(a), array_capacity(a));
    for (i = 0; i < array_size(a); ++i) {
        printf("array[%d]=%f\n", i, array_access(a, i));
    }
}

int main()
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
	int arr[15] = {1,3,4,7,5};
	int b = sizeof(arr);
	int c = b/sizeof(arr[0]);
	printf("%d\n", b);
	printf("%d\n", c);
	
	return 0;
}
