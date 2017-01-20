#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T16:24:27
#
#-------------------------------------------------

QT       += core gui xml multimedia
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projects
TEMPLATE = app

SOURCES += main.cpp\
    spaceboard.cpp \
    player.cpp \
    bullets/bullet.cpp \
    bullets/bulletenemy.cpp \
    bullets/bulletplayer.cpp \
    enemies/enemy.cpp \
    enemies/enemypurple.cpp \
    enemies/enemyred.cpp \
    enemies/enemyyellow.cpp \
    xml/xmlreader.cpp \
    enemies/enemyrow.cpp \
    menuview.cpp \
    levelinfos/levelinfo.cpp \
    levelinfos/rowinfo.cpp \
    item.cpp \
    music/music.cpp \
    music/musicmenu.cpp \
    music/musicgame.cpp

HEADERS  += spaceboard.h \
    player.h \
    bullets/bullet.h \
    bullets/bulletenemy.h \
    bullets/bulletplayer.h \
    enemies/enemy.h \
    enemies/enemypurple.h \
    enemies/enemyred.h \
    enemies/enemyyellow.h \
    xml/xmlreader.h \
    enemies/enemyrow.h \
    menuview.h \
    levelinfos/levelinfo.h \
    levelinfos/rowinfo.h \
    item.h \
    music/music.h \
    music/musicmenu.h \
    music/musicgame.h


RESOURCES += \
    resources.qrc

DISTFILES += \
    levels.xml \
    image/background.png \
    son/Grandioso.mp3 \
    son/Majaise.mp3

FORMS += \
    menuview.ui
