#include "terminal.h"
#include "ui_terminal.h"
#include "transblock.h"
#include "postreq2.h"
#include "cipher.h"
#include <QDebug>
#include <QPushButton>
#include <QDate>
#include <QTime>
#include <QIntValidator>


Terminal::Terminal(QWidget *parent) : QMainWindow(parent), ui(new Ui::Terminal) {

    ui->setupUi(this);

    //Transportation Block created
    tBlock.setTerminalID("TERXXAA0001");

    //CREATE AND ASSIGN NUM BUTTONS

    QPushButton *numButtons[10];

    for(int i=0 ; i < 10 ; i++){
        QString butName = "Button" + QString::number(i);

        //Finding specific children of Widget by providing a name
        //Casting because of casting
        numButtons[i] = Terminal::findChild<QPushButton *>(butName);

        //Whenever button is released, call NumPressed();
        //connect usign SIGNAL, whevener button is released
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    //CREATE AND ASSIGN THE REST OF BUTTONS

    QPushButton *buttonClear = Terminal::findChild<QPushButton *>("ButtonClear");
    QPushButton *buttonConfirm = Terminal::findChild<QPushButton *>("ButtonConfirm");
    QPushButton *buttonInit = Terminal::findChild<QPushButton *>("ButtonInit");
    QPushButton *buttonCard = Terminal::findChild<QPushButton *>("ButtonCard");

    connect(buttonClear, SIGNAL(released()), this, SLOT(ClearPressed()));
    connect(buttonConfirm, SIGNAL(released()), this, SLOT(ConfirmPressed()));
    connect(buttonInit, SIGNAL(released()), this, SLOT(InitPressed()));
    connect(buttonCard, SIGNAL(released()), this, SLOT(CardPressed()));

    QLineEdit *displayAmount = Terminal::findChild<QLineEdit *>("DisplayMerchant");
    displayAmount->setValidator( new QIntValidator(0, 10000000, this) );
}

void Terminal::NumPressed() {

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if((displayVal + butVal).size() <= 4){
        ui->Display->setText(displayVal + butVal);
    }

}

void Terminal::ClearPressed() {
    ui->Display->setText("");
    ui->DisplayLog->appendPlainText("Clear button has been pressed.");
}

void Terminal::ConfirmPressed() {

    QDate date = date.currentDate();
    QTime time = time.currentTime();

    tBlock.setTimestamp(date.toString() + " " + time.toString());

    tBlock.setPIN(pinEncode(ui->Display->text()));

    ui->DisplayLog->appendPlainText("----TRANSACTION BODY----");
    ui->DisplayLog->appendPlainText("Timestamp: " + tBlock.getTimestamp());
    ui->DisplayLog->appendPlainText("Amount: " + QString::number(tBlock.getAmount()));
    ui->DisplayLog->appendPlainText("Currency: " + tBlock.getCurrency());
    ui->DisplayLog->appendPlainText("TerminalID: " + tBlock.getTerminalID());
    ui->DisplayLog->appendPlainText("PAN: " + tBlock.getPAN1());
    ui->DisplayLog->appendPlainText("----TRANSACTION SENT----");

    PostRequest *post = new PostRequest(tBlock.getAmount(), tBlock.getCurrency(), tBlock.getTerminalID(), tBlock.getPAN(), tBlock.getPIN());

}

void Terminal::InitPressed() {
    /*
        ### Hardcoded should be not. ###

        Later:

            Get amount and currency from merchant
            Currency should be represented by code
            Figure out terminal ID - rand number? any scheme to create?
            Get enc PIN from enc method

     */

    tBlock.setAmount(ui->DisplayMerchant->text().toInt());
    tBlock.setCurrency("DKK");
    tBlock.setPAN("5270820790587748");

    ui->DisplayAmount->appendPlainText(QString::number(tBlock.getAmount()) + " " + tBlock.getCurrency());
    ui->DisplayAmount->appendPlainText("Insert Card");
    ui->DisplayLog->appendPlainText("Transaction initialized.");
}

void Terminal::CardPressed() {
    ui->DisplayAmount->clear();
    ui->DisplayAmount->appendPlainText(QString::number(tBlock.getAmount()) + " " + tBlock.getCurrency());
    ui->DisplayAmount->appendPlainText("Insert PIN");
    ui->DisplayLog->appendPlainText("Card inserted: " + tBlock.getPAN());
    ui->DisplayLog->appendPlainText("Waiting for PIN...");
}

//void Terminal::createTransBlock() {



//    QDate timestamp = timestamp.currentDate();


//    transBlock tBlock = new transBlock();
//}

/*
    Transportation Block (TB)

    1. Timestamp       - QDATE Type
    2. Amount          - INT
    3. Amount exponent - ???
    4. Currency code   - INT
    5. Terminal ID     - STRING OR some QTYPE
    6. PAN             - QByteArray
    7. Encrypted PIN   - QByteArray
    8. Retail MAC      - ???

    ### Use terminalWrapper for Terminal logic - seperate GUI handling from logic ###
    ### When is it created? - After Confirm button click ###
    ### Before Confirm button click, check fields are correct ###
  */

QString Terminal::testAES(QByteArray plain){
    qDebug() << "Testing AES...";

    Cipher cWrapper;

    QString passphrase = "secret";
    QByteArray encrypted = cWrapper.encryptAES(passphrase.toLatin1(), plain);
    QByteArray decrypted = cWrapper.decryptAES(passphrase.toLatin1(), encrypted);

    qDebug() << "Plain: " << plain;
    qDebug() << "Encrypted: " << encrypted.toHex();
    qDebug() << "Decrypted: " << decrypted;

    return encrypted.toHex();
}

QString Terminal::pinEncode(QString ppin) {
    /*
        1. Grab PIN from input.
        2. Encode each digit to binary (nibbles - four bits format)
        3. Put into xorPIN format

        ## xorPIN is 64bit number used to encode PIN block
        ## xorPIN is used to be xored with xorPAN
        ##
        ## xorPIN = | 0000 | 0100 | XXXX | XXXX | XXXX | XXXX | 1111 | ...
        ##
        ## Format 0 | num of PIN digits | PIN digit 1 | PIN digit 2 | PIN digit 3 | PIN digit 4 | fill 1s x10 | ...
    */

    QString pinNumber = ppin;

    qDebug() << "PIN before encoding: " << pinNumber;

    QByteArray xorPIN;
    xorPIN.append("00000100");
    QString pinDigit;

    for(int i = 0 ; i < pinNumber.size() ; i++){
        pinDigit = QString::number(pinNumber.at(i).digitValue(), 2);
        switch (pinDigit.size()) {
            case 1:
                pinDigit = "000" + pinDigit;
                break;
            case 2:
                pinDigit = "00" + pinDigit;
                break;
            case 3:
                pinDigit = "0" + pinDigit;
                break;
        }
        xorPIN.append(pinDigit);
    }
    xorPIN.append("1111111111111111111111111111111111111111");

    /*
        1. Grab PAN from input
        2. Encode each digit to binary (nibbles - four bits format)
        3. Put into xorPAN format

        ## xorPAN is 64bit number used to encode PIN block
        ## xorPAN is used to be xored with xorPIN
        ##
        ## xorPAN = | 0000 x4 | PAN1 | PAN2 | PAN3 | .... | PAN12 |
        ##
        ## Format 0 | 0s x4 | 12 right-most PAN digits excluding check digit |
    */

    QByteArray xorPAN;
    xorPAN.append("0000000000000000");
    QString panNumber = "5270820790587748";

    qDebug() << "PAN before encoding: " << panNumber;

    panNumber.remove(0, 3);
    panNumber.chop(1);

    QString panDigit;

    for(int i = 0 ; i < panNumber.size() ; i++){
        panDigit = QString::number(panNumber.at(i).digitValue(), 2);
        switch (panDigit.size()) {
            case 1:
                panDigit = "000" + panDigit;
                break;
            case 2:
                panDigit = "00" + panDigit;
                break;
            case 3:
                panDigit = "0" + panDigit;
                break;
        }
        xorPAN.append(panDigit);
    }

    qDebug () << "PIN after encoding: " << xorPIN;
    qDebug () << "PAN after encoding: " << xorPAN;

    QByteArray digitContainer;
    QByteArray xorResult;

    for(int i = 0; i < xorPIN.size() ; i++){

        digitContainer.append(xorPIN[i] ^ xorPAN[i]);

        if(digitContainer.toHex() == "00"){
            digitContainer = "0";
        }else if(digitContainer.toHex() == "01"){
            digitContainer = "1";
        }

        xorResult.append(digitContainer);

        digitContainer.clear();

    }
    qDebug() << "Result of Format 0 encoding: " << xorResult;

    return testAES(xorResult);
}

Terminal::~Terminal() {
    delete ui;
}
















