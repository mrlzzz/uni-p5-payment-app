#ifndef POSTREQ2_H
#define POSTREQ2_H

#include <QNetworkReply>
#include <QObject>
#include "transblock.h"




class PostRequest : public QObject {
    Q_OBJECT
public:
    PostRequest(int, QString, QString, QString, QString);
public slots:
    void serviceRequestFinish(QNetworkReply*);
};

#endif // POSTREQ2_H
