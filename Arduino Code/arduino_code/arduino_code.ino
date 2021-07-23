int incomingChar;
int incomingNum;
int sentNum=3;
int checkNum=-1;
const int buttonPin = 2;                          //Place of the button's cable on arduino//
int buttonState = 0;
int push=0;
int x=0;
void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}


void loop() {
  if(Serial.available()>0){
    x=0;                                          //Resets 'x' from case 'e'//
    incomingChar=Serial.read();         
    switch(incomingChar){
      case 'a':
      digitalWrite(LED_BUILTIN, HIGH);
      break;
      
      case 'b':
      digitalWrite(LED_BUILTIN, LOW);
      break;

      case 'c':
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      for(int i=0; i<7; i++){
        if(i==0 || i==2 || i==4){
          digitalWrite(LED_BUILTIN, HIGH);
          delay(500);
        }
        if(i==1 || i==3 || i==5){
          digitalWrite(LED_BUILTIN, LOW);
          delay(500);
        }
      }

      break;

      case 'd':
      while(checkNum==-1){                        //waits until 'checkNum' gets an input//
        checkNum=Serial.read();
      }
      sentNum=checkNum*checkNum;
      Serial.println(sentNum);
      checkNum=-1;
      break; 

      case 'e':
      while(x==0){
        buttonState=digitalRead(buttonPin);
        if(buttonState==HIGH){
          push=1;                                 //This line makes 'push=1' after user press button.//
                                                  
          for(int i=0; i<85; i++){                //I wrote this for because I wanted to send an exit message after user press the button for around// 
            delay(i);                             //5 seconds. This code checks the user released or still pressing button. If user release button//
            buttonState=digitalRead(buttonPin);   //when i=83, it will be take '83 ms' to quit from 'for'.//
            if(buttonState==LOW){
              i=86;
            }
            if(i==84){
              push=0;
              Serial.println('e');
              x=1;
            }           
          }
        }
      
        buttonState=digitalRead(buttonPin);
        if(buttonState==LOW && push==1){          //I dont want send data when pushing button, so the arduino sends 'x' only after user release button// 
          Serial.println('x');
          push=0;
        }
      
      }
      break;
      
    }
      
      
  }
}
