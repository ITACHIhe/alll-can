#include "main_func.h"
#include "ui_main_func.h"
#include"set_btm.h"
#include"chat.h"
#include<QMessageBox>
#include<QHostInfo>
#include<QHostAddress>
#include<QAbstractSocket>//注释需要的
main_func::main_func(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_func)
{
    ui->setupUi(this);
    QSize this_size1=this->frameSize();
    this->setMaximumSize(this_size1);
    this->setMinimumSize(this_size1);
    this->setWindowTitle("All Can");


    ui->ip_line->setFocus();//设置焦点
    ui->ip_line->setMaxLength(19);
    ui->ip_line->setInputMask("000.000.000.000;");

    ui->he_ip_line->setInputMask("000.000.000.000;");

    ui->port_line->setPlaceholderText(QString::fromLocal8Bit("1024~65535"));//打底数字
    ui->he_port_line->setPlaceholderText(QString::fromLocal8Bit("1024~65535"));
    ui->port_line->setValidator(new QIntValidator(1024,65535,this));//限制数字范围
    ui->he_port_line->setValidator(new QIntValidator(1024,65535,this));



}

main_func::~main_func()
{
    delete ui;
}

void main_func::on_set_button_clicked()
{

    btm=new set_btm(this);
    btm->setModal(true);
    btm->show();

}

void main_func::on_talkvideoButton_clicked()
{
     t1.my_name=ui->name_line->text();
     qDebug()<<"t1.my_name"<<t1.my_name;


    if(ui->ip_line->text().isEmpty()||ui->name_line->text().isEmpty()||ui->port_line->text().isEmpty()||ui->he_port_line->text().isEmpty()||ui->he_ip_line->text().isEmpty())
    {
        QMessageBox::warning(0,"警告","请把右边所有的选项填完");
    }

    else
    {
        if(ui->port_line->text().toInt()>65535||ui->he_port_line->text().toInt()>65535)
        {
            QMessageBox::warning(0,"警告","端口号不可以高于65535");
        }
        else
        {
            if(ui->port_line->text().toInt()==ui->he_port_line->text().toInt())
            {
                 QMessageBox::warning(0,"警告","端口号不可以相同");
            }
            else
            {
                t1.setModal(true);
                t1.show();

                QHostAddress add;
                QString a= ui->ip_line->text();
                add.setAddress(a);
                this->t1.my_port=ui->port_line->text().toInt();
                this->t1.he_port=ui->he_port_line->text().toInt();

                QString localHostName=QHostInfo::localHostName();//获取主机名
                QHostInfo info=QHostInfo::fromName(localHostName);
                qDebug()<<"local_address"<<info.addresses();
                qDebug()<<localHostName;

                //测试本机的ip地址的
                /*
                foreach (QHostAddress address,info.addresses() )
                {
                    if(address.protocol()==QAbstractSocket::IPv4Protocol)
                    {
                       t1.local_address=address.toString();
                       qDebug()<<"address.toString"<<address.toString();
                    }

                }*/

                bool bindFlag=t1.my_sender->bind(add,this->t1.my_port);
                if(!bindFlag)
                {
                    qDebug()<<"绑定失败";
                }
            }

        }

    }
             QString aaa= ui->he_ip_line->text();
             this->t1.he_address.setAddress(aaa);
}

