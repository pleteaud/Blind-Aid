#include <Servo.h>  // servo library
#define S0 5
#define S1 6
#define S2 9
#define S3 8
#define melodyPin 7
#define sensorOut 10
#define left_forward 180
#define right_forward 0
#define right_backward 180
#define left_backward 0
#define stop_wheel 90
int Blue_frequency = 0;
int Red_frequency = 0;
int Green_frequency = 0;
int white_frequency = 0;
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
int tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4, 
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18,18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};
const int Yellow_buttonpin = 3; //declare pushbutton pins
const int Green_buttonpin = 4;
const int Blue_buttonpin = 2;
int counter = 0;

Servo servo_r;                 // Declare right and left servos
Servo servo_l;
int delayRandom = 0;
void turnLeft(); void turnRight(); void forward(); void reverse();void search();
int song =0;
void setup(){
  pinMode(melodyPin, OUTPUT);//buzzer
// set up the color sens as
pinMode(S0, OUTPUT);
pinMode(S1, OUTPUT);
pinMode(S2, OUTPUT);
pinMode(S3, OUTPUT);
pinMode(sensorOut, INPUT);

//setup buttons to be inputs
pinMode(Yellow_buttonpin, INPUT);
pinMode(Green_buttonpin, INPUT);
pinMode(Blue_buttonpin, INPUT);

// Setting frequency-scaling to 20%
digitalWrite(S0,HIGH);
digitalWrite(S1,HIGH);
servo_r.attach(12);    // attach two servos to pins 12 and 13
servo_l.attach(13);
Serial.begin(9600);

}


        
void loop() {
  int Yellow_button_State, Green_button_State, Blue_button_state; // variables to hold buttons
servo_l.write(stop_wheel);    //left motor Clockwise for reverse
  servo_r.write(stop_wheel);

     Yellow_button_State = digitalRead(Yellow_buttonpin);
     Green_button_State = digitalRead(Green_buttonpin);
     Blue_button_state = digitalRead(Blue_buttonpin);
bool red_tape = false;
  bool green_tape = false;
  bool Blue_tape = false;
  if ((Yellow_button_State == LOW) && (Green_button_State == HIGH)&&(Blue_button_state == HIGH)){
 red_tape = true;
  }
   if ((Yellow_button_State == HIGH) && (Green_button_State == LOW) && (Blue_button_state == HIGH)){
      green_tape = true;
    }
     if ((Yellow_button_State == HIGH) && (Green_button_State == HIGH) && (Blue_button_state == LOW)){
      Blue_tape = true;
    }
while (red_tape == true)
{
  search();  // move around 
      // Setting red filtered photodiodes to be read
 digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  Red_frequency = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  Red_frequency = map(Red_frequency, 16,110,255,0);
   Serial.print("R= ");//printing name
  Serial.print(Red_frequency);//printing RED color frequency
  Serial.print("  ");
  Serial.println(" ");
  delay(100);
      if (Red_frequency >= 170 && Red_frequency <250)
      {
     
        red_tape = false;
          //stop and make some noise
          servo_l.write(stop_wheel);    //left motor Clockwise for reverse
  servo_r.write(stop_wheel);
   Serial.println("Red Tape Reached. Stopping");
      sing(1);           
      }
      else if (Red_frequency <70)
      {
        search();
        }
        else
        {
        reverse();
            int n = random(1,2);
            if (n==1){
             turnRight();
             
          }
          else if(n==2){
            turnLeft();
            }
        }
}

while (green_tape == true)
{
  search();
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    Green_frequency = pulseIn(sensorOut, LOW);
    //Remaping the value of the frequency to the RGB Model of 0 to 255
    Green_frequency = map(Green_frequency, 17, 130, 255, 0);
    Serial.print("G= ");//printing name
    Serial.print(Green_frequency);//printing RED color frequency
    Serial.print("  ");
    Serial.println(" ");
    delay(100);
    //green tape
    if ( Green_frequency >= 170 && Green_frequency <= 230)

      {
        green_tape = false;
          //stop and make some noise
          servo_l.write(stop_wheel);    //left motor Clockwise for reverse
  servo_r.write(stop_wheel);
   Serial.println("Red Tape Reached. Stopping");
  sing(2);
 //beeep periodically
            
      }
      else if (Green_frequency <80)
      {
        search();
        }
        else
        {
        reverse();
            int n = random(1,2);
            if (n==1){
             turnRight();
             
          }
          else if(n==2){
            turnLeft();
            }
        }
      }



while (Blue_tape == true)
{
    search();
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    Blue_frequency = pulseIn(sensorOut, LOW);
    //Remaping the value of the frequency to the RGB Model of 0 to 255
    Blue_frequency = map(Blue_frequency, 35, 67, 255, 0);
    // Printing the value on the serial monitor
    Serial.print("B= ");//printing name
    Serial.print(Blue_frequency);//printing RED color frequency
    Serial.print("  ");
    Serial.println(" ");
    delay(100);
    if (Blue_frequency >=190 && Blue_frequency < 255)
      {
        Blue_tape = false;
          //stop and make some noise
          servo_l.write(stop_wheel);    //left motor Clockwise for reverse
  servo_r.write(stop_wheel);
   Serial.println("Red Tape Reached. Stopping");
   sing(2);
   delay(5000);
   sing(1);       
      }
      else if (Blue_frequency <70)
      {
        search();
        }
        else
        {
        reverse();
            int n = random(1,2);
            if (n==1){
             turnRight();
             
          }
          else if(n==2){
            turnLeft();
            }
        }
      }
}
void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(melodyPin, note, duration);
 //Stop tone on buzzerPin
  noTone(melodyPin);
  delay(50);
}

void search()
{

forward();
    //right motor clockwise forward
            //  millisecond delay
}
void turnLeft()
{
  reverse();
  servo_l.write(left_backward);    //left motor Clockwise for reverse
  servo_r.write(right_forward);   //right motor clockwise forward
  delayRandom = random(900, 1550); //randomized delay alters angle of turn
  delay(delayRandom); 
}
        
void turnRight()
{
  reverse();
  servo_r.write(right_backward);    // spin right motor backwards
  servo_l.write(left_forward); // spin Left motor forwards
int  delayRandom = random(900, 1550); //randomized delay alters angle of turn
  delay(delayRandom);        
}
 
void reverse()
{
  servo_r.write(right_backward); //right motor counterclockwise reverse
  servo_l.write(left_backward);  //left motor Clockwise for reverse
  delay(1500);      //  .5 second delay
}
 
void forward()
{
 
  servo_r.write(right_forward);   //right motor clockwise forward
  servo_l.write(left_forward); //left motor counterClockwise for forward   
 delayRandom = random(900, 1550);
}

void sing(int s){      
   // iterate over the notes of the melody:
   song = s;
   if(song==2){
     Serial.println(" 'Underworld Theme'");
     int size = sizeof(underworld_melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {
       // to calculate the note duration, take one second
       // divided by the note type.
       int noteDuration = 1000/underworld_tempo[thisNote];
       buzz(melodyPin, underworld_melody[thisNote],noteDuration);
       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(melodyPin, 0,noteDuration);

    }

   }else{
     Serial.println("'Mario Theme'");
     int size = sizeof(melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/tempo[thisNote];

       buzz(melodyPin, melody[thisNote],noteDuration);

       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(melodyPin, 0,noteDuration);

    }
  }
}
void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}
