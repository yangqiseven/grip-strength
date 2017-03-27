#ifndef ADCREADER
#define ADCREADER

#include <QThread>
#include "ringBuffer.h"
#include "global.h"

class ADCreader : public QThread
{
public:
	ADCreader() {running = 0;};
	void quit();
    void run();
private:
	bool running;

};

#endif
