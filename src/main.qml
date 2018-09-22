import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11

Window 
{
   id : applicationWindow
   visible: true
   width: 1000
   height: 800
   title: qsTr("Trading Platform Template")

   ToolBar
   {
      id: mainToolbar
      RowLayout 
      {
         id : toolBarRowLayout
         Rectangle
         {
            id: connectionStatus
            width : 20;
            height : 20;
            color : mainViewModel.isConnected ? "green" : "red"
         }
         Button 
         {
            id : connectButton
            text : "Connect"
            enabled: !mainViewModel.isConnected
            onClicked: { mainViewModel.connect(); }
         }
         Button 
         {
            id : disconnectButton
            text : "Disconnect"
            anchors.right : parent.right
            enabled: mainViewModel.isConnected
            onClicked: { mainViewModel.disconnect(); }
         }
      }
   }  
}
