

//include "UbidotsMicroESP8266.h"



#include "Ubidots.h"


#include "Ubidots.h"
#include "DHT.h"
#include <Servo.h>




#define D0   16 //GPIO16 - WAKE UP
#define D1   5  //GPIO5
#define D2   4  //GPIO4
#define D3   0  //GPIO0
#define D4   2  //GPIO2 - TXD1

#define D5   14 //GPIO14 - HSCLK
#define D6   12 //GPIO12 - HMISO
#define D7   13 //GPIO13 - HMOSI - RXD2
#define D8   15 //GPIO15 - HCS   - TXD2
#define RX   3  //GPIO3 - RXD0 
#define TX   1  //GPIO1 - TXD0





#define DEVICE  "esp8266"  // label
#define VARIABLE  "led"  // 
#define VARIABLE2 "ser"
#define ID_TEMP "62bfc5f4801ff90a6e5f0c15" 
#define ID_HUM "62c2132c44064407d78bd52b" 
#define TOKEN  "BBFF-ePiIGLub0DPSFED22tQzBjn23Bjc2H"  // 

#define WIFISSID "MURILLO" // 
#define PASSWORD "3201622028" //

Servo puerta; 
Servo puerta2; 
Ubidots client(TOKEN);
float Valor_Temperatura = 0;
float Valor_Humedad = 0;
float Valor_servo = 0;
const byte  Pin_led = D8; 
const byte  servo = D2; 
const byte  servo2 = D1; 
const byte alarm = D0; 
const byte  Obj_DHT11 = D4;   
#define DHTPIN Obj_DHT11     // 
#define DHTTYPE DHT11   // 

DHT Obj_DHT(DHTPIN, DHTTYPE);


void setup() {
   
     puerta.attach   Obj_DHT.begin();
    pinMode(Pin_led, OUTPUT);
      pinMode(alarm, OUTPUT);
    digitalWrite(Pin_led, LOW);(servo); 
      puerta2.attach(servo2); 
    
    Serial.begin(115200);
    client.wifiConnect(WIFISSID, PASSWORD);
}

void loop() 
{
    float h = Obj_DHT.readHumidity(); //Lee la humedad
    float t = Obj_DHT.readTemperature();//Lee la temperatura en grados centigrados (Valor por defecto)
  
    // verifica si alguna lectura ha fallado
    if (isnan(h) || isnan(t)) {
      Serial.println("Existe un error en la lectura del sensor DHT11!");
      return;
    }

    Serial.println("--------------------------------------------------------");
    Serial.print("Humedad: ");Serial.print(h);Serial.println(" %");
    Serial.print("Temperatura: ");Serial.print(t);Serial.println(" *C");
    Serial.println("--------------------------------------------------------");

   
    float Valor_Led = client.get(DEVICE, VARIABLE);
    float Valor_servo = client.get(DEVICE, VARIABLE2);
    
    
    
    if (Valor_Led != ERROR_VALUE){
      Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL LED: "));
      Serial.println(Valor_Led);
      
      if (Valor_Led==1){digitalWrite(Pin_led, HIGH);}
      else{digitalWrite(Pin_led, LOW);}
      
    }else{
      Serial.println(F("Error getting Valor_Led"));
    }


    
if (Valor_servo != ERROR_VALUE){
      Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL SERVO: "));
      Serial.println(Valor_servo);
      puerta2.write(Valor_servo);
   
      
    }else{
      Serial.println(F("Error getting Valor_servo"));
    }
  


    Valor_Temperatura = t;
    
    client.add(ID_TEMP,Valor_Temperatura ); 
    client.send();
    delay(500);

    Valor_Humedad = h;
    
    client.add(ID_HUM, Valor_Humedad); 
    client.send();
    delay(500);

if(Valor_Temperatura>31){
    
    digitalWrite( Pin_led ,HIGH); 
    digitalWrite( alarm,HIGH); 
     puerta.write(180); 
    
  }
  
  else{
    
    digitalWrite( Pin_led ,LOW); 
    digitalWrite( alarm ,LOW); 
     puerta.write(0); 
      
  }
  







    
}
