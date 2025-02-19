QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_t_converter.cpp \
    ../Converter_p1_p2/src/converter.cpp

HEADERS += \
    ../Converter_p1_p2/src/converter.h
