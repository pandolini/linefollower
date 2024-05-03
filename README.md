# Linefollower control system

*This repository contains the control system for the MK4 linefollower robot. It is currently in late development.*

## Features

- A PID controller for precise control of the robot.
- A webserver that allows live editing of parameters such as max, min, and base motor speed, as well as the Kp, Kd, and Ki parameters of the PID controller.
- Ability to start and stop the robot's engines through the webserver, which is especially useful for emergency braking.
- A system for saving good parameters to the flash of the ESP32, with the possibility to download them to the machine accessing the webserver.

## License

This project is licensed under the [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](LICENSE). This means you are free to use, share, and modify this project, but you must give appropriate credit, provide a link to the license, and indicate if changes were made. You may not use this project for commercial purposes without prior permission.

## Changelog

- v1.0.0: Implements a basic control system for the MK2 robot, utilizing a straightforward PID controller.
- v2.0.0: Introduces an enhanced control system for the MK3 robot, utilizing fuzzy logic and discarding the previous PID controller.
- v3.0.0: Introduces a streamlined control system for the MK4 robot, incorporating a PID controller and a webserver, as detailed above.