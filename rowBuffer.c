// RowBuffer BETTER TITLED: "RowSettingsBuffer"
//    An entire row is calculated and stored in the rowbuffer
//    before each line is displayed.
//    (There is not nearly enough memory for an entire frameBuffer)
//
//    A single byte is used for each drawable pixel in the row
//    this byte is actually a bit-mask of the OCR/DT values
//    so it's more of a settings-buffer
//    
//    Processing each byte and writing registers takes 14 clock cycles
//     so at full-speed LVDS (1 pixel per 7/8ths clock cycle)
//     then each drawable pixel is 16 LCD pixels wide
//     for a maximum resolution of 64 drawable pixels across
//     (thus, the row-settings-buffer is 64Bytes)
//    (Were the bytes not packed, and we used three bytes per drawable
//     pixel, each readFromSRAM*3+loadToRegister*3 pixel would be 
//     9 cycles... for ~100 pixels and ~300Bytes. Would it really be worth
//     3 times the memory for 1/3 more pixels? Probably not...
//     See RowSegmentBuffer for higher resolution...)
//
//   Red: (+OC1D => RX0+)
//    Off (0/63): OCR1D = 0
//    35/63:      OCR1D = 3
//    51/63:      OCR1D = 4   (FOUR_SHADES only)
//    63/63:      OCR1D >= 6
//   Green: (/OC1B => RX1-)          (B1,0 Active, as well as G2,1)
//    Off (6/63): DTL1 = 0
//    38-39/63:      DTL1 = 1
//    54-55/63:      DTL1 = 2 (FOUR_SHADES only)
//    62-63/63:      DTL1 = 3
//   Blue: (+OC1A => RX2+)               (B3,2 Active from here down)
//    Off (15/63):  OCR1A=4
//    47/63:        OCR1A=5
//    63/63:        OCR1A=6
//
//  For faster pixels: these values could be stored in a settingsBuffer
//  (instead of a frame-buffer based on color values)
//  we have: 
//                             0    1    2    3
//                 ColorVal:  00   01   10   11
//     Red (OCR1D): 0,3,4,6  000, 011, 100, 110
//   Green (DTL1):  0,1,2,3  000, 001, 010, 011
//    Blue (OCR1A): 4,5,6    100, 101, 110, 110
//           (I guess it could be noted that Blue's bit2 is always 1)
//           (also: OCR1A = 7 is totally acceptable, 
//                  so blueOCR=0x4|blueColor)
//           ( Similar can be said for Red... 7 is acceptable)
//  For memory space, we could fit these values directly in a single byte
//    Red Mask: 0x07
//  Green Mask: 0x14
//   Blue Mask: 0x60
//
//  Options: mask and shift, no extra memory
//           andi for red
//           andi for green + 3 shifts
//           5 shifts for blue
//           ... 10 cycles (12 pixels)
//           If green is the low two bits:
//           andi for green
//           andi for red + 2 shifts
//           5 shifts for blue
//           ... 9 cycles (11 pixels)
//          + 3 register writes (3 cycles) = 12cycles
//          + 1 SRAM read (2 cycles) = 14 cycles (16 pixels)
//           ALSO: 5 shifts TOTAL, usable?
//         (This may be outdated... and doesn't take into account
//          mov instructions... so see the code instead of believing this)
//         BUT:
//          64 pixels across * 64 pixels down is 4096 bytes
//          WAY more than my RAM
//          So either way we need to precalculate each row before
//          displaying it
//          Could be as simple as loading direct from program memory



#define LOADROW	TRUE

#define RB_WIDTH 64 //100
#define RB_HEIGHT 48
uint8_t rowBuffer[RB_WIDTH];


//Convert from a frameBuffer color to a rowBuffer setting value...
uint8_t fb_to_rb(uint8_t fbColor)
{
   uint8_t rb = 0;

   //rb bit: 7 6 5 4 3 2 1 0
   //        \_ _/ \_ _/ \ /
   //          V     V    V
   //          |     |    Green Setting
   //          |     Red Setting
   //          Blue Setting

   // Frame Buffer color/shade values:
   //fb bit: 7 6 5 4 3 2 1 0
   //        \ / \ / \ / \ /
   //         V   V   V   V
   //         |   |   |   Red Value (0-3)
   //         |   |   Green Value (0-3)
   //         |   Blue Value (0-3)
   //         Alpha... only partially implemented

#warning "This isn't at all optimized..."
   // Blue setting = Blue Value | 0x04
   uint8_t blueValue = (fbColor & 0x30) >> 4;
   rb = (blueValue << 5) | 0x80;

   // Red setting = redVal << 1 | redVal & 0x01
   uint8_t redValue = (fbColor & 0x03);
   rb |= ((redValue << 1) | (redValue & 0x01)) << 2;

   // Green Setting = Green Value...
   uint8_t greenValue = (fbColor & 0x0C) >> 2;
   rb |= greenValue;

   return rb;
}



