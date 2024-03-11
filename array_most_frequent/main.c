
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct map_node {
    int value;
    int count;
} map_node_t;

typedef struct arr_map {
    // Hashing cache
    int arr_min;
    int map_len;

    // Data
    map_node_t *map;

} arr_map_t;

// Map private functions
static int arr_max(int n, int arr[n]) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

static int arr_min(int n, int arr[n]) {
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// Important map index calculation
static int arr_idx_map(arr_map_t *map, int val) {
    return val - map->arr_min;
}

// Map public functions
void map_init(arr_map_t *map, int n, int arr[n]) {
    int amax = arr_max(n, arr);
    map->arr_min = arr_min(n, arr);
    int span = amax - map->arr_min + 1;

    map->map_len = span;
    map->map = (map_node_t *)malloc(span * sizeof(map_node_t));
    if (map->map == NULL) {
        printf("Failed to allocate memory\n");
        return;
    }

    printf("Max: %d, Min: %d\n", amax, map->arr_min);
}

void map_delete(arr_map_t *map) {
    free(map->map);
}

void map_insert(arr_map_t *map, int value) {
    int idx = arr_idx_map(map, value);
    map->map[idx].value = value;
    map->map[idx].count++;
}

void print_map(arr_map_t *map) {
    for (int i = 0; i < map->map_len; i++) {
        printf("Value: %d, count: %d\n", map->map[i].value, map->map[i].count);
    }
}

// Solution
int most_frequent_val_in_arr(int n, int arr[n], int *value, int *count)
{
    if (n <= 0) {
        printf("Invalid array size\n");
        return -1;
    }

    if (arr == NULL) {
        printf("Invalid array\n");
        return -1;
    }

    arr_map_t map[n];
    map_init(map, n, arr);
    
    for (int i = 0; i < n; i++) {
        map_insert(map, arr[i]);
    }

    int max_count = 0;
    int most_frequent_value = arr[0];

    for (int i = 0; i < map->map_len; i++) {
        if (map->map[i].count > max_count) {
            max_count = map->map[i].count;
            most_frequent_value = map->map[i].value;
        }
    }

    *value = most_frequent_value;
    *count = max_count;
    
    print_map(map);

    map_delete(map);

    return 0;
}

int main()
{
    const int arr_size = 11;
    int arr[] = {-5, 6, -5, 0, 1, 8, 9, 9, 9, -5, 9};
    
    int mf_value;
    int mf_count = 0;
    most_frequent_val_in_arr(arr_size, arr, &mf_value, &mf_count);
    
    printf("Most frequent value: %d, count: %d\n", mf_value, mf_count);

    return 0;
}
