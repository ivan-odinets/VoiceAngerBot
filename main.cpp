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

#include <QCoreApplication>

#define APP_NAME                    "VoiceAngerBot"
#define APP_VERSION                 "1.0.0"

#include <cstdlib>
#include <time.h>

#include "CommandLineParser.h"
#include "ReactionSelector.h"
#include "VoiceAngerBot.h"

VoiceAngerBot*    bot = nullptr;

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(APP_VERSION);

    //Parse command line
    CommandLineParser parser;
    parser.process(app);

    if (parser.token().isEmpty()) {
        qCritical() << __FILE__ << ":" << __LINE__ << ". API Token must be specified.";
        return -1;
    }

    if (parser.reactionsFile().isEmpty()) {
        qCritical() << __FILE__ << ":" << __LINE__ << ". Reactions file must be specified.";
        return -1;
    }

    if (!ReactionSelector::get().phrasesLoaded(parser.reactionsFile())) {
        qCritical() << __FILE__ << ":" << __LINE__ << ". Error parsing reactions file.";
        return -1;
    }

    bot = new VoiceAngerBot;

    if (parser.botAdmin() == -1)
        qWarning() << __FILE__ << ":" << __LINE__ << ". Bot administrator is not set, so administration commands will not work!";
    else
        bot->setBotAdmin(parser.botAdmin());

    bot->setApiKey(parser.token());

    //Start Bot
    if (!bot->started()) {
        qCritical() << __FILE__ << ":" << __LINE__ << ". Can not start bot due to some errors.";
        return -1;
    }

    return app.exec();
}
