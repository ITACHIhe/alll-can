#ifndef MAIN_FUNC_H
#define MAIN_FUNC_H

#include <QWidget>
#include"set_btm.h"
#include"chat.h"
#include"file_shared.h"
#include"tcp_send_file.h"
#include"tcp_re_file.h"
namespace Ui {
class main_func;
}

class main_func : public QWidget
{
    Q_OBJECT

public:
    explicit main_func(QWidget *parent = 0);
    ~main_func();


private slots:
    void on_set_button_clicked();

    void on_talkvideoButton_clicked();

    void on_file_shared_Button_clicked();

    void on_file_send_Button_clicked();

    void on_drawButton_clicked();

private:
    Ui::main_func *ui;
    set_btm *btm;
    chat t1;
    file_shared d1;
    tcp_send_file e1;
    tcp_re_file e2;

};

#endif // MAIN_FUNC_H
