QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_t_converter.cpp \
    ../P-Num_Calculator/src/converter.cpp

HEADERS += \
    ../P-Num_Calculator/src/converter.h
