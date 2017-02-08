#-------------------------------------------------
#
# Project created by QtCreator 2017-02-07T08:31:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


HEADERS  += \
    headers/forms/LoginForm.h\
    headers/models/User.h\
    headers/tools/cJSON.h\
    headers/ui/ui_loginform.h

SOURCES +=  main.cpp\
    sources/forms/LoginForm.cpp\
    sources/models/User.cpp\
    sources/tools/cJSON.c





CONFIG +=C++11

QT+=sql

QT += core

FORMS += ui/loginform.ui

