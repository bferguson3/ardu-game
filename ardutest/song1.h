#ifndef SONG_H
#define SONG_H

#define Song const uint8_t PROGMEM

Song score[] = {
0x05,      // Number of tracks
0x00, 0x00,   // Address of track 0
0x0a, 0x00,   // Address of track 1
0x0b, 0x00,   // Address of track 2
0x0c, 0x00,   // Address of track 3
0x0d, 0x00,   // Address of track 4
0x00,     // Channel 0 entry track
0x01,     // Channel 1 entry track
0x02,     // Channel 2 entry track
0x03,     // Channel 3 entry track
//"Track channel 0"
0x9D, 24,   // FX: SET TEMPO: tempo = 24
0x40, 11,   // FX: SET VOLUME: volume = 11
0xFC, 4,    // GOTO track 4
0xFD, 1, 4,   // REPEAT: count = 1 + 1 / track = 4
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 1"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 2"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track channel 3"
0x9F,     // FX: STOP CURRENT CHANNEL
//"Track Track 1"
0x00 + 0,   // NOTE ON: note = 0
0x9F + 2,   // DELAY: ticks = 2
0x00 + 25,    // NOTE ON: note = 25
0x9F + 1,   // DELAY: ticks = 1
0x00 + 37,    // NOTE ON: note = 37
0x9F + 1,   // DELAY: ticks = 1
0x00 + 0,   // NOTE ON: note = 0
0x9F + 1,   // DELAY: ticks = 1
0x00 + 30,    // NOTE ON: note = 30
0x9F + 1,   // DELAY: ticks = 1
0x00 + 49,    // NOTE ON: note = 49
0x9F + 1,   // DELAY: ticks = 1
0x00 + 54,    // NOTE ON: note = 54
0x9F + 1,   // DELAY: ticks = 1
0xFE,     // RETURN

};



#endif
