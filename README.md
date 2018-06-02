ofxESCPOS
=========

Description
-----------

An openFrameworks addon for Point of Sale (POS) printers using the ESC/POS protocol.

Features
--------

-   Print text, images on thermal printers using the ESC/POS protocol.

Required Addons
---------------

-   ofxPoco (included in openFrameworks)
-   [ofxIO](https://github.com/bakercp/ofxIO)
-   [ofxSerial](https://github.com/bakercp/ofxSerial)

Getting Started
---------------

To get started, generate the example project files using the openFrameworks [Project Generator](http://openframeworks.cc/learning/01_basics/how_to_add_addon_to_project/).

Troubleshooting
---------------

If your printer doesn't work right away test the following:

-   Is your printer connected to a serial port on your computer?  If you are using a USB printer, then you'll likely need to install drivers.  If you are using an RS232 printer or USB to Serial Adapter then you should be able to see the printer.

-   If you can see your printer in your list of serial devices, try to connect to the printer directly with a program like [CoolTerm](http://freeware.the-meiers.org/) and connect with the printer's preferred speed, etc and then try typing and hitting return to see if the printer prints your text.  If you printer prints the text you typed, chances are very good that ofxESCPOS will work for you.

-   If ofxESCPOS still isn't working for you, your printer may be using a different or incomplete version of the ESCPOS printing protocol. Attempt to get your hands on a code sheet for your printer and compare the commands to those in ofxESCPOS.  If some of them are different, ofxESCPOS is designed so that you can make subclasses and override the default commands or create custom printer classes with subsets of the the entire protocol.

-   If you still can't get your printer to work, leave an issue [here](https://github.com/bakercp/ofxESCPOS/issues) and I'll do my best to help.

Documentation
-------------

API documentation can be found here.

Build Status
------------

Linux, macOS [![Build Status](https://travis-ci.org/bakercp/ofxESCPOS.svg?branch=master)](https://travis-ci.org/bakercp/ofxESCPOS)

Visual Studio, MSYS [![Build status](https://ci.appveyor.com/api/projects/status/67ndocng7ej561rw/branch/master?svg=true)](https://ci.appveyor.com/project/bakercp/ofxescpos/branch/master)

Compatibility
-------------

The `stable` branch of this repository is meant to be compatible with the openFrameworks [stable branch](https://github.com/openframeworks/openFrameworks/tree/stable), which corresponds to the latest official openFrameworks release.

The `master` branch of this repository is meant to be compatible with the openFrameworks [master branch](https://github.com/openframeworks/openFrameworks/tree/master).

Some past openFrameworks releases are supported via tagged versions, but only `stable` and `master` branches are actively supported.

Versioning
----------

This project uses Semantic Versioning, although strict adherence will only come into effect at version 1.0.0.

Licensing
---------

See `LICENSE.md`.

Contributing
------------

Check out the [Help Wanted](https://github.com/bakercp/ofxIO/issues?q=is%3Aissue+is%3Aopen+label%3A%22help+wanted%22) tag in the issues section for specific ideas or propose your own new ideas.

Pull Requests are always welcome, so if you make any improvements please feel free to float them back upstream :)

1.  Fork this repository.
2.  Create your feature branch (`git checkout -b my-new-feature`).
3.  Commit your changes (`git commit -am 'Add some feature'`).
4.  Push to the branch (`git push origin my-new-feature`).
5.  Create new Pull Request.
