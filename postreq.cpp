//#include "postreq.h"

//#include <QUrl>

//#include <QtNetwork/QNetworkAccessManager>
//#include <QtNetwork/QNetworkRequest>

//postReq::postReq()
//{
//    QUrl url("http://www.payment-app-mrl.herokuapp.com");
//    QNetworkRequest request(url);

//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

//    connect(manager, SIGNAL(finished(QNetworkReply*)),
//            this, SLOT(syncRequestFinished(QNetworkReply*)));

//    QByteArray data = QJson::Json::serialize(collectSyncData());

//    // FIXME for debug
//    qDebug() << "Sync" << QString::fromUtf8(data.data(), data.size());

//    manager->post(request, data);


//}
