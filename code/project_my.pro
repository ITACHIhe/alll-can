#-------------------------------------------------
#
# Project created by QtCreator 2019-07-19T10:30:21
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project_my
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


SOURCES += \
        main.cpp \
        widget.cpp \
    main_func.cpp \
    set_btm.cpp \
    chat.cpp \
    file_shared.cpp \
    tcp_send_file.cpp \
    tcp_re_file.cpp

HEADERS += \
        widget.h \
    main_func.h \
    set_btm.h \
    chat.h \
    file_shared.h \
    tcp_send_file.h \
    tcp_re_file.h

FORMS += \
        widget.ui \
    main_func.ui \
    set_btm.ui \
    chat.ui \
    file_shared.ui \
    tcp_send_file.ui \
    tcp_re_file.ui
