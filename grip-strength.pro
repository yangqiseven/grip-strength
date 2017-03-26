# Qt project file - qmake uses this to generate a Makefile

QT       += core gui

CONFIG          += qt warn_on debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = grip-strength

greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lqwt-qt5 -lm
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lqwt -lm

HEADERS += adcreader.h \
    mainwindow.h \
    qcustomplot.h \
    ringBuffer.h

SOURCES += main.cpp adcreader.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    ringBuffer.c

FORMS += \
    mainwindow.ui
