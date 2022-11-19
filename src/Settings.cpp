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

#include "Settings.h"

#include <QDebug>
#include <QFile>
#include <QSettings>

#include "ProxyHelper.h"

#define BOT_TOKEN       QStringLiteral("token")
#define BOT_ADMIN       QStringLiteral("admin")

#define DATABASE_FILE   QStringLiteral("database")
#define REACTIONS_FILE  QStringLiteral("strings")

#define PROXY           QStringLiteral("proxy")

Settings::Settings(const QString& fileName) :
    p_settings(nullptr)
{
    p_settings = (fileName.isEmpty()) ? new QSettings
            : new QSettings(fileName,QSettings::IniFormat);

    qDebug() << "Using settings file "<<p_settings->fileName();
}

Settings::~Settings()
{
    p_settings->sync();
    delete p_settings;
}

QSettings::Status Settings::status() const
{
    return p_settings->status();
}

QString Settings::token() const
{
    return p_settings->value(BOT_TOKEN).toString();
}

void Settings::setToken(const QString& newToken)
{
    p_settings->setValue(BOT_TOKEN,newToken);
}

Telegram::User::Id Settings::botAdmin() const
{
    return p_settings->value(BOT_ADMIN).toString().toDouble();
}

void Settings::setBotAdmin(Telegram::User::Id newAdminId)
{
    p_settings->setValue(BOT_ADMIN,newAdminId);
}

QString Settings::databaseFile() const
{
    return p_settings->value(DATABASE_FILE).toString();
}

void Settings::setDatabaseFile(const QString& newFileName)
{
    p_settings->setValue(DATABASE_FILE,newFileName);
}

QString Settings::reactionsFile() const
{
    return p_settings->value(REACTIONS_FILE).toString();
}

void Settings::setReactionsFile(const QString& newFileName)
{
    p_settings->setValue(REACTIONS_FILE,newFileName);
}

bool Settings::validProxyConfigured() const
{
    return ProxyHelper::isValidProxy(p_settings->value(PROXY).toString());
}

QNetworkProxy Settings::proxy() const
{
    return ProxyHelper::proxyFromString(p_settings->value(PROXY).toString());
}

void Settings::setProxyString(const QString& proxyString)
{
    p_settings->setValue(PROXY,proxyString);
}

void Settings::setProxy(const QNetworkProxy& proxy)
{
    p_settings->setValue(PROXY,ProxyHelper::stringFromProxy(proxy));
}
