#-------------------------------------------------
#
# Project created by QtCreator 2013-10-16T09:52:16
#
#-------------------------------------------------

QT       += core gui multimedia

QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = player-flat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spectrograph.cpp \
    fft.cpp \
    controls.cpp \
    fftcalc.cpp \
    mediainfo.cpp \
    playlistmodel.cpp
 
HEADERS  += mainwindow.h \
    spectrograph.h \
    fft.h \
    controls.h \
    fftcalc.h \
    mediainfo.h \
    abstractcontrol.h \
    abstractspectrograph.h \
    abstractmediainfo.h \
    playlistmodel.h
   fft.h

FORMS    += mainwindow.ui \
    controls.ui \
    mediainfo.ui

RESOURCES += \
    resources.qrc
