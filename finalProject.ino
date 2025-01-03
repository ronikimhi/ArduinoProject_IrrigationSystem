#include <SoftwareSerial.h>
SoftwareSerial BT(4, 2); // TX, RX on arduino (RX, Tx on bluetooth)
int buttonPin=8;
boolean buttonState=false;
int dryLed=13;
int watering=12;
int goodLed=11;
const int LDRLed = A0; // select the input pin for LDR
float lightSensor;

const int tempSensor = A1; //for the heat temp-> LM35
float sensorValue;
float voltageOut;
float temp;

void setup() {
 pinMode(dryLed,OUTPUT);
 pinMode(watering,OUTPUT);
 pinMode(goodLed,OUTPUT);
 pinMode(LDRLed, INPUT);
 pinMode(buttonPin,INPUT);
 pinMode(tempSensor, INPUT);
 Serial.begin (9600);
 Serial.println("Welcome to your Irrigation simulation");
 Serial.println("Explanation on the system: ");
 Serial.println("RED led: Dry plant - needs watering");
 Serial.println("YELLOW led: during watering");
 Serial.println("GREEN led: good plant - don't need a thing");
 Serial.println("Press 1 to check the state of the plant: ");
 BT.begin(9600);
}

void loop() {

  if (BT.available()){
    char stateFromDevice= BT.read();
    if (stateFromDevice =='1'){ 
      Serial.print("state from device is ");
      Serial.println(stateFromDevice);
      Serial.println("Here is the status of the plant: PLANT IS DRY- water the plant");
      digitalWrite(dryLed, HIGH);
    }

    Serial.println("Press 2 to check the conditions of the light to water: ");
    if (stateFromDevice =='2'){ 
      lightSensor = analogRead(LDRLed);
      Serial.print("light is ");
      Serial.println(lightSensor);
      if(lightSensor<450){
        Serial.println("Good light to water- press the button to water" );
        delay(6000);
        buttonState=digitalRead(buttonPin);
        if(buttonState==HIGH){
          Serial.println("Watering the plant");
            digitalWrite(dryLed, LOW);
            digitalWrite(watering, HIGH);
            delay(3000);

            sensorValue = analogRead(tempSensor);
            voltageOut = (sensorValue * 5000) / 1024;
  
            // calculate temperature for LM35 (LM35DZ)
            temp = voltageOut / 10;
            
            if(temp>27){ //add temp sensor
              Serial.print("HOT temperture: ");
              Serial.print(temp);
              Serial.println(" - keep watering");
              delay(7000);
            }else{
              Serial.print("GOOD temperture: ");
              Serial.print(temp);
              Serial.println(" - can stop watering");
              delay(2000);
          }
          digitalWrite(watering, LOW);
          digitalWrite(goodLed, HIGH);
          delay(5000);
          digitalWrite(goodLed, LOW);
          Serial.println("finish watering. GOOD WATRERING SESSION");
          Serial.println("Press 1 to check the state of the plant: ");
        }
      } else {
        Serial.println("Light conditions are not suitable for watering.");
      }
    }
  }
}
          

   
  

  



