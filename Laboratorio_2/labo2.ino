
//Codigo que se uso para el arduino Fisico

int sensorPin = A0;
int valorADC = 0;
float voltaje = 0;

int pin2 = 2;
int pin3 = 3;
int pin4 = 4;

void setup()
{
  // put your setup code here, to run once:
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  valorADC = analogRead(sensorPin);
  voltaje = valorADC * (5.0 / 1023.0);

  Serial.print("ADC: ");
  Serial.print(valorADC);
  Serial.print("   Voltaje: ");
  Serial.println(voltaje);

  delay(500);

  digitalWrite(pin2, random(0, 2));
  digitalWrite(pin3, random(0, 2));
  digitalWrite(pin4, random(0, 2));
  delay(2000);
}
