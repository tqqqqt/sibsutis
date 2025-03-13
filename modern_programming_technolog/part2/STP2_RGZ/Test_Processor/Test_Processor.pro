QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_t_processor.cpp \
    ../P-Num_Calculator/src/converter.cpp \
    ../P-Num_Calculator/src/pnum.cpp \
    ../P-Num_Calculator/src/processor.cpp

HEADERS += \
    ../P-Num_Calculator/src/converter.h \
    ../P-Num_Calculator/src/pnum.h \
    ../P-Num_Calculator/src/processor.h
