LEDStatus blinkRED(RGB_COLOR_RED, LED_PATTERN_BLINK);
LEDStatus blinkGREEN(RGB_COLOR_GREEN, LED_PATTERN_BLINK);
LEDStatus blinkBLUE(RGB_COLOR_BLUE, LED_PATTERN_BLINK);
LEDStatus blinkCYAN(RGB_COLOR_CYAN, LED_PATTERN_BLINK);

void setup() {
    
    Particle.function("led",colorSwitch);

}

void loop() {
    

}

int colorSwitch(String command) {

    if (command=="blue") {
        changeBlue();
        return 1;
    }
    else if (command=="red") {
        changeRed();
        return 1;
    }
    else if (command=="green") {
        changeGreen();
        return 1;
    }
    else if (command=="cyan") {
        changeCyan();
        return 1;
    }
    else {
        return -1;
    }
}

void changeBlue() {
    blinkRED.setActive(false);
    blinkGREEN.setActive(false);
    blinkCYAN.setActive(false);
    blinkBLUE.setActive(true);
}

void changeGreen() {
    blinkRED.setActive(false);
    blinkBLUE.setActive(false);
    blinkCYAN.setActive(false);
    blinkGREEN.setActive(true);
}

void changeRed() {
    blinkGREEN.setActive(false);
    blinkBLUE.setActive(false);
    blinkCYAN.setActive(false);
    blinkRED.setActive(true);
}

void changeCyan() {
    blinkGREEN.setActive(false);
    blinkBLUE.setActive(false);
    blinkRED.setActive(false);
    blinkCYAN.setActive(true);
}