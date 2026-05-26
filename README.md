# OIC_AplicandoConhecimento_A4

# 🗑️ Lixeira Inteligente IoT

Projeto acadêmico desenvolvido para a disciplina de Objetos Inteligentes Conectados, com foco em Internet das Coisas (IoT) aplicada a cidades inteligentes e alinhado à ODS 11 da ONU.

---

# 📌 Objetivo

Desenvolver um sistema inteligente capaz de monitorar o nível de ocupação de uma lixeira utilizando sensores, atuadores e comunicação MQTT em tempo real.

O projeto busca demonstrar como soluções simples de IoT podem auxiliar no monitoramento urbano e na gestão eficiente de resíduos.

---

# 🌎 Relação com a ODS 11

O projeto está alinhado à ODS 11 — Cidades e Comunidades Sustentáveis, principalmente no objetivo:

> “Reduzir o impacto ambiental negativo das cidades, com especial atenção à gestão de resíduos municipais.”

---

# ⚙️ Componentes Utilizados

- ESP32
- Sensor ultrassônico HC-SR04
- LED RGB
- Resistores
- Protoboard virtual
- Simulador Wokwi

---

# 🧠 Funcionamento do Sistema

O sensor ultrassônico HC-SR04 realiza medições contínuas da distância entre o topo da lixeira e o nível dos resíduos.

Com base nessa distância, o sistema calcula a porcentagem de ocupação da lixeira.

O LED RGB atua como indicador visual:

| Cor         | Situação                   |
| ----------- | -------------------------- |
| 🟢 Verde    | Lixeira com baixa ocupação |
| 🟡 Amarelo  | Lixeira acima de 60%       |
| 🔴 Vermelho | Lixeira acima de 90%       |

Além da sinalização visual, as informações são enviadas em tempo real utilizando o protocolo MQTT.

---

# 🌐 Comunicação MQTT

## Broker utilizado

```txt
broker.hivemq.com
```

## Tópico MQTT

```txt
lixeira_iot/ocupacao
```

## Exemplo de mensagem enviada

```json
{
  "distancia": 120.5,
  "ocupacao": 69,
  "status": "Lixeira acima de 60% da capacidade."
}
```

---

# 📶 WiFi

O sistema utiliza a conexão WiFi do ESP32 para estabelecer comunicação com o broker MQTT e permitir o monitoramento remoto em tempo real.

---

# 💻 Ambiente de Desenvolvimento

## IDE utilizada

- Arduino IDE

## Bibliotecas utilizadas

- WiFi.h
- PubSubClient.h

## Simulador

- Wokwi

---

# 🖼️ Imagens do Projeto

As imagens da montagem, funcionamento do sistema e comunicação MQTT estão disponíveis na pasta `/imagens`.

---

# 📂 Estrutura do Repositório

```txt
/artigo
/codigo
/imagens
```

---

# 🚀 Resultados Obtidos

Durante os testes realizados no simulador Wokwi, o sistema apresentou funcionamento estável, realizando corretamente:

- leitura da distância;
- cálculo da porcentagem de ocupação;
- acionamento do LED RGB;
- conexão WiFi;
- envio de dados via MQTT.

O sistema respondeu em tempo real às alterações simuladas no nível de ocupação da lixeira.

---

# 🔧 Melhorias Futuras

- Dashboard web para monitoramento remoto;
- Aplicativo mobile;
- Notificações automáticas;
- Monitoramento de múltiplas lixeiras;
- Alimentação via energia solar.

---

# 👨‍💻 Autores

- Iury Pereira Galindo Marques
- Camila Sayuri Yoshioka
- Leonardo Caires Vasconcelos Angelo

---

# 📄 Artigo

O artigo completo do projeto está disponível na pasta `/artigo`.

---

# 🎥 Vídeo de Apresentação

Link do vídeo no YouTube:

```txt
Adicionar link após upload do vídeo
```

---

# 🔗 Simulação Wokwi

A simulação utilizada no desenvolvimento do projeto pode ser acessada no link abaixo:

```txt
https://wokwi.com/projects/462855954774758401
```
