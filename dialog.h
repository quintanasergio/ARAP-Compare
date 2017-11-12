#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QList<QString> experimentos, QList<QString> showExp, QWidget *parent = 0 );
    QList<QString> getList();
    ~Dialog();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    QList<QString> allExp;
    QList<QString> addExp;
};

#endif // DIALOG_H
