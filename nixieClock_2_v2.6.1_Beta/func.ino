void burnIndicators() {
  for (byte k = 0; k < BURN_LOOPS; k++) {
    for (byte d = 0; d < 10; d++) {
      for (byte i = 0; i < 4; i++) {
        indiDigits[i]--;
        if (indiDigits[i] < 0) indiDigits[i] = 9;
      }
      delay(BURN_TIME);
    }
  }
}

//========ClockLoop========//
void clockLoop() {
  if (senTimer.isReady()) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
    } else {
      Serial.print(F("Humidity: "));
      Serial.print(h);
      Serial.print(F("%  Temperature: "));
      Serial.print(t);
      Serial.println(F("°C "));    
    }
    senHum = (int8_t) h;
    if (senHum > 99) {
      senHum = 99;  
    }
    senTemp = (int8_t) t;
    if (senTemp > 99) {
      senTemp = 99;  
    }
  }
  
  if (dotTimer.isReady()) {
    calculateTime();                                // каждые 500 мс пересчёт и отправка времени
    Serial.println("tick");
  }
  if (newTimeFlag && curMode == 0) flipTick();      // перелистывание цифр
  dotBrightTick();                                  // плавное мигание точки
  if (BACKL_TYPE == 0 ) backlBrightTick();          // плавное мигание подсветки ламп
  if (GLITCH_ALLOWED && mode == 0) glitchTick();    // глюки
  buttonsTick();                                    // кнопки
  settingsTick();                                   // настройки
}
