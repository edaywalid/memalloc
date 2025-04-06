#include "../memalloc.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_malloc() {
    printf("Running test_malloc...\n");
    void *ptr = malloc(100);
    assert(ptr != NULL);
    free(ptr);
    printf("test_malloc passed.\n");
}

void test_free() {
    printf("Running test_free...\n");
    void *ptr = malloc(100);
    assert(ptr != NULL);
    free(ptr);

    free(ptr);
    printf("test_free passed.\n");
}

void test_realloc() {
    printf("Running test_realloc...\n");
    void *ptr = malloc(100);
    assert(ptr != NULL);
    ptr = realloc(ptr, 200);
    assert(ptr != NULL);
    free(ptr);
    printf("test_realloc passed.\n");
}

void test_calloc() {
    printf("Running test_calloc...\n");
    int *arr = (int *)calloc(10, sizeof(int));
    assert(arr != NULL);
    for (int i = 0; i < 10; i++) {
        assert(arr[i] == 0); 
    }
    free(arr);
    printf("test_calloc passed.\n");
}

void test_memory_stats() {
    printf("Running test_memory_stats...\n");
    void *ptr1 = malloc(50);
    void *ptr2 = malloc(100);
    print_memory_stats();
    free(ptr1);
    free(ptr2);
    print_memory_stats();
    printf("test_memory_stats passed.\n");
}

int main() {
    test_malloc();
    test_free();
    test_realloc();
    test_calloc();
    test_memory_stats();
    printf("All tests passed successfully.\n");
    return 0;
}
