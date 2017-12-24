const int LM35 = 0;
float temperatura = 0;
int ADClido = 0;
const int Buzzer = 12;
const int ledVerde = 8;
const int ledVermelho = 9;
void setup(){
 analogReference(INTERNAL1V1); //No Mega, use INTERNAL1V1, no Leonardo remova essa linha
 pinMode(Buzzer, OUTPUT);
 pinMode(ledVerde, OUTPUT);
 pinMode(ledVermelho, OUTPUT);
 Serial.begin(9600); 
}
void loop(){
 ADClido = analogRead(LM35);
 temperatura = ADClido * 0.1075268817204301; //no Leonardo use 0.4887585532
 if(temperatura > 30){ // setei como 25ºC
 digitalWrite(Buzzer, HIGH);
 digitalWrite(ledVermelho, HIGH);
 digitalWrite(ledVerde, LOW);
 
 }
 else{
 digitalWrite(Buzzer, LOW);
 digitalWrite(ledVermelho, LOW);
 digitalWrite(ledVerde, HIGH);
 }

 Serial.print("Temperatura = ");
 Serial.print(temperatura);
 Serial.println(" *C");
 delay(100); 
 }