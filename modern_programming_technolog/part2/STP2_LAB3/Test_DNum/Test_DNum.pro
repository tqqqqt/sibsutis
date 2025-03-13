QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_t_dnum.cpp \
    ../Multi-Calculator/src/dnum.cpp

HEADERS += \
    ../Multi-Calculator/src/dnum.h
