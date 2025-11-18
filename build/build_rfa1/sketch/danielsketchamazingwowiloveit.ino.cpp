#include <Arduino.h>
#line 1 "C:\\Users\\HP\\Desktop\\danielsketchamazingwowiloveit\\danielsketchamazingwowiloveit.ino"
#include <MakerKit.h>

int hasObject;
int ir_left;
int ir_right;

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
Adafruit_SSD1306 display(128, 32, &Wire, -1);


// Describe this function...
#line 13 "C:\\Users\\HP\\Desktop\\danielsketchamazingwowiloveit\\danielsketchamazingwowiloveit.ino"
void sharp_left();
#line 24 "C:\\Users\\HP\\Desktop\\danielsketchamazingwowiloveit\\danielsketchamazingwowiloveit.ino"
void motor_stop();
#line 35 "C:\\Users\\HP\\Desktop\\danielsketchamazingwowiloveit\\danielsketchamazingwowiloveit.ino"
void read_sensors();
#line 55 "C:\\Users\\HP\\Desktop\\danielsketchamazingwowiloveit\\danielsketchamazingwowiloveit.ino"
void sharp_right();
#line 66 "C:\\Users\\HP\\Desktop\\danielsketchamazingwowiloveit\\danielsketchamazingwowiloveit.ino"
void straight();
#line 75 "C:\\Users\\HP\\Desktop\\danielsketchamazingwowiloveit\\danielsketchamazingwowiloveit.ino"
void reverse();
#line 86 "C:\\Users\\HP\\Desktop\\danielsketchamazingwowiloveit\\danielsketchamazingwowiloveit.ino"
void setup();
#line 106 "C:\\Users\\HP\\Desktop\\danielsketchamazingwowiloveit\\danielsketchamazingwowiloveit.ino"
void loop();
#line 13 "C:\\Users\\HP\\Desktop\\danielsketchamazingwowiloveit\\danielsketchamazingwowiloveit.ino"
void sharp_left() {
  digitalWrite(13,HIGH);
  digitalWrite(14,LOW);
  analogWrite(25,150); // motor (left)
  digitalWrite(18,HIGH);
  digitalWrite(19,LOW);
  analogWrite(15,200); //motor (right)
}


// Describe this function...
void motor_stop() {
  digitalWrite(13,HIGH);
  digitalWrite(14,LOW);
  analogWrite(25,0); 
  digitalWrite(18,HIGH);
  digitalWrite(19,LOW);
  analogWrite(15,0);
}


// Read all sensors with proper timing for ultrasonic
void read_sensors() {
  // Add a small delay before ultrasonic reading to ensure proper timing
  delayMicroseconds(10);
  hasObject = (int)(ultrasonic(12,27));
  delayMicroseconds(10);  // Add a small delay after reading
  ir_left = (int)(digitalRead(22));
  ir_right = (int)(digitalRead(21));
  
  // Reset ultrasonic pins to ensure next reading works
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);
  pinMode(12, INPUT);
}


// Describe this function...
void sharp_right() {
  digitalWrite(13,HIGH);
  digitalWrite(14,LOW);
  analogWrite(25,200); //motor (left)
  digitalWrite(18,HIGH);
  digitalWrite(19,LOW);
  analogWrite(15,150); //motor (right)
}


// Describe this function...
void straight() {             // forward, left motor diff speed so that ir sensors work better aka literally following the right wall
  digitalWrite(13,HIGH);
  digitalWrite(14,LOW);
  analogWrite(25,200); // motor (left)
  digitalWrite(18,HIGH);
  digitalWrite(19,LOW);
  analogWrite(15,190); // motor (right)
}

void reverse() { // seems broken, idk why tbh
  digitalWrite(13,LOW);
  digitalWrite(14,HIGH);
  analogWrite(25,100); 
  digitalWrite(18,LOW);
  digitalWrite(19,HIGH);
  analogWrite(15,100);
}



void setup() {
  pinMode(13,OUTPUT);
 pinMode(14,OUTPUT);
 pinMode(25,OUTPUT);
  pinMode(18,OUTPUT);
 pinMode(19,OUTPUT);
 pinMode(15,OUTPUT);
  pinMode(22, INPUT);
  pinMode(21, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.setTextColor(SSD1306_WHITE);

  pinMode(33, INPUT);
    display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  display.setTextSize(1);

}

void loop() {
    if ((int)(digitalRead(33)) == 0) {
      while (1) {
        // Clear the display first
        display.clearDisplay();
        read_sensors();
        display.setCursor(0,0);
        display.print((String(String("US: ") + String(hasObject)) + String(String(String(" left: ") + String(ir_left)) + String(String("right: ") + String(ir_right)))));
        display.display();
        // Add a small delay to allow display to update and sensors to stabilize (said github copilot lol)
        delay(50);
        if ((ir_left == 1 && ir_right == 0) && hasObject <= 16) { //ultrasonic, left

          digitalWrite(13,LOW); //reverse u blind bitch
          digitalWrite(14,HIGH);
          analogWrite(25,200);
          digitalWrite(18,LOW);
          digitalWrite(19,HIGH);
          analogWrite(15,200);
          delay(200); //how long to reverse     
          
          //turn left
          digitalWrite(13,HIGH);
          digitalWrite(14,LOW);
          analogWrite(25,50); // motor (left)
          digitalWrite(18,HIGH);
          digitalWrite(19,LOW);
          analogWrite(15,200); // motor (right)
          delay(800);
        // emo boy
        } else if ((ir_left == 0 && ir_right == 1) && hasObject <= 16) { //ultrasonic, right

          digitalWrite(13,LOW); //reverse you blind bitch
          digitalWrite(14,HIGH);
          analogWrite(25,200);
          digitalWrite(18,LOW);
          digitalWrite(19,HIGH);
          analogWrite(15,200);
          delay(200); //how long to reverse      
      
          //turn right
          digitalWrite(13,HIGH);
          digitalWrite(14,LOW);
          analogWrite(25,200); // motor (left)
          digitalWrite(18,HIGH);
          digitalWrite(19,LOW);
          analogWrite(15,50); // motor (right)
          delay(800);
        
        } else if ((ir_left == 1 && ir_right == 1 || ir_left == 0 && ir_right == 0) && hasObject <= 16) { //ultrasonic, no ir detection
          
          while (hasObject < 22) { //reverse far
            read_sensors();
            digitalWrite(13,LOW); //reverse you blind bitch
            digitalWrite(14,HIGH);
            analogWrite(25,150);
            digitalWrite(18,LOW);
            digitalWrite(19,HIGH);
            analogWrite(15,150);
            delay(10); // dont change delay, it ukeeps reversing until its the distance required above
          }
          

          motor_stop();
          delay(50); //let this thing rest for a bit smh



          

          while (hasObject >= 22 && ir_right == 1) { //search for the wall on the right
            read_sensors();
            digitalWrite(13,HIGH);
            digitalWrite(14,LOW);
            analogWrite(25,200); // motor (left)
            digitalWrite(18,HIGH);
            digitalWrite(19,LOW);
            analogWrite(15,20); // motor (right)
            delay(10);
          }

          delay(200); //give it a moment to keep detecting the wall (for straight() to work correctly)

        
        } else if (ir_left == 0 && ir_right == 1) { //ir
          sharp_right();
          delay(5);
        } else if (ir_left == 1 && ir_right == 0) { //ir
          sharp_left();
          delay(5);
        } else if ((ir_left == 1 && ir_right == 1 || ir_left == 0 && ir_right == 0) && hasObject > 16) {
          straight();
          delay(10);
        }
      }

    }
}
