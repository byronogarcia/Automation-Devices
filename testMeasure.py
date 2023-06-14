from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QLabel, QVBoxLayout, QHBoxLayout, QLineEdit, QPushButton)
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt, QDateTime
#from PyQt5.QtChart import QChart, QChartView, QLineSeries
from PyQt5.QtPrintSupport import QPrinter
from PyQt5 import QtCore

import sys
import socket

# Constant values
# Temporary since the test device has not been set up with this yet
DEVICE_IP = '192.168.0.100'
DEVICE_PORT = 5000 

class TestApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Test App")
        self.resize(800, 600)

        # Setting up widgets
        # Get IP address, will change with device
        self.ip_label = QLabel("Device IP: ")
        self.ip_input = QLineEdit()
        self.ip_input.setTest(DEVICE_IP)

        # device port
        self.port_label = QLabel("Device Port:")
        self.port_input = QLineEdit()
        self.port_input.setText(str(DEVICE_PORT))

        # test duration
        self.duration_label = QLabel("Test Duration (s):")
        self.duration_input = QLineEdit()

        # start test button
        self.start_button = QPushButton("Start Test")

        # stop test button
        self.stop_button = QPushButton("Stop Test")
        self.stop_button.setEnabled(False)


        # Laying it out on our pyqt5 app
        