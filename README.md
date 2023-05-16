# 🧭 DIGITAL COMPASS
```
This project to be one of the requirements for the Physical Cyber System Practicum class completion in Department of Computer Engineering,  University of Indonesia
```

## About the project

The digital compass is made with assembly language in AVR using an MPU-9250 sensor and displaying the coordinate results at the form of tesla units onto an OLED display. This program is designed by Group A3 which consists of : 

- Zaki Ananda - 2106705474
- Zulfikar Hadzalic - 2106636224
- Muhammad Suhaili - 2106731535
- Aliefya Fikri Ihsani - 2106733843


## Introduction to the problem and the solution
Navigation is an essential part of our daily lives, and a reliable compass is a crucial tool for accurate navigation. Traditional compasses have been used for centuries, but they have limitations such as the need for calibration, sensitivity to nearby magnetic fields, and difficulties in reading the compass accurately in low light conditions.

One possible solution to the challenges faced by traditional compasses is to to make digital compasses that combines the accuracy and simplicity of a traditional compass with the digital display and additional features of a digital compass could be an effective solution. The digital compass could have a traditional needle that points to magnetic north, but also include additional digital features such as an electronic display showing distance and location.

The digital compass could also include additional sensors such as a GPS, gyroscope, and accelerometer, which could provide more accurate readings and allow for more precise navigation. Moreover, digital compasses enable users to be more familiar with their features and readings and will be able to undestand it quickly.


## Hardware design and implementation details
In this project, we're trying to make our own digital compass using an MPU-9250 sensor which has its own utility including a gyroscope module that could read our current position's relative orientation. Furthermore, we would display those plane coordinates which the sensor read onto an OLED display. The equipments we use are:

- MPU-9250 sensor module
- Arduino Uno
- Jumper Cable
- OLED Display
- Breadboard

From top to bottom, the OLED screen will display these three types of angular rate measurements in the form of tesla units :
- Yaw : the horizontal rotation on a flat surface when seen the object from above.
- Pitch : vertical rotation as seen the object from front.
- Roll : horizontal rotation when seen the object from front.


## Software implementation details
There are 1 main assembly file 5 header files which containing the function prototypes and libraries needed to make this project.

```
main.S
```
The main file that is used to combine all of the other header files into one single package and calling the respective routines available in them.
```
delay.h
```
The delay file contains options of delay that wants to be used in the program. 
```
i2c.h
```
This file contains all operations of I2C communications between the arduino and the sensor. We added a new routine called ```I2C_read_NACK``` as a needed variable to execute I2C operation with the module sensor. For further information, we refer to the datasheet which listed in this repository.
```
oled.h
```
This file is used to initialize OLED operations and its sequence to display the sensor reading. OLED uses pages and columns to display the desired results, so we included its prequisites on routine ```OLED_char```  to display characters on the OLED.
```
registerMap.h
```
This file lists all registers used in this program and its functionality.
```
usart.h
```
This file is used for USART operations used in the program.

---
## Test results and performance evaluation
**Assembled result**

![compassPic](https://github.com/zaki-ananda/DigitalCompass/assets/88538229/9fe249dd-772b-46f8-a73d-fc0b33752f40)

As seen above, the project works as expected. The OLED could display yaw, pitch, and roll on tesla units and could varies depending on the device's position. 

However, the performance and functionality hasn't fully met our initial purpose as a digital compass. The reason why we haven't been able to do that is to display the current's yaw, pitch, and roll on tesla units and then convert them into compass directions is a more difficult tasks than we expected before as we need more variables such as calibrations and more.   

---
## Conclusion and future work

In conclusion, the project to make a digital compass was successfully completed although it is not 100% as we expected. The digital compass is a useful tool for navigation, and the project involved the use of various electronic components such as an Arduino Uno, MPU-9250 sensor module, and OLED to display the result.

Although this project still lacks what we need, there is potential for future improvements and developments in this project. One possible improvement is to add more variables into the program so that the OLED could display a more proper compass reading. Additionally, we could improve how the user interface in the OLED works so that it is more understandable by non-expert people to read the compass direction. 

## Report 
[Insert Report file here]
