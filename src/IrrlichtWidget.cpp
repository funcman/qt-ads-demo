#include "IrrlichtWidget.h"
#include <QResizeEvent>

IrrlichtWidget::IrrlichtWidget(QWidget* parent): QWidget(parent) {
    irr::video::E_DRIVER_TYPE driverType = irr::video::EDT_OPENGL;

    irr::SIrrlichtCreationParameters params;
    params.DriverType = driverType;
    params.WindowId = (void*)winId();
    params.WindowSize.Width = geometry().size().width();
    params.WindowSize.Height = geometry().size().height();
    device_ = irr::createDeviceEx(params);

    setAttribute(Qt::WA_OpaquePaintEvent);

    device_->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));
    device_->getGUIEnvironment()->addStaticText(L"Hello Qt and Irrlicht.", irr::core::rect<irr::s32>(10,10,100,22), true);

    QObject::connect(&timer_, &QTimer::timeout, [this](){
        emit inIrrlichtEventLoop();
        device_->run();
        irr::video::IVideoDriver* driver = device_->getVideoDriver();
        driver->beginScene(true, true, irr::video::SColor(255,100,101,140));
        device_->getSceneManager()->drawAll();
        device_->getGUIEnvironment()->drawAll();
        driver->endScene();
    });
    timer_.setInterval(100);
    timer_.start();
}

void IrrlichtWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    if (device_ != nullptr) {
        irr::core::dimension2d<uint> size;
        size.Width = event->size().width();
        size.Height = event->size().height();
        device_->getVideoDriver()->OnResize(size);
    }
}