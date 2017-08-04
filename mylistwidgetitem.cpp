#include "mylistwidgetitem.h"

MyListWidgetItem::MyListWidgetItem(QListWidget * parent, QString name, QString icon_res, int mode)
    : QListWidgetItem(parent)
{
    QFont font("Helvetia");
    font.setBold(false);
    font.setWeight(75);

    setText(name);
    setFont(font);

    if (mode > 0)
    {
        QBrush brush(QColor(225, 223, 173, 255));
        brush.setStyle(Qt::SolidPattern);

        font.setBold(true);

        setBackground(brush);
        setTextAlignment(Qt::AlignCenter);
        setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    }

    if (icon_res.size() > 0) {
        QIcon icon;
        icon.addFile(icon_res, QSize(), QIcon::Normal, QIcon::Off);
        setIcon(icon);
    }

    parent->addItem(this);
}
