const int RS_PIN = 12;
const int D_PIN = 11;
const int JK_PIN = 10;
const int CLOCK_OUT_PIN = 2;
const int OUTPUT_PIN = 3;
const int CLOCK = A5;
const int BTN1 = A0;
const int BTN2 = A1;

const int TICK = 1000;

int output = LOW;
int lastClk = LOW;
unsigned long lastTick = 0;
bool clockState = LOW;

void setup() {
  pinMode(RS_PIN, INPUT_PULLUP);
  pinMode(D_PIN, INPUT_PULLUP);
  pinMode(JK_PIN, INPUT_PULLUP);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(CLOCK, INPUT);
  pinMode(CLOCK_OUT_PIN, OUTPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if(millis() > lastTick + TICK) {
    if(clockState == LOW) clockState = HIGH;
    else clockState = LOW;
    digitalWrite(CLOCK_OUT_PIN, clockState);
    lastTick = millis();
  }

  int btn1 = digitalRead(BTN1);
  int btn2 = digitalRead(BTN2);
  int clk = digitalRead(CLOCK);

  Serial.print("RS:");
  Serial.println(digitalRead(RS_PIN));
  Serial.print("D:");
  Serial.println(digitalRead(D_PIN));
  Serial.print("JK:");
  Serial.println(digitalRead(JK_PIN));
  
  if(digitalRead(RS_PIN) == LOW) {
    
    if(btn1 == HIGH) {
      output = HIGH;
    } else if(btn2 == HIGH) {
      output = LOW;
    }
  
  } else if(digitalRead(D_PIN) == LOW) {

    if(lastClk == LOW && clk == HIGH) {

      if(btn1 == HIGH) {
        output = HIGH;
      } else {
        output = LOW;
      }
      
    }
  
  } else if(digitalRead(JK_PIN) == LOW) {

    if(lastClk == LOW && clk == HIGH) {

      if(btn1 == HIGH && btn2 == HIGH){
        if(output == HIGH) output = LOW;
        else output = HIGH;
      } else {
        if(btn1 == HIGH) {
          output = HIGH;
        } else if(btn2 == HIGH) {
          output = LOW;
        }
      }
      
    }
    
  }

  digitalWrite(OUTPUT_PIN, output);
  lastClk = clk;
}
