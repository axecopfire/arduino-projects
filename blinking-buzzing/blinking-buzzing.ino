
#include "pitches.h"

// Define Pins
#define BLUE 3
#define GREEN 5
#define RED 6
#define delayTime 10

int ledPin = 4;
int buttonApin = 7;
int buttonBpin = 8;
int buzzer = 9; // the pin of the active buzzer
int passiveBuzzerPin = 10;
int tiltSwitchPin = 11;

byte leds = 0;

// notes in the melody:
int melody[] = {
    // NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
    NOTE_C6, NOTE_B5, NOTE_C6, NOTE_A5, NOTE_C6, NOTE_G5, NOTE_C6, NOTE_F5, NOTE_C6, NOTE_E5, NOTE_C6, NOTE_D5, NOTE_C6, NOTE_C5, NOTE_C5, NOTE_C5};
int duration = 500; // 500 miliseconds

void redLedSwitch()
{
  if (digitalRead(buttonApin) == LOW || digitalRead(tiltSwitchPin) == HIGH)
  {
    digitalWrite(ledPin, HIGH);
  }
  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(ledPin, LOW);
  }
}

void lightChanging()
{
  int redValue;
  int greenValue;
  int blueValue; // wait for a second

  redValue = 200; // choose a value between 1 and 255 to change the color.
  greenValue = 0;
  blueValue = 0;

  for (int i = 0; i < 200; i += 1) // fades out red bring green full when i=255
  {
    redLedSwitch();
    redValue -= 1;
    greenValue += 1;
    // The following was reversed, counting in the wrong directions
    // analogWrite(RED, 255 - redValue);
    // analogWrite(GREEN, 255 - greenValue);
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    delay(delayTime);
  }

  redValue = 0;
  greenValue = 200;
  blueValue = 0;

  for (int i = 0; i < 200; i += 1) // fades out green bring blue full when i=255
  {
    redLedSwitch();
    greenValue -= 1;
    blueValue += 1;
    // The following was reversed, counting in the wrong directions
    // analogWrite(GREEN, 255 - greenValue);
    // analogWrite(BLUE, 255 - blueValue);
    analogWrite(GREEN, greenValue);
    analogWrite(BLUE, blueValue);
    delay(delayTime);
  }

  redValue = 0;
  greenValue = 0;
  blueValue = 200;

  for (int i = 0; i < 200; i += 1) // fades out blue bring red full when i=255
  {
    redLedSwitch();
    // The following code has been rearranged to match the other two similar sections
    blueValue -= 1;
    redValue += 1;
    // The following was reversed, counting in the wrong directions
    // analogWrite(BLUE, 255 - blueValue);
    // analogWrite(RED, 255 - redValue);
    analogWrite(BLUE, blueValue);
    analogWrite(RED, redValue);
    delay(delayTime);
  }
}

void onboardLight()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);                     // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED off by making the voltage LOW
  delay(100);
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  delay(100);
}

void activeTone()
{
  unsigned char i;

  int highDelay = random(5);
  int lowDelay = random(5);
  int randNumber = random(300);
  int numOfBeeps = random(50);

  for (i = 0; i < numOfBeeps; i++)
  {
    redLedSwitch();
    digitalWrite(buzzer, HIGH);
    delay(highDelay);
    digitalWrite(buzzer, LOW);
    delay(lowDelay); // wait for 1ms
  }
  delay(randNumber);
}

void activeBuzzer()
{
  unsigned char j;
  int randNumber;
  j = 0;

  while (j < 20)
  {
    // output an frequency
    activeTone();
    j++;
  }
}

void passiveBuzzer()
{
  for (int thisNote = 0; thisNote < 8; thisNote++)
  {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(passiveBuzzerPin, melody[thisNote], duration);

    // Output the voice after several minutes
    delay(100);
  }

  // restart after two seconds
  delay(5000);
}

// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);
  pinMode(ledPin, OUTPUT);
  pinMode(tiltSwitchPin, INPUT);
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT); // initialize the buzzer pin as an output
}

// the loop function runs over and over again forever
void loop()
{
  onboardLight();
  lightChanging();
  activeBuzzer();
  passiveBuzzer();
  redLedSwitch();
}