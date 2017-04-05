# Qt project file - qmake uses this to generate a Makefile

QT       += core gui

CONFIG          += qt warn_on debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = grip-strength

greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lbcm2835 -lm
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lbcm2835 -lm

HEADERS += adcreader.h \
    mainwindow.h \
    qcustomplot.h \
    ringBuffer.h \
    gz_clk.h \
    gpio-sysfs.h

SOURCES += main.cpp adcreader.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    ringBuffer.c \
    gz_clk.cpp \
    gpio-sysfs.cpp

FORMS += \
    mainwindow.ui
