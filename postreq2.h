#ifndef POSTREQ2_H
#define POSTREQ2_H

#include <QNetworkReply>
#include <QObject>



class postReq2 : public QObject {
    Q_OBJECT
public:
    postReq2();
public slots:
    void serviceRequestFinish(QNetworkReply*);
};

#endif // POSTREQ2_H
