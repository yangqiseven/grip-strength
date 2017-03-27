#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QString>

MainWindow::MainWindow(QWidget *parent, ring_buffer_t &buffer, QMutex &mutex) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  ring_buffer(buffer),
  mutex(mutex),
  max(0)
{
  ui->setupUi(this);

  grip_strength(ui->customPlot);
  ui->customPlot->replot();

}

void MainWindow::grip_strength(QCustomPlot *customPlot)
{
  int i = 0;

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));

  customPlot->addGraph(); // red line
  customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));


  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  customPlot->xAxis->setTicker(timeTicker);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->yAxis->setRange(0, 130);
  customPlot->xAxis->setLabel("Time (s)");
  customPlot->yAxis->setLabel("Force (kg)");

  customPlot->legend->setVisible(true);
  QFont legendFont = font();  // start out with MainWindow's font..
  legendFont.setPointSize(9); // and make a bit smaller for legend
  customPlot->legend->setFont(legendFont);
  customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
  customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);

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
    if (buf > max){
        max = buf; // check for max value
    }
    ui->customPlot->graph(0)->addData(key, buf);
    ui->customPlot->graph(1)->addData(key, max);
    ui->customPlot->graph(0)->setName("Current Force: " + QString::number(buf));
    ui->customPlot->graph(1)->setName("Maximum Force: " + QString::number(max));
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








































