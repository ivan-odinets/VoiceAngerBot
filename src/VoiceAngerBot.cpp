/*
 **********************************************************************************************************************
 *
 * MIT License
 * Copyright (c) 2021 Ivan Odinets
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "VoiceAngerBot.h"

#include "ReactionSelector.h"

VoiceAngerBot::VoiceAngerBot(QObject* parent)
    : QObject(parent),p_botApi(nullptr)
{
    m_adminCommands.append(&m_addGlobalCmd);
    m_adminCommands.append(&m_addVideoReactionCmd);
    m_adminCommands.append(&m_addVoiceReactionCmd);
    m_adminCommands.append(&m_statistic);
}
VoiceAngerBot::~VoiceAngerBot()
{}

bool VoiceAngerBot::started()
{
    p_botApi = new Telegram::Bot(m_botApiKey,true,1000);
    connect(p_botApi,&Telegram::Bot::message,this,&VoiceAngerBot::messageRecieved);

    m_botUser = p_botApi->getMe();
    qInfo() << "Staring process using API key for following bot: "<<m_botUser;

    BotAdminCommand::setTelegramApi(p_botApi);

    return true;
}

void VoiceAngerBot::setProxy(const QNetworkProxy& proxy)
{
    if (p_botApi != nullptr)
        p_botApi->setProxy(proxy);
}

void VoiceAngerBot::messageRecieved(const Telegram::Message& message)
{
    m_statistic.increaseMessagesHandled();
    if (message.type == Telegram::Message::VoiceType) {
        handleVoiceMessage(message);
        return;
    }

    if (message.type == Telegram::Message::VideoNoteType) {
        handleVideoMessage(message);
        return;
    }

    if ((message.from.id == message.chat.id) &&
        (message.from.id == m_botAdmin)) {
        parseAdminCommand(message);
        return;
    }
}

void VoiceAngerBot::handleVideoMessage(const Telegram::Message& message)
{
    m_statistic.increaseVideoMessagesHandled();
    _sendReply(ReactionSelector::get().getRandomVideoReaction(),message);
}

void VoiceAngerBot::handleVoiceMessage(const Telegram::Message& message)
{
    m_statistic.increaseVoiceMessagesHandled();
    _sendReply(ReactionSelector::get().getRandomVoiceReaction(),message);
}

void VoiceAngerBot::_sendReply(const QString &text, const Telegram::Message &message)
{
    p_botApi->sendChatAction(message.chat.id,Telegram::Bot::Typing);
    p_botApi->sendMessage(message.chat.id,text,message.id);
}

void VoiceAngerBot::parseAdminCommand(const Telegram::Message& message)
{
    foreach (BotAdminCommand* cmd,m_adminCommands) {
        if (message.string.startsWith(cmd->cmdToken())) {
            cmd->executeCommand(message);
            return;
        }
    }
}
