#ifndef ADCREADER
#define ADCREADER

#include <QThread>
#include "ringBuffer.h"
//#include "global.h"

class ADCreader : public QThread
{
public:
    ADCreader(ring_buffer_t &buffer);
	void quit();
    void run();
private:
	bool running;
    ring_buffer_t& ring_buffer;
};

#endif
