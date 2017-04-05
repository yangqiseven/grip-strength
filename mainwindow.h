#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"
#include "ringBuffer.h"
#include <QMutex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent, ring_buffer_t &buffer, QMutex &mutex);
  ~MainWindow();

  void grip_strength(QCustomPlot *customPlot);



private slots:
  void realtimeDataSlot();

private:
  Ui::MainWindow *ui;
  QTimer dataTimer;
  ring_buffer_t& ring_buffer;
  QMutex& mutex;
  uint16_t max;
};

#endif // MAINWINDOW_H
