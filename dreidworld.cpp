#include <Qt3DCore/QEntity>
#include <Qt3DCore/QAspectEngine>
#include <Qt3DRender/QCamera>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QTextureImage>
#include <Qt3DRender/QMesh>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <Qt3DExtras/QNormalDiffuseSpecularMapMaterial>

#include "dreidworld.h"
#include "my3dplane.h"

dreidworld::dreidworld()
{
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow;
    Qt3DCore::QEntity *sceneRoot = new Qt3DCore::QEntity();

    // Scene Camera
    Qt3DRender::QCamera *basicCamera = view->camera();
    basicCamera->setProjectionType(Qt3DRender::QCameraLens::PerspectiveProjection);
    //basicCamera->setAspectRatio(view->width() / view->height());
    //basicCamera->setUpVector  (QVector3D(0.0f, 1.0f, 0.0f));
    //basicCamera->setViewCenter(QVector3D(-1.0f, -1.5f, -1.0f));

    basicCamera->setPosition  (QVector3D(-2.0f, 0.0f, 0.0f));

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new
    Qt3DExtras::QFirstPersonCameraController(sceneRoot);
    camController->setCamera(basicCamera);

    Qt3DRender::QMesh *logo = new Qt3DRender::QMesh(sceneRoot);
    logo->setSource(QUrl::fromLocalFile("./test.obj"));
    Qt3DCore::QTransform *logo_transform = new Qt3DCore::QTransform();
    logo_transform->setScale(0.1f);
    logo_transform->setTranslation(QVector3D(2.0f,0.0f,0.0f));
    Qt3DExtras::QPhongMaterial *logo_material = new Qt3DExtras::QPhongMaterial();
    logo_material->setDiffuse(QColor(Qt::yellow));

    Qt3DCore::QEntity *plane_Entity = new Qt3DCore::QEntity(sceneRoot);
    plane_Entity->addComponent(logo);
    plane_Entity->addComponent(logo_material);
    plane_Entity->addComponent(logo_transform);


    view->setRootEntity(sceneRoot);
    view->show();
}

void dreidworld::setup()
{
}
