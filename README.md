# brushless_gimbal_motor

## So youre wondering if you can drive a brushless gimbal motor with an arduino?

You can. There two possibilities. 1) There are these expensive, but simple [brushless gimbal controllers](http://www.rovertec.com/products-bgmc.html) and you could use arduino [servo library](https://www.arduino.cc/en/reference/servo) to run them.   

Or, there are cheaper [boards](http://i.imgur.com/IlU6zK8.jpg) that have the same microprocessor as an arduino on them. These boards are amazing - not only are they programmable using the arduino IDE, they also have a motor driver built in.

## Short history of the 

http://www.itsqv.com/QVM/index.php?title=How_To_-_Martinez_Brushless_Gimbal_Controller_Set-Up

https://sourceforge.net/projects/brushless-gimbal-brugi/

https://www.rcgroups.com/forums/showthread.php?1901828-Martinez-board-Open-source-brushless-gimbal-HELP-THREAD

http://fpv-community.de/showthread.php?22617-Gimbal-Brushless-Controller-V3-0-50x50mm-by-Martinez

They are also completely open hardware. The schematics and source code are all on line. I just reprogrammed one to do [this](https://www.youtube.com/watch?v=IOxuy6EuV1g). My code is [here](https://github.com/owhite/brushless_gimbal_motor).  