#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include<QtNetwork/QUdpSocket>
namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = 0);
    ~chat();
    QUdpSocket *my_sender;
    int he_port;
    int my_port;
    QString my_name;
    QString local_address;
    QHostAddress he_address;
private slots:
    void on_pushButton_2_clicked();

    void on_clearButton_clicked();

    void on_sendButton_clicked();

    void on_downloadButton_clicked();

    void on_returnButton_clicked();

    void on_exitButton_clicked();

    void rece_data();


private:
    Ui::chat *ui;
protected:
    void closeEvent(QCloseEvent*event);
};

#endif // CHAT_H
