#ifndef POSTREQ2_H
#define POSTREQ2_H

#include <QNetworkReply>
#include <QObject>



class PostRequest : public QObject {
    Q_OBJECT
public:
    PostRequest();
public slots:
    void serviceRequestFinish(QNetworkReply*);
};

#endif // POSTREQ2_H
