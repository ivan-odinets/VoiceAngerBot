QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(./QtTelegramBot/QtTelegramBot.pri)

SOURCES += \
        CommandLineParser.cpp \
        ReactionSelector.cpp \
        VoiceAngerBot.cpp \
        admin_commands/AddGlobalReaction.cpp \
        admin_commands/AddVideoReaction.cpp \
        admin_commands/AddVoiceReaction.cpp \
        admin_commands/BotAdminCommand.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    CommandLineParser.h \
    ReactionSelector.h \
    VoiceAngerBot.h \
    admin_commands/AddGlobalReaction.h \
    admin_commands/AddVideoReaction.h \
    admin_commands/AddVoiceReaction.h \
    admin_commands/BotAdminCommand.h

DISTFILES += \
    README.md \
    reaction_messages/ua.txt
