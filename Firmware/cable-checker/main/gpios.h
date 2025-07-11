//
// Created by Joshua Wolfson on 9/7/2025.
//

#ifndef DEFINITIONS_H
#define DEFINITIONS_H
// ES8388
///I2C
#define CCLK                2 //SCL
#define CDATA               3 //SDA
#define CE                  4
///I2S
#define MCLK                1
#define ASDOUT              10 //DOUT
#define LRCK                9 //WS
#define DSDIN               8 //DIN
#define SCLK                7 //BCLK

//GlowBit
#define LED_DIN             39
#define LED_COUNT           8

#define MODE_LED_INDEX      0

//Headphone Jack
#define RSH                 11
#define TSH                 12

//ADA377
#define ROTARY_DT           18
#define ROTARY_CLK          17
#define ROTARY_SW           38
#endif //DEFINITIONS_H

//SP3T
#define SP3T_A              40
#define SP3T_B              41
#define SP3T_C              42