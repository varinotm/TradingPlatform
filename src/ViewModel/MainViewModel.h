#pragma once

#include "Model/MainModel.h"

#include <QObject>
#include <qqmlapplicationengine.h>
#include <memory>


class MainViewModel : QObject
{
   Q_OBJECT

      Q_PROPERTY(bool isConnected
                 READ isConnected
                 NOTIFY connectionChanged)

public:

   /// Constructor 
   /// \param[in] parent the parent qt object
   MainViewModel(QObject* parent = nullptr);

   /// destructor
   ~MainViewModel() = default;


   /// QML functions

   /// Connect the client to the API
   Q_INVOKABLE void connect();

Q_SIGNALS:
   /// Signal linked to the isConnected property
   void connectionChanged();

private:
   /// QML getter for the isConnected property
   bool isConnected() const;

   /// the main model
   std::unique_ptr<MainModel> mMainModel;

   /// The qml engine
   QQmlApplicationEngine mQmlEngine;
};