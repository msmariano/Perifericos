#include <Arduino.h>
#include <LiquidCrystal.h>

unsigned long pulso = 0;
unsigned long t1 = 0;
unsigned long t2 = 0;
unsigned long delta = 0;
bool l1 = false;
int buffer = 0;
int deslocamento = 0;
String comando = "";

const int rs = GPIO_NUM_10, en = GPIO_NUM_9, d4 = GPIO_NUM_5, d5 = GPIO_NUM_6, d6 = GPIO_NUM_7, d7 = GPIO_NUM_8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void mede()
{
  delta = micros() - t1;

  if (delta > 9000)
  {
    buffer = 0;
    deslocamento = 0;
  }

  if (delta <= 1300)
  {
    buffer = buffer | 0;
    buffer = buffer << 1;
    deslocamento++;
  }
  if (delta >= 2000 && delta <= 2500)
  {
    buffer = buffer | 1;
    buffer = buffer << 1;
    deslocamento++;
  }
  if (deslocamento == 32)
  {
    String digito = "";
    switch (buffer)
    {
    case 33506490:
      Serial.println("1");
      comando = comando+"1";
      break;
    case 33473850:
      Serial.println("2");
      break;
    case 33539130:
      Serial.println("3");
      break;
    case 33441210:
      Serial.println("4");
      break;
    case 33424890:
      Serial.println("5");
      break;
    case 33522810:
      Serial.println("6");
      break;
    case 33538110:
      Serial.println("7");
      break;
    case 33509550:
      Serial.println("8");
      break;
    case 33497310:
      Serial.println("9");
      break;
    case 33501390:
      Serial.println("0");
      break;
    case 33476910:
      Serial.println("*");
      comando = comando + "*";
      break;
    case 33513630:
      Serial.println("#");
      break;
    case 33461610:
      Serial.println("B");
      break;
    case 33436110:
      Serial.println("C");
      break;
    case 33432030:
      Serial.println("E");
      break;
    case 33469770:
      Serial.println("D");
      break;
    case 33452430:
      Serial.println("OK");
      break;
    default:
      Serial.println(buffer);
      break;
    }
    if(comando.equals("*1")){
      Serial.println("Acionando piscina");
      comando = "";
    }
    Serial.write(buffer);
    buffer = 0;
    deslocamento = 0;
    
  }
  t1 = micros();
}

void setup()
{
  Serial.begin(9600);
  pinMode(GPIO_NUM_21, INPUT);
  attachInterrupt(digitalPinToInterrupt(GPIO_NUM_21), mede, RISING);

  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Marcelo");
  lcd.setCursor(2,0);
  lcd.print("Mariano");
}

void loop()
{
  // Turn off the cursor:
  lcd.noCursor();
  delay(2000);
  // Turn on the cursor:
  lcd.cursor();
  delay(2000);
}
