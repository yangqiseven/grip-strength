#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void grip_strength(QCustomPlot *customPlot);



private slots:
  void realtimeDataSlot();

private:
  Ui::MainWindow *ui;
  QTimer dataTimer;

};

#endif // MAINWINDOW_H
