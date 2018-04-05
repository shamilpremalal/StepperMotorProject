
//Stepper motor control pins
const int stepPin = 11;   //pin to pulse for steps
const int dirPin = 10;    //pin to change step direction

//User input pins 
const int dispenserButton = 8;     // button that controls dispenser movement (digital pin)
const int dispenserVar = 2; // button that controls dispensed amount (analog pin) 
int dispencerONButton = 0;


//Internal controls
const int safetySwitch = 7; //internal switch used to limit the closing movement of the dispenser
int safetyONButton = 0;
int value = 0;
int limit = 0;

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
  dispencerONButton = digitalRead(dispenserButton);
  value = analogRead(dispenserVar);          //Read and save analog value from potentiometer
  value = map(value, 0, 1023, 0, 9000);      //Map value 0-1023 to 0-9000 (PWM)

  //limiter (internal control)
  safetyONButton = digitalRead(safetySwitch);

  //Case user button is HIGH ==> Dispense regardless
  if(dispencerONButton == HIGH){
     
      stepperFWD();
      while(dispencerONButton == HIGH &&  limit <=value ){
      motorStep();
      limit++;
      }
    
    }
    else{ //Case is not pressed ==> close dispenser (until the internal button is hit)
        stepperREV();
      if(safetyONButton == HIGH){ //Case internal button is pressed ==> stop moving dispenser
     
        digitalWrite(stepPin, LOW);
        
        limit = 0;
        
      }else{ //Case internal button has not yet been reached ==> continue closing 
              motorStep();
              limit --;
              if(limit < 0){
                  limit = 0;
              }
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
