
int led1 = D0;
int led2 = D7;
char name[5] = {'j','o','c','e','n'};                       //first name
char surname[8] = {'p','a','g','a','y','o','n','a'};        //surname


void setup() {
    
    pinMode(led2, OUTPUT);
    digitalWrite(led2, LOW);

}

void loop() {
    
    for (int i; i<sizeof(name); i++)
    {
        translate(name[i]);
        delay(1000);
    }

}

/*
Translate Method
Input: single letter
Output: none
Description: This method converts the letter into morse code in the form of blinking lights in the Photon Particle
*/
void translate(char letter) {
    
    switch(letter) {
        case 'a' :
            dot();
            dash();
            break;
        case 'b' :
            dash();
            dot();
            dot();
            dot();
            break;
        case 'c' :
            dash();
            dot();
            dash();
            dot();
            break;
        case 'd':
            dash();
            dot();
            dot();
            break;
        case 'e':
            dot();
            break;
        case 'f':
            dot();
            dot();
            dash();
            break;
        case 'g':
            dash();
            dash();
            dot();
            break;
        case 'h':
            for(int i=0; i<4; i++) {
                dot();
            }
            break;
        case 'i':
            dot();
            dot();
            break;
        case 'j':
            dot();
            for(int i=0; i<3; i++) {
                dash();
            }
            break;
        case 'k':
            dash();
            dot();
            dash();
            break;
        case 'l':
            dot();
            dash();
            dot();
            dot();
            break;
        case 'm':
            dash();
            dash();
            break;
        case 'n':
            dash();
            dot();
            break;
        case 'o':
            for(int i=0; i<3; i++) {
                dash();
            }
            break;
        case 'p':
            dot();
            dash();
            dash();
            dot();
            break;
        case 'q':
            dash();
            dash();
            dot();
            dash();
        case 'r':
            dot();
            dash();
            dot();
        case 's':
            for(int i=0; i<3; i++) {
                dot();
            }
            break;
        case 't':
            dash();
            break;
        case 'u':
            dot();
            dot();
            dash();
            break;
        case 'v':
            for(int i=0; i<3; i++) {
                dot();
            }
            dash();
            break;
        case 'w':
            dot();
            dash();
            dash();
            break;
        case 'x':
            dash();
            dot();
            dot();
            dash();
            break;
        case 'y':
            dash();
            dot();
            dash();
            dash();
        case 'z':
            dash();
            dash();
            dot();
            dot();
            break;
        default:
            break;
    }
}

/*
Dot Method
Input: none
Output: none
Description: blinks in-built LED light from the particle photon imitating a dot for the Morse Code
*/
void dot() {
    
    digitalWrite(led2, HIGH);
    delay(300);
    digitalWrite(led2, LOW);
    delay(100);
}

/*
Dash Method
Input: none
Output: none
Description: blinks in-built LED light from the particle photon imitating a dash for the Morse Code
*/
void dash() {
    
    digitalWrite(led2, HIGH);
    delay(800);
    digitalWrite(led2, LOW);
    delay(100);
}