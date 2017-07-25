#include <Qt3DCore/QEntity>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QCamera>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QTextureImage>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <Qt3DExtras/QNormalDiffuseSpecularMapMaterial>

#include "dreidworld.h"
#include "my3dplane.h"

extern Qt3DExtras::Qt3DWindow *view;
dreidworld::dreidworld()
{
    Qt3DCore::QEntity *sceneRoot = new Qt3DCore::QEntity();

    // Scene Camera
    Qt3DRender::QCamera *basicCamera = view->camera();
    basicCamera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    basicCamera->setAspectRatio(view->width() / view->height());
    basicCamera->setUpVector  (QVector3D(0.0f, 1.0f, 0.0f));
    basicCamera->setViewCenter(QVector3D(0.0f, 3.5f, 0.0f));
    basicCamera->setPosition  (QVector3D(0.0f, 3.5f, 25.0f));
    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(sceneRoot);
    camController->setCamera(basicCamera);

    // Scene floor
    My3Dplane *planeEntity = new My3Dplane(sceneRoot);
    planeEntity->mesh()->setHeight(100.0f);
    planeEntity->mesh()->setWidth(100.0f);
    planeEntity->mesh()->setMeshResolution(QSize(20, 20));

    Qt3DExtras::QNormalDiffuseSpecularMapMaterial *normalDiffuseSpecularMapMaterial = new Qt3DExtras::QNormalDiffuseSpecularMapMaterial();
    normalDiffuseSpecularMapMaterial->setTextureScale(10.0f);
    normalDiffuseSpecularMapMaterial->setShininess(80.0f);
    normalDiffuseSpecularMapMaterial->setAmbient(QColor::fromRgbF(0.2f, 0.2f, 0.2f, 1.0f));

    Qt3DRender::QTextureImage *diffuseImage = new Qt3DRender::QTextureImage();
    diffuseImage->setSource(QUrl(QStringLiteral("qrc:/textures/diffuse.webp")));
    normalDiffuseSpecularMapMaterial->diffuse()->addTextureImage(diffuseImage);

    Qt3DRender::QTextureImage *specularImage = new Qt3DRender::QTextureImage();
    specularImage->setSource(QUrl(QStringLiteral("qrc:/textures/specular.webp")));
    normalDiffuseSpecularMapMaterial->specular()->addTextureImage(specularImage);

    Qt3DRender::QTextureImage *normalImage = new Qt3DRender::QTextureImage();
    normalImage->setSource(QUrl((QStringLiteral("qrc:/textures/normal.webp"))));
    normalDiffuseSpecularMapMaterial->normal()->addTextureImage(normalImage);

    planeEntity->addComponent(normalDiffuseSpecularMapMaterial);


    view->setRootEntity(sceneRoot);
    view->show();
}

void dreidworld::setup()
{
}
