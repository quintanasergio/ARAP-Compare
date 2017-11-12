#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "barrac.h"
#include "dialog.h"
#include <QDirIterator>
#include <QPainter>
#include <QDebug>
#include <QGraphicsTextItem>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ARAP Compare");

    //dirección de instalación de arap
    dirarap = "/home/sergio/Documentos/simulador-arap-v1.0-master/arap-dir/Experiments";

    QString aux;
    QDirIterator it(dirarap, QStringList() << "*.txt", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()){
        aux = it.next();
        aux = aux.split('/').last();
        aux.remove(".txt");
        experimentos.append(aux);
        showExp.append(aux);
        ui->listWidget->addItem(aux);
    }


    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing);
    ui->graphicsView->setFixedSize(600,400);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(0, 0, 600, 400);

    medvarcalculation();
    redraw();



}

void MainWindow::redraw()
{
    scene->clear();

    int maxx =500; //Tamaño máximo en X del histograma
    int maxy =300; //Tamaño máximo en Y del histograma
    float max =0; //Máximo valor entre los RTT

    scene->addLine(50,40,50,maxy);
    scene->addLine(50,maxy,maxx+10,maxy);

    QGraphicsTextItem *text1 = scene->addText("RTT(seg)");
    text1->setPos(20,20);//posicion del texto

    //Cantidad de experimentos en total
    int cantExp = rttMediaExp.size();
    //Cantidad de experimentos a mostrar
    int cantShow = showExp.size();


    //Elije el máximo valor de RTT dentro de histo
    for(int i=0;i<cantExp;i++){
        if(max<rttMediaExp[i]&&showExp.contains(experimentos[i])){
            max = rttMediaExp[i];
           }
    }

    QString maxs = QString::number(max);
    maxs.truncate(5);
    QGraphicsTextItem *textmax = scene->addText(maxs);
    textmax->setPos(5,40);//posicion del texto
    QGraphicsTextItem *textcero = scene->addText("0.0");
    textcero->setPos(15,maxy-20);//posicion del texto


    if(cantShow!=0){

    int maxw = maxx - 50 - ((maxx-50)%cantShow);

    //creación de las barras del histograma
    QList<float> rttShow;

        for(int i = 0; i<cantShow; i++){
            int num = experimentos.indexOf(showExp[i]);
            rttShow.append(rttMediaExp[num]);
        }

        for(int i =0; i<cantShow; i++){
            barraC * bar = new barraC((maxw)/cantShow, ((maxy-50)*rttShow[i])/max);
            scene->addItem(bar);
            bar->setPos(50+(i)*(maxw)/cantShow, maxy-((maxy-50)*rttShow[i])/max);
            bar->setDir(showExp[i]);

            if(ui->comboBox->currentIndex()==0){
                QGraphicsTextItem *text2 = scene->addText("Experimentos");
                text2->setPos(maxx+10,maxy);
            } else if(ui->comboBox->currentIndex()==1){
                QGraphicsTextItem *text2 = scene->addText("Cantidad \nNodos");
                text2->setPos(maxx+10,maxy);
                //dibujo de variables abajo de cada barra
                QGraphicsTextItem *valor = scene->addText(QString::number(par[i].val));
                valor->setPos(50+(i)*(maxw)/cantShow,maxy+5);
            } else if(ui->comboBox->currentIndex()==2){
                QGraphicsTextItem *text2 = scene->addText("Tamaño \nHormigas");
                text2->setPos(maxx+10,maxy);
                //dibujo de variables abajo de cada barra
                QGraphicsTextItem *valor = scene->addText(QString::number(par[i].val));
                valor->setPos(50+(i)*(maxw)/cantShow,maxy+5);
            } else if(ui->comboBox->currentIndex()==3){
                QGraphicsTextItem *text2 = scene->addText("Exploradoras");
                text2->setPos(maxx+10,maxy);
                //dibujo de variables abajo de cada barra
                QGraphicsTextItem *valor = scene->addText(QString::number(par[i].val));
                valor->setPos(50+(i)*(maxw)/cantShow,maxy+5);
            } else if(ui->comboBox->currentIndex()==4){
                QGraphicsTextItem *text2 = scene->addText("Intervalo \nEnvío \nExploradoras");
                text2->setPos(maxx+10,maxy);
                //dibujo de variables abajo de cada barra
                QGraphicsTextItem *valor = scene->addText(QString::number(par[i].val));
                valor->setPos(50+(i)*(maxw)/cantShow,maxy+5);
            } else if(ui->comboBox->currentIndex()==5){
                QGraphicsTextItem *text2 = scene->addText("# Saltos");
                text2->setPos(maxx+10,maxy);
                //dibujo de variables abajo de cada barra
                QGraphicsTextItem *valor = scene->addText(QString::number(par[i].val));
                valor->setPos(50+(i)*(maxw)/cantShow,maxy+5);
            } else if(ui->comboBox->currentIndex()==6){
                QGraphicsTextItem *text2 = scene->addText("Tamaño \nmáximo \nsegmento");
                text2->setPos(maxx+10,maxy);
                //dibujo de variables abajo de cada barra
                QGraphicsTextItem *valor = scene->addText(QString::number(par[i].val));
                valor->setPos(50+(i)*(maxw)/cantShow,maxy+5);
            } else if(ui->comboBox->currentIndex()==7){
                QGraphicsTextItem *text2 = scene->addText("Tamaño \nCola");
                text2->setPos(maxx+10,maxy);
                //dibujo de variables abajo de cada barra
                QGraphicsTextItem *valor = scene->addText(QString::number(par[i].val));
                valor->setPos(50+(i)*(maxw)/cantShow,maxy+5);
            } else if(ui->comboBox->currentIndex()==8){
                QGraphicsTextItem *text2 = scene->addText("Tiempo \nSimulación");
                text2->setPos(maxx+10,maxy);
                //dibujo de variables abajo de cada barra
                QGraphicsTextItem *valor = scene->addText(QString::number(par[i].val));
                valor->setPos(50+(i)*(maxw)/cantShow,maxy+5);
            } else if(ui->comboBox->currentIndex()==9){
                QGraphicsTextItem *text2 = scene->addText("Path \nManager");
                text2->setPos(maxx+10,maxy);
                //dibujo de variables abajo de cada barra
                QGraphicsTextItem *valor = scene->addText(par2[i].val);
                valor->setRotation(90);
                valor->setPos(70+(i)*(maxw)/cantShow,maxy+5);
            }

        }

    }









}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::medvarcalculation()
{


    for(int i=0; i < experimentos.size(); i++){
        QString dirExp = dirarap + "/" + experimentos[i] + "/load-ants-model";

        QString aux;
        QList<float> rtt;

        QDirIterator it(dirExp, QStringList() << "*.csv", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()){
            aux = it.next();
            QFile file(aux);
            if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
                qDebug() << "El archivo no existe";
            } else {
                // Create a thread to retrieve data from a file
                QTextStream in(&file);
                //Reads the data up to the end of file
                while (!in.atEnd())
                {
                    QString line = in.readLine();
                    // Adding to the model in line with the elements
                    if(line.contains("Media de las medias de los tiempos")){
                        rtt.append(line.split(',').last().toFloat());
                    }
                }
                file.close();
            }
        }

        qreal media = 0;

        for(int j=0 ; j<rtt.size() ; j++){
            media+=rtt[j];
        }

        media = media/rtt.size();
        rttMediaExp.append(media);

        qreal varianza =0;

        for(int j = 0; j < rtt.size(); j++){
            varianza+=((rtt[j]-(media))*(rtt[j]-(media)));
        }

        if(rtt.size()==1){
        varianza = 0;
        }else{
        varianza = varianza/(rtt.size()-1);
        }
        rttVarianzaExp.append(varianza);



    }
}

