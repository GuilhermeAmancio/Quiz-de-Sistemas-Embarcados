# Quiz de Sistemas Embarcados
Quiz desenvolvido em projeto da disciplina de Fundamentos de Sistemas Embarcados usando Arduino Uno

# Quiz Master (Arduino)

Um sistema de perguntas e respostas para dois jogadores competitivos, com interface em display LCD e salvamento de recordes permanentes.

## Funcionalidades
* **Dois Jogadores:** Turnos separados para o Jogador A e Jogador B.
* **Sistema de Recordes:** Utiliza a memória **EEPROM** para salvar a maior pontuação de cada jogador, mesmo após desligar o Arduino.
* **Feedback Visual:** LEDs Verde (Acerto) e Vermelho (Erro) para indicação imediata.
* **Perguntas Dinâmicas:** Sistema de rolagem de texto para perguntas longas no LCD 16x2.
* **Reset via Serial:** Possibilidade de reiniciar o jogo enviando o comando 'r' pelo monitor serial.

##  Hardware Necessário
* 1x Arduino (Uno/Nano)
* 1x Display LCD 16x2 (com ou sem módulo I2C)
* 4x Push-buttons (Alternativas A, B, C, D)
* 2x LEDs (Verde e Vermelho)
* 2x Resistores de 220Ω (para os LEDs)
* Potenciômetro de 10kΩ (para o contraste do LCD)

## Pinagem (Wiring)

| Componente | Pino Arduino | Função |
| :--- | :--- | :--- |
| **LCD RS** | 12 | Controle |
| **LCD Enable** | 11 | Controle |
| **LCD D4-D7** | 10, 9, 8, A0 | Dados |
| **Botões (1-4)** | 2, 3, 4, 5 | Alternativas A, B, C, D |
| **LED Verde** | 6 | Indicador de Acerto |
| **LED Vermelho** | 7 | Indicador de Erro |

## Como Jogar
1. Ao iniciar, o LCD mostrará os recordes atuais salvos na memória.
2. O **Jogador A** responde as primeiras 10 perguntas.
3. As alternativas aparecem ciclicamente no LCD.
4. Após o turno do Jogador A, o **Jogador B** assume para suas 10 perguntas.
5. Ao final, o vencedor é anunciado e os recordes são atualizados se a pontuação atual for maior que a anterior.

Link do tinkercad do projeto:
https://www.tinkercad.com/things/iNkAljKGBdZ/editel?sharecode=5ZazJtpCOSxhL90B2t_KSv9ON17V07uye4c93c-VcUQ