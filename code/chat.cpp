#include "chat.h"
#include "ui_chat.h"
#include<QString>
#include<QDebug>
#include<QDateTime>
#include<QTimer>
#include<QMessageBox>
#include<QFileDialog>
#include<QFile>
#include<QTextStream>
chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    // 去掉问号，只保留关闭
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
   //
    QSize this_size1=this->frameSize();
    this->setMaximumSize(this_size1);
    this->setMinimumSize(this_size1);
    this->setWindowTitle("All Can");
       my_sender=new QUdpSocket;
     connect(my_sender,SIGNAL(readyRead()),this,SLOT(rece_data()));

}

chat::~chat()
{
    delete ui;
}

void chat::on_pushButton_2_clicked()
{
        this->close();
}

void chat::on_clearButton_clicked()
{
    ui->messageBrowser->clear();
     ui->userNumLabel->setText(tr("已清空"));
}

void chat::on_sendButton_clicked()
{
    qDebug()<<this->my_name;
    if(ui->messageTextEdit->toPlainText() == "")
    {
        QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
        return;
    }
    else
    {
        QString text=ui->messageTextEdit->toPlainText();
        ui->messageTextEdit->clear();
        QDateTime current_date_time=QDateTime::currentDateTime();
        QString current_date=current_date_time.toString("yyyy.MM.dd hh:mm:ss");

        QString name=this->my_name;

        ui->messageBrowser->append(name+"            "+current_date);
        ui->messageBrowser->append(text);


        QByteArray da=name.toLocal8Bit()+"            "+current_date.toLocal8Bit()+"\n"+text.toLocal8Bit();


         my_sender->writeDatagram(da.data(),da.size(),this->he_address,this->he_port);


    }
    ui->userNumLabel->setText(tr("已发送"));
}

void chat::on_downloadButton_clicked()
{
    if(ui->messageBrowser->document()->isEmpty())
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
            out << ui->messageBrowser->toPlainText();
     }
     }
    // ui->userNumLabel->setText(tr("已保存"));  这个没保存也会显示保存的
}

void chat::on_returnButton_clicked()
{
    this->close();
}

void chat::on_exitButton_clicked()
{
    exit(0);
}

void chat::rece_data()
{
    while(my_sender->hasPendingDatagrams())//判断udpsocket中是否有数据报可读
    {
        QByteArray datagram;
        datagram.resize(my_sender->pendingDatagramSize());
        my_sender->readDatagram(datagram.data(),datagram.size());//读取第一个数据报

        QString msg = QString::fromLocal8Bit(datagram.data());
        QDateTime current_date_time=QDateTime::currentDateTime();
        QString current_date=current_date_time.toString("yyyy.MM.dd hh:mm:ss");
        ui->messageBrowser->append(current_date);
        ui->messageBrowser->append("\n");
        ui->messageBrowser->insertPlainText(msg);



        qDebug()<<"收到数据"<<msg<<endl;
    }
    ui->userNumLabel->setText(tr("已接受"));
}

void chat::closeEvent(QCloseEvent *event)
{
    delete my_sender;
    my_sender=new QUdpSocket;
}


