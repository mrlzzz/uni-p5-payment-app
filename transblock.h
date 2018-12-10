#ifndef TRANSBLOCK_H
#define TRANSBLOCK_H

#include <QDate>
#include <QObject>
#include <QString>
#include <QByteArray>



class TransBlock : public QObject
{
    QString timestamp;
    int amount;
    QString currency;
    QString terminalID;
    QString PAN;
    QString PIN;

public:
    TransBlock();
    void setTimestamp(QString);
    void setAmount(int);
    void setCurrency(QString);
    void setTerminalID(QString);
    void setPAN(QString);
    void setPIN(QString);

    QString getTimestamp();
    int getAmount();
    QString getCurrency();
    QString getTerminalID();
    QString getPAN();
    QString getPIN();

};

#endif // TRANSBLOCK_H
