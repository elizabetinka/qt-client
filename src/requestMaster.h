#pragma once

#include <QObject>
#include <QScopedPointer>
#include <QUrl>
#include <QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class RequestMaster : public QObject
{
    Q_OBJECT

public:
    RequestMaster();

Q_SIGNALS:
    void gotHttpData(const QByteArray& data);
    void httpFinished();
    void timeout();

public Q_SLOTS:

    virtual void onProcessRequest(QUrl url,QString requestType, const QByteArray& data);
    void httpReadyRead();

private:
    // чтобы продлить жизнь и использовать механизм управления жизнью parent-child
    QScopedPointer<QNetworkAccessManager, QScopedPointerDeleter<QNetworkAccessManager>> manager;
    QScopedPointer<QNetworkReply, QScopedPointerDeleter<QNetworkReply>> reply;
    QTimer* timer;
};