#ifndef MYDESIGNERSCENE_H
#define MYDESIGNERSCENE_H

#include <QGraphicsScene>

class MyDesignerScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyDesignerScene(QObject *parent = 0);
    int getGridSize() const { return this->gridSize; }
protected:
    void drawBackground(QPainter *painter, QRectF &rect);
private:
    int gridSize;
};

#endif // MYDESIGNERSCENE_H
