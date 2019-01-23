#include "postreq2.h"
#include "terminal.h"
#include <QApplication>
#include <QObject>
#include <cipher.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>


using namespace std;

QByteArray getPublicKey(){
    QByteArray testPublicKey;

    testPublicKey.append("-----BEGIN PUBLIC KEY-----\n");
    testPublicKey.append("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAsLLYmD6ZFtobPTJftlYG\n");
    testPublicKey.append("n5tjdwM2CJ77VGi9CcVJOqReSDu4OI6T9qpEdMYNjZkWTmojyk/3YD5vuDTHxo9S\n");
    testPublicKey.append("eC6ZdGGPwv0cit2yiHfz0e/1/61PpRMNQPYKhntr2kmoHPaGF8/9i9OkpJl6IMpx\n");
    testPublicKey.append("oXnK8yhhKRTRO6BnqwjXgohIrDavy6H+C1/VV4lkTxifIPTfnPkKbkhJafFS3h/M\n");
    testPublicKey.append("ylumD06py2b+pOQ1Ke/LzXIxfbTeG5LpGuBRqibgBMHQd1U/V9MpFyGY0q889jbf\n");
    testPublicKey.append("+NV7+RRBytHYbpr4UaTW4qklyucVBg79MFszojBpICK2h/W2rfejfKcjFrQm/KiJ\n");
    testPublicKey.append("OwIDAQAB\n");
    testPublicKey.append("-----END PUBLIC KEY-----\n");

    return testPublicKey;
}

QByteArray getPrivateKey(){
    QByteArray testPrivateKey;

    testPrivateKey.append("-----BEGIN RSA PRIVATE KEY-----\n");
    testPrivateKey.append("MIIEowIBAAKCAQEAsLLYmD6ZFtobPTJftlYGn5tjdwM2CJ77VGi9CcVJOqReSDu4\n");
    testPrivateKey.append("OI6T9qpEdMYNjZkWTmojyk/3YD5vuDTHxo9SeC6ZdGGPwv0cit2yiHfz0e/1/61P\n");
    testPrivateKey.append("pRMNQPYKhntr2kmoHPaGF8/9i9OkpJl6IMpxoXnK8yhhKRTRO6BnqwjXgohIrDav\n");
    testPrivateKey.append("y6H+C1/VV4lkTxifIPTfnPkKbkhJafFS3h/MylumD06py2b+pOQ1Ke/LzXIxfbTe\n");
    testPrivateKey.append("G5LpGuBRqibgBMHQd1U/V9MpFyGY0q889jbf+NV7+RRBytHYbpr4UaTW4qklyucV\n");
    testPrivateKey.append("Bg79MFszojBpICK2h/W2rfejfKcjFrQm/KiJOwIDAQABAoIBAFLo6EavgKe/WW6i\n");
    testPrivateKey.append("l1R4Ew2LHOW4BP+QkX9u0dymzJCOlYqxMuSeygDArfRZBfz96wCKPxbr5LgtM8Cs\n");
    testPrivateKey.append("S1z43Qp1Wx3HtWwZ1e22ztHH7wj/3l7E1I0xXlOv3wpxGQ9I5nAIoKzFtEOK4EM3\n");
    testPrivateKey.append("nJ2MQDszaa4ksUpUcUTYJCyVroGZZtAZuYGh/8hyVPwLEO8TUEn4CPPVaP4Er1hh\n");
    testPrivateKey.append("oS5sYQeCIYkGVz3oYiOLZA5Fws/DRFccE+PkNaNyhxMo/YX7QOJc/Q4WV5XIMeLB\n");
    testPrivateKey.append("OOpFCt9GJUxSKWP1F3Eg7vDJbqETrinEM0Do6Di7moNxjMGNxwRwPJ3gG1fJkuLw\n");
    testPrivateKey.append("dRGdoekCgYEA5UWith90vjaysXn2cEpLTNwfx5wzCxS4isYEX1Q32huEdlzXAIHZ\n");
    testPrivateKey.append("/JO94tN6piRvN4vSQJy79AWwRpMtbu+aXEsfihLxI+mziccO9s39CumgM1CLCe66\n");
    testPrivateKey.append("lIY227SINIVH0/1SCjeVPn+J0V4SkNsHtD6LTY/ChBl8vn39xruT0BUCgYEAxUw3\n");
    testPrivateKey.append("gVUrLmlKxOQ97CrLgwaRSa/zs+oAc/LQF6j+uKJX8HnvEEXh9I5k1j2iWc2fwCiL\n");
    testPrivateKey.append("EfpqBW1uOelpVvv01t4yqn74kR5Y0xs3v7r4R9MEy25Ke+G7Lgtvl13/V/otfIxA\n");
    testPrivateKey.append("4IGzoqfDB5UK7+20tzo2VFJGIO2o7SNHLgd/+A8CgYEAs+gar9KrJv+A5OcRTDfg\n");
    testPrivateKey.append("MqWggl+9ZfqSfMK5d5x8Xzesj7x2Mb2zMhE0taLA4VJBu1KKX40dp3Q3SIoA4sY9\n");
    testPrivateKey.append("WCLS0uPeORIPghOjWGN3JnMA9INFNzwPSLCwp2JYZu4W2PA0yjOndu1ZVeL9qpFU\n");
    testPrivateKey.append("0EkrwmcGeeYODuSKmMFkUakCgYAGL8ChzpDfELAmgl2qtSDSh/cwT1Md9h1zhU6f\n");
    testPrivateKey.append("H051banCQaCMaxSNvZVN3nrjw/3ZYawSsT530xmcuUPzVU01G5yNGhQjQMdaP0U9\n");
    testPrivateKey.append("PtigL+67jkbJoadj5znlji3+jTq16BP0tjxywj3sU/EW2uZKxImFlVrbl3gvj2ag\n");
    testPrivateKey.append("+904YwKBgGieB83Yi0yWQihNs1RZTLR/HHHJU1qmIxbwU7mpb7zNws1uTNEIpTwk\n");
    testPrivateKey.append("VHNRsZ8zc7hNDTtxxw9TdlTfJABJZMCf5ijbklpBqQKZ/pZWz2q1sadRQZtDo0H5\n");
    testPrivateKey.append("Y0G8DSu36Xma9bO7GVYx/4UszBpdxtnqSq3SM2NP+ZOh3z+If619\n");
    testPrivateKey.append("-----END RSA PRIVATE KEY-----\n");

    return testPrivateKey;
}

