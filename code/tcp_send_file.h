    #ifndef TCP_SEND_FILE_H
#define TCP_SEND_FILE_H

#include <QDialog>
#include<QtNetwork/QTcpServer>
#include<QtNetwork/QTcpSocket>
#include<QFile>
#include<QTime>
namespace Ui {
class tcp_send_file;
}

class tcp_send_file : public QDialog
{
    Q_OBJECT

public:
    explicit tcp_send_file(QWidget *parent = 0);
    ~tcp_send_file();
    QTcpServer *tcp_server;
    int he_port;
    int my_port;
    QString my_name;
    QString local_address;
    QHostAddress he_address;
    QFile *localFile;
    QString fileName;
    QString theFileName;
    qint64 payloadSize;
    qint64 totalBytes;
    qint64 bytesWritten;
    qint64 bytesToWrite;
    QByteArray outBlock;
    QTcpSocket *clientConnection;
     bool issuccess;

    QTime time;

private:
    Ui::tcp_send_file *ui;

private slots:
    void newConnection();

    void on_openButton_clicked();
    void on_send_Button_clicked();
    void updateClientProgress(qint64 numBytes);
    void on_close_Button_clicked();

signals:
    void sendFileName(QString fileName);
};



#endif // TCP_SEND_FILE_H
