ofxESCPOS
=================

An openFrameworks addon for Point of Sale (POS) printers using the ESC/POS protocol.

Built primarily using the Epson ReadyPrint T20, but cross referenced with several other models and brands using the same ESC/POS protocol.

Run the examples to try it out.

You must have the latest versions of the following addons:

- https://github.com/bakercp/ofxIO
- https://github.com/bakercp/ofxSerial

If your printer doesn't work right away test the following:

- Is your printer connected to a serial port on your computer?  If you are using a USB printer, then you'll likely need to install drivers.  If you are using an RS232 printer or USB to Serial Adapter then you should be able to see the printer.
- If you can see your printer in your list of serial devices, try to connect to the printer directly with a program like http://freeware.the-meiers.org/ and connect with the printer's preferred speed, etc and then try typing and hitting return to see if the printer prints your text.  If you printer prints the text you typed, chances are very good that ofxESCPOS will work for you.
- If ofxESCPOS still isn't working for you, your printer may be using a different or incomplete version of the ESCPOS printing protocol.  Attempt to get your hands on a code sheet for your printer and compare the commands to those in ofxESCPOS.  If some of them are different, ofxESCPOS is designed so that you can make subclasses and override the default commands or create custom printer classes with subsets of the the entire protocol.
- If you still can't get your printer to work, leave an issue [here](https://github.com/bakercp/ofxESCPOS/issues) and I'll do my best to help.

Good luck! 
