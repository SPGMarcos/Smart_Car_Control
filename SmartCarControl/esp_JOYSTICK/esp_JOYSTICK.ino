#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

// Comunicação com Arduino
SoftwareSerial ArduinoSerial(2, -1); // TX = GPIO2 (D4)

const char* ssid = "CarrinhoRC";
const char* password = "12345678";
ESP8266WebServer server(80);

// HTML da interface com joystick responsivo
const char html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'>
  <title>Joystick RC</title>
  <style>
    body { margin: 0; font-family: sans-serif; background: #111; color: #fff; text-align: center; }
    h2 { margin-top: 20px; }
    canvas { background: #222; border-radius: 50%; margin-top: 20px; touch-action: none; }
    #status { margin-top: 15px; font-size: 18px; }
  </style>
</head>
<body>
  <h2>Joystick RC</h2>
  <canvas id="joystick" width="300" height="300"></canvas>
  <p id="status">Comando: —</p>
<script>
  const canvas = document.getElementById('joystick');
  const ctx = canvas.getContext('2d');
  const centerX = canvas.width / 2;
  const centerY = canvas.height / 2;
  let posX = centerX, posY = centerY;
  let dragging = false, ultimoComando = '';

  function drawJoystick() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.beginPath();
    ctx.arc(centerX, centerY, 100, 0, 2 * Math.PI);
    ctx.strokeStyle = '#555';
    ctx.lineWidth = 5;
    ctx.stroke();

    ctx.beginPath();
    ctx.arc(posX, posY, 40, 0, 2 * Math.PI);
    ctx.fillStyle = '#4b0082';
    ctx.fill();
  }

  function getCommand(x, y) {
  let dx = x - centerX,
      dy = y - centerY;
  let cmd = [];

  // TRAÇÃO: F/R ou P
  if (Math.abs(dy) > 15) {            
    cmd.push(dy < 0 ? 'F' : 'R');
  } else {
    cmd.push('P');
  }

  // DIREÇÃO: E/D ou C
  if (Math.abs(dx) > 15) {
    cmd.push(dx < 0 ? 'E' : 'D');
  } else {
    cmd.push('C');
  }

  return cmd.join(',');
}


  function enviarComando(cmd) {
    if (cmd !== ultimoComando) {
      ultimoComando = cmd;
      document.getElementById('status').textContent = 'Comando: ' + cmd;
      fetch('/comando?acao=' + encodeURIComponent(cmd));
    }
  }

  canvas.addEventListener('touchstart', () => dragging = true);
  canvas.addEventListener('touchend', () => {
    dragging = false;
    posX = centerX;
    posY = centerY;
    drawJoystick();
    const cmd = getCommand(centerX, centerY); // Envia 'P,C' ao soltar
    enviarComando(cmd);
  });

  canvas.addEventListener('touchmove', e => {
    if (!dragging) return;
    e.preventDefault();
    const rect = canvas.getBoundingClientRect();
    const t = e.touches[0];
    posX = t.clientX - rect.left;
    posY = t.clientY - rect.top;
    drawJoystick();
    enviarComando(getCommand(posX, posY));
  });

  drawJoystick();
</script>
</body>
</html>
)rawliteral";

// Envia comando para o Arduino
void enviarParaArduino(String cmd) {
  cmd.trim();
  ArduinoSerial.print(cmd);
  ArduinoSerial.print("\n");
  Serial.println(cmd);
}

void setup() {
  Serial.begin(9600);
  ArduinoSerial.begin(9600);

  WiFi.softAP(ssid, password);
  Serial.println("Acesse http://192.168.4.1");

  server.on("/", []() {
    server.send_P(200, "text/html", html);
  });

  server.on("/comando", []() {
    if (server.hasArg("acao")) {
      enviarParaArduino(server.arg("acao"));
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Comando ausente");
    }
  });

  server.begin();
  Serial.println("Servidor iniciado!");
}

void loop() {
  server.handleClient();
}
