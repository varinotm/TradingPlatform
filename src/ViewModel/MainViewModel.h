#pragma once

#include "Model/MainModel.h"

#include <QObject>

#include <memory>


class MainViewModel : QObject
{
public:

   /// Constructor 
   /// \param[in] parent the parent qt object
   MainViewModel(QObject* parent = nullptr);

   /// destructor
   ~MainViewModel() = default;

private:
   std::unique_ptr<MainModel> mModel;
};