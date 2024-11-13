# studious-memory
Providing an open-source solution for communicating with motors via the CAN protocol.


## Overview

1. canBus single channel maximum speed is 6000 fps.
2. A single motor has a maximum speed of 300 fps. approaching to or higher than 300fps will cause the motor to vibrate.
3. In theoretical each Can channel can support up to 20 motors with a maximum speed of 300 fps.

#### 7dof Arm controlled by canBus
![7dof Arm](doc/7motorsdemo.gif)


