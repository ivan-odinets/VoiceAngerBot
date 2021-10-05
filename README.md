# Description

This bot is a modified copy of russian-speaking bot (Звукозавр - [@zvukozavrbot](t.me/zvukozavrbot)).

After addition to the group chat bot will aggressively react on all voice and video messages 

# Compiling and usage

First of all - create bot in Telegram. Check telegram docs [here](https://core.telegram.org/bots#6-botfather).

```bash
qmake
make
./VoiceAngerBot -t API_TOKEN -r /path/to/reaction/file/ -a BOT_ADMIN_USERID
```
Reactions can be added by bot administrator using following commands:

- /addVideoReaction - add reaction on video message
- /addVoiceReaction - add reaction on voice message
- /addGlobalReaction - add reaction on both voice and video messages

### Syntax of reaction file
```
#This is a comment
all:This will be reaction on both voice and video message
voice:This will be reaction on voice message
video:This will be reaction on video message
```
Currently in this repo only ukranian reaction file is present (check reaction_messages folder).

Ukranian-speaking version of this bot - [@zlyukobeaver_bot](t.me/zlyukobeaver_bot).

## License
[MIT](https://choosealicense.com/licenses/mit/)
