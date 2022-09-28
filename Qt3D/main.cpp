#include "mainwindow.h"

#include <QApplication>
#include <Qt3DCore/QTransform>>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QDirectionalLight>
#include <Qt3dExtras/Qt3DWindow>
#include <Qt3dExtras/QTorusMesh>
#include <Qt3dExtras/QOrbitCameraController>
#include <Qt3dExtras/QPhongMaterial>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Qt3DExtras::Qt3DWindow view;
    Qt3DCore::QEntity* scene = new Qt3DCore::QEntity;
    Qt3DRender::QMaterial* material = new Qt3DExtras::QPhongMaterial(scene);
    Qt3DExtras::QTorusMesh* mesh = new Qt3DExtras::QTorusMesh;
    mesh -> setRadius(5);
    mesh -> setMinorRadius(1);
    mesh -> setRings(100);
    mesh -> setSlices(20);

    Qt3DCore::QTransform* transform = new Qt3DCore::QTransform;
    transform -> setRotation(QQuaternion::fromAxisAndAngle(QVector3D(1,0,0),45.f));

    Qt3DCore::QEntity* torus = new Qt3DCore::QEntity(scene);
    torus -> addComponent(mesh);
    torus -> addComponent(transform);
    torus -> addComponent(material);

    Qt3DRender :: QDirectionalLight *light = new Qt3DRender :: QDirectionalLight();
    light -> setColor(Qt::cyan);
    light -> setIntensity(1.0f);
    light -> setWorldDirection(QVector3D(0.0f, -0.5f, 1.0f));
    scene -> addComponent(light);

    Qt3DRender::QCamera *camera =view.camera();
    camera -> lens() -> setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera -> setPosition(QVector3D(0,0,40.0f));
    camera -> setViewCenter(QVector3D(0, 0, 0));

    Qt3DExtras::QOrbitCameraController * manipulator = new Qt3DExtras::QOrbitCameraController(scene);
    manipulator -> setLinearSpeed(50.f);
    manipulator -> setLookSpeed(180.f);
    manipulator -> setCamera(camera);

    view.setRootEntity(scene);
    view.show();

    return a.exec();
}
