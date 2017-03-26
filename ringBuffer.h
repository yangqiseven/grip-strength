#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RINGBUFFER_H
#define RINGBUFFER_H


// The buffer size must be a power of two.

#define RING_BUFFER_SIZE 128

#if (RING_BUFFER_SIZE & (RING_BUFFER_SIZE - 1)) != 0
#error "RING_BUFFER_SIZE must be a power of two"
#endif

// Buffer size type

typedef uint8_t ring_buffer_size_t;

// Used as a modulo operator

#define RING_BUFFER_MASK (RING_BUFFER_SIZE-1)

typedef struct ring_buffer_t ring_buffer_t;


struct ring_buffer_t {
  char buffer[RING_BUFFER_SIZE];
  ring_buffer_size_t tail_index;
  ring_buffer_size_t head_index;
};

void ring_buffer_init(ring_buffer_t *buffer);

// Adds a byte to a ring buffer.

void ring_buffer_queue(ring_buffer_t *buffer, uint8_t data);

// Returns the oldest byte in a ring buffer.
uint8_t ring_buffer_dequeue(ring_buffer_t *buffer, uint8_t *data);

// Returns whether a ring buffer is empty.

inline uint8_t ring_buffer_is_empty(ring_buffer_t *buffer) {
  return (buffer->head_index == buffer->tail_index);
}

// Returns whether a ring buffer is full.

inline uint8_t ring_buffer_is_full(ring_buffer_t *buffer) {
  return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_MASK) == RING_BUFFER_MASK;
}

// Returns the number of items in a ring buffer.

inline ring_buffer_size_t ring_buffer_num_items(ring_buffer_t *buffer) {
  return ((buffer->head_index - buffer->tail_index) & RING_BUFFER_MASK);
}

#endif /* RINGBUFFER_H */

#ifdef __cplusplus
}
#endif
