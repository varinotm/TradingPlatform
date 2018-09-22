import QtQuick.Controls 2.4
import QtQuick 2.11
import QtQuick.Layouts 1.11

Popup 
{
   id: aboutWindow
   x : (parent.width - width) / 2
   y: (parent.height - height) / 2
   width: 400
   height: 600
   modal: true
   focus: true
   closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

   ColumnLayout
   {
      anchors.centerIn : parent
      Image
      {
         
         fillMode: Image.PreserveAspectFit
         Layout.alignment: Qt.AlignHCenter
         source: "Images/Todo.png"
      }
      Text
      {
         text: "<b>Source Trader</b>"
         topPadding : 20
         bottomPadding : 10
         Layout.alignment: Qt.AlignHCenter
         font.pointSize: 24
      }
      Text
      {
         text: "An open source trading platform"
         topPadding : 10
         bottomPadding : 10
         Layout.alignment: Qt.AlignHCenter
         font.pointSize: 16
      }  
      Text
      {
         text: "Made by Mathias Varinot"
         font.pointSize: 12
         Layout.alignment: Qt.AlignHCenter
         color : "gray"
      } 
      Text
      {
         text: "QT 5.11"
         font.pointSize: 12
         Layout.alignment: Qt.AlignHCenter
         color : "gray"
      } 
      Text
      {
         text: "Interactive Broker API 9.73"
         font.pointSize: 12
         Layout.alignment: Qt.AlignHCenter
         bottomPadding : 10
         color : "gray"
      }
      Button
      {
         text : "close"
         Layout.alignment: Qt.AlignHCenter
         onClicked: {aboutWindow.close();}
      }
   }      
}
