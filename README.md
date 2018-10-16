# SONOFF_OTA
Arduino Firmware for controlling the SONOFF Basic relay using a simple Web Page interface.  This firmware can easily be updated in Arduino as required by the user, it also provides the SONOFF with the capability to recieve any new firmware updates directly over WiFi rather than having to connect it via the FTDI cable interface.

The original SONOFF firmware is replaced with the SONOFF_XX_OTA firmware by initially uploading it using the standard FTDI cable method.
Once the initial SONOFF_XX_OTA firmware is uploaded, then subsequent firmware uploads or changes can be sent to the SONOFF via WiFi, or "Over The Air" (OTA).  This means that, once fitted, the SONOFF device can then remain in place, it does not need to be disconnected from the mains or connected to any computer or FTDI device to be updated with new firmware.

Procedure:

Disassemble the SONOFF and install header pins on SONOFF PCB. (see YouTube)

Correctly connect FTDI adapter to SONOFF header pins. (3.3v, Ground, TX and RX)

Press and hold SONOFF push button switch and connect FTDI adapter to computer USB, once connected to computer then release the switch.  This will put SONOFF in programming mode.  If the SONOFF LED is flashing it’s NOT in programming mode, so try again.
Start Arduino.exe on computer.
Load/Open file: Sonoff_XX_OTA
In Arduino “Tools” menu select the correct COM port for the SONOFF.
Verify and then Upload the Sonoff_XX_OTA file to the SONOFF (if it fails to upload then check the COM port is correct or try swapping the TX and RX leads over and try again).
After successful upload, disconnect FTDI USB plug at the computer.
Reconnect the FTDI USB plug to the same computer USB (without pressing the SONOFF switch this time) and immediately select the Arduino “Tools” menu and then “Serial Monitor”.  The Serial Monitor window will open and a few seconds later display the new IP address for the SONOFF. If you were too slow and didn’t see the IP address displayed then repeat this step.
In a Google Chrome address bar type in the IP address for the SONOFF and after a few seconds a SONOFF control screen should open.  Test the ON and OFF function by pressing the relevant buttons on screen, the SONOFF LED should display the relay status.  Note that at this stage the incorrect IP address is shown in the title at the top of the web page.
Close the Google Chrome tab.
In the Arduino file change the SONOFF IP address number in the programme (eg 127 etc) to the correct one for the new SONOFF (also correct the FW version if its changed).
Save the amended file.
Unplug the USB at the computer and then plug it back in again.
In the Tools menu, select the new WiFi port “ESP8266 xxx etc (+ new IP address)" that’s displayed rather than the COM port (if it’s not shown, then deselect the COM port, unplug the USB and plug it in again and try the Tools menu again).
Select Verify and then Upload to send the amended file to the SONOFF via WiFi (no need to press the SONOFF button to put it in programming mode any more).
After successful upload, reopen Google Chrome and in the address bar type in the IP address for the SONOFF again.  This time the SONOFF control screen should open and display the correct IP address as you just entered it in the Arduino file.  This confirms the file was uploaded successfully to the SONOFF via WiFi.    
Again test the ON and OFF function by pressing the buttons on screen. 
Disconnect the SONOFF from USB and remove the FTDI.
Install SONOFF in desired location and connect to mains.
Test SONOFF connectivity and function via Google Chrome Web Page as above.
To upload new firmware in the future make sure the Sonoff is connected to mains power, then just open Arduino on your computer, select  the Tools menu, select the correct WiFi port “ESP8266 xxx etc (+ SONOFF IP address)" and then upload your new firmware. Simple!
