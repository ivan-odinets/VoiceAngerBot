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

#ifndef BOTADMINCOMMAND_H
#define BOTADMINCOMMAND_H

#include "QtTelegramBot/src/types/message.h"

namespace Telegram
{
class Bot;
}

class Database;

class BotAdminCommand
{
public:
    static void setTelegramApi(Telegram::Bot* newApi)      { p_api = newApi; }
    static void setDatabase(Database* db)                  { p_db = db; }

    virtual QString cmdToken() const = 0;
    virtual void executeCommand(const Telegram::Message& message) = 0;

protected:
    static Telegram::Bot* getApi()                         { return p_api; }
    static Database* getDatabase()                         { return p_db; }
    static void _sendReply(const QString& reply,const Telegram::Message& message);

private:
    static Telegram::Bot* p_api;
    static Database*      p_db;
};

#endif // BOTADMINCOMMAND_H
