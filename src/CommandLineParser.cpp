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

#include "CommandLineParser.h"

#include <QDir>

CommandLineParser::CommandLineParser() :
    m_configFileOption(QStringList()           << "c" << "config",    tr("Specify <config> file to use")),
    m_botTokenOption(QStringList()             << "t" << "token",     tr("Set bot token.")),
    m_reactionMessagesFileOption(QStringList() << "r" << "reactions", tr("Set reaction file.")),
    m_botAdminOption(QStringList()             << "a" << "admin",     tr("Set bot administrator userId.")),
    m_dbFileOption(QStringList()               << "d" << "database",  tr("main","Set database file.")),
    m_networkProxy(QStringList()               << "p" << "proxy",     tr("Specify <proxy> to use in following format http|socks5://<server>:<port>"),tr("proxy"))
{
    // -h/ --help
    addHelpOption();
    // -v/ --version
    addVersionOption();

    // -c/ --config
    m_configFileOption.setValueName("config");
    m_configFileOption.setDefaultValue(QString());
    addOption(m_configFileOption);

    // -t/ --token
    m_botTokenOption.setValueName("token");
    m_botTokenOption.setDefaultValue(QString());
    addOption(m_botTokenOption);

    // -r/ --reactions
    m_reactionMessagesFileOption.setValueName("reactions");
    m_reactionMessagesFileOption.setDefaultValue(QString());
    addOption(m_reactionMessagesFileOption);

    // -a/ --admin
    m_botAdminOption.setValueName("admin");
    m_botAdminOption.setDefaultValue("0");
    addOption(m_botAdminOption);

    // -d/ --database
    m_dbFileOption.setValueName("database");
    m_dbFileOption.setDefaultValue("");
    addOption(m_dbFileOption);

    // -p/ --proxy
    m_networkProxy.setValueName("proxy");
    m_networkProxy.setDefaultValue(QString());
    addOption(m_networkProxy);
}
