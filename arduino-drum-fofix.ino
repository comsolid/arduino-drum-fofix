/**
 * Arduino Drum for FoFiX
 */

#define NUM_SENSORS 6
#define DRUM_HIT 1000      // Minimum Analog value to cause a drum hit
#define DELAY 70
#define MAX_PLAY_TIME 90  // Cycles before a 2nd hit is allowed
#define RED_PAD 'a'
#define YELLOW_PAD 'e'
#define BLUE_PAD 'j'
#define GREEN_PAD 'k'
#define SPACE_BAR 32
#define ORANGE_PAD SPACE_BAR // FOOT
#define SERIAL_RATE 57600

// these constants won't change:
const int knocks[NUM_SENSORS] = {A0, A1, A2, A3, A4, A5}; // the piezos are connected to analog pins

boolean activePad[NUM_SENSORS] = {0,0,0,0,0,0};   // Array of flags of pad currently playing
int PinPlayTime[NUM_SENSORS] = {0,0,0,0,0,0};     // Counter since pad started to play

int sensorReading = 0;      // variable to store the value read from the sensor pin

void setup() {
    Serial.begin(SERIAL_RATE); // use the serial port
    Keyboard.begin();
}

void loop() {
    for (short i = 0; i < NUM_SENSORS; i++) {

        sensorReading = analogRead(knocks[i]);

        if((sensorReading > DRUM_HIT)) {
            if((activePad[i] == false)) {
                play(knocks[i], sensorReading);
                PinPlayTime[i] = 0;
                activePad[i] = true;
                } else {
                    PinPlayTime[i] = PinPlayTime[i] + 1;
                }
        } else if((activePad[i] == true)) {
            PinPlayTime[i] = PinPlayTime[i] + 1;
            if(PinPlayTime[i] > MAX_PLAY_TIME) {
                activePad[i] = false;
                play(knocks[i], sensorReading);
            }
        }
    }
}

void play(int knock, int sensorReading) {
    if (sensorReading > DRUM_HIT) {
        Serial.print("Sensor reading: ");
        Serial.print(sensorReading);
        Serial.print(", knock: ");
        Serial.print(knock);
        switch(knock) {
        case A0:
            Serial.println(", Knock Red!");
            Keyboard.write(RED_PAD);
            break;
        case A1:
            Serial.println(", Knock Yellow!");
            Keyboard.write(YELLOW_PAD);
            break;
        case A2:
            Serial.println(", Knock Blue!");
            Keyboard.write(BLUE_PAD);
            break;
        case A3:
            Serial.println(", Knock Green!");
            Keyboard.write(GREEN_PAD);
            break;
        case A4:
            Serial.println(", Knock Orange-1!");
            Keyboard.write(ORANGE_PAD);
            break;
        case A5:
            // Caso a bateria tenha pedal duplo!
            Serial.println(", Knock Orange-2!");
            Keyboard.write(ORANGE_PAD);
            break;
        default:
            Serial.println(", ignored value.");
        }
    }
}
