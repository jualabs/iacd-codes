/***********************************************************************
 * ARQUIVO:        c-language-step-3.c             
 *
 * DESCRICAO:
 *       Terceiro exemplo de codigo no ambiente TinkerCad para aula de
 *       introducao a linguagem C da disciplina Instrumentacao e 
 *       Automacao de Coleta de Dados. Neste exemplo serao abordados os
 *       conceitos de constantes, estruturas e definicao de tipos.
 * 
 * AUTORES:    Victor Medeiros        INICIO:  25 de Marco de 2019
 *			   Glauco Goncalves
 * 
 * MODIFICACOES :
 * DATA    		QUEM          DESCRICAO
 * --/--/--     ----          ----
 ***********************************************************************/

#include <Adafruit_NeoPixel.h>

#define PIN 				2	// pino de dados do NeoPixel
#define NUMPIXELS 			24 	// quantidade de pixels na fita
#define DELAY				100 // tempo de delay entre pixels
#define RAINBOW_NUM_COLORS 	7

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

typedef struct RGBLED_t {
	uint8_t R;
	uint8_t G;
	uint8_t B;
} RGBLED;

const RGBLED VIOLET = {148, 0, 211};
const RGBLED INDIGO = {75, 0, 130};
const RGBLED BLUE   = {0, 0, 255};
const RGBLED GREEN  = {0, 255, 0};
const RGBLED YELLOW = {255, 255, 0};
const RGBLED ORANGE = {255, 127, 0};
const RGBLED RED    = {255, 0, 0};

RGBLED rainbow_colors[NUMPIXELS] = {VIOLET, INDIGO, BLUE, GREEN, YELLOW, ORANGE, RED};

void setup() {
	Serial.begin(9600);
  	// inicializa a biblioteca NeoPixel
  	pixels.begin();
}

void loop() {
	uint8_t current_color = 0;
	for(int i = 0; i < NUMPIXELS; i++) {
		current_color = i % RAINBOW_NUM_COLORS;
    	// pixels.Color recebe valores RGB, de 0,0,0 ate 255,255,255
    	pixels.setPixelColor(i, pixels.Color(rainbow_colors[current_color].R, rainbow_colors[current_color].G, rainbow_colors[current_color].B));
    	// atualiza o valor do pixel no hardware
    	pixels.show();
    	// delay em milisegundos
    	delay(DELAY);
		Serial.println(current_color);
  	}
}