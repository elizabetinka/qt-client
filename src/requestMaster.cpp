#include "requestMaster.h"

RequestMaster::RequestMaster()
{}

void RequestMaster::onProcessRequest(QUrl url,QString requestType, const QByteArray& data)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    reply.reset(); // предыдущий мог стать невалидным
    manager.reset(new QNetworkAccessManager());

    if (requestType == "get") {
        reply.reset(manager->get(request, data));
    }
    else if (requestType == "post"){
        reply.reset(manager->post(request, data));
    }
    else if (requestType == "put"){
        reply.reset(manager->put(request, data));
    }
    else if (requestType == "delete"){
        reply.reset(manager->sendCustomRequest(request,"DELETE", data));
    }

    timer = new QTimer(this);
    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout,this,&RequestMaster::timeout);

    timer->start(5000);

    connect(reply.get(), &QIODevice::readyRead, this, &RequestMaster::httpReadyRead);
    connect(reply.get(), &QNetworkReply::finished, this, &RequestMaster::httpFinished);
}

void RequestMaster::httpReadyRead()
{
    timer->stop();
    emit gotHttpData(reply->readAll());
}