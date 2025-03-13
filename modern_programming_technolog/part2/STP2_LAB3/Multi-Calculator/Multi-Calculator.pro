#-------------------------------------------------
#
# Project created by QtCreator 2025-02-27T14:53:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Multi-Calculator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        RefWindow/refwindow.cpp \
        main.cpp \
        mainwindow.cpp \
        src/cnum.cpp \
        src/cnum_processor.cpp \
        src/dnum.cpp \
        src/dnum_processor.cpp \
        src/memory.cpp \
        src/pnum.cpp \
        src/pnum_converter.cpp \
        src/pnum_processor.cpp

HEADERS += \
        RefWindow/refwindow.h \
        mainwindow.h \
        src/cnum.h \
        src/cnum_processor.h \
        src/dnum.h \
        src/dnum_processor.h \
        src/memory.h \
        src/num.h \
        src/pnum.h \
        src/pnum_converter.h \
        src/pnum_processor.h

FORMS += \
        RefWindow/refwindow.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
