import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

ApplicationWindow 
{
   id : applicationWindow
   visible: true
   width: 1000
   height: 800
   title: qsTr("Trading Platform Template")

   menuBar:MenuBar
   {
      Menu 
      {
         title: qsTr("&File")
         MenuItem { 
            text: qsTr("&Quit") 
            onTriggered: mainViewModel.quit();
         }
      }
      Menu
      {
         title: qsTr("&View")
         Menu 
         {
            title: qsTr("&New") 
            MenuItem
            {
               text : "Live Market Data"
               onTriggered: {console.log("LIVE");}
            }
         }
      }
      Menu {
         title: qsTr("&Help")
         MenuItem 
         { 
            text: qsTr("&About")
            onTriggered: {aboutWindow.open()}
         }
      }
   }

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
            enabled: mainViewModel.isConnected
            onClicked: { mainViewModel.disconnect(); }
         }
      }
   }
   
   AboutWindow
   {
      id : aboutWindow
      visible : false
   }
}
