#include <Arduino.h>
#include <BluetoothSerial.h>
// Define pin
#define motorRight_1 25
#define motorRight_2 26

#define motorLeft_1 18
#define motorLeft_2 19

#define motorLeft_Speed 15
#define motorRight_Speed 14

//Speed
int speed = 120 ;

// Khởi tạo bluetooth
BluetoothSerial SerialBT;

class Motor{
  public:
    Motor(int pin_1, int pin_2, int speed_pin);
    void tien(int speed);
    void lui(int speed);
    void brake();
    void standby();
  private:
    int pin_1;
    int pin_2;
    int speed_pin;
};


void setup() {
  SerialBT.begin("RC car");
  Serial.begin(115200);
  //Set pin
  pinMode(motorLeft_1, OUTPUT);
  pinMode(motorRight_1, OUTPUT);
  pinMode(motorLeft_2, OUTPUT);
  pinMode(motorRight_2, OUTPUT);
}
  Motor motorLeft(motorLeft_1, motorLeft_2, motorLeft_Speed), motorRight(motorRight_1, motorRight_2, motorRight_Speed);
void loop() {
  Serial.println(speed);
  if(SerialBT.available()){
    char lenh = SerialBT.read();
    // Serial.write(lenh);
    if(lenh >= '0' && lenh <= '9'){
      speed = map(lenh - '0', 0, 10, 120, 255); 
    }
    else if(lenh == 'q') speed = 255;
    else {
      switch (lenh)
      {
      case 'F':
        Serial.println("Tien");
        motorRight.tien(speed);
        motorLeft.tien(speed);
        break;
      case 'B':
        Serial.println("Lui");
        motorLeft.lui(speed);
        motorRight.lui(speed);
        break;
      case 'L':
        Serial.println("Quay trai");
        motorLeft.brake();
        motorRight.tien(speed);
        break;
      case 'R':
        Serial.println("Quay phai");
        motorLeft.tien(speed);
        motorRight.brake();
        break;
      // case 'D':
      //   motorLeft.brake();
      //   motorRight.brake();
      //   break;
      default:
        motorLeft.standby();
        motorRight.standby();
        break;
      }
    }
  }
}

Motor::Motor(int pin_1, int pin_2, int speed_pin)
{
  this->pin_1 = pin_1;
  this->pin_2 = pin_2;
  this->speed_pin = speed_pin;
}

void Motor::tien(int speed)
{
  analogWrite(speed_pin, speed);
  digitalWrite(pin_1, HIGH);
  digitalWrite(pin_2, LOW);
}

void Motor::lui(int speed)
{
  analogWrite(speed_pin, speed);
  digitalWrite(pin_2, HIGH);
  digitalWrite(pin_1, LOW);
}

void Motor::brake()
{
  analogWrite(speed_pin, 255);
  digitalWrite(pin_2, HIGH);
  digitalWrite(pin_1, HIGH);
}

void Motor::standby()
{
  digitalWrite(pin_1, LOW);
  digitalWrite(pin_2, LOW);
}
