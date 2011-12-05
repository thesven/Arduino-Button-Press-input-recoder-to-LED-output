const int ORANGE_LED = 10; //orange led at pin 10
const int GREEN_LED = 9; //green led at pin 9
const int RED_LED = 8; //red led at pin 8
const int POTENTIOMETER = A0; // potentiometere at analouge pin 0
const int BUTTON_ONE = 2; // press button one at pin 2
const int BUTTON_TWO = 3; //press button two at pin 3

int buttonOneOldValue = 0;
int buttonOneValue = 0;
int buttonTwoOldValue = 0;
int buttonTwoValue = 0;
int potentiValue = 0;

int values[750] = {};
int curPosition = 0;


boolean recordingState = false;

void setup(){
  
  //Serial.begin(9600);
  
  //set the pin mode for the LEDs
  pinMode(BUTTON_ONE, INPUT);
  pinMode(BUTTON_TWO, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);
}

void loop(){
  
  potentiValue = analogRead(POTENTIOMETER);
  
  if(potentiValue > 0){
    
    //get the value of button one
    buttonOneValue = digitalRead(BUTTON_ONE);
    
    //check to see if it has been pressed
    if(buttonOneValue == HIGH && buttonOneOldValue == LOW){
      //change the state
      recordingState = 1 - recordingState;
      resetPosition();
    }
    
    //check to see if we are in the recording or playing state
    if(recordingState){
      
      if(curPosition == 0){
       digitalWrite(GREEN_LED, HIGH);
       digitalWrite(ORANGE_LED, LOW);
       digitalWrite(RED_LED, HIGH);
     }
      
      //Serial.println(curPosition);
      
      values[curPosition] = digitalRead(BUTTON_TWO);     
      advancePosition();
      
     if(curPosition > 749){
       digitalWrite(RED_LED, LOW);
       recordingState = 0;
       resetPosition();
     }
     
    } else {
      
      digitalWrite(GREEN_LED, HIGH);
      
      if(values[curPosition] == 1 || values[curPosition] == 0) digitalWrite(ORANGE_LED, values[curPosition]);
      
      advancePosition();
      if(curPosition > 749){
        resetPosition();
      }
      
      
    }
    
    buttonOneOldValue = buttonOneValue;
  }
  
  delay(20);
  
}

void advancePosition(){
 curPosition++; 
}

void resetPosition(){
 curPosition = 0; 
}
