#-------------------------------------------------
#
# Project created by QtCreator 2016-09-26T20:03:33
#
#-------------------------------------------------

QT       += core gui

CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = compiler
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
        lexical.cpp \
    errorlog.cpp \
    token.cpp \
    symbol.cpp

HEADERS  += mainwindow.h \
lexical.h \
    errorlog.h \
    token.h \
    symbol.h


FORMS    += mainwindow.ui
