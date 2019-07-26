#ifndef TCP_RE_FILE_H
#define TCP_RE_FILE_H

#include <QDialog>
#include<QtNetwork/QTcpServer>
#include<QtNetwork/QTcpSocket>
#include<QFile>
#include<QTime>
namespace Ui {
class tcp_re_file;
}

class tcp_re_file : public QDialog
{
    Q_OBJECT

public:
    explicit tcp_re_file(QWidget *parent = 0);
    ~tcp_re_file();
    QTcpServer *tcp_client;
    int he_port;
    int my_port;
    QString my_name;
    QString local_address;
    QHostAddress he_address;
      qint64 TotalBytes;

    QString theFileName;
    qint64 payloadSize;
    qint64 totalBytes;
    qint64 bytesToReceive;
     qint64 bytesReceive;
      qint64 fileNameSize;
    QByteArray outBlock;
    QTcpSocket *tcpsocket;
    QString fileName;
    QFile *localFile;
    QByteArray inBlock;
     bool issuccess;

    QTime time;

private:
    Ui::tcp_re_file *ui;
private slots:
    void connect_show();
    void readMessage();
};

#endif // TCP_RE_FILE_H
