#ifndef GLOBAL_H
#define GLOBAL_H
#include "ringBuffer.h"
#include <QMutex>

extern QMutex mutex;
extern ring_buffer_t ring_buffer;

#endif // GLOBAL_H
