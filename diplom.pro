#-------------------------------------------------
#
# Project created by QtCreator 2017-04-10T15:23:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = diplom
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


SOURCES += main.cpp\
        mainwindow.cpp \
    output.cpp \
    song.cpp \
    note.cpp

HEADERS  += mainwindow.h \
    output.h \
    song.h \
    note.h

FORMS +=

DISTFILES += \
    accompaniment/bass.acc \
    accompaniment/dot.acc \
    accompaniment/simple.acc \
    accompaniment/standart.acc \
    lad/натуральные/2_дорийский.lad \
    lad/натуральные/3_фригийский.lad \
    lad/натуральные/4_лидийский.lad \
    lad/натуральные/5_миксолидийский.lad \
    lad/натуральные/7_локрийский.lad \
    lad/этнические/хирайоши.lad \
    lad/этнические/цыганский минор.lad \
    lad/major.lad \
    lad/гармонический минор.lad \
    lad/гармоничский мажор.lad \
    lad/мажор.lad \
    lad/мелодический минор.lad \
    lad/минор.lad \
    lad/натуральные/2_дорийский.lad \
    lad/натуральные/3_фригийский.lad \
    lad/натуральные/4_лидийский.lad \
    lad/натуральные/5_миксолидийский.lad \
    lad/натуральные/7_локрийский.lad \
    lad/этнические/хирайоши.lad \
    lad/этнические/цыганский минор.lad \
    lad/гармонический минор.lad \
    lad/гармоничский мажор.lad \
    lad/мажор.lad \
    lad/мелодический минор.lad \
    lad/минор.lad
