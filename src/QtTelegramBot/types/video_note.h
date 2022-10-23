#ifndef VIDEONOTE_H
#define VIDEONOTE_H

#include <QDebug>
#include <QString>
#include <QJsonObject>

namespace Telegram {

class VideoNote
{
public:
    VideoNote() {}
    VideoNote(const QJsonObject& voice);

    QString fileId;
    quint64 duration;
    quint64 fileSize;
};

inline QDebug operator<< (QDebug dbg, const VideoNote &videoNote)
{
    dbg.nospace() << qUtf8Printable(QString("Telegram::VideoNote(fileId=%1; duration=%2; fileSize=%3)")
                                    .arg(videoNote.fileId)
                                    .arg(videoNote.duration)
                                    .arg(videoNote.fileSize));

    return dbg.maybeSpace();
}

}

#endif // VIDEONOTE_H
