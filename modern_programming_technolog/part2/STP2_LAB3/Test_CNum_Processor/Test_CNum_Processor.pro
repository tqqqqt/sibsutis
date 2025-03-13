QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_t_cnum_processor.cpp \
    ../Multi-Calculator/src/cnum.cpp \
    ../Multi-Calculator/src/cnum_processor.cpp

HEADERS += \
    ../Multi-Calculator/src/cnum.h \
    ../Multi-Calculator/src/cnum_processor.h
