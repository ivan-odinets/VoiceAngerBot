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

#include "StatsCmd.h"

StatsCmd::StatsCmd() :
    m_startingDateTime(QDateTime::currentDateTimeUtc()),
    m_messagesHandled(0),
    m_voiceMessagesHandled(0),
    m_videoMessagesHandled(0)
{}

void StatsCmd::executeCommand(const Telegram::Message& message)
{
    QString result = QString(
                "Bot running since: %1\r\n"
                "Total messages processed: %2\r\n"
                "Voice messages processed: %3\r\n"
                "Video messages processed: %4")
            .arg(m_startingDateTime.toString())
            .arg(m_messagesHandled).arg(m_voiceMessagesHandled).arg(m_videoMessagesHandled);

    BotAdminCommand::_sendReply(result,message);
}
