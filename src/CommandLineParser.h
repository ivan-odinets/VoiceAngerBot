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

#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QCommandLineParser>

#include "QtTelegramBot/src/types/user.h"

#include "ProxyHelper.h"

class CommandLineParser : public QCommandLineParser
{
    Q_DECLARE_TR_FUNCTIONS(CommandLineParser);
public:
    CommandLineParser();
    ~CommandLineParser() {}

    QString configFile() const                 { return value(m_configFileOption); }

    bool validProxyConfigured() const          { return ProxyHelper::isValidProxy(proxyString()); }
    QNetworkProxy proxy() const                { return ProxyHelper::proxyFromString(proxyString()); }
    QString proxyString() const                { return value(m_networkProxy); }

    QString token() const                      { return value(m_botTokenOption); }
    QString reactionsFile() const              { return value(m_reactionMessagesFileOption); }

    Telegram::User::Id botAdmin()              { return value(m_botAdminOption).toLongLong(); }

    QString dbFile() const                     { return value(m_dbFileOption); }

private:
    QCommandLineOption   m_configFileOption;
    QCommandLineOption   m_botTokenOption;
    QCommandLineOption   m_reactionMessagesFileOption;
    QCommandLineOption   m_botAdminOption;
    QCommandLineOption   m_dbFileOption;
    QCommandLineOption   m_networkProxy;

};

#endif // COMMANDLINEPARSER_H
