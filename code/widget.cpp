#include "widget.h"
#include "ui_widget.h"
#include<QPalette>
#include<QMessageBox>
#include<QDebug>
#include<QLineEdit>
#include<QPushButton>
#include<QKeySequence>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPalette pal;

    pal.setColor(QPalette::Background,Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    //这三行实现背景亮度

    ui->id_line->setClearButtonEnabled(true);
    ui->passwordline->setClearButtonEnabled(true);
    ui->passwordline->setEchoMode(QLineEdit::Password);//设置密码格式

    ui->login_button->setFocus();
    ui->login_button->setDefault(true);//登陆键绑定enter




}
Widget::~Widget()
{
    delete ui;
}
void Widget::on_register_button_clicked()//注册键
{
     QMessageBox::information(0,"提示","没有开发网站，账号密码可乱填");

}

void Widget::on_login_button_clicked()//登录键
{
    /*
    QString line1=ui->id_line->text();
    QString line2=ui->passwordline->text();
    if(line1.toInt()==1&&line2.toInt()==1)
    {
        a1.show();
        this->hide();
    }
    else if (ui->id_line->text().isEmpty() ||ui->passwordline->text().isEmpty())
    {
        QMessageBox::warning(0,"警告","密码或者账号为空");
        ui->id_line->clear();
        ui->passwordline->clear();
    }
    else
    {
        QMessageBox::warning(0,"警告","密码或者账号错误");
        ui->id_line->clear();
        ui->passwordline->clear();
    }
    */
    a1.show();
    this->hide();//这是测试简化
}
