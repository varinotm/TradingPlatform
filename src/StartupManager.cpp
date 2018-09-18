#include "StartupManager.h"

#include <QGuiApplication>

StartupManager::StartupManager(int argc, char *argv[])
{
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

   QGuiApplication app(argc, argv);

   mMainViewModel = std::make_unique<MainViewModel>();

   app.exec();
}
