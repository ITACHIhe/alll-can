#include "set_btm.h"
#include "ui_set_btm.h"
#include<QMessageBox>
set_btm::set_btm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::set_btm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog| Qt::FramelessWindowHint);
  //  ui->aboutButton->setStyleSheet("border:none");

}

set_btm::~set_btm()
{
    delete ui;
}

void set_btm::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    QPoint y=event->globalPos();
    QPoint x=y-this->z;
    this->move(x);

}

void set_btm::mousePressEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    QPoint y =event->globalPos();
    QPoint x=this->geometry().topLeft();
    this->z=y-x;

}

void set_btm::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    this->z=QPoint();

}

void set_btm::label_about()
{
    QMessageBox::information(0,"qq","sss");
}

void set_btm::on_pushButton_clicked()
{
    this->close();
}

void set_btm::on_aboutButton_clicked()
{
    QMessageBox::information(0,"关于All Can","暂时没什么告诉你的，因为技术堪忧哈哈哈哈");
}
