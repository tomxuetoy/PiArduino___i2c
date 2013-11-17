#include <Wire.h>

#define SLAVE_ADDRESS 0x041  // the i2c address can be redefined
int number = 0;
int state = 0;
int LEDpin = 13;

void setup() {
  pinMode(LEDpin, OUTPUT);
  Serial.begin(9600);         // start serial for output
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  Serial.println("Ready!");
}

void loop() {
  delay(100);
}

// callback for received data
void receiveData(int byteCount){
  
  while(Wire.available()) {
    number = Wire.read();
    Serial.print("data received: ");
    Serial.println(number);

    if (number == 1){
      if (state == 0){
        digitalWrite(LEDpin, HIGH); // set the LED on
        state = 1;
      }
      else{
        digitalWrite(LEDpin, LOW); // set the LED off
        state = 0;
      }
    }
  }
}

// callback for sending data
void sendData(){
  Wire.write(number);
}
