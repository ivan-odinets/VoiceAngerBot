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

#include "Database.h"

#include <QDebug>
#include <QDateTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql>

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool Database::databaseInitialized()
{
    if (!db.open()) {
        qCritical() << "Error in initializing database - "<<db.lastError();
        return false;
    }

    return true;
}

/*
 *********************************************************************************************************************
 *
 * Retrieving & updating chats information (tables)
 *
 */

bool Database::chatRegistered(qint64 chatId)
{
    return db.tables().contains( QString::number(chatId) );
}

void Database::addChat(qint64 chatId)
{
    if (Q_UNLIKELY(chatRegistered(chatId))) {
        qInfo() << "This should have not happened. Probably database needs to be rechecked. chat_id="<<chatId;
        return;
    }

    QString queryText = QString("CREATE TABLE \"%1\" (\"user_id\" INTEGER, \"score\" INTEGER, \"in_game\" INTEGER, \"last_rolled\" INTEGER)")
            .arg(chatId);
    QSqlQuery query;

    if (Q_UNLIKELY(!query.exec(queryText))) {
        qWarning() << "SQL error: "<<query.lastError();
        return;
    }

}

void Database::removeChat(qint64 chatId)
{
    QSqlQuery query;
    QString queryText = QString("DROP TABLE \"%1\"")
            .arg(chatId);

    if (Q_UNLIKELY(!query.exec(queryText))) {
        qWarning() << "SQL error: "<<query.lastError();
        return;
    }
}

QList<qint64> Database::getAllChats() const
{
    QList<qint64> result;

    foreach (QString tableName,db.tables()) {
        qint64 chatId = tableName.toLongLong();
        if (chatId != 0)
            result.append(chatId);
    }

    return result;
}
