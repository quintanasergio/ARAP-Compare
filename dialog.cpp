#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QList<QString> experimentos, QList<QString> showExp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    allExp = experimentos;
    addExp = showExp;

    //rellenar lista de Exp. a mostrar
    for(int i = 0; i<addExp.size(); i++){
        ui->listWidget_2->addItem(addExp[i]);
    }

    //rellenar lista de Exp que no se mostraran
    for(int i = 0; i < allExp.size(); i++){
        if(!addExp.contains(allExp[i]))
        ui->listWidget->addItem(allExp[i]);
    }


}

QList<QString> Dialog::getList()
{
    return(addExp);
}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_pushButton_clicked()
{
    if(ui->listWidget->currentItem()){
        //agregar a add
        addExp.append(ui->listWidget->currentItem()->text());
        //agregar a lista add
        ui->listWidget_2->addItem(ui->listWidget->currentItem()->text());
        //borrar acá
        ui->listWidget->takeItem(ui->listWidget->currentRow());
    }
}

void Dialog::on_pushButton_2_clicked()
{
    if(ui->listWidget_2->currentItem()){
        //remover de add
        addExp.removeOne(ui->listWidget_2->currentItem()->text());
        //agregar a lista sub
        ui->listWidget->addItem(ui->listWidget_2->currentItem()->text());
        //borrar acá
        ui->listWidget_2->takeItem(ui->listWidget_2->currentRow());
    }
}

void Dialog::on_pushButton_3_clicked()
{
    //vaciar add
    addExp.clear();
    //vaciar addList
    ui->listWidget_2->clear();
    //llenar subL (sacar de ALL o ir pasando 1 por 1)
    ui->listWidget->clear();
    ui->listWidget->addItems(allExp);
}

void Dialog::on_pushButton_4_clicked()
{
    // add = all
    addExp = allExp;
    //vaciar subList
    ui->listWidget->clear();
    //llenar add (sacar de ALL o 1 por 1)
    ui->listWidget_2->clear();
    ui->listWidget_2->addItems(allExp);

}

void Dialog::on_pushButton_5_clicked()
{
    done(1);
}

void Dialog::on_pushButton_6_clicked()
{
    done(0);
}


