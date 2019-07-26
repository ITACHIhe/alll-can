#ifndef FILE_SHARED_H
#define FILE_SHARED_H

#include <QDialog>
#include<QtNetwork/QUdpSocket>
namespace Ui {
class file_shared;
}

class file_shared : public QDialog
{
    Q_OBJECT

public:
    explicit file_shared(QWidget *parent = 0);
    ~file_shared();
    QUdpSocket *my_sender;
    int he_port;
    int my_port;
    QString my_name;
    QString local_address;
    QHostAddress he_address;
private slots:
    void on_clear_Button_clicked();
    void textchanged();
    void processPendingDatagram();

    void on_saveButton_clicked();

    void on_uploadButton_clicked();

private:
    Ui::file_shared *ui;
protected:
    void closeEvent();
};

#endif // FILE_SHARED_H
