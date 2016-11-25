//for strips in parralell instead of series

#include <FastLED.h>
#include <elapsedMillis.h>
#define LED_COUNT 4  
  

int idex;                
int hue;                
int bright;              
int sat = 255;    
struct CRGB leds[LED_COUNT];
       
int cnt;
int md;
int swp; 
int butOne;
int butValOne;

long randNumber;


void button () { //if you want to add an external button to cycle through the modes
   butOne = digitalRead(9);
 if (butOne == LOW){
 switch (butValOne){
 case 0:  {butValOne = 1; swp = 1; break; } 
 case 1:  {butValOne = 2; swp = 2; break; } 
 case 2:  {butValOne = 3; swp = 3; break; }
 case 3:  {butValOne = 4; swp = 4; break; }
 case 4:  {butValOne = 5; swp = 5; break; }
 case 5:  {butValOne = 0; swp = 0; break; }
 } }

switch (swp) {
case 0: multiflick(); break;
case 1: natural(); break;
case 2: blue_fire (); break;
case 3: green_fire (); break;
case 4: purple_fire (); break;
case 5: rainbow_fire (); break;
 break; }
 
}


void reset_switch () { //to use the reset button to switch randomly between modes
  switch (randNumber){
    case 0: multiflick (); break;
    case 1: blue_fire (); break;
    case 2: green_fire (); break;
    case 3: purple_fire (); break;
    case 4: rainbow_fire (); break;
    break;
}}


void natural() {   //looks like a natural candle                    
  idex = random(0, LED_COUNT); //selects one of the 4 LEDs at random
  hue = random(30, 60);  //randomly picks a hue between two numbers (these are orangy/yellowy/)
  bright = random(100, 200); //randomly picks a brightness bewtween two values
  leds[idex] = CHSV(hue, sat, bright); //shows them
  LEDS.show();
   wait(); //short delay so it doesn't go too fast
    
    idex = random(0, LED_COUNT);  //pick one of the 4 LEDs again at random and turn it off
    leds[idex] = CHSV(0, 0, 0);
    LEDS.show();
    
    
    // idex = random(0, LED_COUNT);  //an extra random LED off, for experementing
    //  leds[idex] = CHSV(0, 0, 0);
      //LEDS.show();
     
   wait(); //again so it doesn't go too fast
  }



void multiflick() {          //looks like a natural candle most of the time, and then after a set number of loops - 
                             // it changes to one of the colours (selected randomly) just briefly enough to catch your eye - 
                             //then it goes back to the natural candle again
cnt ++; //start counting
  idex = random(0, LED_COUNT);
  hue = random(30, 60);  //30 60
  bright = random(160, 200);
  leds[idex] = CHSV(hue, sat, bright);
  LEDS.show();
  wait();
        
if (cnt == 255) { md = random(0,3);  //when you reach a set number randomly pick a mode
while (cnt < 259) { cnt ++; // keep counting and while that number is below another number
if (md == 0) {blue_fire();} //if mode is 0 turn the fire blue
else if (md == 1) {green_fire ();} //or if mode is 1 turn the fire green
else if (md == 2) {purple_fire();} } //or if the mode is 2 turn the fire purple
cnt = 0;} //after the higher number is reached, restart the count
   
   else { //if you didnt reach the minimum count, just pick a led at random and turn it off, wait a bit and start the loop again
    idex = random(0, LED_COUNT);  
    leds[idex] = CHSV(0, 0, 0);
    LEDS.show(); }
    wait(); 
  }


void purple_fire () {
  idex = random(0, LED_COUNT);
  hue = random(190, 210);  
  bright = random(160, 255);
  sat = random(120, 255);
  
  leds[idex] = CHSV(hue, sat, bright);
  LEDS.show();
  wait();
    
   idex = random(0, LED_COUNT);  
   leds[idex] = CHSV(0, 0, 0);   
   LEDS.show();
   wait(); 
 }

void green_fire () {
  idex = random(0, LED_COUNT);
  hue = random(90, 110);  
  bright = random(160, 255);
  sat = random(150, 210);
  
  leds[idex] = CHSV(hue, sat, bright);
  LEDS.show();
  wait();
    
   idex = random(0, LED_COUNT);  
   leds[idex] = CHSV(0, 0, 0);
   LEDS.show();
    wait(); 
}


void blue_fire () {
  idex = random(0, LED_COUNT);
  hue = random(140, 150);  
  bright = random(160, 255);
  sat = random(140, 235);
  
  leds[idex] = CHSV(hue, sat, bright);
  LEDS.show();
  wait();
    
   idex = random(0, LED_COUNT);  
   leds[idex] = CHSV(0, 0, 0);
   LEDS.show();
   wait(); 
}


void rainbow_fire () { //this is a little harder because you want all the leds to be the same hue at once, otherwise it gets messy
int rcnt;
 
hue = random(0, 255); //pick a hue at random
while (rcnt <4) { rcnt ++; //keep that hue for 4 loops but change everything else as usual
   
  idex = random(0, LED_COUNT);
  bright = random(100, 255);
  sat = random(120, 255);

  leds[idex] = CHSV(hue, sat, bright);
  LEDS.show();
  wait();
    
  idex = random(0, LED_COUNT);  
  leds[idex] = CHSV(0, 0, 0);
  LEDS.show();

  idex = random(0, LED_COUNT);  
  leds[idex] = CHSV(0, 0, 0);
  LEDS.show();
  wait(); 
  
} rcnt = 0;
  for (int i = 0; i < 4; i++){ //to turn them all off before the hue changes, othewise leftover LEDS mix
  leds[i] = CHSV(0, 0, 0);}
  }


void wait() {  //instead of a delay
unsigned long startTime = millis();
while(millis() - startTime < 110){}
}


void setup() {
  //initalise strips
FastLED.addLeds<APA102,4,3,BGR>(leds, 2); //first 2 leds (total number leds on the first strip)
FastLED.addLeds<APA102,7,6,BGR>(leds, 2, LED_COUNT); //from the 1st index of the 2nd strip to the total number of leds
pinMode(9, INPUT);  //in case we want to use an external button
randomSeed(analogRead(0)); //uses data of a floating pin (A0) to pick a random point in the random string
randNumber = random(5);    //between 0 and 4 (inclusive). this random number picks the mode in the reset_switch loopand changes every time -
                           //the reset button is pressed or the power toggled
}

void loop() { //pick which loop you wanna run

//button ();

reset_switch ();

//natural();
//blue_fire ();
//green_fire ();
//multiflick();
//purple_fire (); 
//rainbow_fire ();

}

