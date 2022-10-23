#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDebug>

#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QSharedPointer>

#include "audio.h"
#include "document.h"
#include "photosize.h"
#include "sticker.h"
#include "video.h"
#include "voice.h"
#include "video_note.h"
#include "contact.h"
#include "location.h"
#include "chat.h"
#include "user.h"

namespace Telegram {

class Message
{
public:
    Message() : id(0) {}
    Message(const QJsonObject& message);

    operator bool() const { return id == 0; }

    /**
     * @brief Telegram message events
     */
    enum MessageType {
        TextType, AudioType, DocumentType, PhotoType, StickerType, VideoType, VoiceType, VideoNoteType, ContactType,
        LocationType, NewChatParticipantType, LeftChatParticipantType, NewChatTitleType,
        NewChatPhotoType, DeleteChatPhotoType, GroupChatCreatedType
    };

    // required
    quint32 id;
    QDateTime date;
    Chat chat;

    // optional
    User from;
    User forwardFrom;
    QDateTime forwardDate;
    QSharedPointer<Message> replyToMessage;

    MessageType type;

    // payload
    QString string;
    User user;
    Audio audio;
    Document document;
    QList<PhotoSize> photo;
    Sticker sticker;
    Video video;
    Voice voice;
    VideoNote videoNote;
    Contact contact;
    Location location;
    bool boolean;
};

inline QDebug operator<< (QDebug dbg, const Message &message)
{
    dbg.nospace() << qUtf8Printable(QString("Telegram::Message(id=%1; date=%2; chat=%3; type=%4)")
                                    .arg(message.id)
                                    .arg(message.date.toString("dd.MM.yyyy hh:mm:ss"))
                                    .arg("Chat(" + QString::number(message.chat.id) + ")")
                                    .arg(message.type));

    return dbg.maybeSpace();
}

}

#endif // MESSAGE_H
