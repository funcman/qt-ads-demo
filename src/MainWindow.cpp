#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "IrrlichtWidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow) {
    ui->setupUi(this);

    dockManager_ = new ads::CDockManager(this);

    IrrlichtWidget* irrWidget = new IrrlichtWidget(this);
    ads::CDockWidget* DockWidget = new ads::CDockWidget("Irrlicht Widget");
    DockWidget->setWidget(irrWidget);

    ui->menuView->addAction(DockWidget->toggleViewAction());

    dockManager_->addDockWidget(ads::TopDockWidgetArea, DockWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}