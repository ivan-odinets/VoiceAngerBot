#  Description

This bot is a modified copy of russian-speaking bot (Звукозавр - [@zvukozavrbot](t.me/zvukozavrbot)). After  addition  to  the  group  chat  bot  will  aggressively  react  on  all  voice  and  video  messages.

Working Ukranian-speaking version of this bot - [@zlyukobeaver_bot](t.me/zlyukobeaver_bot).

##  Compiling  and  building

For  Debian:
```
sudo  apt-get  install  qtbase5-dev  qtbase5-dev-tools  qt5-qmake  libqt5core5a  libqt5network5
debuild  -b  -uc  -us
```
For  other  Linux  systems:
```bash
qmake
make
./bin/voice-anger-bot  --help
```

##  Configuration  &  Usage

Configuration for this bot can be done either using config file ( /etc/telegram-bots/voice-anger-bot.conf, if using systemd voice-anger-bot.service file provided. Or required parameters can be specified using command line. 

Required parameters - telegram bot api token (check instructions [here](https://core.telegram.org/bots#6-botfather)) and propper reaction file. By default bot will use file reactions in ukranian language.

Available  commands  for  bot  administrator:

- /addVideoReaction - add reaction on video message
- /addVoiceReaction - add reaction on voice message
- /addGlobalReaction - add reaction on both voice and video messages
- /stats - show some simple statistic (amount of messages parsed, their type)

##  Syntax  of  reaction  file
```
#This  is  a  comment
all:This  will  be  reaction  on  both  voice  and  video  message
voice:This  will  be  reaction  on  voice  message
video:This  will  be  reaction  on  video  message
```

Currently  in  this  repo  only  ukranian  reaction  file  is  present.

##  License

[MIT](https://choosealicense.com/licenses/mit/)
