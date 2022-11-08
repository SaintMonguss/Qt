#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(replyFinished(QNetworkReply*)));

    manager -> get(QNetworkRequest(QUrl("http://www.google.com")));
}

void Downloader::replyFinished(QNetworkReply *reply)
{
    if(reply -> error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply -> errorString();
    } else
    {
        qDebug() << reply -> header(QNetworkRequest::ContentTypeHeader).toS
    }
}
