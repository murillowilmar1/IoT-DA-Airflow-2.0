

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


DHT dht (D4, DHT11);



int v5 = 12;

#define DHTTYPE           DHT11     // DHT 11



void setup() {
  Serial.begin(115200); 
  // Initialize device.
  dht.begin();
  sensor_t sensor;
  //dht.readTemperature().getSensor(&sensor);


}

void loop() {

 delay(2000);


   float h = dht.readHumidity();

   float t = dht.readTemperature();


   if (isnan(h) || isnan(t)) {
   Serial.println("Existe un error en la lectura del sensor DHT11!");
   return;
 }


   Serial.print(h);
   Serial.print(" ");
   Serial.println(t);
//   Serial.println(sensor.sensor_id);
 
  
}