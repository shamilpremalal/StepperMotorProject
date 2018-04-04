//ItKindaWorks - Creative Commons 2016
//github.com/ItKindaWorks
//
//Stepper motor control pins
const int stepPin = 11;   //pin to pulse for steps
const int dirPin = 10;    //pin to change step direction

//User input pins 
const int dispenserButton = 8;     // button that controls dispenser movement (digital pin)
const int dispenserVar = 2; // button that controls dispensed amount (analog pin) 

//Internal controls
const int safetySwitch = 7; //internal switch used to limit the closing movement of the dispenser

void setup() {
  
  //set pins as outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  //Set user pins as input
  pinMode(dispenserButton, INPUT);


  //Set internal control pins as input
  pinMode(safetySwitch, INPUT);
}

void loop() {

  
  // Collect all data from user: dispenser limit & dispenser button
  int dispencerONButton = digitalRead(dispenserButton);


  //limiter (internal control)
  int safetyONButton = digitalRead(safetySwitch);

  //Case user button is HIGH ==> Dispense regardless
  if(dispencerONButton ==HIGH){
      stepperFWD();
      motorStep();
    
    }
    else{ //Case is not pressed ==> close dispenser (until the internal button is hit)
            stepperREV();
      if(safetyONButton == HIGH){ //Case internal button is pressed ==> stop moving dispenser
     
        digitalWrite(stepPin, LOW);
        
      }else{ //Case internal button has not yet been reached ==> continue closing
              motorStep();
       }
    }

}


//change the stepper direction to forward
void stepperFWD(){
  digitalWrite(dirPin, HIGH);
}

//change the stepper direction to reverse
void stepperREV(){
  digitalWrite(dirPin, LOW);

}

//have the stepper motor take one step
void motorStep(){
  digitalWrite(stepPin, HIGH);
  delay(1);
  digitalWrite(stepPin, LOW);
}
