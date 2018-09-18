import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11

Window 
{
   id : applicationWindow
   visible: true
   width: 640
   height: 480
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
            anchors.right : applicationWindow.right
            onClicked: { mainViewModel.connect(); }
         }
      }
   }  
}
