QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_t_pnum_processor.cpp \
    ../Multi-Calculator/src/pnum.cpp \
    ../Multi-Calculator/src/pnum_converter.cpp \
    ../Multi-Calculator/src/pnum_processor.cpp

HEADERS += \
    ../Multi-Calculator/src/pnum.h \
    ../Multi-Calculator/src/pnum_converter.h \
    ../Multi-Calculator/src/pnum_processor.h
