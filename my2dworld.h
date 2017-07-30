#ifndef MY2DWORLD_H
#define MY2DWORLD_H

#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QPolygon>
#include <QVector>

class my2dworld: public QWidget
{
public:
    my2dworld(QWidget *parent);
    my2dworld();

    void drawBoard();
    QPolygon setupPoly(int x, int y);
    int getTile(QPoint pt);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    QVector<QPolygon> pixies;
    int poly;

    int m_xpos;
    int m_ypos;

    int tile_no;
    int tile_width;
    int tile_height;

    int ymap;
    int xmap;

    int level_xt;
    int level_yt;
};

#endif // MY2DWORLD_H
