# SONOFF_OTA
SONOFF firmware for controlling the relay using a simple Web Page interface.  The firmware also provides the sonoff with OTA capability for future firmware uploads as shown below.

The SONOFF_OTA firmware is first uploaded to the SONOFF device using the standard FTDI method.
Once the SONOFF_OTA firmware is uploaded, then a SONOFF_XX_OTA file containing a working sketch can be uploaded to the SONOFF via Wifi, or Over The Air (OTA).  

Procedure:
Install header pins on SONOFF PCB.
Connect FTDI adapter to SONOFF header pins.
Press and hold SONOFF push button switch and connect FTDI adapter to computer USB, once connected to computer then release the switch.  This will put SONOFF in programming mode.  If the SONOFF LED is flashing it’s NOT in programming mode, so try again.
Start Arduino.exe on computer.
Open file: Sonoff_13_OTA
In Arduino “Tools” menu select the correct COM port for the SONOFF.
Verify and then Upload the file to the SONOFF (if it fails to upload then check the COM port is correct or try swapping the TX and RX leads and try again).
After successful upload, disconnect FTDI USB port at the computer.
Reconnect FTDI to the same computer USB (without pressing the SONOFF switch this time) and immediately select the Arduino “Tools” menu and then “Serial Monitor”.  The Serial Monitor window will open and a few seconds later display the IP address for the SONOFF. If you were too slow and didn’t see the IP address displayed then repeat this step.
In a Google Chrome address bar type in the IP address for the SONOFF and after a few seconds the SONOFF control screen should open.  Test the ON and OFF function by pressing the relevant buttons on screen, the SONOFF LED should display the relay status.  Note that at this stage the incorrect IP address is shown in the title at the top of the web page.
Close the Google Chrome tab.
In the Arduino file change the IP address in the programme at line 35 to the correct one for the new SONOFF (also correct the FW version in this line if its changed).
Save the amended file.
Unplug the USB at the computer and then plug it back in again.
In the Tools menu, select the new WiFi port “ESP8266 xxx etc (+ new IP address) that’s displayed” rather than the COM port (if it’s not available then deselect the COM port and try  the Tools menu again).
Select Verify and then Upload to send the amended file to the SONOFF via WiFi (no need to press the SONOFF button to put it in programming mode any more).
After successful upload, reopen Google Chrome and in the address bar type in the IP address for the SONOFF again.  This time the SONOFF control screen should open and display the correct IP address as you just enter it in the Arduino file.  This confirms the file was uploaded successfully to the SONOFF via WiFi.    
Again test the ON and OFF function by pressing the buttons on screen. 
Disconnect the SONOFF from USB and remove the FTDI.
Install SONOFF in desired location and connect to mains.
Test SONOFF connectivity and function via Google Chrome Web Page as above.
