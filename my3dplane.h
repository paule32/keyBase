#ifndef PLANEENTITY_H
#define PLANEENTITY_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DExtras/QPlaneMesh>
#include <QMesh>

class My3Dplane : public Qt3DCore::QEntity
{
public:
    My3Dplane(Qt3DCore::QNode *parent = 0);
    ~My3Dplane();

    Qt3DExtras::QPlaneMesh *mesh() const;

private:
    Qt3DExtras::QPlaneMesh *m_mesh;
    Qt3DCore::QTransform *m_transform;
};

#endif // PLANEENTITY_H
