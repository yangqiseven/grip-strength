#include <QApplication>
#include "mainwindow.h"
#include "ringBuffer.h"
#include "adcreader.h"
#include "global.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  QApplication::setGraphicsSystem("raster");
#endif

  QApplication a(argc, argv);

  MainWindow w;
  w.show();

  ring_buffer_init(&ring_buffer);

  ADCreader adcReader;
  adcReader.start();

  return a.exec();
}
