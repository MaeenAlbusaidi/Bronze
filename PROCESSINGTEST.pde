import processing.net.*;

Client myClient;
String serverIP = "192.168.4.1";  
int port = 5200;
boolean buttonPressed1 = false, buttonPressed2 = false, buttonPressed3 = false;

void setup() {
  size(400, 400);
  myClient = new Client(this, serverIP, port);
}

void draw() {
  background(220);
  textSize(30); textAlign(CENTER, CENTER);
  fill(buttonPressed1 ? 0 : 255); rect(100, 100, 100, 50); fill(255); text("Start", 150, 125);
  fill(buttonPressed2 ? 200 : 255); rect(100, 200, 100, 50); fill(255); text("Stop", 150, 225);
  fill(buttonPressed3 ? 0 : 255); rect(100, 300, 150, 50); fill(255); text("Follow Object", 175, 325);
}

void mousePressed() {
  if (mouseY < 150) { myClient.write("START\n"); buttonPressed1 = true; }
  if (mouseY > 200 && mouseY < 250) { myClient.write("STOP\n"); buttonPressed2 = true; }
  if (mouseY > 300) { myClient.write("OBJECT\n"); buttonPressed3 = true; }
}
