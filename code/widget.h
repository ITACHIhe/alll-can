#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"main_func.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    main_func a1;

private slots:
    void on_register_button_clicked();
    void on_login_button_clicked();
};

#endif // WIDGET_H
