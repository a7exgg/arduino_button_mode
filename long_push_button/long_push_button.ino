/*
   Реализация разных типов нажатий
*/
#define button 5  //  пин для кнопки
#define debounce 500  //  время для устранения дребезга (200мс для кнопочного выключателя)
#define hold 1000 //  время для удержания клавиши
boolean button_state = false; //  состояние кнопки
boolean button_flag = false;  //  флажок нажатия кнопки
boolean button_once_push = false; //  флажок одиночного нажатия
boolean button_hold_push = false; //  флажок долгого нажатия
unsigned long button_timer; //  таймер последнего нажатия на кнопку

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  button_state = !digitalRead(button);
  buttonFucnction();
  if (button_once_push == true) {
    Serial.println("Button once push");
    button_once_push = false;
  }
  if (button_hold_push == true) {
    Serial.println("Button hold push");
    button_hold_push = false;
  }
}

void buttonFucnction() {
  if (button_state == true && button_flag == false && millis() - button_timer > debounce) {
    button_flag = true;
    button_timer = millis();
  }
  if (button_state == false && button_flag == true && millis() - button_timer < hold) {
    button_flag = false;
    button_once_push = true;
  }
  if (button_state == false && button_flag == true && millis() - button_timer > hold) {
    button_flag = false;
    button_hold_push = true;
  }
}
