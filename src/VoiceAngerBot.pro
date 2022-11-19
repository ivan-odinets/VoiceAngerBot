QT -= gui
QT += sql network

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = voice-anger-bot

DEFINES += APP_NAME=\\\"VoiceAngerBot\\\"
DEFINES += APP_VERSION=\\\"1.2.0\\\"

DESTDIR = ../bin
MOC_DIR = ../build/moc
RCC_DIR = ../build/rcc
unix:OBJECTS_DIR = ../build/o/unix
win32:OBJECTS_DIR = ../build/o/win32
macx:OBJECTS_DIR = ../build/o/mac

include(./QtTelegramBot/QtTelegramBot.pri)

CONFIG(release, debug|release) : DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += \
        CommandLineParser.cpp \
        Database.cpp \
        ProxyHelper.cpp \
        ReactionSelector.cpp \
        Settings.cpp \
        VoiceAngerBot.cpp \
        admin_commands/AddGlobalReaction.cpp \
        admin_commands/AddVideoReaction.cpp \
        admin_commands/AddVoiceReaction.cpp \
        admin_commands/BackupDbCommand.cpp \
        admin_commands/BotAdminCommand.cpp \
        admin_commands/SendGlobalMessage.cpp \
        admin_commands/StatsCmd.cpp \
        admin_commands/VersionCmd.cpp \
        main.cpp

HEADERS += \
    CommandLineParser.h \
    Database.h \
    ProxyHelper.h \
    ReactionSelector.h \
    Settings.h \
    VoiceAngerBot.h \
    admin_commands/AddGlobalReaction.h \
    admin_commands/AddVideoReaction.h \
    admin_commands/AddVoiceReaction.h \
    admin_commands/BackupDbCommand.h \
    admin_commands/BotAdminCommand.h \
    admin_commands/SendGlobalMessage.h \
    admin_commands/StatsCmd.h \
    admin_commands/VersionCmd.h

DISTFILES += \
    ../var/lib/telegram-bots/voice-anger-bot/reactions/ua.txt
