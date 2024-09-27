int InputPin = A0;
 
void current_setup(){
  pinMode(InputPin, INPUT); 
}
 
 
void current_reading(){
  current_value = 0.3*current_value + 0.7*analogRead(InputPin);
}