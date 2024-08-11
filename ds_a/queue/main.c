
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
  size_t qsize;
  size_t data_index;
  int *data;
} queue_t;


void queue_init_dynamic(queue_t *qhdl, size_t qsize) {
  if (qhdl == NULL) {
    return;
  }

  qhdl->qsize = qsize;
  qhdl->data_index = 0;
  qhdl->data = malloc(qsize * sizeof(int));
  if (qhdl->data == NULL) {
    return;
  }
}

void queue_delete_dynamic(queue_t *qhdl) {
  if (qhdl == NULL) {
    return;
  }

  free(qhdl->data);
  qhdl->data = NULL;
  qhdl->qsize = 0;
  qhdl->data_index = 0;
}

void queue_init_static(queue_t *qhdl, size_t qsize, int *buffer) {
  if (qhdl == NULL) {
    return;
  }

  qhdl->qsize = qsize;
  qhdl->data_index = 0;
  qhdl->data = buffer;
}

void queue_is_full(queue_t *qhdl, int *is_full) {
  if (qhdl == NULL) {
    return;
  }

  *is_full = (qhdl->data_index == qhdl->qsize);
}

void queue_is_empty(queue_t *qhdl, int *is_empty) {
  if (qhdl == NULL) {
    return;
  }

  *is_empty = (qhdl->data_index == 0);
}

void queue_slots_remaining(queue_t *qhdl, size_t *slots_remaining) {
  if (qhdl == NULL) {
    return;
  }

  *slots_remaining = qhdl->qsize - qhdl->data_index;
}

void queue_enqueue(queue_t *qhdl, int elem) {
  if (qhdl == NULL) {
    return;
  }

  // If the queue is full, do nothing
  int is_full = 0;
  queue_is_full(qhdl, &is_full);
  if (is_full) {
    return;
  }

  qhdl->data[qhdl->data_index] = elem;
  qhdl->data_index++;
}

void queue_dequeue(queue_t *qhdl, int *elem) {
  if (qhdl == NULL) {
    return;
  }

  // If the queue is empty, do nothing
  int is_empty = 0;
  queue_is_empty(qhdl, &is_empty);
  if (is_empty) {
    return;
  }

  // Dequeue the first element, and shift the rest of the elements
  *elem = qhdl->data[0];
  qhdl->data_index--;
  for (int i = 0; i < qhdl->data_index; i++) {
    qhdl->data[i] = qhdl->data[i + 1];
  }
}

int main()
{
    queue_t q;

    printf("Dynamic queue\n");
    queue_init_dynamic(&q, 5);

    queue_enqueue(&q, 12);
    queue_enqueue(&q, 47);
    queue_enqueue(&q, 3);

    printf("Slots remaining: %ld\n", q.qsize - q.data_index);

    int elem;
    queue_dequeue(&q, &elem);
    printf("%d\n", elem);

    queue_dequeue(&q, &elem);
    printf("%d\n", elem);

    queue_dequeue(&q, &elem);
    printf("%d\n", elem);

    queue_delete_dynamic(&q);

    printf("........................................\n");

    printf("Static queue\n");
    int data[10] = {0};
    queue_init_static(&q, 10, data);

    queue_enqueue(&q, 36);
    queue_enqueue(&q, 7);
    queue_enqueue(&q, 9);

    printf("Slots remaining: %ld\n", q.qsize - q.data_index);

    queue_dequeue(&q, &elem);
    printf("%d\n", elem);

    queue_dequeue(&q, &elem);
    printf("%d\n", elem);

    queue_dequeue(&q, &elem);
    printf("%d\n", elem);

    return 0;
}
