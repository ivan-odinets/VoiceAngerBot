QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = voice-anger-bot

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = ../bin
MOC_DIR = ../build/moc
RCC_DIR = ../build/rcc
unix:OBJECTS_DIR = ../build/o/unix
win32:OBJECTS_DIR = ../build/o/win32
macx:OBJECTS_DIR = ../build/o/mac

include(./QtTelegramBot/QtTelegramBot.pri)

SOURCES += \
        CommandLineParser.cpp \
        ReactionSelector.cpp \
        VoiceAngerBot.cpp \
        admin_commands/AddGlobalReaction.cpp \
        admin_commands/AddVideoReaction.cpp \
        admin_commands/AddVoiceReaction.cpp \
        admin_commands/BotAdminCommand.cpp \
        admin_commands/StatsCmd.cpp \
        main.cpp

HEADERS += \
    CommandLineParser.h \
    ReactionSelector.h \
    VoiceAngerBot.h \
    admin_commands/AddGlobalReaction.h \
    admin_commands/AddVideoReaction.h \
    admin_commands/AddVoiceReaction.h \
    admin_commands/BotAdminCommand.h \
    admin_commands/StatsCmd.h

DISTFILES += \
    ../var/lib/telegram-bots/voice-anger-bot/reactions/ua.txt
