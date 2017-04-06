# Qt project file - qmake uses this to generate a Makefile

QT       += core gui

CONFIG          += qt warn_on debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

Release:DESTDIR = build
Release:OBJECTS_DIR = build/.obj
Release:MOC_DIR = build/.moc
Release:RCC_DIR = build/.rcc
Release:UI_DIR = build/.ui

TARGET = grip-strength

greaterThan(QT_MAJOR_VERSION, 4): LIBS += -lbcm2835 -lm
lessThan(QT_MAJOR_VERSION, 5): LIBS += -lbcm2835 -lm

HEADERS += src\adcreader.h \
    src\mainwindow.h \
    src\qcustomplot.h \
    src\ringBuffer.h \
    src\gz_clk.h \
    src\gpio-sysfs.h

SOURCES += src\main.cpp src\adcreader.cpp \
    src\mainwindow.cpp \
    src\qcustomplot.cpp \
    src\ringBuffer.c \
    src\gz_clk.cpp \
    src\gpio-sysfs.cpp

FORMS += \
    src\mainwindow.ui
