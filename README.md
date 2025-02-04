# EmbarcaTechTemporizadores

Projeto desenvolvido durante a primeira fase da residência Embarcatech.

Este repositório contém dois projetos em C para a Raspberry Pi Pico, ambos relacionados ao uso de temporizadores e manipulação de LEDs via GPIO.
Temporizador One-Shot: Acende três LEDs simultaneamente ao pressionar um botão e os desliga um por vez em intervalos definidos.
Temporizador Periódico: Alterna entre três LEDs de forma cíclica a cada 3 segundos, sem necessidade de interação do usuário.


## Recursos e Funcionalidades

### Temporizador One-Shot
- Aciona três LEDs simultaneamente ao pressionar um botão.
- LEDs desligam um por vez em intervalos de 3 segundos.
- O botao aciona os leds novamente apenas quando estão todos desligados.

### Temporizador Periódico
- Alterna automaticamente entre três LEDs a cada 3 segundos.
- Implementa um temporizador periódico (add_repeating_timer_ms).
- Apenas um LED permanece aceso por vez, seguindo um ciclo contínuo com intervalos de 3s.
- Mensagens de depuração são enviadas via printf().

## Componentes Utilizados
- Microcontrolador Raspberry Pi Pico
- 3 LEDs (azul, vermelho e verde no One-Shot; vermelho, amarelo e verde no Periódico)
- 1 botão para acionamento no modo One-Shot
- Resistores pull-up para entrada digital do botão

## Dependências
- pico-sdk para programação do Raspberry Pi Pico.
- pico/stdlib.h para manipulação de GPIO e temporizadores.
- hardware/timer.h (no modo periódico) para configuração do temporizador repetitivo.

## Estrutura do Código
### TemporizadorOneShot
- init_hardware(): Configura os pinos de LEDs e botão.
- turn_off_callback(): Callback para desligamento progressivo dos LEDs.
- main(): Loop principal que aguarda a ativação do botão.

### TemporizadorPeriodico
- init_hardware(): Configura os pinos de LEDs.
- repeating_timer_callback(): Callback que alterna entre os LEDs periodicamente.
- main(): Inicializa o temporizador e mantém o programa em execução.

## Instalação

Clone este repositório e configure o ambiente de desenvolvimento do Raspberry Pi Pico utilizando o pico-sdk.

```bash
git clone https://github.com/MariaP-Ramalho/EmbarcaTechTemporizadores
cd TemporizadorOneShot (ou TemporizadorPeriodico)
mkdir build
cd build
cmake ..
make
```

## Como Executar

- Envie o binário gerado (.uf2) para o Raspberry Pi Pico via USB.
- Para o Temporizador One-Shot: Pressione o botão para ativar a sequência de LEDs.
- Para o Temporizador Periódico: O código inicia automaticamente a alternância de LEDs a cada 3 segundos.
