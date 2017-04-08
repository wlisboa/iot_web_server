#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/*
#include "DHT.h"
// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
// DHT Sensor
const int DHTPin = 5;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

// Temporary variables
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];
*/

const char *ssid = "ESPap";
const char *password = "12345678";

ESP8266WebServer server(80);

const int led = 0;

String monta_pagina()
{
String pagina_root = "<!DOCTYPE html>";
pagina_root += "<html lang=\"pt-br\">";
pagina_root +=               "<head>";
pagina_root +=        "<title>IOT_PAGE</title>";
pagina_root +=        "<meta charset=\"uft=8\">";
pagina_root +=        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
pagina_root +=    "</head>";
pagina_root +=    "<body>";
pagina_root +=    	"<header>";
pagina_root +=    		"<h1> Arduino Day </h1>";
pagina_root +=    	"</header>";
pagina_root +=    	"<main>";
pagina_root +=    		"<div>";
pagina_root +=    			"<p>Demonstra&ccedil;&atilde;o IOT</p>";
pagina_root +=    		"</div>";
pagina_root +=    		"<div class=\"sens-area\">";
pagina_root +=    			"<button type=button onclick=\"comando()\">Ler Sensor</button>";
pagina_root +=    			"<p id=\"sensor\">valor lido</p>";
pagina_root +=    		"</div>";
pagina_root +=    		"<div class=\"cmd-area\">";
pagina_root +=				"<form action=\"/cmd1\" method=\"post\">";
pagina_root +=                                  "<input type=\"hidden\" value=\"10\" name=\"cmd1\">";
pagina_root +=					"<button type=\"submit\" >comando 1</button>";
pagina_root +=				"</form>";
pagina_root +=				"<form action=\"/cmd2\" method=\"post\">";
pagina_root +=                                  "<input type=\"hidden\" value=\"10\" name=\"cmd2\">";
pagina_root +=					"<button type=\"submit\" >comando 2</button>";
pagina_root +=				"</form>";
pagina_root +=    		"</div>";
pagina_root +=    	"</main>";
pagina_root +=    	"<footer>";
pagina_root +=    		"<p>instrutor: Washington Lisboa</p>";
pagina_root +=    		"<a href=\"https://github.com/wlisboa/iot_web_server\">fonte do codigo</a>";
pagina_root +=    	"</footer>";
pagina_root +=    "</body>";
pagina_root +=    	"<script>";
pagina_root +=			"function comando() {";
pagina_root +=				"var xhttp = new XMLHttpRequest();";
pagina_root +=				"xhttp.onreadystatechange = function()";
pagina_root +=				"{";
pagina_root +=					"if (xhttp.readyState == 4 && xhttp.status == 200)";
pagina_root +=					"{";
pagina_root +=						"document.getElementById(\"sensor\").innerHTML = xhttp.responseText;";
pagina_root +=					"}";
pagina_root +=				"};";
pagina_root +=				"xhttp.open(\"POST\", \"/sensor\", true);";
pagina_root +=				"xhttp.send();";
pagina_root +=			"}";
pagina_root +=		"</script>";
pagina_root +=		"<style>";
pagina_root +=			"body {";
pagina_root +=				"text-align: center;";
pagina_root +=			"}";
pagina_root +=			"button {";
pagina_root +=				"height: 50px;";
pagina_root +=  				"width: 150px;";
pagina_root +=			"}";
pagina_root +=			"header {";
pagina_root +=				"padding-top: 5px;";
pagina_root +=				"border-bottom: 2px solid #000;";
pagina_root +=				"background-color: #38C2B3;";
pagina_root +=			"}";
pagina_root +=			"main {";
pagina_root +=				"border-bottom: 2px solid #000;";
pagina_root +=			"}";
pagina_root +=			".sens-area{";
pagina_root +=				"border-bottom: 2px solid #000;";
pagina_root +=			"}";
pagina_root +=			".cmd-area{";
pagina_root +=				"display: fex;";
pagina_root +=				"align-items: center;";
pagina_root +=				"justify-content: space-between;";
pagina_root +=				"border-bottom: 2px solid #000;";
pagina_root +=				"padding-top: 10px;";
pagina_root +=				"padding-bottom: 10px;";
pagina_root +=			"}";
pagina_root +=			".cmd-area form{";
pagina_root +=				"padding-top: 10px;";
pagina_root +=				"padding-bottom: 10px;";
pagina_root +=			"}";			
pagina_root +=		"</style>";
pagina_root += "</html>";

  return pagina_root;
}

/*
void le_sensor()
{
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    strcpy(celsiusTemp,"Failed");
    strcpy(fahrenheitTemp, "Failed");
    strcpy(humidityTemp, "Failed");         
  }
  else{
    // Computes temperature values in Celsius + Fahrenheit and Humidity
    float hic = dht.computeHeatIndex(t, h, false);       
    dtostrf(hic, 6, 2, celsiusTemp);             
    float hif = dht.computeHeatIndex(f, h);
    dtostrf(hif, 6, 2, fahrenheitTemp);         
    dtostrf(h, 6, 2, humidityTemp);
    // You can delete the following Serial.print's, it's just for debugging purposes
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.println(" *F");
  }
} 
*/

/*
 *=============================================================================
 *NAME:         void handleRoot()
 *
 *DESCRIPTION:  Essa função é usada pelo servidor web e é responsavel por
 *              enviar uma pagina para o navegador.
 *=============================================================================
*/
void handleRoot() {
    
  digitalWrite(led, 1);
  server.send(200, "text/html", monta_pagina());
  digitalWrite(led, 0);
}
/*
 *=============================================================================
 *NAME:         void handleSensor()
 *
 *DESCRIPTION:  
 *=============================================================================
*/
void handleSensor() {
    
  digitalWrite(led, 1);
  Serial.println("Sensor");
  server.send ( 200, "text/html", "100"); 
  digitalWrite(led, 0);
}
/*
 *=============================================================================
 *NAME:         void handleCmd1()
 *
 *DESCRIPTION:  
 *=============================================================================
*/
void handleCmd1() {
    
  digitalWrite(led, 1);
  Serial.println("Comando 1"); 
  server.send(200, "text/html", monta_pagina());
}
/*
 *=============================================================================
 *NAME:         void handleCmd2()
 *
 *DESCRIPTION:  
 *=============================================================================
*/
void handleCmd2() {
    
  digitalWrite(led, 0);
  Serial.println("Comando 2");
  server.send(200, "text/html", monta_pagina());
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
void setup(void)
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);

  //delay(10);
  //dht.begin();

  Serial.println();
  Serial.print("Configuring access point...");

  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);


  Serial.println("");

  server.on("/", handleRoot);
  server.on("/sensor", handleSensor);
  server.on("/cmd1", handleCmd1);
  server.on("/cmd2", handleCmd2);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}
/*
 *=============================================================================
 *NAME:         void loop(void)
 *
 *DESCRIPTION:  Essa é a função a função principal, essa função é chamada
 *              repetidamente. 
 *=============================================================================
*/
void loop(void)
{
  server.handleClient();
}
