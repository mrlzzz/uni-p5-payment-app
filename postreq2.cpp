#include "postreq2.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QUrlQuery>

#include <QtNetwork/QNetworkAccessManager>

PostRequest::PostRequest()
{

    qDebug() << "Hej, I work :)";

    //Set up HTTP POST request destination

    QUrl serviceUrl = QUrl("https://payment-app-mrl.herokuapp.com/post");
    QNetworkRequest networkRequest(serviceUrl);

    //Set up data to send

    QJsonObject json;
    json.insert("name", "PSSSSSS be invisible in wireshark :)");
    json.insert("text", "Plz be invisible in wireshark :)");
    QJsonDocument jsonDoc(json);
    QByteArray postData = jsonDoc.toJson();

    //HTTP POST Headers

    QByteArray postDataSize = QByteArray::number(postData.size());
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader, postDataSize);

    //HTTPS Config

//    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
//    config.setProtocol(QSsl::TlsV1_2);
//    networkRequest.setSslConfiguration(config);

    //NAM and slots (SLOT will run when connection is done, has to be defined)

    QNetworkAccessManager *networkManager = new QNetworkAccessManager();
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(serviceRequestFinish(QNetworkReply*)));

    //Send POST request

    networkManager->post(networkRequest, postData);

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

void PostRequest::serviceRequestFinish(QNetworkReply* rep) {
    qDebug() << "POST REQUEST SENT";
    qDebug() << rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Reply from server: " << rep->readAll();
}
