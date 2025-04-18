#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <ArduinoJson.h>

const char* ssid = "ESP32_Robot";
const char* password = "12345678";

// Web Server
AsyncWebServer server(80);

// DFPlayer Mini
HardwareSerial mySerial(2);
DFRobotDFPlayerMini myDFPlayer;

// Servo Motors
Servo servos[12];
const int servoPins[12] = {13, 12, 14, 27, 26, 25, 15, 2, 4, 5, 18, 19};
int initialPos[12] = {90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};

// Ultrasonic Sensor
const int trigPin = 12;
const int echoPin = 2;
struct VoiceCommand {
    String keyword;
    String filename;
};
VoiceCommand mp3Files[] = {
    {"duniya", "001.mp3"},
    {"awaaz pasand", "002.mp3"},
    {"chocolate", "003.mp3"},
    {"pani", "004.mp3"},
    {"tut", "005.mp3"},
    {"cartoon", "006.mp3"},
    {"machine", "007.mp3"},
    {"afraid", "008.mp3"},
    {"brother", "009.mp3"},
    {"dance", "010.mp3"},
    {"secret", "011.mp3"},
    {"dream", "012.mp3"},
    {"family", "013.mp3"},
    {"father", "014.mp3"},
    {"friend", "015.mp3"},
    {"grand parents", "016.mp3"},
    {"work", "017.mp3"},
    {"dosti", "018.mp3"},
    {"joke", "019.mp3"},
    {"pyar", "020.mp3"},
    {"homework", "021.mp3"},
    {"super hero", "022.mp3"},
    {"control", "023.mp3"},
    {"baat kar", "024.mp3"},
    {"dekh sakte", "025.mp3"},
    {"dard hota", "026.mp3"},
    {"mother", "027.mp3"},
    {"namaste", "028.mp3"},
    {"sad", "029.mp3"},
    {"sister", "030.mp3"},
    {"chalte", "031.mp3"},
    {"kis se bane", "032.mp3"},
    {"surfaces", "033.mp3"},
    {"kaise sunte", "034.mp3"},
    {"charge", "035.mp3"},
    {"kahan jana hai", "036.mp3"},
    {"indian flag", "037.mp3"},
    {"grow up", "038.mp3"},
    {"microchip", "039.mp3"},
    {"sensor", "040.mp3"},
    {"baisakhi", "041.mp3"},
    {"buddh purnima", "042.mp3"},
    {"chhath puja", "043.mp3"},
    {"christmas", "044.mp3"},
    {"diwali", "045.mp3"},
    {"durga puja", "046.mp3"},
    {"dussehra", "047.mp3"},
    {"eid ul adha", "048.mp3"},
    {"eid ul fitr", "049.mp3"},
    {"ganesh", "050.mp3"},
    {"good friday", "051.mp3"},
    {"guru nanak ", "052.mp3"},
    {"holi", "053.mp3"},
    {"flower", "054.mp3"},
    {"lohri", "055.mp3"},
    {"mahaveer jayanti", "056.mp3"},
    {"muharram", "057.mp3"},
    {"onam", "058.mp3"},
    {"pongal", "059.mp3"},
    {"raksha bandhan", "060.mp3"},
    {"capital of india", "061.mp3"},
    {"mountain", "062.mp3"},
    {"favourite colour", "063.mp3"},
    {"longest river", "064.mp3"},
    {"father of nation", "065.mp3"},
    {"prime minister", "066.mp3"},
    {"independence day", "067.mp3"},
    {"republic day", "068.mp3"},
    {"nanha munna rahi","069.mp3"},
    {"twinkle twinkle ","070.mp3"},
    {"play a song","071.mp3"},
    {"koshish","072.mp3"},
    {"poem","0.69.mp3"}
};
const int numCommands = sizeof(mp3Files) / sizeof(mp3Files[0]);
void sayAndDoNamaste() {
    Serial.println("Performing Namaste...");

    myDFPlayer.play(28);  
    delay(1000); 

    servos[0].write(60);  
    servos[1].write(120); 
    delay(2000); 


    servos[0].write(90);
    servos[1].write(90);
    delay(500);
    
    Serial.println("Namaste completed.");
}

