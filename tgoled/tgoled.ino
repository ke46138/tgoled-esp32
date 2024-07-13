#define WIFI_SSID "WIFI_SSID"
#define WIFI_PASS "WIFI_PASS"
#define BOT_TOKEN "Ваш токен"
#include <GyverOLED.h>
#include <FastBot.h>
FastBot bot(BOT_TOKEN);
GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
//String tgm;
//int x, y;
void setup() {
  connectWiFi();
  bot.attach(newMsg);
  //bot.setChatID(ID); //если вам надо чтобы бот общался только с одним аккаунтом
  oled.init();  
  oled.clear();
  oled.setCursor(0, 0);
  oled.update();
}

// обработчик сообщений
void newMsg(FB_msg& msg) {
  // выводим ID чата, имя юзера и текст сообщения
  Serial.print(msg.chatID);     // ID чата 
  Serial.print(", ");
  Serial.print(msg.username);   // логин
  Serial.print(", ");
  Serial.println(msg.text);     // текст
  /*if(msg.text == "clear"){
    oled.clear();
    Serial.println("clear");
    oled.setCursor(0, 0);
    oled.update();
  }
  else{
  oled.println(msg.text);
  Serial.println("text");
  oled.update();
  */
  String tgm = msg.text;
  if(tgm.substring(0, 2) == "/c"){
    //x = tgm.substring(8).toInt();
    //y = tgm.substring(12).toInt();
    
    String bufString = tgm.substring(7);       // читаем как строку
    byte dividerIndex = bufString.indexOf(' ');   // ищем индекс разделителя
    String buf_1 = bufString.substring(0, dividerIndex);    // создаём строку с первым числом
    String buf_2 = bufString.substring(dividerIndex + 1);   // создаём строку со вторым числом
    int x = buf_1.toInt();    // преобразуем во инт
    int y = buf_2.toInt();    // ...



    
    Serial.println("/clear ");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    Serial.println(tgm);
    oled.dot(x, y, 0);   
    oled.update();
    tgm = "";
  }
  if(tgm.substring(0, 2) == "/s"){
    //x = tgm.substring(6).toInt();
    //y = tgm.substring(10).toInt();

    String bufString = tgm.substring(5);       // читаем как строку
    byte dividerIndex = bufString.indexOf(' ');   // ищем индекс разделителя
    String buf_1 = bufString.substring(0, dividerIndex);    // создаём строку с первым числом
    String buf_2 = bufString.substring(dividerIndex + 1);   // создаём строку со вторым числом
    int x = buf_1.toInt();    // преобразуем во инт
    int y = buf_2.toInt();    // ...



    
    Serial.print("/set ");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    Serial.println(tgm);
    oled.dot(x, y, 1);   
    oled.update();
    tgm = "";
  }
  else{
    Serial.println("Unknown");
    Serial.println(tgm);
    Serial.println(tgm.substring(0));
    Serial.println(tgm.substring(0, 2));
    Serial.println("Unknown");
  }
}
void loop() {
  bot.tick();
}

void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}