void MainWindow::on_pushButton_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    Dialog editexp(experimentos, showExp, this);
    editexp.exec();

    if (editexp.result() == 1)
      {
        showExp = editexp.getList();
        ui->listWidget->clear();
        for(int i =0; i < showExp.size(); i++){
            ui->listWidget->addItem(showExp[i]);
        }
        redraw();
      }
}

QList<QString> MainWindow::getShowExp() const
{
    return showExp;
}

QList<QString> MainWindow::getExperimentos() const
{
    return experimentos;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{

    //caso de orden standard
    if(index==0){
        //cambiar orden Showexp
        qSort(showExp.begin(), showExp.end());
        //rellena la lista widget
        ui->listWidget->clear();
        for(int i =0; i < showExp.size(); i++){
            ui->listWidget->addItem(showExp[i]);
        }
        //llama al redibujado
        redraw();
        return;
    }

    //cualquier otro caso

    par.clear();
    par2.clear();



    for(int i=0; i<showExp.size(); i++){
        QString aux = dirarap + "/" + showExp[i] + "/" +showExp[i] + ".txt";
        QFile file(aux);
        if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            qDebug() << "El archivo no existe";
        } else {
            // Create a thread to retrieve data from a file
            QTextStream in(&file);
            //Reads the data up to the end of file
            while (!in.atEnd())
            {
                QString line = in.readLine();
                // Selecciono la variable
                if(index==1){
                    if(line.contains("nodos")&& !line.contains("#")){
                        par.push_back(Elem(i,line.split(' ').last().toInt()));
                    }
                } else if(index == 2){
                    if(line.contains("tamanio-hormiga")&& !line.contains("#")){
                        par.push_back(Elem(i,line.split(' ').last().toInt()));
                    }
                } else if(index == 3){
                    if(line.contains("habilitar-exploradoras")&& !line.contains("#")){
                        par.push_back(Elem(i,line.split(' ').last().toInt()));
                    }

                } else if(index == 4){
                    if(line.contains("intervalo-exploradoras")&& !line.contains("#")){
                        par.push_back(Elem(i,line.split(' ').last().toInt()));
                    }

                } else if(index == 5){
                    if(line.contains("saltos")&& !line.contains("#")){
                        par.push_back(Elem(i,line.split(' ').last().toInt()));
                    }

                } else if(index == 6){
                    if(line.contains("tamanio-segmento")&& !line.contains("#")){
                        par.push_back(Elem(i,line.split(' ').last().toInt()));
                    }

                } else if(index == 7){
                    if(line.contains("tamanio-cola")&& !line.contains("#")){
                        par.push_back(Elem(i,line.split(' ').last().toInt()));
                    }

                } else if(index == 8){
                    if(line.contains("tiempo-detener-simulador")&& !line.contains("#")){
                        par.push_back(Elem(i,line.split(' ').last().toInt()));
                    }

                } else if(index == 9){
                    if(line.contains("path-manager")&& !line.contains("#")){
                        par2.push_back(ElemS(i,line.split(' ').at(1)));
                    }

                }
            }
            file.close();
        }
    }

    //caso especial pathmanager
    if(index==9){
        qStableSort(par2.begin(), par2.end(), myLessThanS);
        QList<QString> sorted;
        for(int i=0;i<showExp.size();++i){
        sorted.push_back(showExp.at(par2.at(i).pos));
        }
        showExp = sorted;
        //rellena la lista widget
        ui->listWidget->clear();
        for(int i =0; i < showExp.size(); i++){
            ui->listWidget->addItem(showExp[i]);
        }
        redraw();
        return;
    }

    qStableSort(par.begin(), par.end(), myLessThan);
    QList<QString> sorted;
    for(int i=0;i<showExp.size();++i){
    sorted.push_back(showExp.at(par.at(i).pos));
    }

    showExp = sorted;

    //rellena la lista widget
    ui->listWidget->clear();
    for(int i =0; i < showExp.size(); i++){
        ui->listWidget->addItem(showExp[i]);
    }
    //llama al redibujado
    redraw();    

}

bool MainWindow::myLessThan(const Elem& e1, const Elem& e2){
return (e1.val < e2.val);
}

bool MainWindow::myLessThanS(const ElemS& e1, const ElemS& e2){
return (e1.val < e2.val);
}
