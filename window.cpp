#include "window.h"
// #include "adcreader.h"

#include <cmath>  // for sine stuff


Window::Window() : gain(5), count(0)
{
	// set up the initial plot data
    for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
        yMData[index] = gain * sin( M_PI * index/50 );
        yFData[index] = gain * cos( M_PI * index/50 );
	}

    curveM = new QwtPlotCurve;
    plotM = new QwtPlot;
    curveF = new QwtPlotCurve;
    plotF = new QwtPlot;
	// make a plot curve from the data and attach it to the plot
    curveM->setSamples(xData, yMData, plotDataSize);
    curveM->attach(plotM);
    curveF->setSamples(xData, yFData, plotDataSize);
    curveF->attach(plotF);

    plotM->replot();
    plotM->show();
    plotF->replot();
    plotF->show();


    // set up the layout - knob above thermometer
    vLayout = new QVBoxLayout;
    //vLayout->addWidget(knob);
    //vLayout->addWidget(thermo);

    // plot to the left of knob and thermometer
	hLayout = new QHBoxLayout;
    //hLayout->addLayout(vLayout);
    hLayout->addWidget(plotM);
    hLayout->addWidget(plotF);


	setLayout(hLayout);

	// This is a demo for a thread which can be
	// used to read from the ADC asynchronously.
	// At the moment it doesn't do anything else than
	// running in an endless loop and which prints out "tick"
	// every second.
//	adcreader = new ADCreader();
//	adcreader->start();
}

Window::~Window() {
	// tells the thread to no longer run its endless loop
//	adcreader->quit();
	// wait until the run method has terminated
//	adcreader->wait();
//	delete adcreader;
}

void Window::timerEvent( QTimerEvent * )
{
    double inValM = gain * sin( M_PI * count/50.0 );
    double inValF = gain * cos( M_PI * count/50.0 );
	++count;

	// add the new input to the plot
    memmove( yMData, yMData+1, (plotDataSize-1) * sizeof(double) );
    yMData[plotDataSize-1] = inValM;
    curveM->setSamples(xData, yMData, plotDataSize);
    plotM->replot();

    memmove( yFData, yFData+1, (plotDataSize-1) * sizeof(double) );
    yFData[plotDataSize-1] = inValF;
    curveF->setSamples(xData, yFData, plotDataSize);
    plotF->replot();
}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
	// for example purposes just change the amplitude of the generated input
	this->gain = gain;
}
