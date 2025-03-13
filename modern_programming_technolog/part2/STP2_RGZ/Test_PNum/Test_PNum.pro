QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_t_pnum.cpp \
    ../P-Num_Calculator/src/pnum.cpp

HEADERS += \
    ../P-Num_Calculator/src/pnum.h
