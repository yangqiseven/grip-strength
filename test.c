#include <stdio.h>
#include <assert.h>
#include "ringBuffer.h"

int main(void) {

        //Create and initialize ring buffer

        ring_buffer_t ring_buffer;
        ring_buffer_init(&ring_buffer);

        int i = 0;
        int buf = 0;

        // Partially fill buffer
        for (i = 0; i < 100; i++) {
                ring_buffer_queue(&ring_buffer, i);
        }

        // Verify size of ring buffer
        assert(ring_buffer_num_items(&ring_buffer) == 100);

        // Check if buffer is empty
        assert(!ring_buffer_is_empty(&ring_buffer));

        // Empty buffer
        while(ring_buffer_dequeue(&ring_buffer, &buf) > 0) {
                printf("Read: %d\n", buf);
        }

        // Check if buffer is empty
        assert(ring_buffer_is_empty(&ring_buffer));

        // Put too much data in buffer
        for(i = 0; i < 1000; i++) {
                ring_buffer_queue(&ring_buffer, (i % 127));
        }

        // Check if buffer is full
        assert(ring_buffer_is_full(&ring_buffer));

        // Empty buffer
        while(ring_buffer_dequeue(&ring_buffer, &buf) > 0) {
                printf("Read: %d\n", buf); // Observe that the bufffer overflows and replaces the oldest data
        }

        // Check if buffer is empty
        assert(ring_buffer_is_empty(&ring_buffer));

}
