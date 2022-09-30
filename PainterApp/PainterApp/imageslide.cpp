#include <QDir>
#include <QQuickItem>
#include <QQmlContext>
#include <QFileInfo>

#include "imageslide.h"
#include "dataelement.h"

ImageSlide::ImageSlide(QWidget *parent) : QQuickWidget(parent)
{
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

    resize(width(), 100);
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    setContentsMargins(50, 50, 50, 50);

    reloadImages();
    setSource(QUrl::fromLocalFile(":/ImageSlide.qml"));
}

void ImageSlide::reloadImages()
{
    QDir dir(".");
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.bmp";
    QFileInfoList fileInfoList = dir.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);

    QList<QObject*> dataList;
    for(int i = 0; i < fileInfoList.count(); i++) {
        dataList.append(new DataElement(fileInfoList.at(i).absoluteFilePath(), fileInfoList.at(i).baseName()));
    };

    QQmlContext *ctxt = rootContext();
    ctxt->setContextProperty("dataModel", QVariant::fromValue(dataList));

    QObject *object = rootObject();
    if(object)
        QObject::connect(object, SIGNAL(itemSelected(QString)), SLOT(selectItem(QString)));
}

#if 0
void ImageSlide::resizeEvent(QResizeEvent*)
{
    QQuickItem* rootQml = rootObject();
    rootQml->setProperty("width", size().width());
    rootQml->setProperty("height", size().height());
}
#endif

void ImageSlide::selectItem(const QString &str)
{
    qDebug() << str;
    emit itemSelected(str);
}

void ImageSlide::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->angleDelta().y() / 8;

    QQuickItem* object = rootObject();
    QVariant returnedValue;
    if(numDegrees > 0) {
        QMetaObject::invokeMethod(object, "decrementCurrentIndex",
                                  Q_RETURN_ARG(QVariant, returnedValue));
    } else if(numDegrees < 0) {
        QMetaObject::invokeMethod(object, "incrementCurrentIndex",
                                  Q_RETURN_ARG(QVariant, returnedValue));
    }
}

