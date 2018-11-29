#include "postreq2.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QUrlQuery>

#include <QtNetwork/QNetworkAccessManager>

postReq2::postReq2()
{

    qDebug() << "Hej, I work :)";

    QUrl serviceUrl = QUrl("http://payment-app-mrl.herokuapp.com/post");
    QNetworkRequest networkRequest(serviceUrl);

    QJsonObject json;
    json.insert("name", "<script>alert('fuckoff')</script>");
    json.insert("text", "HULLO");
    QJsonDocument jsonDoc(json);
    QByteArray postData = jsonDoc.toJson();

//    QByteArray postData = "{\"name\": \"Jack\", \"text\": \"HULLO\"}";
    QByteArray postDataSize = QByteArray::number(postData.size());
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader, postDataSize);

    QNetworkAccessManager *networkManager = new QNetworkAccessManager();
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(serviceRequestFinish(QNetworkReply*)));

    networkManager->post(networkRequest, postData);

    QNetworkReply *reply = networkManager->post(networkRequest, postData);

//    curl -X POST -d "{\"name\": \"Jack\", \"text\": \"HULLO\"}" -H "Content-Type: application/json" localhost:3000/post

//    while(!reply->isFinished()){
//    }


//    QUrl params;
//    QUrlQuery query;
//    query.addQueryItem("name","string1");
//    query.addQueryItem("text","string2");

//    params.setQuery(query);

//    postData = params.toEncoded(QUrl::RemoveFragment);

    // Call the webservice



//    networkRequest.setRawHeader("User-Agent", "My app name v0.1");
//    networkRequest.setRawHeader("X-Custom-User-Agent", "My app name v0.1");

//    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");



}

void postReq2::serviceRequestFinish(QNetworkReply* rep) {
    qDebug() << "POST REQUEST SENT";
    qDebug() << rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Reply from server: " << rep->readAll();
}
