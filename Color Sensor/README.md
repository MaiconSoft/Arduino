
# SoftAPD9960: APD9960 using Softwire

<p align="center">
  <img width="150" height="150" src="https://cdn.sparkfun.com//assets/parts/9/6/0/3/12787-01.jpg">
</p>

Allow you use two APD9960 colors sensors. By default, they are adress fixed, so they do not work without in the same I2C bus. Using a SoftWire will allow use an additional sensor.

A library is compatible with [SparkFun_APDS9960](https://github.com/sparkfun/SparkFun_APDS-9960_Sensor_Arduino_Library "SparkFun_APDS9960"). In ADS.ino example, the two libraries work concurrently.

Only Colors features are supported for the release.

## Requeriments
### SoftAPD9960:

* [SoftI2CMaster](https://github.com/felias-fogg/SoftI2CMaster "SoftI2CMaster") adjusted for this application, can be download [here](https://github.com/MaiconSoft/Arduino/tree/master/Color%20Sensor/Requeiments/SoftI2CMaster) the changed library.

### SparkFun_APDS9960
* [SparkFun_APDS9960](https://github.com/sparkfun/SparkFun_APDS-9960_Sensor_Arduino_Library "SparkFun_APDS9960")
* [Wire](https://www.arduino.cc/en/reference/wire "Wire")

## Wiring:
Conections of arduino boards and APDS9960 using SoftAPD9960:

|APDS9960  |  Arduino Uno (Atmega328) | Arduino Mega (Atmega2560) |
| :------------: | :------------: | :------------: |
|  +3,3V | +3V3  |+3V3  |
| GND   |  GND | GND |
| SDA |D6|D18|
| SCL |D7|D19|

Conections of arduino boards and SparkFun_APDS9960 using [SparkFun_APDS9960](https://github.com/sparkfun/SparkFun_APDS-9960_Sensor_Arduino_Library "SparkFun_APDS9960"):

|APDS9960  |  Arduino Uno (Atmega328) | Arduino Mega (Atmega2560) |
| :------------: | :------------: | :------------: |
|  +3,3V | +3V3  |+3V3  |
| GND   |  GND | GND |
| SDA |D4|D20|
| SCL |D5|D21|


## Note:

The** "enableColor"** command must be **"true"** in your SoftAPD9960 application, this is because, in this case the parameter enable color module, otherwise in SparkFun_APDS9960 this parameter enables the interrupt (may be this can be change in future updade of SoftAPD9960).

## TODO:
* Normalize color values with ambient light;
* Add motion features.
