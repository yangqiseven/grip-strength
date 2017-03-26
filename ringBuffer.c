#include "ringBuffer.h"

void ring_buffer_init(ring_buffer_t *buffer) {
  buffer->tail_index = 0;
  buffer->head_index = 0;
}

void ring_buffer_queue(ring_buffer_t *buffer, uint8_t data) {

  if(ring_buffer_is_full(buffer)) {
    buffer->tail_index = ((buffer->tail_index + 1) & RING_BUFFER_MASK);
  }

  buffer->buffer[buffer->head_index] = data;
  buffer->head_index = ((buffer->head_index + 1) & RING_BUFFER_MASK);
}

ring_buffer_size_t ring_buffer_dequeue(ring_buffer_t *buffer, uint8_t *data) {
  if(ring_buffer_is_empty(buffer)) {
    return 0;
  }

  *data = buffer->buffer[buffer->tail_index];
  buffer->tail_index = ((buffer->tail_index + 1) & RING_BUFFER_MASK);
  return 1;
}

extern inline uint8_t ring_buffer_is_empty(ring_buffer_t *buffer);
extern inline uint8_t ring_buffer_is_full(ring_buffer_t *buffer);
extern inline uint8_t ring_buffer_num_items(ring_buffer_t *buffer);
