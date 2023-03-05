import sys
from PyQt5 import QtCore, QtGui, QtWidgets

def windowsShow(argv):
    app = QtWidgets.QApplication(argv)
    widgetHello = QtWidgets.QWidget()
    widgetHello.resize(800,600)
    widgetHello.setWindowTitle("hello world")

    labHello = QtWidgets.QLabel(widgetHello)
    labHello.setText("hello PyQt5")


    font = QtGui.QFont()
    font.setPointSize(12)
    font.setBold(True)

    labHello.setFont(font)
    size = labHello.sizeHint()
    labHello.setGeometry(200, 200, size.width(), size.height())

    widgetHello.show()

    sys.exit(app.exec_())