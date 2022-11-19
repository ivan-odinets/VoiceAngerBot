/*
 **********************************************************************************************************************
 *
 * MIT License
 * Copyright (c) 2022 Ivan Odinets
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

#ifndef STATSCMD_H
#define STATSCMD_H

#include "BotAdminCommand.h"

class StatsCmd : public BotAdminCommand
{
public:
    StatsCmd();
    QString cmdToken() const override                      { return QStringLiteral("/stats"); }
    void executeCommand(const Telegram::Message& message) override;

    void increaseMessagesHandled()                         { m_messagesHandled++; }
    void increaseVoiceMessagesHandled()                    { m_voiceMessagesHandled++; }
    void increaseVideoMessagesHandled()                    { m_videoMessagesHandled++; }

private:
    QDateTime        m_startingDateTime;
    quint64          m_messagesHandled;
    quint64          m_voiceMessagesHandled;
    quint64          m_videoMessagesHandled;
};

#endif // STATSCMD_H
