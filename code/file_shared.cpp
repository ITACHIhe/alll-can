#include "file_shared.h"
#include "ui_file_shared.h"
#include<QDebug>
#include<QMessageBox>
#include<QFile>
#include<QFileDialog>
file_shared::file_shared(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::file_shared)
{
    ui->setupUi(this);
    QSize this_size1=this->frameSize();
    this->setMaximumSize(this_size1);
    this->setMinimumSize(this_size1);
    this->setWindowTitle("All Can");
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    my_sender=new QUdpSocket();

    connect(my_sender,&QUdpSocket::readyRead,this,&file_shared::processPendingDatagram);

    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(textchanged()));

}

file_shared::~file_shared()
{
    delete ui;
}

void file_shared::on_clear_Button_clicked()
{
    ui->textEdit->clear();
}

void file_shared::textchanged()
{
    QString aa=ui->textEdit->toPlainText();
    QByteArray bb=aa.toLocal8Bit();
    my_sender->writeDatagram(bb.data(),bb.size(),he_address,he_port);
}

void file_shared::processPendingDatagram()
{

    while (my_sender->hasPendingDatagrams())
    {

        QByteArray datagram;
        datagram.resize(my_sender->pendingDatagramSize());
        my_sender->readDatagram(datagram.data(),datagram.size());

      QString msg = QString::fromLocal8Bit(datagram.data());
      if(msg!=ui->textEdit->toPlainText())
      {

          ui->textEdit->setText(msg);
      }
      else
      {

           qDebug()<<"没有改变"<<endl;
      }

    }

}


void file_shared::on_saveButton_clicked()
{
    if(ui->textEdit->document()->isEmpty())
    {
      QMessageBox::warning(0,tr("警告"), tr("聊天记录为空,无法保存!"),QMessageBox::Ok);
     }
    else
    {
        QString fileName = QFileDialog::getSaveFileName(this,tr("保存聊天记录"),tr("聊天记录"),tr("文本(*.txt);;All File(*.*)"));
     if(!fileName.isEmpty())
     {
         QFile file(fileName);
            if(!file.open(QFile::WriteOnly|QFile::Text))
            {
                QMessageBox::warning(this,tr("保存文件"),tr("无法保存文件 %1:\n %2").arg(fileName).arg(file.errorString()));
            }
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
     }
     }
}

void file_shared::on_uploadButton_clicked()
{
        QFile file;
        QString f = QFileDialog::getOpenFileName(this, QString("选择文件"), QString("/"),QString("TEXT(*.txt)"));
        file.setFileName(f);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
      {
         QByteArray t ;
         while(!file.atEnd())
     {
            t += file.readLine();
      }
           ui->textEdit->setText(QString(t));
           file.close();
        }
}

void file_shared::closeEvent()
{
    delete my_sender;
    my_sender=new QUdpSocket;
}
