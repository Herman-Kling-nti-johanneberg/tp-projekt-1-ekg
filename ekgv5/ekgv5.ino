//Check your heart beat and see your BPM on a screen
//The code that's not original is from PulseSensor's library PulseSensor Playground's example code "Getting_BPM_to_Monitor"

#define USE_ARDUINO_INTERRUPTS true           // Set-up low-level interrupts for most acurate BPM math.           *Not original code
#include <PulseSensorPlayground.h>            // Includes the PulseSensorPlayground Library.                      *Not original code
#include "U8glib.h"                           // Library for the screen
U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE); // Library for the screen

//  Variables
const int PulseWire = 0;       // Sensor signal wire connected to ANALOG PIN 0                               
int Threshold = 560;           // Determine which Signal to "count as a beat" and which to ignore. Tuned for best results
int Signal;                    //Holds the raw sensor data

PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"   *Not original code

void setup() {
  Serial.begin(9600);                   // set up Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it.      *Not original code
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  
  pulseSensor.begin();                  // set up pulse sensor
}

//draws the raw value in serial plotter, gets bpm and refreshes screen
void loop() {

  //used for tuning the threshold and troubleshooting
  Signal = analogRead(PulseWire);   //get the sensor value to "signal"
  Serial.println(Signal);           //draw the value in serial plotter

  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function that returns BPM as an int.       *Not original code


  // Refresh screen
  oled.firstPage();
  do {
    draw(myBPM);
  } while (oled.nextPage());
    
  delay (20);
}

//print strings on the screen
void draw(int bpm) {
  oled.setFont(u8g_font_fub20);                 // Set font and size
  oled.drawStr(0, 20, "BPM:" );                 //print "BPM:" on the screen
  oled.drawStr(80, 20, String(bpm).c_str());    //Print bmp value from the previous void loop
}
