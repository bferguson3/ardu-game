#include <Arduboy2.h>

#include "misaki_font.h"

#include <ATMlib.h>
#include "song1.h"

Arduboy2 arduboy;
ATMsynth ATM;

///////////////////////////
//Script Definition Block//
///////////////////////////
PROGMEM const byte jpstring[] = { 0xf0, 0x55,0x8e,0x69, 0xf2, 0x00,0x01,0x02, 0xf0, 0x94, 0xf1, 0x21,0x52,0x44,0x55,0x42,0x4f,0x59, 0xf0, 0x6d, 0xf2, 0x03,0x04,0x05,0x06, 0xf0, 0x8d,0x8a,0x48,0x6d,0x6c,0x8c,0x80,0x59,0x61,0x09,0x5b,0x65,0x56,0xee,0x46,0x65,0x09,0x09, 0xf2, 0x07, 0xf0, 0x48, 0xf2, 0x08, 0xf0, 0x54,0x8d, 0xf2, 0x09, 0xf0, 0x8d, 0xf2, 0x0a,0x0b, };
PROGMEM const byte jpstring2[] = { 0xf0, 0x55,0x8e,0x71,0x6b,0x48,0x4d,0x6c,0x08,0x53,0x65,0x55,0x48, 0xf1, 0x33,0x43,0x49,0x26,0x49, 0xf0, 0x68,0x4f,0x6c,0x4d,0x95,0x5a, }; 

////////////////////////////
//Sprite GFX Def Block//////
////////////////////////////
PROGMEM const byte player_down_1[] = { 0x30, 0x16, 0xed, 0xcd, 0x4d, 0x2d, 0x36, 0x10, };
PROGMEM const byte player_down_2[] = { 0x10, 0x36, 0x2d, 0x4d, 0xcd, 0xed, 0x16, 0x30, };
PROGMEM const byte player_right_1[] = { 0x00, 0x6c, 0x5e, 0x9e, 0xda, 0x5a, 0x2c, 0x00, };
PROGMEM const byte player_right_2[] = { 0x20, 0x16, 0xaf, 0x4f, 0x6d, 0xad, 0x16, 0x00, };
PROGMEM const byte player_left_1[] = { 0x00, 0x2c, 0x5a, 0xda, 0x9e, 0x5e, 0x6c, 0x00, };
PROGMEM const byte player_left_2[] = { 0x00, 0x16, 0xad, 0x6d, 0x4f, 0xaf, 0x16, 0x20, };
PROGMEM const byte player_up_1[] = { 0x30, 0x16, 0xef, 0xcf, 0x4f, 0x2f, 0x36, 0x10, };
PROGMEM const byte player_up_2[] = { 0x10, 0x36, 0x2f, 0x4f, 0xcf, 0xef, 0x16, 0x30, };

//pointer array to sprites (byte arr) 
const byte *player_sheet[] = { player_down_1, player_down_2, player_right_1, player_right_2, 
                               player_left_1, player_left_2, player_up_1, player_up_2 };

byte player_frame = 0x00;
byte player_frame_delay = 0x00;
const byte p_anim_speed = 0x03; 
const byte player_speed = 0x01;
byte player_x = 0x20;
byte player_y = 0x20;
byte player_dir_offset = 0x00;


void setup()
{
  arduboyQuickInit();
  
  arduboy.setFrameRate(30);
  arduboy.audio.on();

  ATM.play(score);
}

void arduboyQuickInit()
{
  arduboy.boot();
  arduboy.display();
  arduboy.audio.begin();
  arduboy.waitNoButtons();
}

void loop()
{
  if (!(arduboy.nextFrame())) {
    FixedUpdate(); //Only call once per frame; call update every cycle
    return;
  }

  //Player Animation frame offset tick:
  player_frame_delay++;
  if(player_frame_delay > p_anim_speed){
    player_frame++;
    player_frame_delay = 0;
  }
  if(player_frame > 1) player_frame = 0;

  //Input code:
  if(arduboy.pressed(UP_BUTTON)) {
    player_dir_offset = 6;
    player_y -= player_speed;
  }
  if(arduboy.pressed(DOWN_BUTTON)) {
    player_dir_offset = 0;
    player_y += player_speed;
  }
  if(arduboy.pressed(RIGHT_BUTTON)) {
    player_dir_offset = 2;
    player_x += player_speed;
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    player_dir_offset = 4;
    player_x -= player_speed;
  }  
  draw();
}

void FixedUpdate()
{
  
}

void draw()
{
  arduboy.clear(); //Erase vbuffer

  drawText(0, 0, jpstring2, sizeof(jpstring2));
  arduboy.drawBitmap(player_x, player_y, player_sheet[player_frame+player_dir_offset], 8, 8, WHITE);
  
  arduboy.display(); //Push vbuffer
}

//////////////////////////////////
//Bitmap JP Text Display Routine//
//////////////////////////////////
void drawText(uint8_t x, uint8_t y, const uint8_t *mes, uint8_t cnt)
{
  uint8_t pb;
  uint8_t page;
  uint8_t screen_start = 0;
  uint8_t screen_end = 128;

  if (x < screen_start) {
    x = screen_start;
  }
  
  for (uint8_t i = 0; i < cnt; i++) {
    pb = pgm_read_byte_near(mes + i);

    switch (pb) {
      case MISAKI_FONT_F0_PAGE:
        page = MISAKI_FONT_F0_PAGE;
        continue;
      case MISAKI_FONT_F1_PAGE:
        page = MISAKI_FONT_F1_PAGE;
        continue;
      case MISAKI_FONT_F2_PAGE:
        page = MISAKI_FONT_F2_PAGE;
        continue;
    }

    if (!page) {
      continue;
    }

    switch (page) {
      #ifdef MISAKI_FONT_F0_H
        case MISAKI_FONT_F0_PAGE:
          if (pb > MISAKI_FONT_F0_SIZE) {
            continue;
          }      
          if ((x + 8) > screen_end) {
            x = screen_start;   
            y = y + 8;
          }
          arduboy.drawBitmap(x, y,  misaki_font_f0[ pb ], MISAKI_FONT_F0_W, 8, WHITE);
          x = x + 8;    
          break;
      #endif
      #ifdef MISAKI_FONT_F1_H
        case MISAKI_FONT_F1_PAGE:
          if (pb > MISAKI_FONT_F1_SIZE) {
            continue;
          }      
          if ((x + 4) > screen_end) {
            x = screen_start;   
            y = y + 8;
          }
          arduboy.drawBitmap(x, y,  misaki_font_f1[ pb ], MISAKI_FONT_F1_W, 8, WHITE);
          arduboy.drawBitmap(x + 3, y, misaki_font_0x00, 1, 8, WHITE);
          x = x + 4;  
          break;
      #endif
      #ifdef MISAKI_FONT_F2_H
        case MISAKI_FONT_F2_PAGE:
          if (pb > MISAKI_FONT_F2_SIZE) {
            continue;
          }      
          if ((x + 8) > screen_end) {
            x = screen_start;   
            y = y + 8;
          }
          arduboy.drawBitmap(x, y,  misaki_font_f2[ pb ], MISAKI_FONT_F2_W, 8, WHITE);
          arduboy.drawBitmap(x + 7, y, misaki_font_0x00, 1, 8, WHITE);
          x = x + 8;    
          break;
      #endif
    }
  }
}
