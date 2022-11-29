#include <Wire.h>
#include <Keypad.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char ssid[] = "Totalplay-EDA2";
const char password[] = "EDA206C2uRUFdpjB";

String HOST_NAME = "http://192.168.100.5"; // REPLACE WITH YOUR PC's IP ADDRESS
String PHP_FILE_NAME   = "/insertar_mensaje.php";  //REPLACE WITH YOUR PHP FILE NAME
String tempQuery = "?Nombre=Estan-intentando-abrir-la-cerradura";

LiquidCrystal_I2C lcd(0x27,16,2);

Servo myservo;
int pulsador = 35;
int mot_min = 0;   //min servo angle  (set yours)
int mot_max = 180; //Max servo angle   (set yours)
int estado = 0;
// define numero de filas
const uint8_t ROWS = 4;
// define numero de columnas
const uint8_t COLS = 4;

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
// pines correspondientes a las filas
uint8_t colPins[COLS] = { 19, 18, 5, 17 };
// pines correspondientes a las columnas
uint8_t rowPins[ROWS] = { 23, 4, 3, 16 };

char clave[5] = {'1','2','3','4','5'};
char claveUsuario[5];

Keypad keypad = Keypad(makeKeymap(keys),rowPins, colPins, ROWS, COLS);

int variableDatos = 0;
int buzzer=32;

int cont = 0;
int iden = 0;
int con2 = 5;

void setup() {
  pinMode(pulsador, INPUT);
Serial.begin(115200);
//-----------------------------------------
WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
//------------------------------------------
lcd.init(); // inicializar pantalla
lcd.backlight(); //luz de fondo
lcd.clear();
myservo.attach(2);
myservo.write(mot_min);   
}

void loop() {
char Tecla = keypad.getKey();
lcd.setCursor(0,0);
lcd.print("INGRESE LA CLAVE");
if (Tecla) {
    // envia a monitor serial la tecla presionada
    Serial.println(Tecla);
  }

if(Tecla){
  claveUsuario[cont] = Tecla;
  cont++;
  
  lcd.setCursor(con2,1);
  lcd.print("*");
  con2++;
  
  
if(cont == 1 && Tecla != 'C'){
  if(estado == 1){
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CERRAR PARA");
    lcd.setCursor(0,1);
    lcd.print("INGRESAR CLAVE");
    delay(2000);
     lcd.clear();
     cont = 0;
    iden = 0;
    con2 =5;
    }
  }
if(cont == 5){
  for(int i = 0; i<=4;i++){
    
    if(claveUsuario[i] != clave[i]){
      iden = 1;
    }
    }
    
   if(iden ==1 && estado == 0){
    variableDatos = 1;
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("CLAVE");
    lcd.setCursor(3,1);
    lcd.print("INCORRECTA");    
    analogWrite(buzzer,100);
      delay(1000);
      analogWrite(buzzer,200);
      delay(1000);
      analogWrite(buzzer,240);
      delay(1000);
      analogWrite(buzzer,100);
      delay(1000);
      analogWrite(buzzer,LOW);
    cont = 0;
    iden = 0;
    con2 =5;
     lcd.clear();
  }
  if(variableDatos == 1 && estado == 0){
    lcd.setCursor(0,0);
    lcd.print("ESPERAR DE 2 A 6");
    lcd.setCursor(4,1);
    lcd.print("SEGUNDOS");
  HTTPClient http;
  String server = HOST_NAME + PHP_FILE_NAME + tempQuery;
  http.begin(server); 
  int httpCode = http.GET();

  if(httpCode > 0) {
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.printf("HTTP GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("HTTP GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
   variableDatos = 0;
   lcd.clear();
  }
  if(claveUsuario[0] == '1' && claveUsuario[1] == '2' && claveUsuario[2] == '3' && claveUsuario[3] == '4' && claveUsuario[4] == '5' && estado == 0){
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("CLAVE");
    lcd.setCursor(4,1);
    lcd.print("CORRECTA"); 
    myservo.write(mot_max);
    delay(2000);
    estado = 1;
    con2 =5;
    iden = 0;
    cont= 0;
      lcd.clear();
  } 
  }
  
}
if(Tecla == 'C' && estado == 1){
  lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("CERRADURA");
    lcd.setCursor(4,1);
    lcd.print("CERRADA"); 
  myservo.write(mot_min);
  delay(2000);
    estado = 0;
    cont = 0;
    iden = 0;
    con2 =5;
     lcd.clear();
    }
    if(digitalRead(pulsador) == HIGH && estado == 1){
     lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("CERRADURA");
    lcd.setCursor(4,1);
    lcd.print("CERRADA"); 
  myservo.write(mot_min);
  delay(1000);
    estado = 0;
    cont = 0;
    iden = 0;
    con2 =5;
     lcd.clear();
}
if(digitalRead(pulsador) == HIGH && estado == 0){
     lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("CERRADURA");
    lcd.setCursor(4,1);
    lcd.print("ABIERTA"); 
  myservo.write(mot_max);
  delay(1000);
    estado = 1;
    cont = 0;
    iden = 0;
    con2 =5;
     lcd.clear();
}
}
