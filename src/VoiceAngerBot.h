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

#ifndef VOICEANGERBOT_H
#define VOICEANGERBOT_H

#include "qttelegrambot.h"

#include "admin_commands/AddGlobalReaction.h"
#include "admin_commands/AddVideoReaction.h"
#include "admin_commands/AddVoiceReaction.h"
#include "admin_commands/BackupDbCommand.h"
#include "admin_commands/SendGlobalMessage.h"
#include "admin_commands/StatsCmd.h"
#include "admin_commands/VersionCmd.h"

class Database;

class VoiceAngerBot : public QObject
{
    Q_OBJECT
public:
    explicit VoiceAngerBot(QObject* parent = nullptr);
    ~VoiceAngerBot();

    bool started();
    void setApiKey(const QString& key)                     { m_botApiKey = key; }
    void setDatabase(Database* newDb);
    void setBotAdmin(qint32 userId)                        { m_botAdmin = userId; }
    void setProxy(const QNetworkProxy& proxy);

public slots:
    void messageRecieved(const Telegram::Message& message);

    void parseAdminCommand(const Telegram::Message& message);

    void handleVoiceMessage(const Telegram::Message& message);
    void handleVideoMessage(const Telegram::Message& message);

    void handleNewChat(const Telegram::Message& message);
    void handleChatRemoval(const Telegram::Message& message);

private:
    Telegram::Bot*   p_botApi;
    Database*        p_db;
    Telegram::User   m_botUser;
    QString          m_botApiKey;

    void _sendReply(const QString& text,const Telegram::Message& message);

    qint32                    m_botAdmin;
    QList<BotAdminCommand*>   m_adminCommands;
    AddGlobalReaction         m_addGlobalCmd;
    AddVideoReaction          m_addVideoReactionCmd;
    AddVoiceReaction          m_addVoiceReactionCmd;
    BackupDbCommand           m_backupDbCmd;
    SendGlobalMessage         m_sendGlobalMessageCmd;
    StatsCmd                  m_statistic;
    VersionCmd                m_versionCmd;
};

#endif // VOICEANGERBOT_H
