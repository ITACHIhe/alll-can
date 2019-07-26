#ifndef SET_BTM_H
#define SET_BTM_H

#include <QDialog>
#include<QMouseEvent>
#include<QPoint>
namespace Ui {
class set_btm;
}

class set_btm : public QDialog
{
    Q_OBJECT

public:
    explicit set_btm(QWidget *parent = 0);
    ~set_btm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::set_btm *ui;
    QPoint x,y,z;


private:
   void mouseMoveEvent(QMouseEvent *event);
   void mousePressEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);
private slots:
   void label_about();
   void on_aboutButton_clicked();
};

#endif // SET_BTM_H