bool encryptCombined() {
    Cipher cWrapper;

    QByteArray key = getPublicKey();
    RSA* publickey = cWrapper.getPublicKey(key);

    QByteArray passphrase = cWrapper.randomBytes(8).toBase64();
    QByteArray encryptedKey = cWrapper.encryptRSA(publickey, passphrase);

    qDebug() << "EncryptedKey" << encryptedKey;

    //Encrypt the data

    QByteArray plain = "0000010010010000000101001101110010111111111111111111101001101111";
    QByteArray encrypted = cWrapper.encryptAES(passphrase, plain);

    QString filename = "test.enc";
    QFile f(filename);
    if(!f.open(QFile::WriteOnly)){
        qCritical() << "Could not open; " << filename;
        return false;
    }

    qDebug() << "Encrypted Key Len: " << encryptedKey.length();

    QByteArray encryptedData;
    encryptedData.append(encryptedKey);
    encryptedData.append(encrypted);
    f.write(encryptedData);
    f.close();

    qDebug() << "Encryption finished!";

    return true;
}

void testRSA(QByteArray plain){
    QByteArray testPrivateKey = getPrivateKey();
    QByteArray testPublicKey = getPublicKey();

    Cipher cWrapper;

    RSA* publicKey = cWrapper.getPublicKey(testPublicKey);
    RSA* privateKey = cWrapper.getPrivateKey(testPrivateKey);

    QByteArray encrypted = cWrapper.encryptRSA(publicKey, plain);
    QByteArray decrypted = cWrapper.decryptRSA(privateKey, encrypted);

    qDebug() << "Plaintext: " << plain;
    qDebug() << "Encrypted: " << encrypted.toHex();
    qDebug() << "Decrypted: " << decrypted;
}

