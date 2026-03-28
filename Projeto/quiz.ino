#include <LiquidCrystal.h>
#include <EEPROM.h>

const int addrRecordeA= 0;
const int addrRecordeB = 1;
int recordeA = 0;
int recordeB = 0;

// RS=12, E=11, D4=10, D5=9, D6=8, D7=A0
LiquidCrystal lcd(12, 11, 10, 9, 8, A0);

const int ledVerde = 6;
const int ledVermelho = 7;
const int botoes[] = {2, 3, 4, 5}; 

int pontosA = 0, pontosB = 0, perguntaAtual = 0, jogadorAtual = 0; 

// Gabarito (0=A, 1=B, 2=C, 3=D)
int gabarito[] = {
  2, 3, 1, 3, 1, 1, 0, 2, 3, 0, // Jogador A (Respostas 1-10)
  1, 2, 0, 3, 1, 2, 0, 1, 3, 1  // Jogador B (Respostas 1-10)
}; 

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  for(int i = 0; i < 4; i++) pinMode(botoes[i], INPUT);
  
  recordeA = EEPROM.read(addrRecordeA);
  recordeB = EEPROM.read(addrRecordeB);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("REC A:")); lcd.print(recordeA);
  lcd.setCursor(0,1);
  lcd.print(F("REC B:")); lcd.print(recordeB);
  delay(3000);
  
  lcd.clear();
  lcd.println(F("  QUIZ MASTER  "));
  delay(2000);
 

  
  mostrarJogador();
  proximaPergunta();
  

}

void loop() {
  if (perguntaAtual < 20) {
    for(int i = 0; i < 4; i++) {
      if(digitalRead(botoes[i]) == HIGH) {
        Serial.print(F("Jogador "));
        Serial.print(jogadorAtual == 0 ? 'A' : 'B');
        Serial.print(F(" escolheu opcao "));
        Serial.println(i);
        verificarResposta(i);
        while(digitalRead(botoes[i]) == HIGH); 
        delay(250); 
      }
    }
  }
  
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'r') {
      pontosA = pontosB = 0;
      perguntaAtual = 0;
      jogadorAtual = 0;
      mostrarJogador();
      proximaPergunta();
      Serial.println(F("Jogo reiniciado pelo Serial"));
    }
  }    
}

void mostrarJogador() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(jogadorAtual == 0 ? F("TURNO: JOGADOR A") : F("TURNO: JOGADOR B"));
  delay(2000);
}

void rolarPergunta(String texto) {
  lcd.clear();
  if (texto.length() <= 16) {
    lcd.print(texto);
    delay(2000);
  } else {
    for (int pos = 0; pos <= texto.length() - 16; pos++) {
      lcd.setCursor(0, 0);
      lcd.print(texto.substring(pos, pos + 16));
      delay(200); 
    }
    delay(800);
  }
  lcd.setCursor(0, 0);
  lcd.print(F("                ")); 
  lcd.setCursor(0, 0);
  lcd.print(texto.substring(0, 16)); 
}

void exibirAlternativas(String a, String b, String c, String d) {
  String opcoes[] = {"A) " + a, "B) " + b, "C) " + c, "D) " + d};
  for(int i = 0; i < 4; i++) {
    lcd.setCursor(0, 1);
    lcd.print(F("                ")); 
    lcd.setCursor(0, 1);
    lcd.print(opcoes[i]);
    delay(1300); 
  }
  lcd.setCursor(0, 1);
  lcd.print(F("VALENDO!        "));
}

