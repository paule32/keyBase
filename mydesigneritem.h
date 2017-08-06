#ifndef MYDESIGNERITEM_H
#define MYDESIGNERITEM_H

#include <QString>
#include <QGraphicsItem>

#include "mydesignercornergrabber.h"
#include "mydesignerscene.h"

class MyDesignerItem: public QGraphicsItem
{
public:
    explicit MyDesignerItem(QRect rect, MyDesignerScene *p);
protected:
    void mouseMoveEvent    (QGraphicsSceneMouseEvent* event);
    void mousePressEvent   (QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent (QGraphicsSceneMouseEvent* event);
private:
    QRectF boundingRect() const;

    void mouseMoveEvent (QGraphicsSceneDragDropEvent *event);
    void mousePressEvent(QGraphicsSceneDragDropEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w);

    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
    void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );

    void setCornerPositions();
    void adjustSize(int x, int y);

    QPointF mLastMousePosition;

    bool mMoving;
    bool sceneEventFilter(QGraphicsItem *watched, QEvent * event);

protected:
    QColor _outterborderColor; ///< the hover event handlers will toggle this between red and black
    QPen   _outterborderPen; ///< the pen is used to paint the red/black border

    QPointF _location;
    QPointF _dragStart;
    int     _gridSpace;
    qreal   _width;
    qreal   _height;

    QPointF _cornerDragStart;

    int _XcornerGrabBuffer;
    int _YcornerGrabBuffer;

    qreal   _drawingWidth;
    qreal   _drawingHeight;
    qreal   _drawingOrigenX;
    qreal   _drawingOrigenY;

    class QWidget       * _widget;
    class QPixmap         _pixmap;

    class MyDesignerCornerGrabber * _corners[4];
    class QGraphicsItem * current_item;
};

class DesignerPushButtonItem: public MyDesignerItem { public: explicit
      DesignerPushButtonItem(QString caption, QRect rect, MyDesignerScene *p);};

class DesignerRadioButtonItem: public MyDesignerItem { public: explicit
      DesignerRadioButtonItem(QString caption, QRect rect, MyDesignerScene *p);};

class DesignerLabelItem:       public MyDesignerItem { public: explicit
      DesignerLabelItem        (QString caption, QRect rect, MyDesignerScene *p);};

class DesignerGroupBoxItem:    public MyDesignerItem { public: explicit
      DesignerGroupBoxItem     (QString caption, QRect rect, MyDesignerScene *p);};


class DesignerSymbol_Addition: public MyDesignerItem { public: explicit
      DesignerSymbol_Addition  (QString image, QRect rect, MyDesignerScene *s); };


#endif // MYDESIGNERITEM_H
