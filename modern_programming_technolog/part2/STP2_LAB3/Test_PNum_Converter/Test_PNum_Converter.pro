QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_t_pnum_converter.cpp \
    ../Multi-Calculator/src/pnum_converter.cpp

HEADERS += \
    ../Multi-Calculator/src/pnum_converter.h
