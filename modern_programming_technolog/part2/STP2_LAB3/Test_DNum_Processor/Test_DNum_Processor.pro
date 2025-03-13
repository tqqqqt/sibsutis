QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_t_dnum_processor.cpp \
    ../Multi-Calculator/src/dnum.cpp \
    ../Multi-Calculator/src/dnum_processor.cpp

HEADERS += \
    ../Multi-Calculator/src/dnum.h \
    ../Multi-Calculator/src/dnum_processor.h
