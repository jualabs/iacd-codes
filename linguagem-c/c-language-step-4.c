/***********************************************************************
 * ARQUIVO:        c-language-step-4.c              
 *
 * DESCRICAO:
 *       Quarto exemplo de codigo no ambiente TinkerCad para aula de
 *       introducao a linguagem C da disciplina Instrumentacao e 
 *       Automacao de Coleta de Dados. Neste exemplo sera abordado o
 *       conceito de funcoes.
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

void setRGBLED(uint8_t LED_index, struct RGBLED_t LED) {
    pixels.setPixelColor(LED_index, pixels.Color(LED.R, LED.G, LED.B));
}

void setup() {
  	// inicializa a biblioteca NeoPixel
  	pixels.begin();
}

void loop() {
	uint8_t current_color = 0;
	for(int i = 0; i < NUMPIXELS; i++) {
		current_color = i % RAINBOW_NUM_COLORS;
    	// setRGBLED recebe o indice do LED que ira acender um valor RGBLED que contem as cores
    	setRGBLED(i, rainbow_colors[current_color]);
    	// atualiza o valor do pixel no hardware
    	pixels.show();
    	// delay em milisegundos
    	delay(DELAY);
  	}
}