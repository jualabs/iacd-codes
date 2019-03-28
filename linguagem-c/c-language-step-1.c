/***********************************************************************
 * ARQUIVO:        c-language-step-1.c             
 *
 * DESCRICAO:
 *       Primeiro exemplo de codigo no ambiente TinkerCad para aula de
 *       introducao a linguagem C da disciplina Instrumentacao e 
 *       Automacao de Coleta de Dados. Neste exemplo serao abordados os
 *       conceitos de tipo de dados e a estrutura de repeticao for. 
 * 
 * AUTORES:    Victor Medeiros        INICIO:  25 de Marco de 2019
 *			   Glauco Goncalves
 * 
 * MODIFICACOES :
 * DATA    		QUEM          DESCRICAO
 * --/--/--     ----          ----
 ***********************************************************************/

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(24, 2, NEO_GRB + NEO_KHZ800);

uint8_t redColor = 255;
uint8_t greenColor = 0;
uint8_t blueColor = 0;

void setup() {
  	// inicializa a biblioteca NeoPixel
  	pixels.begin();
}

void loop() {
	for(int i= 0; i < 24; i++) {
		// pixels.Color recebe valores RGB, de 0,0,0 ate 255,255,255
    	pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
		// atualiza o valor do pixel no hardware
    	pixels.show();
		// delay em milisegundos
		delay(100);
  	}
}