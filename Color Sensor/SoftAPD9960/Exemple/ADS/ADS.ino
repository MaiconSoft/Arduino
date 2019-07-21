/**********************************
No arduino uno use:
***********************************
 Sensor 1:
 	[arduino]				[ADS1]
 	+3,3V   --------------- VCC
 	GND     --------------- GND
 	pino A4  --------------- SDA
 	pino A5  --------------- SCL

 Sensor 2:
 	[arduino]				[ADS2]
 	+3,3V   --------------- VCC
 	GND     --------------- GND
 	pino 06 --------------- SDA
 	pino 07 --------------- SCL

***********************************
No arduino Mega use:
***********************************

 Sensor 1:
 	[arduino]				[ADS1]
 	+3,3V   --------------- VCC
 	GND     --------------- GND
 	pino 20  --------------- SDA
 	pino 21  --------------- SCL

 Sensor 2:
 	[arduino]				[ADS2]
 	+3,3V   --------------- VCC
 	GND     --------------- GND
 	pino 18(TX1)  --------- SDA
 	pino 19(RX1)  --------- SCL

**********************************/

#include <SoftAPD9960.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include "Debug.h"

SoftAPD9960 SensorCor2;
SparkFun_APDS9960 SensorCor1;

void setup()
{
	Serial.begin(115200);

	IFPRINT(SensorCor1.begin(), "Sensor de cor 1 inicializando: ", "OK", "NOK");
	IFPRINT(SensorCor1.enableColor(false), "Sensor de cor 1 config. cores: ", "OK", "NOK");

	IFPRINT(SensorCor2.begin(), "Sensor de cor 2 inicializando: ", "OK", "NOK");
	IFPRINT(SensorCor2.enableColor(true), "Sensor de cor 2 config. cores: ", "OK", "NOK");
}

void loop()
{
	rgb_t cor;

	SensorCor1.getColor(&cor);

	PRINT2("vermelho1", cor.red);
	PRINT2("verde1", cor.green);
	PRINT2("azul1", cor.blue);
	PRINT2("luz1", cor.light);
	Serial.println();

	SensorCor2.getColor(&cor);

	PRINT2("vermelho2", cor.red);
	PRINT2("verde2", cor.green);
	PRINT2("azul2", cor.blue);
	PRINT2("luz2", cor.light);
	Serial.println();

	delay(500);
}