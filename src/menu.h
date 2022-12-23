class Menu {
private:
    String incubationModeValue;
    byte customChar[8] = {
            B00100,
            B00100,
            B01110,
            B10001,
            B10001,
            B10001,
            B01110,
            B00100
    };

    byte customChar1[8] = {
            B00100,
            B00100,
            B01110,
            B11111,
            B11111,
            B11111,
            B01110,
            B00100
    };

    byte arrow[8] = {
            0b01000,
            0b01100,
            0b01110,
            0b01111,
            0b01110,
            0b01100,
            0b01000,
            0b00000
    };
public:
    void charInitialization() {
        lcd.createChar(0, customChar);
        lcd.createChar(1, customChar1);
        lcd.createChar(10, arrow);

    }

    void saveChanges() {

        operatingTempValue = setTempValue;
        EEPROM.write(9, setTempValue);

        operatingHumidityValue = setHumidityValue;
        EEPROM.write(10, setHumidityValue);

//Tolerance values for humidity and Temperature
        EEPROM.write(11, tempTolerance);
        EEPROM.write(12, humidityTolerance);

        incubationDays = setIncubationDays;
        EEPROM.write(7, setIncubationDays);


        hours = timeBetweenSpin - 1;
        EEPROM.write(14, hours);

        buttonsCounter = 0;
    }




    void IncubationScreen() {

        switch (buttonsCounter) {

            case 1: {
                lcd.home();

                lcd.setCursor(1, 0);
                lcd.print("Set Temperature:");
                lcd.setCursor(4, 1);
                lcd.print("=>");// special select item character
                lcd.setCursor(6, 1);
                lcd.print(setTempValue);
                lcd.setCursor(11, 1);
                lcd.print((char) 223);
                lcd.setCursor(12, 1);
                lcd.print("C");

                lcd.setCursor(2, 2);
                lcd.print("Temp Tolerance:");
                lcd.setCursor(6, 3);
                lcd.print(tempTolerance);
                lcd.setCursor(10, 3);
                lcd.print((char) 223);
                lcd.setCursor(11, 3);
                lcd.print("C");
                break;
            }
            case 2: {
                lcd.setCursor(1, 0);
                lcd.print("Set Temperature:");
                lcd.setCursor(6, 1);
                lcd.print(setTempValue);
                lcd.setCursor(11, 1);
                lcd.print((char) 223);
                lcd.setCursor(12, 1);
                lcd.print("C");
                lcd.setCursor(4, 3);
                lcd.print("=>");// special select item character
                lcd.setCursor(2, 2);
                lcd.print("Temp Tolerance:");
                lcd.setCursor(6, 3);
                lcd.print(tempTolerance);
                lcd.setCursor(10, 3);
                lcd.print((char) 223);
                lcd.setCursor(11, 3);
                lcd.print("C");
                break;
            }

            case 3: {
                // display and selection of reference humidity for editing
                lcd.setCursor(4, 1);
                lcd.print("=>");// special select item character
                lcd.setCursor(3, 0);
                lcd.print("Set Humidity:");
                lcd.setCursor(6, 1);
                lcd.print(setHumidityValue);
                lcd.setCursor(11, 1);
                lcd.print("% RH");
                //display of reference humdity
                lcd.setCursor(1, 2);
                lcd.print("Humidity Tolerance:");
                lcd.setCursor(6, 3);
                lcd.print(humidityTolerance);
                lcd.setCursor(10, 3);
                lcd.print("% RH");

                break;
            }

            case 4: {
                lcd.setCursor(3, 0);
                lcd.print("Set Humidity:");
                lcd.setCursor(6, 1);
                lcd.print(setHumidityValue);
                lcd.setCursor(11, 1);
                lcd.print("% RH");
                lcd.setCursor(4, 3);
                lcd.print("=>");// special select item character
                //display of reference humidity
                lcd.setCursor(1, 2);
                lcd.print("Humidity Tolerance:");
                lcd.setCursor(6, 3);
                lcd.print(humidityTolerance);
                lcd.setCursor(10, 3);
                lcd.print("% RH");

                break;
            }

            case 5: {

                lcd.setCursor(0, 2);
                lcd.print("=>");
                lcd.setCursor(0, 0);
                lcd.print("Set Incubation_Mode:");
                lcd.setCursor(2, 2);
                lcd.print(setIncubationMode[incubationModeCounter]);
//                lcd.setCursor(9,2);
//                lcd.print("Days");
                break;

            }

            case 6: {
                if (incubationModeCounter == 0) {
                    buttonsCounter = 7;
                } else if (incubationModeCounter == 1) {
                    lcd.setCursor(4, 2);
                    lcd.print("=>");
                    lcd.setCursor(0, 0);
                    lcd.print("Set Incubation_Time:");
                    lcd.setCursor(6, 2);
                    lcd.print(setIncubationDays);
                    lcd.setCursor(9, 2);
                    lcd.print("Days");
                    break;
                }

                if (incubationModeCounter == 2) {

                    //TODO: egg trays turning
                    buttonsCounter = 8;
                }
            }

            case 7: {
                lcd.setCursor(4, 2);
                lcd.print("=>");
                lcd.setCursor(0, 0);
                lcd.print("Time Between Spins:");
                lcd.setCursor(6, 2);
                lcd.print(timeBetweenSpin);
                lcd.setCursor(9, 2);
                lcd.print("Hour/s");

                break;
            }

            case 8: {
                lcd.setCursor(0, 0);
                lcd.print(" Press 'Ok' to save");
                lcd.setCursor(2, 1);
                lcd.print(" Changes or any");
                lcd.setCursor(0, 2);
                lcd.print("Other key to discard");
                break;
            }

            case 9: {
                lcd.clear();
                saveChanges();
                /*  lcd.setCursor(0,0);
                 lcd.print("saved");
                 delay(300); */

                lcd.clear();
                lcd.setCursor(4, 0);
                lcd.print("SAVING...");
                lcd.setCursor(3, 3);
                for (int i = 0; i < 17; i++) {
                    lcd.setCursor(i + 1, 1);
                    // lcd.print("*");
                    lcd.write(byte(10));
                    lcd.setCursor(i + 1, 2);
                    lcd.write(byte(10));
                    delay(60);
                }
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("SAVED SUCCESSFULLY!!");
                delay(500);
                lcd.clear();



//                else{
//                    lcd.clear();
//                    discardChanges();
//                    lcd.setCursor(0,0);
//                    lcd.print("changes discarded");
//                    delay(300);
//                }
//
//                lcd.clear();

                break;
            }

            default: {
                lcd.home();
                lcd.print("Temp: ");
                lcd.print(avgTemp);
                lcd.print((char) 223);
                lcd.print("C");
                lcd.setCursor(13, 0);
                if (heatingState)
                    if (blinkState)
                        lcd.write(byte(1));
                    else
                        lcd.print(" ");
                else
                    lcd.print(" ");

//                lcd.print("  ");
//                lcd.print(temp2);

                //lcd.println(" ");
//    lcd.setCursor(16,0);
//    if(voltage<=18){
//    lcd.write(2);
//    }
//    if(18<voltage && voltage<=32){
//    lcd.write(3);}
//if(32<voltage && voltage<=50){
//    lcd.write(4);}
//     if(50<voltage && voltage<=81){
//    lcd.write(5);}
//     if(81<voltage && voltage<=96){
//    lcd.write(6);}
//    if(96<voltage && voltage<=100){
//    lcd.write(7);}
//    if(voltage<10)
//    lcd.print("0");
//    lcd.print(voltage);
//    lcd.print("%");
                lcd.setCursor(0, 1);
                lcd.print("Humid: ");
                lcd.print(avgHum);
                lcd.print("%");

//        lcd.print("  ");
//        lcd.print(hum2);


                lcd.setCursor(0, 2);
                lcd.print("Time: ");
//        lcd.print(day);
//        lcd.print("d ");
                lcd.print(hours);
                lcd.print("h ");
                lcd.print(minutes);
                lcd.print("m ");

                lcd.print(seconds);
                lcd.print("s");
                if (seconds < 10)
                    lcd.print(" ");

                lcd.setCursor(0, 3);
                lcd.print("Days :");
                lcd.print(day);
                lcd.setCursor(10, 3);
                lcd.print("Count :");
                lcd.print(daysCounter);
                //   if (celcius > 0)
                //       lcd.print(celcius, 1);
                //   else
                //   if (powerPriority == 1)
                //      lcd.print("GAS ");
                //  else
                //     lcd.print("ELEC");
//        lcd.print((char) 223);
//        lcd.print("C");

            }


        }


    }

    void resetIncubation(){
        lcd.setCursor(0, 0);
        lcd.print(" Press 'Ok' to reset");
        lcd.setCursor(2, 1);
        lcd.print(" Incubation or any");
        lcd.setCursor(0, 2);
        lcd.print("Other key to discard");

    }

    void stopIncubation(){

        lcd.setCursor(0, 0);
        lcd.print(" Press 'Ok' to stop");
        lcd.setCursor(2, 1);
        lcd.print(" Incubation or any");
        lcd.setCursor(0, 2);
        lcd.print("Other key to discard");

    }

};

Menu menu;