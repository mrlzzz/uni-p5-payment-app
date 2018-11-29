//#include "http.h"

//#include <QByteArray>
//#include <QUrl>

//#include <QtNetwork/QNetworkRequest>

//http::http()
//{

//    connect(m_qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleNetworkData(QNetworkReply*)));
//    connect(m_qnam,SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(handleSSLErrors(QNetworkReply*)));


//    // Build your JSON string as usual
//    QByteArray jsonString = "{\"method\":\"AuthenticatePlain\",\"loginName\":\"username@domain.com\",\"password\":\"mypass\"}";

//    // For your "Content-Length" header
//    QByteArray postDataSize = QByteArray::number(jsonString.size());

//    // Time for building your request
//    QUrl serviceURL("https://www.superService.com/api/1.7/ssapi.asmx");
//    QNetworkRequest request(serviceURL);

//    // Add the headers specifying their names and their values with the following method : void QNetworkRequest::setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);
//    request.setRawHeader("User-Agent", "My app name v0.1");
//    request.setRawHeader("X-Custom-User-Agent", "My app name v0.1");
//    request.setRawHeader("Content-Type", "application/json");
//    request.setRawHeader("Content-Length", postDataSize);

//    // Use QNetworkReply * QNetworkAccessManager::post(const QNetworkRequest & request, const QByteArray & data); to send your request. Qt will rearrange everything correctly.
//    QNetworkReply * reply = m_qnam->post(request, jsonString);



//}
