
class ButtonsHandler{
public:

    boolean upDebounceButton(boolean state)
    {
        boolean stateNow = digitalRead(upButton);
        if(state!=stateNow)
        {
            delay(10);
            stateNow = digitalRead(upButton);
        }
        return stateNow;

    }

    boolean selectDebounceButton(boolean state)
    {
        boolean stateNow = digitalRead(selectButton);
        if(state!=stateNow)
        {
            delay(10);
            stateNow = digitalRead(selectButton);
        }
        return stateNow;

    }

    boolean downDebounceButton(boolean state)
    {
        boolean stateNow = digitalRead(downButton);
        if(state!=stateNow)
        {
            delay(10);
            stateNow = digitalRead(downButton);
        }
        return stateNow;

    }

    void discardChanges() {
        Serial.println("&&&&");
        setTempValue = operatingTempValue;
        setHumidityValue = operatingHumidityValue;
        tempTolerance = EEPROM.read(11);
        humidityTolerance = EEPROM.read(12);
        setIncubationDays = EEPROM.read(7);;
        timeBetweenSpin = EEPROM.read(14);
        buttonsCounter = 0;


    }

    void buttonsListener(){


        if(upDebounceButton(upButtonState) == HIGH && upButtonState == LOW)
        {

            Serial.println("up");
            // heatingState = !heatingState;
            upButtonState = HIGH;
            if(buttonsCounter==1){
setTempValue = setTempValue+0.1;

        }
            else if(buttonsCounter==2){
                tempTolerance = tempTolerance+0.1;
            }

            else if (buttonsCounter == 3){
                setHumidityValue = setHumidityValue+1;
            }

            else if (buttonsCounter==4){
                humidityTolerance = humidityTolerance +1;
            }

            else if(buttonsCounter==5){
                incubationModeCounter++;
                lcd.clear();
                if(incubationModeCounter>2)
                    incubationModeCounter =0;


            }

            else if (buttonsCounter==6){
                setIncubationDays = setIncubationDays + 1;
            }

            else if(buttonsCounter==7){
                timeBetweenSpin = timeBetweenSpin+1;
            }

            else if(buttonsCounter==8){
                lcd.clear();
                discardChanges();
            }

    }

        else if(upDebounceButton(upButtonState) == LOW && upButtonState == HIGH)
        {
            upButtonState = LOW;
        }

        if(selectDebounceButton(selectButtonState) == HIGH && selectButtonState == LOW)
        {
             buttonsCounter++;
              lcd.clear();
            Serial.println("select");
            // heatingState = !heatingState;
            selectButtonState = HIGH;
        }
        else if(selectDebounceButton(selectButtonState) == LOW && selectButtonState == HIGH)
        {
            selectButtonState = LOW;
        }

        if(downDebounceButton(downButtonState) == HIGH && downButtonState == LOW)
        {
            //buttonsCounter++;
            //   lcd.clear();
            Serial.println("down");
            // heatingState = !heatingState;
            downButtonState = HIGH;

            if(buttonsCounter==1){
                setTempValue = setTempValue-0.1;

            }

            else if(buttonsCounter==2){
tempTolerance = tempTolerance-0.1;
            }

            else if (buttonsCounter == 3){
setHumidityValue = setHumidityValue-1;
            }

            else if (buttonsCounter==4){
                humidityTolerance = humidityTolerance -1;
            }

            else if(buttonsCounter==5){
                incubationModeCounter--;
                lcd.clear();
                Serial.println(incubationModeCounter);
                if(incubationModeCounter<0)
                    incubationModeCounter =2;


            }

            else if (buttonsCounter==6){
                setIncubationDays = setIncubationDays - 1;
            }

            else if(buttonsCounter==7){
                timeBetweenSpin = timeBetweenSpin-1;
            }

            else if(buttonsCounter==8){
                lcd.clear();
                discardChanges();
            }
        }
        else if(downDebounceButton(downButtonState) == LOW && downButtonState == HIGH)
        {
            downButtonState = LOW;
        }

    }

};

ButtonsHandler buttonsHandler;