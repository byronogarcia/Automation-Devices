import sys
import time
import threading
import random
from matplotlib.backends.backend_pdf import PdfPages
from matplotlib.figure import Figure
from matplotlib.backends.backend_qt5agg import (
    FigureCanvasQTAgg as FigureCanvas,
    NavigationToolbar2QT as NavigationToolbar,
)
from PyQt5.QtWidgets import (
    QApplication,
    QMainWindow,
    QWidget,
    QVBoxLayout,
    QHBoxLayout,
    QLabel,
    QLineEdit,
    QPushButton,
)


class TestDeviceSimulatorClient:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port
        self.running = False
        self.stop_event = threading.Event()
        self.measurements = []
        self.status_timer = None

    def connect(self):
        # Implement your connection logic here
        pass

    def start_test(self, duration, rate):
        self.running = True
        self.stop_event.clear()
        threading.Thread(target=self._test_loop, args=(duration, rate)).start()

    def stop_test(self):
        self.running = False
        self.stop_event.set()

    def _test_loop(self, duration, rate):
        start_time = time.time()
        self.measurements = []

        while self.running and not self.stop_event.is_set():
            # Simulate receiving and processing data from the test device
            time.sleep(rate / 1000)
            # Generate a random measurement value for demonstration
            measurement = 50 + 10 * (2 * random.random() - 1)
            self.measurements.append((time.time() - start_time) * 1000, measurement)

            # Process and store the measurement data

        self.stop_test()

    def get_test_results(self):
        # Implement your test results generation logic here
        return {
            "Test Duration": f"{len(self.measurements)} ms",
            # Add more information as needed
        }


class TestWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.client = None
        self.test_running = False
        self.pdf_path = ""

        self.ip_label = QLabel("IP Address:")
        self.ip_lineedit = QLineEdit()
        self.port_label = QLabel("Port:")
        self.port_lineedit = QLineEdit()
        self.duration_label = QLabel("Test Duration (s):")
        self.duration_lineedit = QLineEdit()
        self.rate_label = QLabel("Status Rate (ms):")
        self.rate_lineedit = QLineEdit()
        self.connect_button = QPushButton("Connect")
        self.start_button = QPushButton("Start Test")
        self.stop_button = QPushButton("Stop Test")
        self.plot_figure = Figure()
        self.plot_canvas = FigureCanvas(self.plot_figure)
        self.toolbar = NavigationToolbar(self.plot_canvas, self)

        self.connect_button.clicked.connect(self.connect_clicked)
        self.start_button.clicked.connect(self.start_clicked)
        self.stop_button.clicked.connect(self.stop_clicked)

        input_layout = QHBoxLayout()
        input_layout.addWidget(self.ip_label)
        input_layout.addWidget(self.ip_lineedit)
        input_layout.addWidget(self.port_label)
        input_layout.addWidget(self.port_lineedit)
        input_layout.addWidget(self.duration_label)
        input_layout.addWidget(self.duration_lineedit)
        input_layout.addWidget(self.rate_label)
        input_layout.addWidget(self.rate_lineedit)

        button_layout = QHBoxLayout()
        button_layout.addWidget(self.connect_button)
        button_layout.addWidget(self.start_button)
        button_layout.addWidget(self.stop_button)

        layout = QVBoxLayout()
        layout.addLayout(input_layout)
        layout.addLayout(button_layout)
        layout.addWidget(self.plot_canvas)
        layout.addWidget(self.toolbar)
        self.setLayout(layout)

    def connect_clicked(self):
        ip = self
