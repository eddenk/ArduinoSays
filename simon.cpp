#include <Arduino.h>
// Define all the LED and  pins.
// in the order of {RED, GREEN, YELLOW, BLUE}
int button[] = {6, 2, 12, 9}; //buttons pins
int led[] = {5, 3, 11, 10};  // LED pins
int turn = 0;  //initialize turn counter
int buttonstate = 0;  //initialize button state -- used to check if input is correct or not
int randomArray[100]; //Intentionally long to store up to 100 inputs (if person get this far they need a life)
int inputArray[100];
const int failPin = 5; //if you get the sequence wrong, a single red pin will show

void setup()
{
	Serial.begin(115200);
	for(int x=0; x<4; x++)
	{
		pinMode(led[x], OUTPUT);
	}
	for(int x=0; x<4; x++)
	{
		pinMode(button[x], INPUT);
		digitalWrite(button[x], HIGH);
	}
	pinMode(failPin, OUTPUT);
	randomSeed(analogRead(40));
}

// Turns all the LEDs on.
void showLEDs()
{
	for(int pin = 0; pin < 4; pin++)
	{
		digitalWrite(led[pin], HIGH);
	}
}

//function to clear the LEDs
void clearLEDs()
{
	for(int pin = 0; pin < 4; pin++)
	{
		digitalWrite(led[pin], LOW);
	}
}

//blink all leds
void blinkAll(int times)
{
	for(int count = 0; count < times; count++)
	{
		showLEDs();
		delay(300);
		clearLEDs();
		delay(300);
	}
}

//user fails, fail pin (red) will blink and the turns will reset and start the game over
void fail() { //Function used if the player fails to match the sequence
	digitalWrite(failPin, HIGH);
	delay(100);
	digitalWrite(failPin, LOW);
	turn = -1; //Resets turn value so the game starts over without need for a reset button
}

//function for the users input and checking if the input is the same as the randomized array sequence
void input()
{
	for (int x=0; x <= turn;) { //Statement controlled by turn count
    for(int y=0; y<4; y++) {
    	buttonstate = digitalRead(button[y]);
    	//check the correct input for every button press/led
    	if (buttonstate == LOW && button[y] == 6)
    	{
    		digitalWrite(led[0], HIGH);
    		delay(200);
    		digitalWrite(led[0], LOW);
    		blinkAll(3);
    		inputArray[x] = 1;
    		delay(250);
    		Serial.print(" ");
    		Serial.print("Red");
    		if (inputArray[x] != randomArray[x])
    		{ //error handling for each button
    			fail();
    		}
    		x++;
      }
      if (buttonstate == LOW && button[y] == 2)
      {
    	  digitalWrite(led[0], HIGH);
    	  delay(200);
    	  digitalWrite(led[0], LOW);
    	  blinkAll(3);
    	  inputArray[x] = 2;
    	  delay(250);
    	  Serial.print(" ");
    	  Serial.print("Green");
    	  if (inputArray[x] != randomArray[x])
    	  { //error handling for each button
          fail();
    	  }
        x++;
      }
      if (buttonstate == LOW && button[y] == 12)
      {
    	  digitalWrite(led[0], HIGH);
    	  delay(200);
    	  digitalWrite(led[0], LOW);
    	  blinkAll(3);
    	  inputArray[x] = 3;
    	  delay(250);
    	  Serial.print(" ");
    	  Serial.print("Yellow");
    	  if (inputArray[x] != randomArray[x])
    	  { //error handling for each button
          fail();
    	  }
        x++;
      }
      if (buttonstate == LOW && button[y] == 9)
      {
    	  digitalWrite(led[0], HIGH);
    	  delay(200);
    	  digitalWrite(led[0], LOW);
    	  blinkAll(3);
    	  inputArray[x] = 4;
    	  delay(250);
    	  Serial.print(" ");
    	  Serial.print("Blue");
    	  if (inputArray[x] != randomArray[x]) { //error handling for each button
          fail();
        }
        x++;
      }
    }
  }
  delay(500);
  //increment the turn if the buttons were pressed in the correct order
  turn++;
}
void loop()
{
    for (int y=turn; y <= turn; y++)
    {
    	Serial.println("");
    	Serial.print("Turn: ");
    	Serial.print(y);
    	Serial.println("");
    	randomArray[y] = random(1, 5); //Assigning a random number (1-4) to the randomArray[y], y being the turn count
    	for (int x=0; x <= turn; x++)
    	{
    		for(int y=0; y<4; y++)
    		{
    			//check red led on
    			if (randomArray[x] == 1 && led[y] == 5)
    			{
    				digitalWrite(led[y], HIGH);
    				delay(500);
    				digitalWrite(led[y], LOW);
    				delay(150);
    			}
    			//check green led on
    			if (randomArray[x] == 2 && led[y] == 3)
    			{
    				digitalWrite(led[y], HIGH);
    				delay(500);
    				digitalWrite(led[y], LOW);
    				delay(150);
    			}
    			//check yellow led on
    			if (randomArray[x] == 3 && led[y] == 11)
    			{
    				digitalWrite(led[y], HIGH);
    				delay(500);
    				digitalWrite(led[y], LOW);
    				delay(150);
    			}
    			//check blue led on
    			if (randomArray[x] == 4 && led[y] == 10)
    			{
    				digitalWrite(led[y], HIGH);
    				delay(500);
    				digitalWrite(led[y], LOW);
    				delay(150);
    			}
    		}
    	}
    }
    //ask for input
    input();
}