void playVoiceResponse(String command) {
    command.toLowerCase();  
    for (int i = 0; i < numCommands; i++) {
        if (command.indexOf(mp3Files[i].keyword) != -1) {  
            Serial.println("Playing: " + mp3Files[i].filename);
            myDFPlayer.play(i + 1); 
            return;
        }
    }
    Serial.println("No matching keyword found!");
}

void setupWiFi() {
    WiFi.softAP(ssid, password);
    Serial.println("ESP32 AP started!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
}

bool setupDFPlayer() {
    mySerial.begin(9600, SERIAL_8N1, 16, 17);
    if (!myDFPlayer.begin(mySerial)) {
        Serial.println("DFPlayer ERROR! Check connections.");
        return false;
    }
    myDFPlayer.volume(80);
    Serial.println("DFPlayer Ready!");
    return true;
}

void setupServos() {
    for (int i = 0; i < 12; i++) {
        servos[i].attach(servoPins[i]);
    }
}

void setupUltrasonic() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

long getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    return pulseIn(echoPin, HIGH) * 0.034 / 2;
}


//Movement
void moveForward() {
    for (int i = 0; i < 12; i += 2) {
        servos[i].write(45);
        servos[i + 1].write(135);
    }
    delay(500);
}

void moveBackward() {
    for (int i = 0; i < 12; i += 2) {
        servos[i].write(135);
        servos[i + 1].write(45);
    }
    delay(500);
}

void turnLeft() {
    for (int i = 0; i < 12; i += 2) {
        servos[i].write(30);
        servos[i + 1].write(150);
    }
    delay(500);
}

void turnRight() {
    for (int i = 0; i < 12; i += 2) {
        servos[i].write(150);
        servos[i + 1].write(30);
    }
    delay(500);
}

void danceMove() {
    for (int i = 0; i < 6; i++) {
        servos[i].write(90);
    }
    for (int i = 6; i < 12; i++) {
        servos[i].write(180);
    }
    delay(500);
    for (int i = 6; i < 12; i++) {
        servos[i].write(90);
    }
    delay(500);
    if (myDFPlayer.available()) myDFPlayer.play(2); 

// Autonomous

void autonomousMode() {
    while (true) {
        long distance = getDistance();
        Serial.print("Distance: ");
        Serial.println(distance);
        if (distance < 20) {
            turnLeft();
        } else {
            moveForward();
        }
    }
}



void setupWebServer() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("State")) {
            String state = request->getParam("State")->value();
            Serial.print("Received State: ");
            Serial.println(state);
            if (state == "A") {
                autonomousMode();
                request->send(200, "text/plain", "Autonomous Mode Activated");
            } 
            else if (state == "F") {
                moveForward();
                request->send(200, "text/plain", "Moving Forward");
            } 
            else if (state == "B") {
                moveBackward();
                request->send(200, "text/plain", "Moving Backward");
            } 
            else if (state == "L") {
                turnLeft();
                request->send(200, "text/plain", "Turning Left");
            } 
            else if (state == "R") {
                turnRight();
                request->send(200, "text/plain", "Turning Right");
            } 
            else if (state == "D") {
                danceMove();
                request->send(200, "text/plain", "Dancing!");
            } 
            else {
                request->send(400, "text/plain", "Invalid State");
            }
        } else {
            request->send(400, "text/plain", "Missing State Parameter");
        }
    });
    server.on("/command", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("text")) {
            String command = request->getParam("text")->value();
            Serial.println("Received Command: " + command);
            playVoiceResponse(command);
            request->send(200, "text/plain", "Playing response...");
        } else {
            request->send(400, "text/plain", "Missing 'text' parameter");
        }
    });



    server.begin();
}


void setup() {
    Serial.begin(9600);
    setupWiFi();
    
    if (!setupDFPlayer()) {
        Serial.println("DFPlayer setup is failed! Skipping.");
    }

    setupServos();
    setupUltrasonic();
    setupWebServer();
    sayAndDoNamaste();
}

void loop() {
    delay(100);  
}