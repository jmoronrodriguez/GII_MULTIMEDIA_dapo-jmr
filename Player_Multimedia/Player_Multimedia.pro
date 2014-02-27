#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T21:52:41
#
#-------------------------------------------------

QT += multimedia \
      multimediawidgets \
      widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += multimedia \
      multimediawidgets \
      widgets

TARGET = Player_Multimedia
TEMPLATE = app


SOURCES += main.cpp\
        ventanaprincipal.cpp \
    lista.cpp

HEADERS  += ventanaprincipal.h \
    lista.h

FORMS    += ventanaprincipal.ui \
    lista.ui

