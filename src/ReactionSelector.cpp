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

#include "ReactionSelector.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

#define VOICE_PREFIX   "voice:"
#define VIDEO_PREFIX   "video:"
#define ALL_PREFIX     "all:"

bool ReactionSelector::phrasesLoaded(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << __FILE__ << ":" << __LINE__ << ". Error loading phrases file "<<fileName<<". Error: "<<file.errorString();
        return false;
    }

    m_fileName = fileName;

    if (file.size() == 0) {
        qCritical() << __FILE__ << ":" << __LINE__ << ". Phrases file "<<fileName<<" is empty.";
        file.close();
        return false;
    }

    //Read everything
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("#") || line.isEmpty())  //Ignore comments & empty lines
            continue;

        if (line.startsWith(VOICE_PREFIX)) {         //This is reaction on voice message
            line.remove(VOICE_PREFIX);
            m_voiceReactions.append(line);
        } else if (line.startsWith(VIDEO_PREFIX)) {  //This is reaction on video message
            line.remove(VIDEO_PREFIX);
            m_videoReactions.append(line);
        } else if (line.startsWith(ALL_PREFIX)) {    //This is reaction on everything
            line.remove(ALL_PREFIX);
            m_voiceReactions.append(line);
            m_videoReactions.append(line);
        } else {                                     //Wrong syntax? Ignore.
            qWarning() << "Syntax error in file: "<<fileName<<". Line: "<<line;
        }
    }

    file.close();

    return true;
}

void ReactionSelector::addGlobalReaction(QString text)
{
    m_voiceReactions.append(text);
    m_videoReactions.append(text);

    text = ALL_PREFIX + text;
    _appentLineToFile(text);
}

void ReactionSelector::addVoiceReaction(QString text)
{
    m_voiceReactions.append(text);

    text = VOICE_PREFIX + text;
    _appentLineToFile(text);
}

void ReactionSelector::addVideoReaction(QString text)
{
    m_videoReactions.append(text);

    text = VIDEO_PREFIX + text;
    _appentLineToFile(text);
}

void ReactionSelector::_appentLineToFile(const QString& line)
{
    QFile file(m_fileName);

    if (!file.open(QIODevice::WriteOnly|QIODevice::Append)) {
        qWarning() << __FILE__ <<":"<<__LINE__<<". Error opening "<<m_fileName<<" for writing. Error: "<<file.errorString();
        return;
    }

    QTextStream out(&file);
    out << line << Qt::endl;

    file.close();
    return;
}

QString ReactionSelector::getRandomVoiceReaction()
{
    return _getRandomString(m_voiceReactions);
}

QString ReactionSelector::getRandomVideoReaction()
{
    return _getRandomString(m_videoReactions);
}

QString ReactionSelector::_getRandomString(const QStringList &list)
{
    return list.at(std::rand() % list.count());
}
