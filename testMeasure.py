from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QLabel, QVBoxLayout, QHBoxLayout, QLineEdit, QPushButton)
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt, QDateTime
from PyQt5.QtChart import QChart, QChartView, QLineSeries
from PyQt5.QtPrintSupport import QPrinter
from PyQt5 import QtCore

import sys
import socket
import struct

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
        self.ip_input.setText(DEVICE_IP)

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
        layout = QVBoxLayout()
        layout.addWidget(self.ip_label)
        layout.addWidget(self.ip_input)
        layout.addWidget(self.port_label)
        layout.addWidget(self.port_input)
        layout.addWidget(self.duration_label)
        layout.addWidget(self.duration_input)
        layout.addWidget(self.start_button)
        layout.addWidget(self.stop_button)
        central_widget = QWidget()
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)

        # Chart
        # self.chart_view = QChartView()
        # self.chart_view.setRenderHint(QPainter.Antialiasing)
        # self.chart = QChart()
        # self.series = QLineSeries()
        # self.chart.addSeries(self.series)
        # self.chart.createDefaultAxes()
        # self.chart_view.setChart(self.chart)

        # Plot update timer
        self.timer = QtCore.QTimer()
        self.timer.setInterval(1000) # Update plot each second
        #self.timer.timeout.connect(self.update_plot)

        # Connect signals and slots
        self.start_button.clicked.connect(self.start_test)
        self.stop_button.clicked.connect(self.stop_test)

    def start_test(self):
        # disabled start, enable stop
        self.start_button.setEnabled(False)
        self.stop_button.setEnabled(True)

        # start plot update timer
        self.timer.start()

        # connect to the test device
        ip = self.ip_input.text()
        port = int(self.port_input.text())
        # need to add code to connect to the test device using socket

    def stop_test(self):
        # disable stop, enable start
        self.stop_button.setEnabled(False)
        self.start_button.setEnabled(True)

        # Stop plot update timer
        self.timer.stop()

    #def update_plot(self):


    def closeEvent(self, event):
        self.timer.stop()
        event.accept()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    test_app = TestApp()
    test_app.show()
    sys.exit(app.exec())
