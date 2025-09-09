// ==== Librerías OLED ====
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Definiciones para la OLED
#define i2c_Address 0x3C 

#define SCREEN_WIDTH 128 // ancho OLED en px
#define SCREEN_HEIGHT 64 // alto OLED en px
#define OLED_RESET -1    // algunos módulos no usan reset

// Inicializa pantalla
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Constantes  para el sensor   
const int pinLM35 = A0;              // pin analógico donde está conectado LM35 Vout
const unsigned long intervalo = 1000; // intervalo de actualización en ms
unsigned long ultimaMillis = 0;

void setup() {
  // Monitor Serial
  Serial.begin(9600);
  while (!Serial) { /* espera en algunas placas */ }
  delay(50);
  Serial.println("LM35 + OLED - Lectura de temperatura");

  // OLED
  delay(250); // espera a que el OLED encienda
  display.begin(i2c_Address, true); 
  display.setContrast(255); // máximo brillo
  display.clearDisplay();
  display.display();
}

void loop() {
  unsigned long ahora = millis();
  if (ahora - ultimaMillis >= intervalo) {
    ultimaMillis = ahora;

    // === Lectura del LM35 ===
    int lectura = analogRead(pinLM35);              
    const float Vref = 5.0;                         
    float voltaje = lectura * (Vref / 1023.0);      
    float tempC = voltaje * 100.0;                  

    // === Salida por Serial ===
    Serial.print("Temperatura: ");
    Serial.print(tempC, 2);
    Serial.println(" °C");

    // === Mostrar en OLED ===
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);

    display.setCursor(10, 10);
    display.println("Temperatura:");

    display.setTextSize(2); 
    display.setCursor(20, 30);
    display.print(tempC, 1);
    display.println(" C");

    display.display(); 
  }

  // Aquí podrías hacer otras tareas no bloqueantes
}
