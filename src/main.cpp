#include <Arduino.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x3F, 20, 4);
LiquidCrystal_I2C lcd(0x27, 20, 4);

//Global Variables to used in classes
uint8_t timeBetweenSpin =1,setIncubationDays=18;
int seconds=59, minutes = 59, hours = 1, daysCounter = 0, day = 0, incubationDays = 18, hatchingDays = 3, buttonsCounter=0, incubationModeCounter;
float tempValue[20], avgTemp, sum, humReading;
float tempTolerance =0.3, setTempValue = 37.9, setHumidityValue=65, humidityTolerance=2.0;
float humValue[10],sumHum,avgHum;
float minTempValue , operatingTempValue, maxTempValue, minHumidityIncubation, operatingHumidityValue, maxHumidityIncubation;
uint8_t upButton = 2, downButton = 4, selectButton = 3;
bool state1, state2,state3, heatingState,blinkState;
boolean upButtonState = LOW, downButtonState = LOW, selectButtonState = LOW;

char setIncubationMode[3][20] ={"Incubation only", "Incubation + Hatch","Hatching only"};


#include "menu.h"
#include "buttonHandler.h"


void setup() {
// write your initialization code here

    noInterrupts();           // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = 62500;            // compare match register
    // (256*62500)/16MHz = 1sec =
    TCCR1B |= (1 << WGM12);   // CTC mode
    TCCR1B |= (1 << CS12);    // 256 prescaler
    TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
    interrupts();             // enable all interrupts
    TCNT1  = 0;

    lcd.begin();
    lcd.clear();
    lcd.backlight();
    lcd.setBacklight(HIGH);
    Serial.begin(9600);


  //  processInitiated = EEPROM.read(2);
     EEPROM.write(5,0);
    daysCounter = EEPROM.read(5);

    // daysCounter = 0;
      EEPROM.write(6,4);
    day = EEPROM.read(6);
    // EEPROM.write(6,18);
    // day =18;
    incubationDays = EEPROM.read(7);
    hatchingDays = EEPROM.read(8);

    //to be removed
    EEPROM.write(9,37.8);
    EEPROM.write(10,65);
    EEPROM.write(11,0.3);
    EEPROM.write(12,2);
    // to be removed

    //Temperature + Humidity values
    operatingTempValue = EEPROM.read(9);
    operatingHumidityValue = EEPROM.read(10);
    tempTolerance = EEPROM.read(11);
    humidityTolerance = EEPROM.read(12);

    maxTempValue = operatingTempValue+tempTolerance;
    minTempValue = operatingTempValue-tempTolerance;

    maxHumidityIncubation = operatingHumidityValue + humidityTolerance;
    minHumidityIncubation = operatingHumidityValue-humidityTolerance;

    //to be removed
  //  EEPROM.write(13,18);
    EEPROM.write(14,2);

    //incubation standards
    setIncubationDays = EEPROM.read(13);
    timeBetweenSpin = EEPROM.read(14);

    hours = timeBetweenSpin-1;

    pinMode(upButton,INPUT);
    pinMode(downButton,INPUT);
    pinMode(selectButton,INPUT);
   // attachInterrupt(digitalPinToInterrupt(selectButton),selectButtonFunction, FALLING);

   menu.charInitialization();
}

ISR(TIMER1_COMPA_vect)
{
    seconds--;
    blinkState = !blinkState;
  //  motorTimer++;
}



void loop() {
buttonsHandler.buttonsListener();
menu.IncubationScreen();
}



