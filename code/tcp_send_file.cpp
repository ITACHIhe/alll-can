#include "tcp_send_file.h"
#include "ui_tcp_send_file.h"
#include<QFileDialog>
#include<QMessageBox>
tcp_send_file::tcp_send_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tcp_send_file)
{
    ui->setupUi(this);
    tcp_server=new QTcpServer;
    QSize this_size1=this->frameSize();
    this->setMaximumSize(this_size1);
    this->setMinimumSize(this_size1);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    connect(tcp_server,&QTcpServer::newConnection,this,&tcp_send_file::newConnection);
    ui->send_Button->setEnabled(false);

}

tcp_send_file::~tcp_send_file()
{
    delete ui;
}

void tcp_send_file::newConnection()
{
    ui->biaojilabel->setText("有链接");
}

void tcp_send_file::on_openButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
        ui->label->setText(tr("要传送的文件为：%1").arg(theFileName));
        ui->send_Button->setEnabled(true);

    }
}

void tcp_send_file::on_send_Button_clicked()
{
    ui->send_Button->setEnabled(false);
    clientConnection=tcp_server->nextPendingConnection();
    connect(clientConnection,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
    ui->label->setText(tr("开始传送文件 %1 ！").arg(theFileName));
    localFile = new QFile(fileName);
    if(!localFile->open((QFile::ReadOnly)))
    {
        QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件 %1:\n %2")
                             .arg(fileName).arg(localFile->errorString()));
        return;
    }
    totalBytes = localFile->size();
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_9);
    QString currentFile = fileName.right(fileName.size()
                                         - fileName.lastIndexOf('/')-1);
    sendOut << qint64(0) << qint64(0) << currentFile;
    totalBytes += outBlock.size();
    sendOut.device()->seek(0);
    sendOut << totalBytes << qint64((outBlock.size() - sizeof(qint64) * 2));
    bytesToWrite = totalBytes - clientConnection->write(outBlock);
    outBlock.resize(0);
}

void tcp_send_file::updateClientProgress(qint64 numBytes)
{
    qApp->processEvents();
    bytesWritten += (int)numBytes;
    if(bytesWritten > 0) {
        outBlock = localFile->read(qMin(bytesToWrite,payloadSize));
        bytesToWrite -= (int)clientConnection->write(outBlock);
        outBlock.resize(0);
    }
    else
    {
        localFile->close();
    }
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesWritten);

    float userTime = time.elapsed();
    double speed = bytesWritten / userTime;
    ui->label->setText(tr("已发送 %1MB（%2MB/s)"
                                   "\n共%3MB 已用时：%4秒\n 估计剩余时间:%5秒")
            .arg(bytesWritten / (1024*1024))
            .arg(speed * 1000 / (1024*1024),0,'f',2)
            .arg(totalBytes / (1024*1024))
                       .arg(userTime/1000,0,'f',0));
}


void tcp_send_file::on_close_Button_clicked()
{

    if(tcp_server->isListening())
    {
        tcp_server->close();
        if(localFile->isOpen())
            localFile->close();
        clientConnection->abort();
    }
    close();
}
