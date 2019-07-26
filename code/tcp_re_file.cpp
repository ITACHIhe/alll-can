#include "tcp_re_file.h"
#include "ui_tcp_re_file.h"
#include<QDebug>
#include<QMessageBox>
tcp_re_file::tcp_re_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tcp_re_file)
{
    ui->setupUi(this);
    tcpsocket=new QTcpSocket;
    TotalBytes = 0;
    bytesReceive = 0;
    fileNameSize = 0;
    connect(tcpsocket,&QTcpSocket::connected,this,&tcp_re_file::connect_show);
    connect(tcpsocket,&QTcpSocket::readyRead,this,&tcp_re_file::readMessage);
}

tcp_re_file::~tcp_re_file()
{
    delete ui;
}

void tcp_re_file::connect_show()
{
    qDebug()<<"yi jin lianjie shang le";
     time.start();
}

void tcp_re_file::readMessage()
{
    QDataStream in(tcpsocket);
    in.setVersion(QDataStream::Qt_5_9);

    float useTime = time.elapsed();
    qDebug() << bytesReceive << endl;
    if(bytesReceive <= sizeof(qint64)*2) {
        if((tcpsocket->bytesAvailable()>=sizeof(qint64) * 2) && (fileNameSize == 0))
        {
            in >> TotalBytes >> fileNameSize;
            bytesReceive += sizeof(qint64) * 2;
        }
        if((tcpsocket->bytesAvailable() >= fileNameSize) && (fileNameSize != 0)) {
            in >> fileName;
            bytesReceive += fileNameSize;
            if(!localFile->open(QFile::WriteOnly)) {
                QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件 %1：\n %2")
                                     .arg(fileName).arg(localFile->errorString()));
                return;
            }

        }
        else
        {
            return;
        }
    }
    if(bytesToReceive < TotalBytes) {
        bytesReceive += tcpsocket->bytesAvailable();
        inBlock = tcpsocket->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }

    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesReceive);
    double speed = bytesReceive / useTime;
    ui->tcpClientStatuslabel->setText(tr("已接收 %1 MB (%2MB/s)"
                                         "\n共%3MB.已用时：%4秒\n估计剩余时间：%5秒")
                                      .arg(bytesReceive / (1024*1024))
                                      .arg(speed * 1000/(1024 * 1024),0,'f',2)
                                      .arg(TotalBytes / (1024*1024))
                                      .arg(useTime/1000,0,'f',0)
                                      .arg(TotalBytes/speed/1000 - useTime/1000,0,'f',0));
    if(bytesReceive == TotalBytes) {
        localFile->close();
        tcpsocket->close();
        ui->tcpClientStatuslabel->setText(tr("接收文件%1完毕").arg(fileName));
    }
}
