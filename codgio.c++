#include <DHT.h>  // Biblioteca do DHT 
#define DHTPIN 7     // Define o pino ao qual o sensor DHT11 está conectado 
#define DHTTYPE DHT11   // Define o tipo de sensor DHT (DHT11 neste caso) 
#include <ArduinoJson.h>
DHT dht(DHTPIN, DHTTYPE); 

int cm = 0;
int triggerPin = 10;
int echoPin = 8;
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);  
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}

void setup() { 

  Serial.begin(9600); 

  dht.begin(); 

} 

void loop() { 

  delay(3000);  // Aguarda 2 segundos entre as leituras 
  
  float umidade = dht.readHumidity(); 
  float temperatura = dht.readTemperature(); 

  

  // Verifica se a leitura do sensor foi bem-sucedida 

 // isnan = se o valor é nulo 

  if (isnan(umidade) || isnan(temperatura)) { 

    Serial.println("Erro ao ler o sensor DHT!"); 

  } else { 

    Serial.print("Umidade: "); 

    Serial.print(umidade); 

    Serial.print(" %\t"); 

    Serial.print("Temperatura: "); 

    Serial.print(temperatura); 

    Serial.println(" °C");  

  } 

  cm = 0.01723 * readUltrasonicDistance(triggerPin, echoPin);
 
  // Criar um objeto JSON
  StaticJsonDocument<200> doc;
  doc["distance_cm"] = cm; 

    StaticJsonDocument<200> doc1;
  doc1["temperatura"] = temperatura;

   StaticJsonDocument<200> doc2;
  doc2["umidade"] = umidade;
  
  // Serializar o objeto JSON para enviar pela porta serial
  serializeJson(doc, Serial);
   Serial.println();
   serializeJson(doc1, Serial);
    Serial.println();
    serializeJson(doc2, Serial);
     Serial.println();
//  serializeJson(temp, Serial);

}