void proximaPergunta() {
  // --- JOGADOR A (Perguntas 1 a 10) ---
  if(perguntaAtual == 0) { rolarPergunta(F("1) 35 x 5?")); exibirAlternativas("150", "165", "175", "185"); }
  else if(perguntaAtual == 1) { rolarPergunta(F("2) Lados de um icosaedro?")); exibirAlternativas("12", "15", "18", "20"); }
  else if(perguntaAtual == 2) { rolarPergunta(F("3) Quantos planetas tem o sist. solar?")); exibirAlternativas("7", "8", "9", "10"); }
  else if(perguntaAtual == 3) { rolarPergunta(F("4) Existem quantos bits em um byte?")); exibirAlternativas("2", "4", "6", "8"); }
  else if(perguntaAtual == 4) { rolarPergunta(F("5) Qual o maior Oceano?")); exibirAlternativas("Atlanttico", "Pacifico", "Indico", "Artico"); }
  else if(perguntaAtual == 5) { rolarPergunta(F("6) Segundo presidente do Brasil?")); exibirAlternativas("Deodoro", "Floriano", "Prudente", "Vargas"); }
  else if(perguntaAtual == 6) { rolarPergunta(F("7) Simbolo do Itrio?")); exibirAlternativas("Y", "It", "Ir", "Yo"); }
  else if(perguntaAtual == 7) { rolarPergunta(F("8) Pais com mais fusos horarios?")); exibirAlternativas("Russia", "EUA", "Franca", "China"); }
  else if(perguntaAtual == 8) { rolarPergunta(F("9) Continente mais perto do Polo Sul?")); exibirAlternativas("Africa", "Oceania", "Asia", "America"); }
  else if(perguntaAtual == 9) { rolarPergunta(F("10) Artista que pintou 'O Semeador'?")); exibirAlternativas("Van Gogh", "Monet", "Picasso", "Dali"); }
  
  // --- JOGADOR B (Perguntas 1 a 10 reiniciadas) ---
  else if(perguntaAtual == 10) { rolarPergunta(F("1) Quantos segundos ha em 1 min?")); exibirAlternativas("30", "60", "100", "120"); }
  else if(perguntaAtual == 11) { rolarPergunta(F("2) Azul + Amarelo?")); exibirAlternativas("Roxo", "Laranja", "Verde", "Marrom"); }
  else if(perguntaAtual == 12) { rolarPergunta(F("3) Qual a capital da Australia?")); exibirAlternativas("Camberra", "Sydney", "Melbourne", "Perth"); }
  else if(perguntaAtual == 13) { rolarPergunta(F("4) Numero de elementos da tabela periodica?")); exibirAlternativas("108", "112", "115", "118"); }
  else if(perguntaAtual == 14) { rolarPergunta(F("5) Simbolo do Tungstenio?")); exibirAlternativas("Tu", "W", "Tn", "Tg"); }
  else if(perguntaAtual == 15) { rolarPergunta(F("6) Montanha mais alta fora da Asia?")); exibirAlternativas("Everest", "K2", "Aconcagua", "Kilimanjaro"); }
  else if(perguntaAtual == 16) { rolarPergunta(F("7) Inicio da Primeira Guerra?")); exibirAlternativas("1914", "1918", "1939", "1945"); }
  else if(perguntaAtual == 17) { rolarPergunta(F("8) Autor de Dom Casmurro?")); exibirAlternativas("Eca Queiroz", "M. de Assis", "Jorge Amado", "Guim. Rosa"); }
  else if(perguntaAtual == 18) { rolarPergunta(F("9) Substancia mais dura?")); exibirAlternativas("Aco", "Grafite", "Quartzo", "Diamante"); }
  else if(perguntaAtual == 19) { rolarPergunta(F("10) Osso humano que nao se conecta a nenhum outro?")); exibirAlternativas("Femur", "Hioide", "Atlas", "Estribo"); }
}

void verificarResposta(int escolha) {
  lcd.clear();
  if(escolha == gabarito[perguntaAtual]) {
    digitalWrite(ledVerde, HIGH);
    lcd.print(F("ACERTOU!"));
    if(jogadorAtual == 0) pontosA++; else pontosB++;
    delay(1500);
    digitalWrite(ledVerde, LOW);
  } else {
    digitalWrite(ledVermelho, HIGH);
    lcd.print(F("ERROU!"));
    delay(1500);
    digitalWrite(ledVermelho, LOW);
  }

  perguntaAtual++;
  if(perguntaAtual == 10 && jogadorAtual == 0) {
    lcd.clear();
    lcd.print(F("FIM TURNO A: ")); lcd.print(pontosA);
    delay(3000);
    jogadorAtual = 1;
    mostrarJogador();
  }

  if(perguntaAtual < 20) proximaPergunta();
  else finalizarJogo();
}

void salvarRecordes() {
  if (pontosA > recordeA){
    recordeA = pontosA;
    EEPROM.write(addrRecordeA, recordeA);
  }
  if (pontosB > recordeB){
    recordeB = pontosB;
    EEPROM.write(addrRecordeB, recordeB);
  }
}

void finalizarJogo() {
  salvarRecordes();
  lcd.clear();
  lcd.print(F("J-A:")); lcd.print(pontosA);
  lcd.print(F(" | J-B:")); lcd.print(pontosB);
  lcd.setCursor(0,1);
  if(pontosA > pontosB) lcd.print(F("VENCEU: J-A"));
  else if(pontosB > pontosA) lcd.print(F("VENCEU: J-B"));
  else lcd.print(F("EMPATE!"));
}