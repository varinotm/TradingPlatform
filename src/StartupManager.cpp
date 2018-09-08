#include "StartupManager.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QFile>
#include <QDirIterator>
#include <qDebug>

#include <iostream>

StartupManager::StartupManager(int argc, char *argv[])
{
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

   QGuiApplication app(argc, argv);

   QDirIterator it(":", QDirIterator::Subdirectories);
   while (it.hasNext())
   {
      qDebug() << it.next();
   }

   QQmlApplicationEngine engine;
   std::cout << QFile::exists("qrc:/main.qml") << std::endl;
   engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

   app.exec();
}
