

#include "Energia.h"

void setup();
void loop();

// include the SPI library:
#include <SPI.h>

// set pin 8 as the slave select for the digital pot:
const int slaveSelectPin = SS;

void setup() {
	// set the slaveSelectPin as an output:
	pinMode (slaveSelectPin, OUTPUT);
	// take the SS pin high to de-select the chip:
	digitalWrite(slaveSelectPin,HIGH);
	pinMode(GREEN_LED, OUTPUT);
	digitalWrite(GREEN_LED, HIGH);
	// initialize SPI:
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV32);
	Serial.begin(115200);
	Serial.println("Benvenuto!");
	delay(100);
}

void loop() {

	// put your main code here, to run repeatedly:
	uint8_t valore[2];
	uint16_t upper;
	float temp;
	// take the SS pin low to select the chip:
	digitalWrite(slaveSelectPin,LOW);
	//  send in the address and value via SPI:
	valore[0] = SPI.transfer(0x0);
	valore[1] = SPI.transfer(0x0);
	// take the SS pin high to de-select the chip:
	digitalWrite(slaveSelectPin,HIGH);
	/// il bit 2 di valore[1] indica lo stato della tc: 1 aperta, 0 ok
	if (valore[1] & 0x4){
		Serial.println("tc non collegata!");
	}
	else{
		/// termocoppia ok
		valore[1] >>= 3;	/// eliminati i 3 bit di stato
		upper = valore[0] & 0xFF;
		/// lascia i 5 bit per valore[1]
		upper <<= 5;
		upper |= valore[0];
		temp = (float) upper / 4.0;
		Serial.print("Temperatura: ");
		Serial. println(temp, 2);
	}
	delay(1000);
	P4OUT ^= BIT7;
}


