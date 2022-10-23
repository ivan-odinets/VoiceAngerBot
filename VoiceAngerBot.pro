SUBDIRS += src/VoiceAngerBot.pro

TEMPLATE = subdirs
CONFIG += ordered warn_on qt debug_and_release 

DISTFILES += README.md \
    debian/voice-anger-bot.service \
    debian/voice-anger-bot.conf
