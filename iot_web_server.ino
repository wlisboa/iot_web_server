#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "ESPap";
const char *password = "12345678";

ESP8266WebServer server(80);

const int led = 13;
/*
 *=============================================================================
 *NAME:         void handleRoot()
 *
 *DESCRIPTION:  Essa função é usada pelo servidor web e é responsavel por
 *              enviar a mensagem de hello
 *=============================================================================
*/
void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}
/*
 *=============================================================================
 *NAME:         handleNotFound(){
 *
 *DESCRIPTION:  Essa função é usada pelo servidor web e é responsavel por
 *              enviar uma página de erro.
 *=============================================================================
*/
void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
/*
 *=============================================================================
 *NAME:         void setup(void){
 *
 *DESCRIPTION:  Essa é a função de inicialização do sistema, nessa função
 *              é feita a configuração de todoo hardware que será utilizado
 *=============================================================================
*/
void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);

  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("");

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}
/*
 *=============================================================================
 *NAME:         void loop(void){
 *
 *DESCRIPTION:  Essa é a função a função principal, essa função é chamada
 *              repetidamente. 
 *=============================================================================
*/
void loop(void){
  server.handleClient();
}
