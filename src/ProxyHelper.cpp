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

#include "ProxyHelper.h"

bool ProxyHelper::isValidProxy(const QString& input)
{
    static QRegExp proxyPattern("^(http|socks5)://.*:([0-6]\\d\\d\\d\\d|\\d\\d\\d\\d)$");
    return proxyPattern.exactMatch(input);
}

QNetworkProxy ProxyHelper::proxyFromString(QString inputString)
{
    QNetworkProxy result;

    if (inputString.isEmpty()) {
        result.setType(QNetworkProxy::NoProxy);
        return result;
    }

    //Get proxy type
    QRegExp protocolRegExp("^.*(?=://)");
    if (protocolRegExp.indexIn(inputString) < 0) { //No protocol specified
        qWarning() << tr("Error parsing proxy protocol!");
        return QNetworkProxy();
    }
    QString protocol = protocolRegExp.cap(0);
    if (protocol == QStringLiteral("http")) {
        result.setType(QNetworkProxy::HttpProxy);
        inputString.remove(QRegExp("^http://"));
    } else if (protocol == QStringLiteral("socks5")) {
        result.setType(QNetworkProxy::Socks5Proxy);
        inputString.remove(QRegExp("^socks5://"));
    } else {
        qWarning() << tr("Unknown proxy protocol %1. Disabling proxy.").arg(protocol);
        return QNetworkProxy();
    }

    //Get proxy server
    QRegExp hostNameRegExp("^.*(?=:)");
    if (hostNameRegExp.indexIn(inputString) < 0) {
        //Probably some syntax error, return sth
        qWarning() << "Error parsing proxy host. Disabling proxy...";
        return QNetworkProxy();
    }

    result.setHostName(hostNameRegExp.cap(0));
    inputString.remove(hostNameRegExp);
    if (!inputString.startsWith(":")) {
        //Probably no port specified, return sth
        qWarning() << "Error parsing proxy port. Disabling proxy...";
        return QNetworkProxy();
    }

    inputString.remove(QRegExp("^:"));
    bool ok = false;
    qint32 proxyPort = inputString.toInt(&ok);
    if (!ok) {
        //Error in port input
        qWarning() << "Another error parsing proxy port. Disabling proxy...";
        return QNetworkProxy();
    }

    result.setPort(proxyPort);

    return result;
}

QString ProxyHelper::stringFromProxy(const QNetworkProxy& proxy)
{
    QString proxyType;
    switch (proxy.type()) {
    case QNetworkProxy::HttpProxy:
    case QNetworkProxy::HttpCachingProxy:
        proxyType = "http";
        break;
    case QNetworkProxy::Socks5Proxy:
        proxyType = "socks5";
        break;
    case QNetworkProxy::DefaultProxy:
    case QNetworkProxy::FtpCachingProxy:
    case QNetworkProxy::NoProxy:
        return QString();
    }

    return QString("%1://%2:%3")
            .arg(proxyType)
            .arg(proxy.hostName())
            .arg(proxy.port());
}
