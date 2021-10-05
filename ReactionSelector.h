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

#ifndef REACTIONSELECTOR_H
#define REACTIONSELECTOR_H

#include <QStringList>

class ReactionSelector
{
public:
    static ReactionSelector& get() {
        static ReactionSelector theOne;
        return theOne;
    }

    bool phrasesLoaded(const QString& fileName);
    void addGlobalReaction(QString text);
    void addVoiceReaction(QString text);
    void addVideoReaction(QString text);

    QString getRandomVoiceReaction();
    QString getRandomVideoReaction();

private:
    ReactionSelector() {};
    Q_DISABLE_COPY_MOVE(ReactionSelector);

    QString _getRandomString(const QStringList &list);
    void _appentLineToFile(const QString& line);

    QStringList m_voiceReactions;
    QStringList m_videoReactions;

    QString m_fileName;
};

#endif // REACTIONSELECTOR_H
