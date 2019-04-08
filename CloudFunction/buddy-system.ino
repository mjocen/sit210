LEDStatus blinkRED(RGB_COLOR_RED, LED_PATTERN_BLINK);
LEDStatus blinkBLUE(RGB_COLOR_BLUE, LED_PATTERN_BLINK);
LEDStatus blinkCYAN(RGB_COLOR_CYAN, LED_PATTERN_BLINK);

int led1 = D7;
int led2 = D6;

void setup() {
    
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    Particle.subscribe("Deakin_RIOT_SIT210_Photon_Buddy", myHandler);
    
    digitalWrite(led1, LOW);            //set inbuilt led to low
    digitalWrite(led2, HIGH);            //set inbuilt led to low
}

void loop() {
    

}

void myHandler(const char *event, const char *data) {

    if(strcmp(data,"wave")==0) {
        wave();
        delay(1000);
    }
    else if (strcmp(data,"pat")==0) {
        pat();
        delay(1000);
    }
    else
    {
        // something else
    }
}

void wave() {
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    delay(200);
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
    delay(200);
    digitalWrite(led2, HIGH);
    delay(200);
    digitalWrite(led2, LOW);
}

void pat() {
    digitalWrite(led1, HIGH);
    delay(200);
    digitalWrite(led1, LOW);
    delay(200);
    digitalWrite(led1, HIGH);
    delay(200);
    digitalWrite(led1, LOW);
    delay(200);
    digitalWrite(led1, HIGH);
    delay(200);
    digitalWrite(led1, LOW);
}