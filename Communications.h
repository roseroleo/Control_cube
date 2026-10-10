#ifndef COMMUNICATIONS_H
#define COMMUNICATIONS_H

#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Preferences.h>
#include <WebServer.h>

class Communications {
public:
    Communications();
    void begin();                 // Inicializa WiFi y OTA
    void handle();                // Atiende OTA y servidor web
    bool isConnected();           // Estado de conexión
    String getIP();               // IP actual del ESP32

private:
    Preferences prefs;
    String ssid;
    String password;
    void loadCredentials();       // Leer SSID/Password desde NVS
    void saveCredentials(const char* ssid, const char* pass); // Guardar en NVS
    void connectToWiFi();         // Conectar al router
    void startAPMode();           // Crear red temporal + portal cautivo
    void setupOTA();              // Inicializar OTA
};

#endif

