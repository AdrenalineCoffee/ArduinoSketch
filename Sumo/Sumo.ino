#include <Ultrasonic.h>

Ultrasonic ultrasonic(11,12);

int IN1 = 7; // Input1 подключен к выводу 5
int IN2 = 6;
int IN3 = 4;
int IN4 = 5;
int ENA = 9;
int ENB = 3;

int b1 = 2; // Бампер слева
int b2 = 10; // Бампер справа

int IRpin = 3; // ИК передний дальномер
float volts = 0.0;
float distance = 0.0;
void setup()
{
pinMode (ENA, OUTPUT);
pinMode (IN1, OUTPUT);
pinMode (IN2, OUTPUT);
pinMode (ENB, OUTPUT);
pinMode (IN4, OUTPUT);
pinMode (IN3, OUTPUT);
pinMode(b1, INPUT);
pinMode(b2, INPUT);
delay(3000);
//Wire.begin(); // join i2c bus (address optional for master)
//Serial.begin(9600); // start serial for output
}

void loop() {


    
  if (digitalRead(b1) == HIGH && digitalRead(b2) == HIGH){ //Если всё заебись
    volts = analogRead(IRpin)*0.0048828125;   // считываем значение сенсора и переводим в напряжение
    distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
    delay(100);
    //Serial.println(distance);
    if(distance < 120) up();
    else right();
    if(ultrasonic.Ranging(CM) < 50) down();
    
  }
  if (digitalRead(b1) == HIGH && digitalRead(b2) == LOW){ //Если черная линия справа
    left();
    delay(1000);
  }
  if (digitalRead(b1) == LOW && digitalRead(b2) == HIGH){// Если черная линия слева
    right();
    delay(1000);
  }
  if (digitalRead(b1) == LOW && digitalRead(b2) == LOW){// Если полностью заехали на черную линию
    down();
    delay(1000);
    left();
    delay(1000);
  }
//if(digitalRead(b1) == LOW) left();
//else if(digitalRead(b2) == LOW) right();
//else stopd();

// volts = analogRead(IRpin)*0.0048828125;   // считываем значение сенсора и переводим в напряжение
// distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
//  Serial.println(distance);  

}

void down(){
   digitalWrite (IN2, LOW);
    digitalWrite (IN1, HIGH);
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW);

    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
}

void up(){
   digitalWrite (IN2, HIGH);
    digitalWrite (IN1, LOW);
    digitalWrite (IN4, LOW);
    digitalWrite (IN3, HIGH);

    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
}

void right(){
   digitalWrite (IN2, LOW);
    digitalWrite (IN1, HIGH);
    digitalWrite (IN4, LOW);
    digitalWrite (IN3, HIGH);

    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
}

void left(){ 

    digitalWrite (IN2, HIGH);
    digitalWrite (IN1, LOW);
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW);

    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    }

    void stopd(){ 

    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    }

