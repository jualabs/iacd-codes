/***********************************************************************
 * ARQUIVO:        c-language-step-2.c             
 *
 * DESCRICAO:
 *       Segundo exemplo de codigo no ambiente TinkerCad para aula de
 *       introducao a linguagem C da disciplina Instrumentacao e 
 *       Automacao de Coleta de Dados. Neste exemplo serao abordados os
 *       conceitos de diretivas de compilacao e arrays.
 * 
 * AUTORES:    Victor Medeiros        INICIO:  25 de Marco de 2019
 *			   Glauco Goncalves
 * 
 * MODIFICACOES :
 * DATA    		QUEM          DESCRICAO
 * --/--/--     ----          ----
 ***********************************************************************/

#include <Adafruit_NeoPixel.h>

#define PIN 		2	// pino de dados do NeoPixel
#define NUMPIXELS 	24 	// quantidade de pixels na fita
#define DELAY		100 // tempo de delay entre pixels

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint8_t redColor[NUMPIXELS] = 	{255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0};
uint8_t greenColor[NUMPIXELS] = {0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0};
uint8_t blueColor[NUMPIXELS] =  {0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0, 255};

void setup() {
	// inicializa a biblioteca NeoPixel
	pixels.begin();
}

void loop() {
	for(int i= 0; i < NUMPIXELS; i++) {
    	// pixels.Color recebe valores RGB, de 0,0,0 ate 255,255,255
    	pixels.setPixelColor(i, pixels.Color(redColor[i], greenColor[i], blueColor[i]));
	    // atualiza o valor do pixel no hardware
    	pixels.show();
	    // delay em milisegundos
    	delay(DELAY);
  	}
}