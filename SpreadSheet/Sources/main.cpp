#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <thread>
#include <chrono>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow;
    QPixmap pixmap(":/icons/icons/PixmapforMain.jpg");
    QSplashScreen *splash = new QSplashScreen(pixmap.scaled(mainWindow->width(), mainWindow->height()));
    splash->show();
    QPropertyAnimation *animation;

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;

    splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::white);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    splash->showMessage(QObject::tr("Loading modules..."), topRight, Qt::white);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    splash->showMessage(QObject::tr("Making connections..."), topRight, Qt::white);
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    splash->finish(mainWindow);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    animation = new QPropertyAnimation(mainWindow, "windowOpacity");
    animation->setDuration(1000); // Длительность анимации в миллисекундах
    animation->setStartValue(0); // Начальное значение прозрачности окна
    animation->setEndValue(1); // Конечное значение прозрачности окна
    animation->start();
    mainWindow->show();

    delete splash;
    return app.exec();
}
