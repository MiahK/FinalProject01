#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Vector.h>
const int ELEMENT_COUNT_MAX = INT8_MAX;
int storage_array[ELEMENT_COUNT_MAX];
Vector<int> playerScores(storage_array); 
//notes taken from pitches.h 
#define NOTE_C3  131 //move forward 
#define NOTE_F2  87  //move down 
#define NOTE_F3  175 // move up 
#define NOTE_A2  110 //welcome

Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 9, A2, A3); //initialize display
//Obstacles
const unsigned char image [] PROGMEM = {
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0x83, 
	0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xdf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0x83, 
	0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x7f, 0xff, 0xbb, 
	0xff, 0xff, 0xf7, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x99, 0xff, 0xff, 0xcf, 0xf0, 
	0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0x83, 
	0xff, 0xff, 0xf0, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xcf, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//Sprite 
const unsigned char mySprite [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x1c, 0x00, 0x1c, 0x00, 0xff, 0x80, 0xff, 0x80, 
	0xff, 0x80
};

//Buttons
const byte PIN_BUTTON_A = 2; 
const byte PIN_BUTTON_B = 3;
const byte PIN_BUTTON_C = 4;
const byte PIN_BUTTON_D = 5;
const byte PIN_BUTTON_E = 6;
const byte PIN_BUTTON_F = 7;

//Joystick 
const byte JOYSTICK_BTN = 8;
const byte JOYSTICK_AXIS_X = A0;
const byte JOYSTICK_AXIS_Y = A1;


class GameStats{
  public: 
    int score = 0; 
    int winner = 1; 
    bool gamePlayed = false; 
    GameStats game(); 
}; 


void setup() {
  display.begin();
  display.setContrast(60); 

  //Welcome
  display.clearDisplay(); 
	display.setCursor(0,20);
  display.setTextColor(BLACK); 
  display.setTextSize(2);
	display.println("WELCOME");
  display.display(); 
  tone(10, NOTE_A2, 5000); 
  delay(5000); 


  pinMode(PIN_BUTTON_A, INPUT);  
  digitalWrite(PIN_BUTTON_A, HIGH);  
  
  pinMode(PIN_BUTTON_B, INPUT);  
  digitalWrite(PIN_BUTTON_B, HIGH);
 
  pinMode(PIN_BUTTON_C, INPUT);  
  digitalWrite(PIN_BUTTON_C, HIGH);
 
  pinMode(PIN_BUTTON_D, INPUT);  
  digitalWrite(PIN_BUTTON_D, HIGH);
 
  pinMode(PIN_BUTTON_E, INPUT);  
  digitalWrite(PIN_BUTTON_E, HIGH);
 
  pinMode(PIN_BUTTON_F, INPUT);  
  digitalWrite(PIN_BUTTON_F, HIGH); 

  pinMode(JOYSTICK_BTN, INPUT); 
  digitalWrite(JOYSTICK_BTN, HIGH); 


}

int drawSprite(int xvalue = 5, int yvalue = 35){
  display.drawBitmap(xvalue, yvalue, mySprite, 9, 9, 0); 
}

int forwardSprite(int prevX, int yvalue){ 
  int forwardMovement = 5; 
  display.drawBitmap(prevX + forwardMovement, yvalue, mySprite, 9, 9, 0); //chang x position
  return prevX + forwardMovement; 
}

int downSprite(int xvalue, int yvalue){
  int downward = 17; 
  display.drawBitmap(xvalue, yvalue + downward, mySprite, 9, 9, 0); //change y position
  return yvalue + downward; 
}    

void gameOver(){
  display.clearDisplay(); 
  display.setTextColor(BLACK);
	display.setCursor(0,0);
	display.setTextSize(2);
	display.println("GAME");
  display.println("OVER");
	display.display();
  delay(2000); 
  display.clearDisplay(); 
}
void gameWon(){
  display.clearDisplay(); 
  display.setTextColor(BLACK);
	display.setCursor(0,20);
	display.setTextSize(2);
	display.println("WINNNER");
	display.display();
  delay(2000);
  display.clearDisplay();
}

bool collisionDetection(int frame, int spriteX, int spriteY){
  int yUpperBound, xUpperBound, distanceToObstacle1, sizeOfSprite, obstaclesPassed, distanceToObstacle2, distanceToObstacle3;
  yUpperBound = 15; 
  sizeOfSprite = 9;  
  bool collisionDetected = false; 

  if(frame == 0){
    distanceToObstacle1 = 27; 
    distanceToObstacle2 = distanceToObstacle1 * 2; 
    if(spriteX >= (distanceToObstacle1 - sizeOfSprite) && spriteY != 17){ // reached the obstacle +1
      if(spriteX < distanceToObstacle1){ 
         collisionDetected = true; 
      }
      else{
        obstaclesPassed = 1; 
      }
    }
    if(obstaclesPassed == 1){
      if(spriteX >= (distanceToObstacle2 - sizeOfSprite) && spriteY != 17){
        if(spriteX < 55){
          collisionDetected = true;
        }
        else{
          obstaclesPassed = 2; 
        }
      } 
    }
  }
  if(frame == 1){
    distanceToObstacle1 = 16; 
    distanceToObstacle2 = 37; 
    distanceToObstacle3 = 64; 
    if(spriteX >= (distanceToObstacle1 - sizeOfSprite) && spriteY != 17){ 
      if(spriteX < distanceToObstacle1){
        collisionDetected = true;
      }
      else{
        obstaclesPassed = 1; 
      }
    }
    if(obstaclesPassed == 1){
       if(spriteX >= (distanceToObstacle2 - sizeOfSprite) && spriteY != 17){
        if(spriteX < distanceToObstacle2){
         collisionDetected = true;
        }
        else{
          obstaclesPassed = 2; 
        }
      }      
    }
    if(obstaclesPassed == 2){
      if(spriteX > (distanceToObstacle3 - sizeOfSprite) && spriteY != 17){
        if(spriteX < distanceToObstacle3){
          collisionDetected = true; 
        }
        else{
          obstaclesPassed = 3; 
        }
      }
    }
  }
  if(frame == 2){
    distanceToObstacle1 = 22; 
    distanceToObstacle2 = 49; 
    distanceToObstacle3 = 74; 
    if(spriteX >= (distanceToObstacle1 - sizeOfSprite) && spriteY != 17){ 
      if(spriteX < distanceToObstacle1){
        collisionDetected = true;
      }
      else{
        obstaclesPassed = 1; 
      }
    } 
    if(obstaclesPassed == 1){
       if(spriteX >= (distanceToObstacle2 - sizeOfSprite) && spriteY != 17){
        if(spriteX < distanceToObstacle2){
          collisionDetected = true; 
        }
        else{
          obstaclesPassed = 2; 
        }
      }      
    }
    if(obstaclesPassed == 2){
      if(spriteX > (distanceToObstacle3 - sizeOfSprite) && spriteY != 17){
        if(spriteX < distanceToObstacle3){
          collisionDetected = true;
        }
        else{
          obstaclesPassed = 3; 
        }
      } 
    }
  }

  return collisionDetected; 
}

void playSound(int action = 1){
  if(action == 1){ //forward
    tone(10, NOTE_C3, 250); 
  }
  if(action == 2){ //up
    tone(10, NOTE_F3, 250); 
  }
  if(action == 3){ //down
    tone(10, NOTE_F2, 250); 
  }
  if(action == 4){ //down after obstacle
    tone(10, NOTE_A2, 250); 
  }
}
int randMovement(int i, int spriteX, int spriteY){ //drops Sprite after certain obstacles are passed
        if(i == 0){
          if((spriteX == 30 && spriteY == 17) || (spriteX == 60 && spriteY == 17) ){ 
             display.clearDisplay(); 
             display.drawBitmap(-(84*i), 0, image, 252, 48, 1);
             spriteY = 35; 
             drawSprite(spriteX, spriteY); 
          }
        }
        if(i == 1){
          if((spriteX == 25) || (spriteX == 45) || (spriteX == 70) ){ 
             display.clearDisplay(); 
             display.drawBitmap(-(84*i), 0, image, 252, 48, 1);
             spriteY = 35; 
             drawSprite(spriteX, spriteY); 
          }
        }
        if(i == 2){
          if((spriteX == 25 && spriteY == 17) || (spriteX == 55 && spriteY == 17) ){ 
             display.clearDisplay(); 
             display.drawBitmap(-(84*i), 0, image, 252, 48, 1);
             spriteY = 35; 
             drawSprite(spriteX, spriteY); 
          }
        }
        display.display(); 
  return spriteY; 
}

GameStats game() { 
  GameStats thisGame; 
  int action; 

  while(thisGame.score < 90){ // runs 3 times
  for(int i = 0; i <= 2; i++){
    int spriteX = 5; 
    int spriteY = 35; 
    bool singleFrame = true;  
    display.clearDisplay(); 
    display.drawBitmap(-(84*i), 0, image, 252, 48, 1); 
    drawSprite(); 
    display.display();
    while(singleFrame == true){
      if(spriteX >= 75){ 
        singleFrame == false; 
        break;
      }
      if (digitalRead(PIN_BUTTON_A)==LOW){ //jump
        action = 2; 
        display.clearDisplay();
        display.drawBitmap(-(84*i), 0, image, 252, 48, 1);
        spriteY = 0; 
        if(i != 0){
          spriteY = 17; 
        }
        drawSprite(spriteX, spriteY);
        playSound(action); 
        display.display();
      }
      if (digitalRead(PIN_BUTTON_B)==LOW){ //forward
        thisGame.score += 1; 
        action = 1; 
        display.clearDisplay(); 
        display.drawBitmap(-(84*i), 0, image, 252, 48, 1);
        spriteX = forwardSprite(spriteX, spriteY); 
        playSound(action); 
        spriteY = randMovement(i, spriteX, spriteY);
        display.display();
      }
      if (digitalRead(PIN_BUTTON_C)==LOW){ //down
          if(spriteY < 48){ 
            action = 3; 
            display.clearDisplay(); 
            display.drawBitmap(-(84*i), 0, image, 252, 48, 1);
            spriteY = downSprite(spriteX, spriteY); 
            playSound(action); 
            display.display();
          }
        }
         if(collisionDetection(i,spriteX,spriteY) == true){
            thisGame.winner = 0; 
            return thisGame; 
         }
        } 
      }
  }

  return thisGame; 

}

void leaderBoard(Vector<int> scores){
  int highScore = 0; 
  int lastScore = 0; 
  if(scores.empty() == false){
    lastScore = scores[scores.size()-1]; 
  }
  for(int i = 0; i < scores.size(); i++){
    if(scores[i] > highScore){
      highScore = scores[i]; 
    }
  }
  if(highScore == lastScore){
    display.clearDisplay(); 
	  display.setCursor(0,0);
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(1); 
	  display.println("NEW HIGH SCORE");
    display.println(lastScore); 
    display.display(); 
    delay(7000); 
  }
  else{
    display.clearDisplay(); 
	  display.setCursor(0,0);
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(1); 
	  display.println("HIGH SCORE");
    display.println(highScore); 
    display.println("YOUR SCORE"); 
    display.println(lastScore); 
    display.display(); 
    delay(7000); 
  }

}

void homeScreen(){
  display.clearDisplay(); 
	display.setCursor(0,0);
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(2); 
	display.println("PLAY");
  display.setTextColor(BLACK);
  display.setTextSize(1); 
  display.println("LEADERBOARD");
	display.display();
	delay(2000); 
  GameStats stats;

  if(analogRead(JOYSTICK_AXIS_X) == 0 && analogRead(JOYSTICK_AXIS_Y) >= 500){
    stats = game(); 
    stats.gamePlayed = true; 
    if(stats.winner == 1){
      gameWon(); 
    }
    else{
      gameOver(); 
    }
  }
  if(stats.gamePlayed == true){
    playerScores.push_back(stats.score);                  
  }

  if((analogRead(JOYSTICK_AXIS_X)> 440 && analogRead(JOYSTICK_AXIS_X)  <= 750) && analogRead(JOYSTICK_AXIS_Y) == 0){
    display.clearDisplay(); 
	  display.setCursor(0,0);
	  display.setTextSize(2);
    display.setTextColor(BLACK);
	  display.println("PLAY");
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(1);
    display.println("LEADERBOARD"); 
	  display.display(); 
    delay(7000);       

    if(analogRead(JOYSTICK_AXIS_X)== 0 && (analogRead(JOYSTICK_AXIS_Y) > 400 && analogRead(JOYSTICK_AXIS_Y) < 520)){
      leaderBoard(playerScores); 
    }
    if((analogRead(JOYSTICK_AXIS_X) > 508&& analogRead(JOYSTICK_AXIS_X) <= 1023) && analogRead(JOYSTICK_AXIS_Y) == 1023){
        display.clearDisplay(); 
	      display.setCursor(0,0);
	      display.setTextSize(2);
        display.setTextColor(WHITE, BLACK);
	      display.println("PLAY");
        display.setTextColor(BLACK);
        display.setTextSize(1);
        display.println("LEADERBOARD"); 
        display.display(); 
        delay(1000);  
    }

  }

}

void loop() {
  homeScreen(); 
  display.display();
}
