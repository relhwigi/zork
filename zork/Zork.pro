TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    character.cpp \
    characterdeathlistener.cpp \
    defeatlistener.cpp \
    enterroomlistener.cpp \
    eventmanager.cpp \
    exitlistener.cpp \
    game.cpp \
    golistener.cpp \
    infolistener.cpp \
    inputlistener.cpp \
    main.cpp \
    maplistener.cpp \
    restartlistener.cpp \
    room.cpp \
    teleportlistener.cpp \
    victorylistener.cpp \
    item.cpp

DISTFILES += \
    main.txt

HEADERS += \
    character.h \
    characterdeathlistener.h \
    defeatlistener.h \
    enterroomlistener.h \
    eventlistener.h \
    eventmanager.h \
    exitlistener.h \
    game.h \
    golistener.h \
    infolistener.h \
    inputlistener.h \
    maplistener.h \
    restartlistener.h \
    room.h \
    teleportlistener.h \
    victorylistener.h \
    item.h
