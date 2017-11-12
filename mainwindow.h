#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void redraw();
    ~MainWindow();

    QList<QString> getExperimentos() const;

    QList<QString> getShowExp() const;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);
    
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<QString> experimentos;
    QList<QString> showExp;
    QString dirarap;
    void medvarcalculation();
    QList<float> rttMediaExp;
    QList<float> rttVarianzaExp;


    struct Elem {
    Elem(int p, int v) { pos = p; val = v; }
    int pos;
    int val;
    };

    struct ElemS {
    ElemS(int p, QString s) { pos = p; val = s; }
    int pos;
    QString val;
    };

    static bool myLessThan(const Elem& e1, const Elem& e2);
    static bool myLessThanS(const ElemS& e1, const ElemS& e2);

    QList<Elem> par;
    QList<ElemS> par2;
};

#endif // MAINWINDOW_H
