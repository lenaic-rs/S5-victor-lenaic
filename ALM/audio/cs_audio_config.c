#include "cs_audio_config.h"
#include "i2c_audio.h"

#include <stdio.h>

void cs_begin_init() {
        // Standard initialization sequence,
        // CS43l22 documentation 4.1 page 32
        write_cs(0x00,0x99);
        write_cs(0x32,0x80);
        write_cs(0x32,0x00);
        write_cs(0x00,0x00);
}

void cs_end_init() {
        write_cs(CODEC_MAP_PWR_CTRL1,0x9E);
}

cs_command_t cs_analog_init_seq [] = {
// Delay standard init after analog config

        
        // headphones on and speakers  off
        {CODEC_MAP_PWR_CTRL2,0xAF},        // page 38

        //hp gain 0,4 (000) playback B=A (1)
        // no inverted PCM, no mute
        {CODEC_MAP_PLAYBACK_CTRL1,0x00},   // page 43

        // reset value for charge pump frequency   page 58
        {CODEC_MAP_CHARGE_PUMP_FREQ,0x00},

        // Analog passthrough enable A&B
        // No Mute, no freeze, no de-emphasis, no soft ramp
        {CODEC_MAP_MISC_CTRL,0xC0},               // page 44

        // PAssthrough Gang control B=A
        {CODEC_MAP_PASSTHROUGH_GANG_CTRL,0x80},  // page 42

        // CODEC_MAP_PASSTHROUGH_A & B : default in1  page 46

        // neither zero crossing nor soft ramp 
        {CODEC_MAP_ANALOG_ZC_SR_SET,0x00}, // page 42

        // Analog passtrough in1

        // Passtrough A&B volume  -10dB
        {CODEC_MAP_PASSTHROUGH_A_VOL,-60},      // Page 46
        {CODEC_MAP_PASSTHROUGH_B_VOL,-60},      // Page 46

        // Pass X sel : default reset  : AIN1   // Page 42
        {CODEC_MAP_PASSTHROUGH_A_SELECT,0x01},
        {CODEC_MAP_PASSTHROUGH_B_SELECT,0x01},

        {CS_NOREGISTER,0}

};


void cs_config (cs_command_t *seq) {
   while ((seq != NULL) && (seq->regnum != CS_NOREGISTER)) {
     write_cs(seq->regnum,seq->regval);
     seq++;
   }
}
