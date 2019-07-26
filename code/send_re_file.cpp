#include "send_re_file.h"
#include "ui_send_re_file.h"

send_re_file::send_re_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::send_re_file)
{
    ui->setupUi(this);
}

send_re_file::~send_re_file()
{
    delete ui;
}
