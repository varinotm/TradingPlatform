#pragma once

#include <boost/signals2.hpp>

#include <memory>

class IBWrapper;

class MainModel
{
public:
   /// Constructor
   MainModel();

   /// Destructor
   ~MainModel() = default;

   /// Connect to the ib api client
   void Connect();

   /// Disconnect from the ib api client
   void Disconnect();

   /// get the connection status
   /// \return true if connected, else false
   bool IsConnected() const;

   /// Signal emitted when the instrument set changed
   boost::signals2::signal<void()> ConnectionStatusChanged;

private:
   std::shared_ptr<IBWrapper> mIBWrapper;
};