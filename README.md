# Smart_Car_Control 🚗 
ESP8266 em modo AP + Arduino + joystick web em tempo real  
Um carrinho que cria sua própria rede Wi‑Fi, hospeda uma interface web responsiva e permite controle simultâneo de tração e direção sem depender de roteador ou broker MQTT.

## 📌 Visão Geral
Este projeto é um veículo robótico controlado por Wi‑Fi, composto por:

- ESP‑01 (ESP8266) em modo Access Point.

- Arduino Uno para controle de movimento.

- Driver H‑Bridge para os motores.

- Servo para direção.

- Estrutura mecânica construída sob medida.

- Interface web em tempo real com joystick responsivo.

O sistema cria sua própria rede, hospeda um servidor HTTP e permite controle bidirecional em tempo real de tração e direção.

## 🎯 Objetivo do Projeto
- Hospedar uma rede sem fio própria.

- Oferecer uma interface web simples e responsiva.

- Processar comandos de movimento em tempo real.

- Controlar dois eixos simultaneamente (tração e direção).

- Comunicar microcontroladores por protocolo serial leve.

- Integrar mecânica, eletrônica e firmware de forma modular.

## 🧠 Arquitetura do Sistema
Fluxo de dados:
- Usuário (smartphone ou PC) → Rede Wi‑Fi do carrinho (AP) → ESP‑01 (servidor web) → Comunicação serial → Arduino Uno → H‑Bridge + Servo → Movimento

Separação de responsabilidades:
- ESP‑01: cria o ponto de acesso e hospeda a interface web.

- Interface web: gera comandos a partir do joystick.

- ESP‑01: envia comandos via serial.

- Arduino: interpreta e executa comandos.

- H‑Bridge: controla sentido dos motores.

- Servo: ajusta o ângulo de direção.

Essa divisão facilita manutenção e evolução do projeto.

## 🔧 Construção Mecânica e Projeto Físico
Destaques da estrutura:

- Chassi rígido e compacto.

- Tração traseira dedicada.

- Direção dianteira com linkagem para o servo.

- Compartimento de baterias acessível.

- Carenagem superior removível.

- Cabeamento interno organizado.

Critérios de projeto:

- Facilidade de manutenção.

- Expansão modular (câmera, sensores, telemetria).

- Separação elétrica entre controle e alimentação.

- Estabilidade durante deslocamento.

## ⚙️ Firmware Arduino Controle de Movimento
O Arduino recebe comandos seriais do ESP‑01 e executa:

- Parsing do formato TRAÇÃO,DIREÇÃO.

- Controle dos pinos do H‑Bridge.

- Controle do servo para direção.

Formato de comando:

Exemplo: F,E (Frente, Esquerda)

Exemplo de parsing

cpp
int pos = comando.indexOf(',');
String tracao = comando.substring(0, pos);
String direcao = comando.substring(pos + 1);
Cada eixo é tratado de forma independente, permitindo movimento e direção simultâneos.

## 📡 Firmware ESP8266 Servidor Web e Rede
O ESP‑01 é responsável por:

- Criar o ponto de acesso Wi‑Fi.

- Hospedar o servidor HTTP com a interface.

- Enviar comandos em tempo real via serial.

- Armazenar a interface HTML em flash usando PROGMEM para economizar RAM.

- Configuração de rede

SSID: CarrinhoRC

Senha: 12345678

IP: 192.168.4.1

## 🌐 Interface Web Joystick Responsiva
Tecnologias:

- HTML5 e Canvas API.

- Eventos de toque e mouse.

- Cálculo vetorial em JavaScript.

- Fetch API para requisições assíncronas.

Lógica de controle:

- Eixo Y: tração (Frente, Ré, Parado).

- Eixo X: direção (Esquerda, Direita, Centro).

- Zona morta 15 px para evitar ruído.

- Envio de comando apenas quando o estado muda.

- Retorno automático ao neutro ao soltar o joystick.

Isso reduz tráfego serial e melhora a estabilidade do controle.

## 🔄 Protocolo de Comunicação
Códigos:

- F = Frente

- R = Ré

- P = Parado

- E = Esquerda

- D = Direita

- C = Centro

Exemplos:

- F,E → Frente e curva à esquerda

- F,D → Frente e curva à direita

- R,C → Ré em linha reta

- P,C → Neutro

## 🛠 Tecnologias e Componentes
Hardware:

- ESP8266 (ESP‑01)

- Arduino Uno

- Driver H‑Bridge

- Servo motor

- Motor DC

- Fonte 5V

Software:

- C++ para Arduino

- Biblioteca ESP8266WebServer

- SoftwareSerial para comunicação serial

- HTML5 + JavaScript para interface

- Protocolo serial leve e eficiente

## 🔐 Melhorias de Engenharia Implementadas

- Controle simultâneo de tração e direção.

- Filtragem por zona morta no joystick.

- Redução de comandos redundantes.

- Firmware modular com responsabilidades separadas.

- Operação em modo AP sem necessidade de roteador.

- Protocolo serial estruturado e previsível.

## 📷 Mídia do Projeto


## 📈 Melhorias Futuras

- Controle de velocidade por PWM.

- Comunicação por WebSocket para menor latência.

- Telemetria de bateria.

- Migração para ESP32 com arquitetura unificada.

- Streaming de câmera embarcada.

- Aplicativo móvel dedicado.

## 👨‍💻 Autor

Marcos Gabriel Ferreira Miranda  

Desenvolvedor IoT e Sistemas Embarcados

Belo Horizonte MG
