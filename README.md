# Care Plus Gamificada – Sistema de Engajamento e Prevenção em Saúde

## Integrantes

* Helton Pacheco                RM 567113
* Geovanna Caroline Lima Santos RM 567754
* Gustavo Firmino Barbosa       RM 566903

---

# Descrição do Projeto

O nossa solução de IoT para a Care Plus Gamificada é voltada para monitoramento de indicadores básicos de saúde em tempo real, incentivando o acompanhamento contínuo do usuário.

O sistema coleta dados de temperatura corporal e frequência cardíaca por meio de sensores conectados a um ESP32. Os dados são enviados utilizando o protocolo MQTT para o broker HiveMQ e posteriormente armazenados em um banco de dados InfluxDB para visualização e análise histórica.

---

# Objetivo

Desenvolver uma plataforma capaz de:

* Monitorar sinais vitais em tempo real;
* Registrar histórico de medições;
* Utilizar comunicação MQTT para transmissão de dados;
* Armazenar dados em banco de séries temporais;
* Possibilitar futuras integrações com dashboards e sistemas de gamificação.

---

# Componentes Utilizados

## ESP32

Microcontrolador responsável pela leitura dos sensores e envio das informações via Wi-Fi.

## DHT11

Sensor utilizado para monitoramento da temperatura.

Dados coletados:

* Temperatura (°C)

## MAX30100

Sensor biométrico responsável pela leitura da frequência cardíaca.

Dados coletados:

* Batimentos por minuto (BPM)

---

# Tecnologias Utilizadas

* ESP32
* Arduino IDE
* MQTT
* HiveMQ Cloud
* Node-RED
* InfluxDB Cloud
* Wokwi (simulação)

---

# Tópicos MQTT

## Frequência Cardíaca

careplus/bpm

Exemplo:

{
"batimentos": 102
}

## Temperatura

careplus/temp

Exemplo:

{
"temperatura": 24,
"umidade": 40
}

---

# Fluxo Node-RED

O Node-RED é responsável por:

1. Receber mensagens MQTT do HiveMQ;
2. Converter os dados JSON;
3. Formatar os campos para o InfluxDB;
4. Armazenar os dados no bucket "careplus".

---

# Estrutura dos Dados no InfluxDB

Measurement:

careplus

Campos:

* batimentos
* temperatura
* umidade

---

# Como Executar

## 1. Configurar o HiveMQ

Criar:

* Broker MQTT
* Usuário
* Senha

## 2. Configurar o ESP32

Inserir:

* SSID da rede Wi-Fi
* Senha Wi-Fi
* Endereço do broker MQTT
* Usuário MQTT
* Senha MQTT

## 3. Configurar o Node-RED

Instalar:

node-red-contrib-influxdb

Configurar:

* URL do InfluxDB Cloud
* Token
* Organização
* Bucket

## 4. Executar o Fluxo

* Iniciar ESP32
* Conectar ao HiveMQ
* Executar Node-RED
* Verificar dados chegando no InfluxDB

---

# Evidências

## Comunicação MQTT

Inserir screenshot do Node-RED recebendo mensagens MQTT.

## Armazenamento no InfluxDB

Inserir screenshot do Data Explorer mostrando:

* batimentos
* temperatura
* umidade

## Simulação Wokwi

Inserir screenshot do circuito.

---

# Resultados Obtidos

O sistema foi capaz de:

* Coletar sinais vitais simulados;
* Transmitir dados via MQTT;
* Armazenar dados históricos no InfluxDB;
* Demonstrar uma arquitetura IoT funcional para monitoramento de saúde.

---

# Vídeo Demonstrativo

Inserir link do YouTube:

https://youtube.com/SEU_VIDEO

---

# Licença

Projeto acadêmico desenvolvido para a disciplina de Edge Computing & Computer Systems da FIAP.
