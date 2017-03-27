
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent, ring_buffer_t &buffer, QMutex &mutex) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  ring_buffer(buffer),
  mutex(mutex)
{
  ui->setupUi(this);

  grip_strength(ui->customPlot);
  ui->customPlot->replot();

}

void MainWindow::grip_strength(QCustomPlot *customPlot)
{

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
  //customPlot->addGraph(); // red line
  //customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  customPlot->xAxis->setTicker(timeTicker);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->yAxis->setRange(0, 130);
  customPlot->xAxis->setLabel("Time (s)");
  customPlot->yAxis->setLabel("Force (kg)");

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(1); // Interval is in ms 0 means to refresh as fast as possible
}


void MainWindow::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  uint8_t buf = 0;

  // add data to lines:
  mutex.lock();
  while(ring_buffer_dequeue(&ring_buffer, &buf) > 0) { // empty buffer
    ui->customPlot->graph(0)->addData(key, buf);
  }
  mutex.unlock();

  // rescale value (vertical) axis to fit the current data:
  //ui->customPlot->graph(0)->rescaleValueAxis();
  //ui->customPlot->graph(1)->rescaleValueAxis(true);

  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
  ui->customPlot->replot();
}


MainWindow::~MainWindow()
{
  delete ui;
}








































