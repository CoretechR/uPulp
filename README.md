# uPulp

uPulp (micro-Pulp) is a little tool for displaying the Playdate Pulp Player on my ESP32-powered display board. It might be helpful to show how games look on the original PlayDate screen.

This was botched together in an afternoon. Use at your own risk!

The code is a mix between these two projects: 
 - https://github.com/CoretechR/Keybon
 - https://github.com/CoretechR/ESP32-Handheld

How it works: The Windows App captures part of the screen where the Pulp player is running. The 400x240px image is then sent to the ESP32 via a serial connection. Currently this is running at only 4 frames per second, but there is a lot of room for optimization. Button pressed are sent the other way via serial where the Windows app converts them to actual key events.


![](uPulp_Demo.jpg)

![](Animation.gif)
