#include "video_note.h"

using namespace Telegram;

VideoNote::VideoNote(const QJsonObject& voice)
{
    fileId = voice.value("file_id").toString();
    duration = voice.value("duration").toInt();
    fileSize = voice.value("file_size").toInt();
}
