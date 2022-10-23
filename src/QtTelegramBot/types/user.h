#ifndef USER_H
#define USER_H

#include <QDebug>
#include <QString>
#include <QJsonObject>

namespace Telegram {

class User
{
public:
    typedef qint64 Id;

    User() : id(0), firstname(QString()), lastname(QString()), username(QString()) {}
    User(const QJsonObject& user);

    Id id;
    QString firstname;
    QString lastname;
    QString username;
    bool is_bot;
};

inline QDebug operator<< (QDebug dbg, const User &user)
{
    dbg.nospace() << qUtf8Printable(QString("Telegram::User(id=%1; firstname=%2; lastname=%3; username=%4)")
                     .arg(user.id)
                     .arg(user.firstname)
                     .arg(user.lastname)
                     .arg(user.username));

    return dbg.maybeSpace();
}

}

#endif // USER_H