//void testAES(QByteArray plain){
//    qDebug() << "Testing AES...";

//    Cipher cWrapper;

//    QString passphrase = "secret";
//    QByteArray encrypted = cWrapper.encryptAES(passphrase.toLatin1(), plain);
//    QByteArray decrypted = cWrapper.decryptAES(passphrase.toLatin1(), encrypted);

//    qDebug() << "Plain: " << plain;
//    qDebug() << "Encrypted: " << encrypted.toHex();
//    qDebug() << "Decrypted: " << decrypted;
//}

//void pinEncode() {
//    /*
//        1. Grab PIN from input.
//        2. Encode each digit to binary (nibbles - four bits format)
//        3. Put into xorPIN format

//        ## xorPIN is 64bit number used to encode PIN block
//        ## xorPIN is used to be xored with xorPAN
//        ##
//        ## xorPIN = | 0000 | 0100 | XXXX | XXXX | XXXX | XXXX | 1111 | ...
//        ##
//        ## Format 0 | num of PIN digits | PIN digit 1 | PIN digit 2 | PIN digit 3 | PIN digit 4 | fill 1s x10 | ...
//    */

//    QString pinNumber = "1234";

//    qDebug() << "PIN before encoding: " << pinNumber;

//    QByteArray xorPIN;
//    xorPIN.append("00000100");
//    QString pinDigit;

//    for(int i = 0 ; i < pinNumber.size() ; i++){
//        pinDigit = QString::number(pinNumber.at(i).digitValue(), 2);
//        switch (pinDigit.size()) {
//            case 1:
//                pinDigit = "000" + pinDigit;
//                break;
//            case 2:
//                pinDigit = "00" + pinDigit;
//                break;
//            case 3:
//                pinDigit = "0" + pinDigit;
//                break;
//        }
//        xorPIN.append(pinDigit);
//    }
//    xorPIN.append("1111111111111111111111111111111111111111");

//    /*
//        1. Grab PAN from input
//        2. Encode each digit to binary (nibbles - four bits format)
//        3. Put into xorPAN format

//        ## xorPAN is 64bit number used to encode PIN block
//        ## xorPAN is used to be xored with xorPIN
//        ##
//        ## xorPAN = | 0000 x4 | PAN1 | PAN2 | PAN3 | .... | PAN12 |
//        ##
//        ## Format 0 | 0s x4 | 12 right-most PAN digits excluding check digit |
//    */

//    QByteArray xorPAN;
//    xorPAN.append("0000000000000000");
//    QString panNumber = "5270820790587748";

//    qDebug() << "PAN before encoding: " << panNumber;

//    panNumber.remove(0, 3);
//    panNumber.chop(1);

//    QString panDigit;

//    for(int i = 0 ; i < panNumber.size() ; i++){
//        panDigit = QString::number(panNumber.at(i).digitValue(), 2);
//        switch (panDigit.size()) {
//            case 1:
//                panDigit = "000" + panDigit;
//                break;
//            case 2:
//                panDigit = "00" + panDigit;
//                break;
//            case 3:
//                panDigit = "0" + panDigit;
//                break;
//        }
//        xorPAN.append(panDigit);
//    }

//    qDebug () << "PIN after encoding: " << xorPIN;
//    qDebug () << "PAN after encoding: " << xorPAN;

//    QByteArray digitContainer;
//    QByteArray xorResult;

//    for(int i = 0; i < xorPIN.size() ; i++){

//        digitContainer.append(xorPIN[i] ^ xorPAN[i]);

//        if(digitContainer.toHex() == "00"){
//            digitContainer = "0";
//        }else if(digitContainer.toHex() == "01"){
//            digitContainer = "1";
//        }

//        xorResult.append(digitContainer);

//        digitContainer.clear();

//    }
//    qDebug() << "Result of Format 0 encoding: " << xorResult;

//    testAES(xorResult);
//}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Terminal w;
    w.show();
    // testRSA("mati");
    // encryptCombined();
    //pinEncode();


    return a.exec();
}
