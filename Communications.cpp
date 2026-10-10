#include "Communications.h"

WebServer server(80);  // Servidor HTTP en puerto 80

Communications::Communications() {}

void Communications::begin() {
    prefs.begin("wifi", false);
    loadCredentials();

    if (ssid.length() > 0 && password.length() > 0) {
        connectToWiFi();
    } else {
        startAPMode();
    }
}

void Communications::handle() {
    ArduinoOTA.handle();
    server.handleClient();  // Atiende peticiones web
}

bool Communications::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String Communications::getIP() {
    return WiFi.localIP().toString();
}

void Communications::loadCredentials() {
    ssid = prefs.getString("ssid", "");
    password = prefs.getString("pass", "");
}

void Communications::saveCredentials(const char* newSsid, const char* newPass) {
    prefs.putString("ssid", newSsid);
    prefs.putString("pass", newPass);
}

void Communications::connectToWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());

    unsigned long startAttempt = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 8000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConectado al WiFi con éxito!");
        Serial.print("IP del cubo: ");
        Serial.println(WiFi.localIP());
        setupOTA();
    } else {
        Serial.println("\nNo se pudo conectar. Activando AP...");
        startAPMode();
    }
}

void Communications::startAPMode() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("CuboLED_Config", "12345678");
    Serial.println("AP iniciado: CuboLED_Config");
    Serial.println(WiFi.softAPIP());

  /*
    // Página principal: formulario para SSID y contraseña
    server.on("/", []() {
        String html = "<html><body>";
        html += "<h2>Configurar Cubo LED</h2>";
        html += "<form action='/save' method='POST'>";
        html += "SSID: <input type='text' name='ssid'><br>";
        html += "Password: <input type='password' name='pass'><br>";
        html += "<input type='submit' value='Guardar'>";
        html += "</form></body></html>";
        server.send(200, "text/html", html);
    });
*/
    // Página principal: formulario con estilos
    server.on("/", []() {
        String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
        html += "<style>body{font-family:Arial;text-align:center;background:#f0f0f0;}";
        html += "h2{color:#333;}form{background:#fff;padding:20px;border-radius:10px;display:inline-block;}";
        html += "input{margin:10px;padding:8px;width:80%;border:1px solid #ccc;border-radius:5px;}";
        html += "input[type=submit]{background:#4CAF50;color:white;border:none;cursor:pointer;}";
        html += "input[type=submit]:hover{background:#45a049;}</style></head><body>";
        html += "<h2>Configurar Cubo LED</h2>";
        html += "<form action='/save' method='POST'>";
        html += "<input type='text' name='ssid' placeholder='Nombre de la red WiFi'><br>";
        html += "<input type='password' name='pass' placeholder='Contraseña'><br>";
        html += "<input type='submit' value='Guardar'>";
        html += "</form></body></html>";
        server.send(200, "text/html", html);
    });
    
    // Guardar credenciales
    server.on("/save", HTTP_POST, [this]() {
        if (server.hasArg("ssid") && server.hasArg("pass")) {
            String newSsid = server.arg("ssid");
            String newPass = server.arg("pass");
            saveCredentials(newSsid.c_str(), newPass.c_str());
            server.send(200, "text/html", "<h3>Credenciales guardadas. Reiniciando...</h3>");
            delay(2000);
            ESP.restart();
        } else {
            server.send(400, "text/html", "Error: faltan datos");
        }
    });

    server.begin();
}

void Communications::setupOTA() {
    ArduinoOTA.setHostname("CuboLED-ESP32");
    ArduinoOTA.begin();
}

