#ifndef __LCD_DEFINES_H__
#define __LCD_DEFINES_H__

//One dot-clock is 7/8ths of a CPU cycle... (prescaler = 1)
//                 14/8ths with prescaler = 2 ...
//
//    1 dot = 7/8 cyc
//    n dots = n * 7/8 cyc
//
//    1 = 1 dot / (7/8) cyc
//    1 = 8 dots / 7 cyc
//
//  With prescaling = 2:
//
//    1 dot = 7/8 * 2 cyc = 14/8 cyc
//   
//    8/14 dots = 1 cyc
//    n dots = n*14/8 cyc
//   
//    I coulda sworn the prescaler was on the divide-side...
//   Also, is there any benefit to adding +7*LVDS_PRESCALER-1 for rounding?
// a/o v59-12ish, upon PLL_SYSCLK addition:
// I'm not sure this math is right... but can't visualize it right now
// Regardless, changing the scaler in PLL_SYSCLK doesn't seem to affect
// the apparent syncing problem that resulted from PLL_SYSCLK
// This *should* have some effect! It affects the timer, which determines
// the duration of a row!
// No, it is *definitely* affecting the refresh-rate, but these white bars
// still exist.
// I've seen these before... what was the deal? carry-over from a previous row?
#warning "REVISIT DOTS_TO_CYC MATH"
#warning "DOTS_TO_CYC DOESN'T ROUND UP"
#if(defined(PLL_SYSCLK) && PLL_SYSCLK)
   #define DOTS_TO_CYC(dots) ((((dots)*(7l)*(LVDS_PRESCALER))/4))
#else
   #define DOTS_TO_CYC(dots) ((((dots)*(7l)*(LVDS_PRESCALER))/8))
#endif

#define delay_Dots(numDots) delay_cyc(DOTS_TO_CYC(numDots))


//THESE NOTES ARE OLD:
//This has to be changed every time the DE code is changed...
// Actually, I think it should just match IMAGE_WIDTH
//#define FB_WIDTH 28 //21//19
//#define IMAGE_WIDTH 21


#define TESTVALS   0		//Currently TESTVALS are being used with the LTN
								// display... 
#define LTN 1				//LTN and IDT haven't been used for a while.
#define IDT 2


//Options LTN, IDT, or TESTVALS
// IDT display *still* doesn't sync... maybe my H/V signals aren't right
#define DISPLAY TESTVALS //LTN //TESTVALS //IDT //LTN





//TIMING:
//  Measurements below (in microseconds) are referring to preLVDS
//  There may be other such old-notes...


//        |<--T_Hhigh-->| |<-T_Hlow
//    __   _____________   ____________  3.6V
// H    |_|             |_|           _  0V
//
//    Data Enable
//       Only active when there's valid pixel data
//       (for 512 of the 717 clocks in HSYNC-active)
//       Low during Vsync... (~720us)
//

//IDTech display: 136 dots
//2-136+
//IDTech, last used: 40
//LTN Last used 8
// LTN: 1072-1344-1500 clocks per line, 1024DE... Hsync unused
// SEE Hlow_Delay() notes if this value is large!

#if (DISPLAY == LTN)
#define H_LOW_DOTS   8
#elif (DISPLAY == IDT)
#define H_LOW_DOTS   40//8//1//40 //30 //2//136
#elif (DISPLAY == TESTVALS)
#define H_LOW_DOTS   100//0 //LTN doesn't use H_LOW (DE-only)
                       // And having a value here increases codesize
#endif


//H is set low immediately upon entry of the timer interrupt
// its low-time is controlled via nops
// (so if HLow is long for a particular display, this might need revising)
#define Hlow_Delay() \
   delay_Dots(H_LOW_DOTS)


//#define T_Hlow_CYC 1//8 //(T_Halow_REAL*3)
#define T_Hlow_CYC DOTS_TO_CYC(H_LOW_DOTS)



//This was found expermentally with SwitchResX
//IDTech Last Used: 680
//LTN last used 1024
// Oddly: For the LTN, this doesn't seem to affect the horizontal
//        it does, however, affect the vertical(!)
// If I recall Correctly, this is used only for setting the timer interrupt
//  rate...
#if (DISPLAY == LTN)
#define DE_ACTIVE_DOTS   1024
#elif (DISPLAY == IDT)
#define DE_ACTIVE_DOTS   680 //1024 //800 //920 //943 //812 //472 //1024
#elif (DISPLAY == TESTVALS)
#define DE_ACTIVE_DOTS   1024
#endif

#define T_DE_CYC   DOTS_TO_CYC(DE_ACTIVE_DOTS)

