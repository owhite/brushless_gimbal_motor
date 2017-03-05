# brushless_gimbal_motor

## So youre wondering if you can drive a brushless gimbal motor with an arduino?

You can. There two possibilities. 1) There are these expensive, but simple [brushless gimbal controllers](http://www.rovertec.com/products-bgmc.html) and you could use arduino [servo library](https://www.arduino.cc/en/reference/servo) to run them.   

Or, there are cheaper [boards](http://i.imgur.com/IlU6zK8.jpg) that have the same microprocessor as an arduino on them. These boards are amazing - not only are they programmable using the arduino IDE, they also have a motor driver built in.

## Short history of brushless gimbal motor controllers

Quite some time ago the quad copter community really did it right and started publishing some open source gimbal controllers.

The origin of these boards but if you search for ["Martinez gimbal controller"](https://www.google.com/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#q=google.+Martinez+gimbal+controller&*) you'll see a proliferation of hits. 

One thread that started in [2011](https://www.rcgroups.com/forums/showthread.php?1829058-Open-Source-Brushless-Gimbal) is an example. There are others [link1](https://www.rcgroups.com/forums/showthread.php?1901828-Martinez-board-Open-source-brushless-gimbal-HELP-THREAD) and [link](http://fpv-community.de/showthread.php?22617-Gimbal-Brushless-Controller-V3-0-50x50mm-by-Martinez) 

That eventually led me to [this sourceforge](https://sourceforge.net/projects/brushless-gimbal-brugi/) site and a code base that has the following acknowledgement:

```
Brushless Gimbal Controller Software by Christian Winkler and Alois Hahn (C) 2013

Brushless Gimbal Controller Hardware and Software support 
by Ludwig Fäerber, Alexander Rehfeld and Martin Eckart
```

What is amazing about this project is it's success as open hardware. The schematics and source code were made available to the community, and now an abundance of cheap boards can be found everywhere: [example1](http://www.readytoflyquads.com/rtf-mini-brushless-gimbal-controller), [example2](http://www.olliw.eu/2013/storm32bgc/), [example3](https://www.amazon.com/s/ref=nb_sb_noss?url=search-alias%3Daps&field-keywords=gimbal+controller).

## Details on the Martinez brushless gimbal controller

As of this writing the current location of the Martinez brushless gimbal controller is at [Source forge](https://sourceforge.net/projects/brushless-gimbal-brugi/). 

There are several set up guides for using the controller, one example is [here](http://www.itsqv.com/QVM/index.php?title=How_To_-_Martinez_Brushless_Gimbal_Controller_Set-Up). I have also seen several outdated pdfs. 

There are also multiple locations of the orginal files for the board schematic, which made for free program, [Eagle software](http://www.autodesk.com/products/eagle/overview). I have a copy of the martinez eagle file at [this repo](https://github.com/owhite/brushless_gimbal_motor/docs/martinez.sch), and [this](https://github.com/owhite/brushless_gimbal_motor/docs/martinez.png) is a bitmap of that schematic. 

## Okay suppose I have a gimbal controller and I want to load firmware on to it.

While I'm not going to talk you through the [setup](http://www.itsqv.com/QVM/index.php?title=How_To_-_Martinez_Brushless_Gimbal_Controller_Set-Up), I can help with using the Arduino IDE to load up a 2017-version of the firmware. 

[This](https://sourceforge.net/projects/brushless-gimbal-brugi/files/) is the sourceforge site listing all the firmware files.

Download, for example, [BruGi_050_r217.zip](https://sourceforge.net/projects/brushless-gimbal-brugi/files/BruGi_050_r217.zip/download). I also recently downloaded the latest Arduino IDE [v1.8.1](https://www.arduino.cc/en/main/software) on my mac.

Go to tools->board and set to "Arduino Pro or Pro mini, (5V, 16 MHz) w/ ATmega328"

Uncompress the BruGI zip file, then open "_BruGi.ino".

That file and a bunch of others should load. Hit verify and then you'll get this error:

"error: 'initMPU' was not declared in this scope"

Which is fine, we can fix this. The issue is this. Because of changes to the IDE's compiler, it now needs to have some functions declared as external in some of the files.

What this means is you need to make the following changes to some of the files. All of these changes are at the top of the file. There is no reason to go any further into the code. Be sure to put the lines ABOVE the #include statements. Okay, here we go.

In BLcontroller.h, add this line to top of the file:
```
   extern void TIMER0_isr_emulation();
```

In SerialCom.h, add these lines to the top of the file:
```
   extern void initIMUtc();
   extern void initSensorOrientationDefault();
   extern void initSensorOrientation();
   extern void initIMU();
```

In orientationRoutines.h, put this line on the top of the file:
```
   extern void initMPU();
```

Make these changes to the files and it should be possible to upload the firmware. 

## My modifications to the Martinez firmware

The original firmware code is artwork. Absolute artwork. I'm really impressed by the state machine, the PID computation, the sine wave sent to the motor driver, the I2C calls to the external Intertial Measurement Unit (IMU) board, and the programmable capability through the serial. 

In my case, I didnt need most of that, so I made a bunch of changes in [this repo](https://github.com/owhite/brushless_gimbal_motor/tree/master/src). They are:

* complete search and replace on the terms pitch and roll
 * These were what the original author used to designate each of the motor outputs. They're now called motor1 and motor2.

* complete removal of the IMU code.
 * I'm not using at this point and I just wanted to make it simpler to read.

* deactivation of the PID calculations
 * it's wonderful code, I just wasnt using it. 

One thing to note is in the call to:
```
MoveMotorPosSpeed(config.motorNumberMotor1, motor1MotorDrive, maxPWMmotorMotor1Scaled);
```
the value maxPWMmotorMotor1Scaled is basically a power setting. This is really sweet. If you ramp that up, more amps go to the motor. This allowed me to dial it way down, to make the motor behave like gentle little wind up toy. You could ramp that thing up and drive a big tough motor.

## I dont use the Arduino IDE

Just not a fan. I'm all about command line programming. I really like [platformio](http://platformio.org/). You dont have to use it. You may be able to install my code in the same way as I described above. 

## What did I do with it?

This:

[![animatronic moth ](http://img.youtube.com/vi/IOxuy6EuV1g/0.jpg)](http://www.youtube.com/watch?v=IOxuy6EuV1g)
