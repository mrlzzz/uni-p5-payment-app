#include "transblock.h"
#include <QDate>


TransBlock::TransBlock() {

}

void TransBlock::setTimestamp(QString ts){
    timestamp = ts;
}
void TransBlock::setAmount(int a){
    amount = a;
}
void TransBlock::setCurrency(QString c){
    currency = c;
}
void TransBlock::setTerminalID(QString t){
    terminalID = t;
}
void TransBlock::setPAN(QString p){
    PAN = p;
}
void TransBlock::setPIN(QString p1){
    PIN = p1;
}

QString TransBlock::getTimestamp(){
    return timestamp;
}
int TransBlock::getAmount(){
    return amount;
}
QString TransBlock::getCurrency(){
    return currency;
}
QString TransBlock::getTerminalID(){
    return terminalID;
}
QString TransBlock::getPAN1(){


    return "5270-****-****-7748";
}
QString TransBlock::getPAN(){


    return PAN;
}
QString TransBlock::getPIN(){
    return PIN;
}



