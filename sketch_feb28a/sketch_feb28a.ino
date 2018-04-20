#include <Servo.h>
#include <Password.h> 
#include <Keypad.h> 
#include <LiquidCrystal.h> 
int RS=A5, E=A4, D4=A3, D5=A2, D6=A1, D7=A0;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7); // initialize the library with the numbers of the interface pins
Password password = Password( "6942" );
Servo myServo;
int buz=13;
int greenled=10;
int redled=11;
int pos = 0;

const byte ROWS = 4; // Four rows
const byte COLS = 3; //  columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = { 2,3,4,5 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 6,7,8 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  myServo.attach(9);
  lcd.begin(16, 2); // set up the LCD's number of columns and rows: 
  pinMode(buz,OUTPUT);
  pinMode(greenled,OUTPUT);
  pinMode(redled,OUTPUT);
  digitalWrite(buz, LOW);
  lcd.setCursor(0, 0);
  lcd.print("DOOR-LOCK-SYSTEM");
  lcd.setCursor(3, 1);
  lcd.print("**ENTER PASSWORD**");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PASSWORD PROTECT");
  lcd.setCursor(3, 1);
  lcd.print("**SYSTEM**");
  delay(3000);
  lock();
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}

void loop()
{
  keypad.getKey();
  
}

//take care of some special events
void keypadEvent(KeypadEvent eKey)
{
  
  switch (keypad.getState())
  {
    case PRESSED:
        
    lcd.print("*");
        digitalWrite(buz, HIGH);
        delay(100);
        digitalWrite(buz, LOW);
    switch (eKey){
      case '*': checkPassword(); break;
      case '#': lock(); break;
      default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()) 
  { 
    unlock();
  }
  else{
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0, 0);
    lcd.print("**TRY AFGAIN MOFO**");
    lcd.setCursor(0, 1);
    lcd.print("***************");
    digitalWrite(buz, HIGH);
    digitalWrite(redled, HIGH);
    delay(2000);
    digitalWrite(buz, LOW);
    digitalWrite(redled, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**TRY AFGAIN MOFO**");
    delay(2000);
    lcd.clear();
    password.reset();
    lcd.blink();
    lcd.print("Enter Passcode:");
  }
}
void lock() // Function For Lock 
{
  closeDoor();
  digitalWrite(greenled, LOW);
  digitalWrite(redled, LOW);
  delay(200);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM IS LOCKED");
  lcd.setCursor(0, 1);
  lcd.print("***************");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password to Unlock: ");
  lcd.setCursor(0, 1);
  lcd.print("*****Again*****");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password to Unlock:");
  lcd.blink();
    
}

void unlock() // Function For Unlock 
{
    openDoor();
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0, 0);
    lcd.print("*SWAAGAT HAI AAPKA*");
    lcd.setCursor(0, 1);
    lcd.print("***************");
     delay(3000);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("**WELCOME**"); 
    digitalWrite(buz, HIGH);
    digitalWrite(greenled, HIGH);
    delay(20000);
    digitalWrite(greenled, LOW);
    digitalWrite(buz, LOW);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.noBlink();
    lcd.print(" Press # key to");
    lcd.setCursor(0, 1);
    lcd.print("***Lock Again***");
    password.reset(); 
  
}

void openDoor(){
  while(pos < 90){
    myServo.write(pos);
    delay(15);
    ++pos;
  }
}

void closeDoor(){
  while(pos > 0){
    myServo.write(pos);
    delay(15);         
    --pos;
  }
}
