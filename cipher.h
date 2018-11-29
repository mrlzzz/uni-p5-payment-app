#ifndef CIPHER_H
#define CIPHER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define PADDING RSA_PKCS1_PADDING
#define KEYSIZE 32
#define IVSIZE 32
#define BLOCKSIZE 256
#define SALTSIZE 8

class Cipher : public QObject
{
    Q_OBJECT
public:
    explicit Cipher(QObject *parent = nullptr);
    RSA *getPublicKey(QString filename);
    RSA *getPublicKey(QByteArray &data);
    RSA *getPrivateKey(QString filename);
    RSA *getPrivateKey(QByteArray &data);

    QByteArray encryptRSA (RSA *key, QByteArray &data);
    QByteArray decryptRSA (RSA *key, QByteArray &data);


    QByteArray encryptAES (QByteArray passphrase, QByteArray &data);
    QByteArray decryptAES (QByteArray passphrase, QByteArray &data);

    QByteArray randomBytes(int size);

    void freeRSAKey(RSA *key);

signals:

public slots:

private:
    void initialize();
    void finalize();
    QByteArray readFile(QString filename);
    void writeFile(QString filename, QByteArray &data);

};

#endif // CIPHER_H
