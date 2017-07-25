#include "my3dplane.h"

#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DCore/QTransform>

My3Dplane::My3Dplane(Qt3DCore::QNode *parent)
    : Qt3DCore::QEntity(new Qt3DCore::QEntity(parent))
    , m_mesh(new Qt3DExtras::QPlaneMesh())
    , m_transform(new Qt3DCore::QTransform())
{
    addComponent(m_mesh);
    addComponent(m_transform);
}

My3Dplane::~My3Dplane()
{
}

Qt3DExtras::QPlaneMesh *My3Dplane::mesh() const
{
    return m_mesh;
}

