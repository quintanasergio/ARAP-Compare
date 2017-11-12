#ifndef BARRAC_H
#define BARRAC_H
#include <QPainter>
#include <QGraphicsItem>

class barraC :public QGraphicsItem
{
public:
    barraC(float w, float h);
    QRectF boundingRect() const;
    //Override paint
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int width;
    int height;
    int numexe;
    float rtt;
    QString dirmodel;
    bool mousehover;
    bool setDir(QString dir);
    QString name;

protected:

  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
  void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
  QString dirExp;


};

#endif // BARRAC_H
