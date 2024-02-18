#ifndef IRRLICHTWIDGET_H
#define IRRLICHTWIDGET_H

#include <QWidget>
#include <QTimer>

#include "irrlicht.h"

class IrrlichtWidget : public QWidget{
    Q_OBJECT

public:
    IrrlichtWidget(QWidget* parent);

    ~IrrlichtWidget(){
        device_->drop();
    }

    void resizeEvent(QResizeEvent* event);

    bool paused() const{
        return timer_.signalsBlocked();
    }

    irr::IrrlichtDevice* getIrrlichtDevice() const{
        return device_;
    }

public slots:
    void setPaused(bool paused){
        timer_.blockSignals(paused);
    }

    void pause(){
        setPaused(true);
    }

    void resume(){
        setPaused(false);
    }

signals:
    void inIrrlichtEventLoop();

private:
    irr::IrrlichtDevice* device_;
    QTimer timer_;
};

#endif//IRRLICHTWIDGET_H