/**
 * DHT11 Temperature Reader
 * This sketch reads temperature data from the DHT11 sensor and prints the value to the serial port.
 * It also handles potential error states that might occur during reading.
 *
 * Author: Dhruba Saha
 * Version: 2.1.0
 * License: MIT
 */

// Include the DHT11 library for interfacing with the sensor.
#include <DHT11.h>

DHT11 dht11(8); //Clase de DHT11, pin 8 donde está conectado el sensor.
String dato ; // Para recibir dato desde fuera.

const int ledPin = LED_BUILTIN; // Pin del led del Arduino
int ledState = LOW; // variable para estado del led.


void setup() {
    Serial.begin(9600); // Tasa de comunicación del puerto serial.
    pinMode(ledPin,OUTPUT); // modo del pin que tiene led en Arduino 1    
    // Uncomment the line below to set a custom delay between sensor readings (in milliseconds).
    // dht11.setDelay(500); // Set this to the desired delay. Default is 500ms.
}

void loop() {
    // Lectura del sensor dht11.
    int temperature = dht11.readTemperature();

    // Verificación de la letura del sensor
    if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");
    } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(temperature));
    }
    // Lectura del puerto serial de la pc, estamos esperando un texto.
    if (Serial.available()>0){
        dato = Serial.readStringUntil("\n");
        dato.trim();
        if (dato.length()>0){
            Serial.print("Dato recibido: ");
            Serial.println(dato);
        } else {
            Serial.println("No se reibió un dato válido");
        } 
    }
    // Si el texto enviado es "ON". se enciendo el led, de lo contrario es apagado
    if (dato.equals("ON")) {
        ledState = HIGH;
    } else {
        ledState = LOW;
    }
    digitalWrite(ledPin, ledState);

}
