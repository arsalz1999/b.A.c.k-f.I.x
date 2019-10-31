
#include <Wire.h>                                     // I2C Wire Library

// Adafruit Libraries 
#include <Adafruit_MMA8451.h>                         
#include <Adafruit_Sensor.h>                          


//Defining the object for each sensor, mma and mma2
Adafruit_MMA8451 mma  = Adafruit_MMA8451();
Adafruit_MMA8451 mma2 = Adafruit_MMA8451();

const int FLEX_PIN_1 = A0;
const int FLEX_PIN_2 = A1;

const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47500.0; // Measured resistance of 3.3k resistor


const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

void setup(void)
{
  //bool begin(uint8_t addr = MMA8451_DEFAULT_ADDRESS);

  Serial.begin(9600);                                 // Initiate serial communication

  pinMode(FLEX_PIN_1, INPUT);
  pinMode(FLEX_PIN_2, INPUT);
  
  if (! mma.begin(0x1C)) {                            // First sensor in the address of 0x1C
    Serial.println("Couldnt start first sensor 1");
    while (1);
  }

  if (!mma2.begin(0x1D)) {                           // Second sensor in the address of 0x1D
    Serial.println("Couldnt start second sensor 2");
    while (1);
  }
   
  
  mma.setRange(MMA8451_RANGE_4_G);
  mma2.setRange(MMA8451_RANGE_4_G);
  
 
}

void loop()
{
  
  char c = Serial.read();
  if(c == 'a'){
    mma.read();

    Serial.print("Strain on Left Shoulder");
    Serial.print(mma.x); 
    Serial.print(","); 
    Serial.print(mma.y); 
    Serial.print(","); 
    Serial.print(mma.z); 
    Serial.print(",");
    


    sensors_event_t event; 
    mma.getEvent(&event);

    Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
    Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
    Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
    Serial.println("m/s^2 ");
    }
    if(c == 'b'){
    mma2.read();
    Serial.print("Strain on Right Shoulder");
    Serial.print(mma2.x); 
    Serial.print(","); 
    Serial.print(mma2.y); 
    Serial.print(",");
    Serial.print(mma2.z); 
    Serial.println();

    sensors_event_t event2; 
    mma2.getEvent(&event2);
    Serial.print("X: \t"); Serial.print(event2.acceleration.x); Serial.print("\t");
    Serial.print("Y: \t"); Serial.print(event2.acceleration.y); Serial.print("\t");
    Serial.print("Z: \t"); Serial.print(event2.acceleration.z); Serial.print("\t");
    Serial.println("m/s^2 ");
  
    }
    if(c == 'c'){
    int flexADC_1 = analogRead(FLEX_PIN_1);
    int flexADC_2 = analogRead(FLEX_PIN_2);
    
    float flexV_1 = flexADC_1 * VCC / 1023.0;
    float flexR_1 = R_DIV * (VCC / flexV_1 - 1.0);
    float flexV_2 = flexADC_2 * VCC / 1023.0;
    float flexR_2 = R_DIV * (VCC / flexV_2 - 1.0);
    Serial.println("Resistance Sensor 1: " + String(flexR_1) + " ohms");
    Serial.println("Resistance Sensor 2: " + String(flexR_2) + " ohms");

    // Use the calculated resistance to estimate the sensor's
    // bend angle:
    float angle_1 = map(flexR_1, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
    float angle_2 = map(flexR_2, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
    float total = flexR_1 + flexR_2;
    float angle_linearised = map(total, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
    
    Serial.println("Lower-back tilt: " + String(angle_linearised) + " degrees (linearised)");
    Serial.println();
 
    }
    
    delay(50); 
}
