#include "U8glib.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

float t = 0;
float p = 0;
char t_buffer[5] = " ";
char p_buffer[5] = " ";
Adafruit_BMP280 bmp; 

U8GLIB_NHD_C12864 u8g(13, 11, 8, 10, 9); // Instancia para la pantalla.
/*---------------------------------------------------------------------------
 | JLX12864G-086 (LCD Gráfico 128x64)                                        |
 |---------------------------------------------------------------------------|
 | Conexionado de la pantalla :                                                             |
 |          CS : 8         VDD : 3v3                                         |
 |         RST : 9         VSS : GND                                         |
 |          RS : 10       LEDA : 5v                                          |
 | SPI:    SDA : 11                                                          |
 | SPI:    SCK : 13                                                          |
  ---------------------------------------------------------------------------*/
 
void D1(void) {
  u8g.drawFrame(0,0,128,64);    // Dibujar un marco del tamaño de la pantalla.
  u8g.drawFrame(1,1,126,62);    // Dibujar otro marco mas pequeño para hacer la líneas mas gruesas
  u8g.setFont(u8g_font_9x15B);  // Seleccionar una fuente con negrita
  u8g.drawStr(6, 17, "Sensor BMP280");  // Colocar texto incial
  u8g.drawHLine(0, 21, 127);            // Colocar una línea debajo del texto
  u8g.setFont(u8g_font_6x12);           // Cambiar a otra fuente mas pequeña.
  u8g.drawStr(16, 38, "Temp:");         // Desplegar carteles
  u8g.drawStr(16, 53, "Pres:"); 
  u8g.drawFrame(10,25,108,35);          // Dibujar dos marcos para contener los datos.
  u8g.drawFrame(12,27,104,31);
  u8g.setFont(u8g_font_9x15B);          // Cambiar de fuente
  u8g.drawStr(60, 39, t_buffer);        // Mostrar los datos de temperatura y presión
  u8g.drawStr(60, 54, p_buffer);
  u8g.setFont(u8g_font_6x10);           // Cambiar la fuente
   u8g.drawStr(100, 39, "C");           // Carteles de unidades en las variables
  u8g.drawStr(98, 54, "Hp");
}
 
void setup(void) {
  Serial.begin(9600);
   if (!bmp.begin()) {  
    Serial.println(F("No encuentro el sensor BMP280!"));
    while (1);
  }
  u8g.setContrast(1);     // Configurar contraste
  u8g.setRot180();        // Rotar la pantalla (si es necesario)
  u8g.setColorIndex(1);   // Pixeles activados
}

void loop(void) {
  u8g.firstPage();  
  do {
        // Bucle para dibujar en la pantalla
    D1();
   } 
  while( u8g.nextPage() );
   t= (bmp.readTemperature());  // Obtener la temperatura
  dtostrf(t, 2, 1, t_buffer);   // Pasar a texto
  p =(bmp.readPressure()/100);  // Obtener la presión
  dtostrf(p, 4, 0, p_buffer);   // Pasar a texto
  delay(100);                   // Redibujar cada 100 mS
}
