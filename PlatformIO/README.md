# SONOFF_OTA for Platform IO
The SONOFF_OTA  Firmware is an alternative Arduino based firmware for controlling the SONOFF Basic (and new Mini) relay using a simple Web Page interface from your computer or phone etc.  This firmware can easily be updated in Platform IO as required by the user, it also provides the SONOFF with the capability to recieve any new firmware updates directly over WiFi rather than having to connect it via the FTDI cable interface.  This firmware also allows you to retain the original light switch on the wall (if thats what you want to do) to control the lighs manually (the old way), you just need to use the new Sonoff Mini and connect the original light switch to S1 and S2 of the device rather than the mains wiring.  This functionality works in conjunction with the sonoff WiFi capability and toggling the switch will automatically switch the light to the opposite condition.

The original SONOFF firmware is replaced with the SONOFF_OTA firmware by initially uploading it using the standard FTDI cable method.
Once the initial SONOFF_XX firmware is uploaded, then subsequent firmware uploads or changes can be sent to the SONOFF  via the "Over The Air" (OTA) capability in Platform IO.  This means that, once fitted, the SONOFF device can remain in place, it does not need to be disconnected from the mains or connected to any computer or FTDI device to be updated with new firmware.

Procedure:

The only 2 files you will need to download (or just copy the code) are located in the Platform IO page, the 2 files are SONOFF_OTA and Platformio.ini

Disassemble the SONOFF and install header pins on SONOFF PCB. (see YouTube)

Correctly connect FTDI adapter to SONOFF header pins. (3.3v, Ground, TX and RX)

Press and hold SONOFF push button switch and connect FTDI adapter to computer USB, once connected to computer then release the switch.  This will put SONOFF in programming mode.  If the SONOFF LED is flashing it’s NOT in programming mode, so try again.

Start Platform IO on your computer.

Create a new Project for a "esp01_1m" board and then import (copy and paste) the SONOFF_OTA code into the main.cpp file.

Import (copy and paste) the Platformio.ini code into the Platformio.ini file.

In the new main.cpp file change the SSID and Password at lines 12 and 13 to those of your own Router.

Enabled the OTA lines in the Platformio.ini file with the correct ip address for your SONOFF in the Platformio.ini file.

Now compile and verify the code to make sure it builds correctly for the esp01 board.

Load/Open file: Sonoff_OTA

If it compiles correctly then Upload the code to the SONOFF for the first time using the (autodetected) COM port (if it fails to upload then try swapping the TX and RX leads over and try again).

After a successful upload run the serial monitor function in Platform IO and the SONOFF should reboot and show you the IP address that its been give by your Router. Note down the IP address as youll need it in the next step.

Now, in the main.cpp file (at the Web Page Design section) change the SONOFF IP address number in the programme (eg 127 etc) to the correct one for the new SONOFF (also correct the FW version if its changed).

Save the amended file.

Then in the Platformio.ini file uncomment the ; upload protocol....... line (by removing the; at the fromt of it)
Also change the IP address in the next line to the IP address you recorded in the steps above, then uncomment that line too. 

Select Verify again to compile the code once more and then Upload the amended file to the SONOFF via WiFi (no need to press the SONOFF button to put it in programming mode any more).

After successful upload, open Google Chrome and in the address bar type in the IP address for the SONOFF again.  This time the SONOFF control screen should open and display the correct IP address as you just entered it in the Arduino file.  This confirms the file was uploaded successfully to the SONOFF via WiFi. 

Again test the ON and OFF function by pressing the buttons on screen. 

Disconnect the SONOFF from USB and remove the FTDI.

Install SONOFF in desired location and connect to mains.

Test SONOFF connectivity and function via Google Chrome Web Page as above.

To upload new firmware in the future make sure the Sonoff is connected to mains power, then just open Platform IO on your computer, make sure the correct IP address is in the Platformio.ini file (if you have several SONOFFs) and then just upload your new firmware OTA. Simple!


