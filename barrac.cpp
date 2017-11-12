#include "barrac.h"
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

barraC::barraC(float w, float h)
{
    width = w;
    height = h;
    mousehover = false;

    setAcceptHoverEvents(true);
    setToolTip("Presione la barra para ver carpeta de Experimento");

}

QRectF barraC::boundingRect() const
{
    return QRectF(0,0,width,height);
}

void barraC::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

        QPen pen(Qt::black);
        QBrush brush(QColor(44,91,119));

        if(mousehover==true){ brush.setColor(QColor(17,152,174)); }

        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawRect(rect);


}

bool barraC::setDir(QString dir)
{
    name = dir;
    dirExp = "file:///home/sergio/Documentos/simulador-arap-v1.0-master/arap-dir/Experiments/" + dir;
}

void barraC::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    mousehover = true;
    QGraphicsItem::hoverEnterEvent(event);

}

void barraC::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    mousehover = false;
    QGraphicsItem::hoverLeaveEvent(event);

}

void barraC::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
    QDesktopServices::openUrl(QUrl(dirExp, QUrl::TolerantMode));
}