//Horizontal Blank Time: HD_DOTS + H_LOW + DH_DOTS
//  90-320+
//Horizontal Total Time: 1206-1344-2047
// ... but Total = Blank + Pixels, so 90+1024 != 1206
// Excess waits should be thrown in DH (since that's between interrupts)
//T_HD is the time from H inactivated to DE activated
//aka H back-porch: 1-160+
//IDTech Last Used: 50
//LTN last used 5

#if (DISPLAY == LTN)
#define HD_DOTS 5
#elif (DISPLAY == IDT)
#define HD_DOTS   50 //5 //0//20//5 //50 //30 //1 //160
#elif (DISPLAY == TESTVALS)
#define HD_DOTS 50//5
#endif

#define HD_Delay()   delay_Dots(HD_DOTS)

//#define T_HD_CYC 1//3//(T_HD_REAL*3)
#define T_HD_CYC   DOTS_TO_CYC(HD_DOTS)

// This is the number of CPU cycles between DE->L and Horiz->L
// This is just used in calculating the OCR value...
// aka H Front Porch: 0-24+
// IDTech Last Used: 24
// LTN last used 46
// 1072-1024-1-1 = 46
#if (DISPLAY == LTN)
#define DH_DOTS   46
#elif (DISPLAY == IDT)
#define DH_DOTS   24 //46 //480//6//12//24 //46 //24 //122//30 //0 //24
#elif (DISPLAY == TESTVALS)
#define DH_DOTS   0//1000//100//46
#endif

#define T_DH_CYC   DOTS_TO_CYC(DH_DOTS)

//       |
//       v
//      T_DH
//      ||    |<-T_DE->|  |  |<--T_HD (Hsync->DE)
// H   __.  ____________  .___________
//      .|_|  .        .|_|  .
//     _.     .________.     .___________
// DE   |_____| 512clk |_____|
//      ^              ^
//       \___________   \                        (just avoiding \ warning)
//                   \  |     768 Hsyncs
//                    v v
//     _             _ _ _ _ _ _ _ _ _ _ 
// DE   |___________| | | | | | | | | | |______
//
// one Hsync = T_HD+T_DH+T_Hlow+T_DE = 19.865us

//aka V-sync back porch: 7-29-63 "Vbp should be static"
// IDTech Last Used: 29
// LTN last used 3
//LTN Frame: 772-806-1000 lines...
#if (DISPLAY == LTN)
#define T_VD 3
#elif (DISPLAY == IDT)
#define  T_VD 29 //3//29 //7 //29
#elif (DISPLAY == TESTVALS)
#define T_VD 3
#endif

//aka V-sync front porch: 1-3+
// IDTech Last Used: 3
// LTN last used 3
#if (DISPLAY == LTN)
#define T_DV 3
#elif (DISPLAY == IDT)
#define T_DV 3//3 //1 //3
#elif (DISPLAY == TESTVALS)
#define T_DV 3
#endif

//1-6+ (1 is used by the first switch-case...)
// IDTech Last Used: 6
// LTN Last used 16
// 772 - 768 - 1 - 1 = 2
#if (DISPLAY == LTN)
#define T_Vlow 16
#elif (DISPLAY == IDT)
#define T_Vlow   6 //16//6 //2 //6
#elif (DISPLAY == TESTVALS)
#define T_Vlow 32
#endif

// IDTech Last Used: 768
#if (DISPLAY == LTN)
#define V_COUNT   768
#elif (DISPLAY == IDT)
#define V_COUNT   768
#elif (DISPLAY == TESTVALS)
 #if (LVDS_PRESCALER == 8)
  #define V_COUNT 768
 #else
#warning "V_COUNT for LVDS_PRESCALER != 8 was originally 2/3 * 768... this has been removed"
  //This must've been due to stretching... or repeated-rows due to extended
  // DE's? Doesn't make sense, should be the opposite, the case when 
  //  LVDS_PRESCALER is large, no?
  //#define V_COUNT   (768*2/3)
  #define V_COUNT (768)
 #endif
#endif

//                       
//                      |           
//                      V           
//              |<-T_DV>|           |<-T_VD-->|
//              .       .           .         .
//     _____________||__.   124us   .____||___________________
//  V           .   ||  |___________|    ||   .
//     _ _ _ _ _ _ _|| _ _ _ _ _ _ _ _ _ ||_ _ _ _ _ _ _ _ _ _ _
//  H   | | | | | | ||| | | | | | | | | ||| | | | | | | | | | |
//              .   ||                   ||   .
//     _ _ _ _ _.   ||       720us       ||   ._ _ _ _ _ _ _ _ _
// DE   | | | | |___||___________________||___| | | | | | | | |
//                  ||                   ||
//
//                        1
//                        |
//                        v               
//     _________________   ___________________   _____________
//  V                   |_|                   |_|
//  H  |||||||||||||||||||||||||||||||||||||||||||||||||||||||
// DE  ||||||||||||||||_____|||||||||||||||||_____||||||||||||
//                          ^
//                          |
//                          2

#endif
