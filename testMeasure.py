import sys
import socket
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QLabel, QVBoxLayout, QHBoxLayout, QLineEdit, QPushButton
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt
#from PyQt5.QtChart import QChart, QChartView, QLineSeries
from PyQt5.QtPrintSupport import QPrinter
from PyQt5 import QtCore

# Constant values
# Temporary since the test device has not been set up with this yet
DEVICE_IP = '192.168.0.100'
DEVICE_PORT = 5000 

class TestApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Test App")
        self.resize(800, 600)