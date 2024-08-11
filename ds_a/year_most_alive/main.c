
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct person {
  int birth;
  int death;
} person_t;

int compare_int(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

int arr_sort(int arr[], int n)
{
  // Sanity checks
  assert(arr != NULL);
  assert(n > 0);

  // Quicksort
  qsort(arr, n, sizeof(int), compare_int);

  return 0;
}

int year_most_alive(person_t records[], int num_records, int *year_most_alive, int *number_alive)
{
  // Sanity checks
  assert(records != NULL);
  assert(num_records > 0);
  assert(year_most_alive != NULL);
  assert(number_alive != NULL);
  // TODO: Add error return values

  // Create birth year and death year arrays
  // o(n) performance and memory
  int births[num_records];
  int deaths[num_records];

  // Populate birth and death year arrays
  for (int i = 0; i < num_records; i++) {
    births[i] = records[i].birth;
    deaths[i] = records[i].death;
  }

  // Sort the arrays
  arr_sort(births, num_records);  //o(nlogn)
  arr_sort(deaths, num_records);  //o(nlogn)

  // Tracking variables
  int num_alive = 0;
  int max_alive = 0;

  // Iterate through records, add count on birth year and subtract count on death year +1
  // o(n)-ish. Actually O(m) where m is the number of years between the first and last birth year
  int birth_index = 0;
  int death_index = 0;

  int start_year = births[0];
  int end_year = births[num_records - 1];

  bool decrement_next_iter = false; // Needed to decrement count on year after death
  for (int i = start_year; i < end_year; i++) {
    if (decrement_next_iter) {
      num_alive--;
      decrement_next_iter = false;
    }
    
    if (i == births[birth_index]) {
      num_alive++;
      birth_index++;
    }
    if (i == deaths[death_index]) {
      death_index++;
      decrement_next_iter = true;
    }

    if (num_alive > max_alive) {
      max_alive = num_alive;
      *year_most_alive = i;
    }
  }

  *number_alive = max_alive;

  return 0;
}

int main(void)
{
  // Test record
  person_t records[] = {
    {1904, 1922},
    {1895, 1919},
    {1930, 1950},
    {1910, 1940},
    {1920, 1940},
    {1915, 1970}
  };

  int number = 0;
  int year = 0;

  // Time: O(nlogn) + O(m) = ~O(nlogn) if n >> m
  // Space: O(n)
  int err = year_most_alive(records, sizeof(records)/sizeof(records[0]), &year, &number);

  printf("Year with most people alive: %d\n", year);
  printf("Number of people alive: %d\n", number);

  return 0;
}