void main_func::on_file_shared_Button_clicked()
{
   if(ui->ip_line->text().isEmpty()||ui->name_line->text().isEmpty()||ui->port_line->text().isEmpty()||ui->he_port_line->text().isEmpty()||ui->he_ip_line->text().isEmpty())
   {
       QMessageBox::warning(0,"警告","请把右边所有的选项填完");
   }

   else
   {
       if(ui->port_line->text().toInt()>65535||ui->he_port_line->text().toInt()>65535)
       {
           QMessageBox::warning(0,"警告","端口号不可以高于65535");
       }
       else
       {
           if(ui->port_line->text().toInt()==ui->he_port_line->text().toInt())
           {
                QMessageBox::warning(0,"警告","端口号不可以相同");
           }
           else
           {
               d1.setModal(true);
               d1.show();
               d1.my_name=ui->name_line->text();
               qDebug()<<"d1.my_name"<<d1.my_name;
               QString aaa= ui->he_ip_line->text();
               this->d1.he_address.setAddress(aaa);
               QHostAddress add;
               QString a= ui->ip_line->text();
               add.setAddress(a);
               this->d1.my_port=ui->port_line->text().toInt();
               this->d1.he_port=ui->he_port_line->text().toInt();

               QString localHostName=QHostInfo::localHostName();//获取主机名
               QHostInfo info=QHostInfo::fromName(localHostName);
               qDebug()<<"local_address"<<info.addresses();
               qDebug()<<localHostName;
               //测试本机的ip地址的
               /*
               foreach (QHostAddress address,info.addresses() )
               {
                   if(address.protocol()==QAbstractSocket::IPv4Protocol)
                   {
                      d1.local_address=address.toString();
                      qDebug()<<"address.toString"<<address.toString();
                   }

               }*/
               bool bindFlag=d1.my_sender->bind(add,this->d1.my_port);
               if(!bindFlag)
               {
                   qDebug()<<"绑定失败";
               }
           }
       }
   }
}

void main_func::on_file_send_Button_clicked()
{
   if(ui->ip_line->text().isEmpty()||ui->name_line->text().isEmpty()||ui->port_line->text().isEmpty()||ui->he_port_line->text().isEmpty()||ui->he_ip_line->text().isEmpty())
   {
       QMessageBox::warning(0,"警告","请把右边所有的选项填完");
   }

   else
   {
       if(ui->port_line->text().toInt()>65535||ui->he_port_line->text().toInt()>65535)
       {
           QMessageBox::warning(0,"警告","端口号不可以高于65535");
       }
       else
       {
           if(ui->port_line->text().toInt()==ui->he_port_line->text().toInt())
           {
                QMessageBox::warning(0,"警告","端口号不可以相同");
           }
           else
           {
               e1.my_name=ui->name_line->text();
               e1.he_address=ui->he_ip_line->text();
               e1.local_address=ui->ip_line->text();
               e1.my_port=ui->port_line->text().toInt();
               e1.he_port=ui->he_port_line->text().toInt();
               e1.setModal(true);
               e1.show();
               QHostAddress add;
               add.setAddress(e1.local_address);
              e1.issuccess= e1.tcp_server->listen(add,e1.my_port);
              if(!e1.issuccess)
              {
               qDebug()<<"tcp监听失败";
              }
              else
              {
               qDebug()<<"tcp监听成功";
              }
           }

       }

   }
            QString aaa= ui->he_ip_line->text();
            this->e1.he_address.setAddress(aaa);
}

void main_func::on_drawButton_clicked()
{

    if(ui->ip_line->text().isEmpty()||ui->name_line->text().isEmpty()||ui->port_line->text().isEmpty()||ui->he_port_line->text().isEmpty()||ui->he_ip_line->text().isEmpty())
    {
        QMessageBox::warning(0,"警告","请把右边所有的选项填完");
    }

    else
    {
        if(ui->port_line->text().toInt()>65535||ui->he_port_line->text().toInt()>65535)
        {
            QMessageBox::warning(0,"警告","端口号不可以高于65535");
        }
        else
        {
            if(ui->port_line->text().toInt()==ui->he_port_line->text().toInt())
            {
                 QMessageBox::warning(0,"警告","端口号不可以相同");
            }
            else
            {
                e2.my_name=ui->name_line->text();
                e2.he_address=ui->he_ip_line->text();
                e2.local_address=ui->ip_line->text();
                e2.my_port=ui->port_line->text().toInt();
                e2.he_port=ui->he_port_line->text().toInt();
                e2.setModal(true);
                e2.show();
                e2.tcpsocket->connectToHost(e2.he_address,e2.he_port);
            }

        }

    }
}
