#ifndef SEND_RE_FILE_H
#define SEND_RE_FILE_H

#include <QDialog>

namespace Ui {
class send_re_file;
}

class send_re_file : public QDialog
{
    Q_OBJECT

public:
    explicit send_re_file(QWidget *parent = 0);
    ~send_re_file();

private:
    Ui::send_re_file *ui;
};

#endif // SEND_RE_FILE_H
