GPIO Driver Sample Code
=======================

NOTE: If you use this sample application for your own purposes, follow
      the licensing agreement specified in `Software_Use_Agreement.rtf`
      in the home directory of the installed RSL10 Software
      Development Kit (SDK).

Overview
--------
This sample project demonstrates an application that:

1.  Uses GPIO5 to toggle the LED diode.
2.  Uses GPIO11 to disable the LED toggling.

The source code exists in `app.c`, with additional `app.h` and 
`RTE_device.h` header files included.

Verification
------------
To verify that the application is working correctly, connect the board
to the power supply. On each button press the LED toggles. When GPIO11
is connected to ground, LED toggling is disabled.

Hardware Requirements
---------------------
This application can be executed on any Evaluation and Development Board
with no external connections required.

Importing a Project
-------------------
To import the sample code into your IDE workspace, refer to the
Getting Started Guide for your IDE for more information.

Notes
-----
Sometimes the firmware in RSL10 cannot be successfully re-flashed, due to the
application going into Sleep Mode or resetting continuously (either by design 
or due to programming error). To circumvent this scenario, a software recovery
mode using DIO12 can be implemented with the following steps:

1.  Connect DIO12 to ground.
2.  Press the RESET button (this restarts the application, which will
    pause at the start of its initialization routine).
3.  Re-flash RSL10. After successful re-flashing, disconnect DIO12 from
    ground, and press the RESET button so that the application will work
    properly.

***
Copyright (c) 2019 Semiconductor Components Industries, LLC
(d/b/a ON Semiconductor).
