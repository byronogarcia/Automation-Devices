# Production Automation Test Devices
 
To run this project you'll download the repo and open the terminal. Once there, change directories until you are in the folder. There is a virtual environment set up. Before running activate the virtual environment:
### Windows
```
call venv/scripts/activate.bat
```
### On Mac and Linux, use:
```
source venv/bin/activate
```

Once the virtual environment is setup you'll be able to see the GUI paired with the measuring device. Please make sure you have compiled the C++ code into an executable using
```
make
```
There should be an executable present, but a makefile has been provided in case it needs to be generated again. Then go ahead and execute it with a port number after like so:

```
./device_simulator 500
```
Then while that is running, open another terminal window to run the python file within the virtual environment to ensure PyQt5 works properly. Then execute it like so:
```
python3 test_measurement_device.py
```
There you can specify the port and IP address, then start and stop tests.

##Disclaimer:
The solution I created does not work completely, but I wanted to submit what I had come up with, and the kind of fun I had creating the GUI. Thank you for this opportunity!
