//charBitmap 0.10-2
//0.10-2 adding CHAR_COUNT
//0.10-1 Making it visible...
//0.10 - first version
//       Taken, and modified, from LCDRevisited2012v24

#if defined(__AVR_ARCH__)
#include <avr/pgmspace.h>
#endif
#include <stdint.h>

#define LAST_CHAR '~'
#define FIRST_CHAR ' '
#define CHAR_COUNT (LAST_CHAR - FIRST_CHAR + 1) //95

//Access a row from a character (stored in a byte, as explained below)
#define getCharRow(letter, row) \
	pgm_read_byte(&(characters[row][(uint8_t)(letter)-(uint8_t)' ']))

// Doing some reverse-engineering here...
// Apparently (judging by orientations of '!' and '$')
//  The characters are stored row-by-row
//  bit 0 corresponds to the LEFT side of the character
//  bit 6 corresponds to the RIGHT side of the character
//  bit 7 is nearly always blank (except one glaring 255)
//  Thus, the font is 7x8 with a space for the next character (8x8?)
// This array starts with ASCII ' ' (0x20)
// -->> !"#$%&'()*+,-./0123456789:;<=>?@ABCDE...Z[\]^_`abcde...z{|}~<<<---
// There's no reason to waste memory on ' ', but it's there...
uint8_t __attribute__ ((progmem)) characters[][CHAR_COUNT] = //'~'-' '+1]=
{
     [0][' '-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1][' '-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2][' '-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [3][' '-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [4][' '-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5][' '-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6][' '-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7][' '-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['!'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [1]['!'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [2]['!'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [3]['!'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4]['!'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['!'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6]['!'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [7]['!'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['"'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [1]['"'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [2]['"'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [3]['"'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [4]['"'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5]['"'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6]['"'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7]['"'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['#'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [1]['#'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [2]['#'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [3]['#'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [4]['#'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [5]['#'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [6]['#'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [7]['#'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['$'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [1]['$'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [2]['$'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [3]['$'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [4]['$'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [5]['$'-' ']=reverseBin(1,1,1,1,1,0,0,0),
     [6]['$'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [7]['$'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['%'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['%'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [2]['%'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['%'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [4]['%'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['%'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [6]['%'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [7]['%'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['&'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [1]['&'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [2]['&'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [3]['&'-' ']=reverseBin(0,1,1,1,0,1,1,0),
     [4]['&'-' ']=reverseBin(1,1,0,1,1,1,0,0),
     [5]['&'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['&'-' ']=reverseBin(0,1,1,1,0,1,1,0),
     [7]['&'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['\''-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [1]['\''-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [2]['\''-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [3]['\''-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [4]['\''-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5]['\''-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6]['\''-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7]['\''-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['('-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [1]['('-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2]['('-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [3]['('-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [4]['('-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [5]['('-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['('-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [7]['('-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0][')'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [1][')'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2][')'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [3][')'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [4][')'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [5][')'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6][')'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [7][')'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['*'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['*'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [2]['*'-' ']=reverseBin(0,0,1,1,1,1,0,0),
     [3]['*'-' ']=reverseBin(1,1,1,1,1,1,1,1),
     [4]['*'-' ']=reverseBin(0,0,1,1,1,1,0,0),
     [5]['*'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [6]['*'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7]['*'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['+'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['+'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2]['+'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [3]['+'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [4]['+'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['+'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['+'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7]['+'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0][','-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1][','-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2][','-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [3][','-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [4][','-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5][','-' ']=reverseBin(0,1,1,1,0,0,0,0),
     [6][','-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [7][','-' ']=reverseBin(0,1,1,0,0,0,0,0),

     [0]['-'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['-'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['-'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [3]['-'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [4]['-'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5]['-'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6]['-'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7]['-'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['.'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['.'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['.'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [3]['.'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [4]['.'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5]['.'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['.'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [7]['.'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['/'-' ']=reverseBin(0,0,0,0,0,1,1,0),
     [1]['/'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [2]['/'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [3]['/'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4]['/'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [5]['/'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [6]['/'-' ']=reverseBin(1,0,0,0,0,0,0,0),
     [7]['/'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['0'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1]['0'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['0'-' ']=reverseBin(1,1,0,1,1,1,0,0),
     [3]['0'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [4]['0'-' ']=reverseBin(1,1,1,0,1,1,0,0),
     [5]['0'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['0'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['0'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['1'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [1]['1'-' ']=reverseBin(1,1,1,1,0,0,0,0),
     [2]['1'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [3]['1'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4]['1'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['1'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['1'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [7]['1'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['2'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1]['2'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['2'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [3]['2'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [4]['2'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [5]['2'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['2'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [7]['2'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['3'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1]['3'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['3'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [3]['3'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [4]['3'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [5]['3'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['3'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['3'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['4'-' ']=reverseBin(0,0,0,1,1,1,0,0),
     [1]['4'-' ']=reverseBin(0,0,1,1,1,1,0,0),
     [2]['4'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [3]['4'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['4'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [5]['4'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [6]['4'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [7]['4'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['5'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [1]['5'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [2]['5'-' ']=reverseBin(1,1,1,1,1,0,0,0),
     [3]['5'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [4]['5'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [5]['5'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['5'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['5'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['6'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [1]['6'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [2]['6'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [3]['6'-' ']=reverseBin(1,1,1,1,1,0,0,0),
     [4]['6'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['6'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['6'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['6'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['7'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [1]['7'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['7'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [3]['7'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [4]['7'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['7'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [6]['7'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [7]['7'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['8'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1]['8'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['8'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['8'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [4]['8'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['8'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['8'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['8'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['9'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1]['9'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['9'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['9'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [4]['9'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [5]['9'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [6]['9'-' ']=reverseBin(0,1,1,1,0,0,0,0),
     [7]['9'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0][':'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1][':'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2][':'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [3][':'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4][':'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5][':'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6][':'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [7][':'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0][';'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1][';'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2][';'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [3][';'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4][';'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5][';'-' ']=reverseBin(0,1,1,1,0,0,0,0),
     [6][';'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [7][';'-' ']=reverseBin(0,1,1,0,0,0,0,0),

     [0]['<'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [1]['<'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2]['<'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [3]['<'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [4]['<'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [5]['<'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['<'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [7]['<'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['='-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['='-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['='-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [3]['='-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [4]['='-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [5]['='-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6]['='-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7]['='-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['>'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [1]['>'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2]['>'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [3]['>'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [4]['>'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [5]['>'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['>'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [7]['>'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['?'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1]['?'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['?'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [3]['?'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [4]['?'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['?'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6]['?'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [7]['?'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['@'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [1]['@'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [2]['@'-' ']=reverseBin(1,1,0,1,1,1,1,0),
     [3]['@'-' ']=reverseBin(1,1,0,1,1,1,1,0),
     [4]['@'-' ']=reverseBin(1,1,0,1,1,1,1,0),
     [5]['@'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [6]['@'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['@'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['A'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [1]['A'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [2]['A'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['A'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['A'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [5]['A'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['A'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [7]['A'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['B'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [1]['B'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [2]['B'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [3]['B'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [4]['B'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [5]['B'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [6]['B'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [7]['B'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['C'-' ']=reverseBin(0,0,1,1,1,1,0,0),
     [1]['C'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [2]['C'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [3]['C'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [4]['C'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [5]['C'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [6]['C'-' ']=reverseBin(0,0,1,1,1,1,0,0),
     [7]['C'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['D'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [1]['D'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [2]['D'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [3]['D'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [4]['D'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [5]['D'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [6]['D'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [7]['D'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['E'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [1]['E'-' ']=reverseBin(0,1,1,0,0,0,1,0),
     [2]['E'-' ']=reverseBin(0,1,1,0,1,0,0,0),
     [3]['E'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [4]['E'-' ']=reverseBin(0,1,1,0,1,0,0,0),
     [5]['E'-' ']=reverseBin(0,1,1,0,0,0,1,0),
     [6]['E'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [7]['E'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['F'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [1]['F'-' ']=reverseBin(0,1,1,0,0,0,1,0),
     [2]['F'-' ']=reverseBin(0,1,1,0,1,0,0,0),
     [3]['F'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [4]['F'-' ']=reverseBin(0,1,1,0,1,0,0,0),
     [5]['F'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [6]['F'-' ']=reverseBin(1,1,1,1,0,0,0,0),
     [7]['F'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['G'-' ']=reverseBin(0,0,1,1,1,1,0,0),
     [1]['G'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [2]['G'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [3]['G'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [4]['G'-' ']=reverseBin(1,1,0,0,1,1,1,0),
     [5]['G'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [6]['G'-' ']=reverseBin(0,0,1,1,1,1,1,0),
     [7]['G'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['H'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [1]['H'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['H'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['H'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [4]['H'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['H'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['H'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [7]['H'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['I'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1]['I'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2]['I'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [3]['I'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4]['I'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['I'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['I'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['I'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['J'-' ']=reverseBin(0,0,0,1,1,1,1,0),
     [1]['J'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [2]['J'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [3]['J'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [4]['J'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['J'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['J'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['J'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['K'-' ']=reverseBin(1,1,1,0,0,1,1,0),
     [1]['K'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [2]['K'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [3]['K'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [4]['K'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [5]['K'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [6]['K'-' ']=reverseBin(1,1,1,0,0,1,1,0),
     [7]['K'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['L'-' ']=reverseBin(1,1,1,1,0,0,0,0),
     [1]['L'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [2]['L'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [3]['L'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [4]['L'-' ']=reverseBin(0,1,1,0,0,0,1,0),
     [5]['L'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [6]['L'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [7]['L'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['M'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [1]['M'-' ']=reverseBin(1,1,1,0,1,1,1,0),
     [2]['M'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [3]['M'-' ']=reverseBin(1,1,0,1,0,1,1,0),
     [4]['M'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [5]['M'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [6]['M'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [7]['M'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['N'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [1]['N'-' ']=reverseBin(1,1,1,0,0,1,1,0),
     [2]['N'-' ']=reverseBin(1,1,1,1,0,1,1,0),
     [3]['N'-' ']=reverseBin(1,1,0,1,1,1,1,0),
     [4]['N'-' ']=reverseBin(1,1,0,0,1,1,1,0),
     [5]['N'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [6]['N'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [7]['N'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['O'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [1]['O'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [2]['O'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [3]['O'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [4]['O'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [5]['O'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [6]['O'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [7]['O'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['P'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [1]['P'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [2]['P'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [3]['P'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [4]['P'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [5]['P'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [6]['P'-' ']=reverseBin(1,1,1,1,0,0,0,0),
     [7]['P'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['Q'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1]['Q'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['Q'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['Q'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['Q'-' ']=reverseBin(1,1,0,1,1,1,0,0),
     [5]['Q'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [6]['Q'-' ']=reverseBin(0,0,0,1,1,1,0,0),
     [7]['Q'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['R'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [1]['R'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [2]['R'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [3]['R'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [4]['R'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [5]['R'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [6]['R'-' ']=reverseBin(1,1,1,0,0,1,1,0),
     [7]['R'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['S'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1]['S'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['S'-' ']=reverseBin(1,1,1,0,0,0,0,0),
     [3]['S'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [4]['S'-' ']=reverseBin(0,0,0,1,1,1,0,0),
     [5]['S'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['S'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['S'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['T'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [1]['T'-' ']=reverseBin(1,0,1,1,0,1,0,0),
     [2]['T'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [3]['T'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4]['T'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['T'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['T'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['T'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['U'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [1]['U'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['U'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['U'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['U'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['U'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['U'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [7]['U'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['V'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [1]['V'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['V'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['V'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['V'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['V'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [6]['V'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [7]['V'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['W'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [1]['W'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [2]['W'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [3]['W'-' ']=reverseBin(1,1,0,1,0,1,1,0),
     [4]['W'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [5]['W'-' ']=reverseBin(1,1,1,0,1,1,1,0),
     [6]['W'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [7]['W'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['X'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [1]['X'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [2]['X'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [3]['X'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [4]['X'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [5]['X'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [6]['X'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [7]['X'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['Y'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [1]['Y'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['Y'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['Y'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [4]['Y'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['Y'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['Y'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['Y'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['Z'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [1]['Z'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [2]['Z'-' ']=reverseBin(1,0,0,1,1,0,0,0),
     [3]['Z'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4]['Z'-' ']=reverseBin(0,1,1,0,0,0,1,0),
     [5]['Z'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [6]['Z'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [7]['Z'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['['-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1]['['-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [2]['['-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [3]['['-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [4]['['-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [5]['['-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [6]['['-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['['-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['\\'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [1]['\\'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [2]['\\'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [3]['\\'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [4]['\\'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [5]['\\'-' ']=reverseBin(0,0,0,0,0,1,1,0),
     [6]['\\'-' ']=reverseBin(0,0,0,0,0,0,1,0),
     [7]['\\'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0][']'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [1][']'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [2][']'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [3][']'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [4][']'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [5][']'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [6][']'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7][']'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['^'-' ']=reverseBin(0,0,0,1,0,0,0,0),
     [1]['^'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [2]['^'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [3]['^'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [4]['^'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5]['^'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6]['^'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7]['^'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['_'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['_'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['_'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [3]['_'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [4]['_'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5]['_'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6]['_'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7]['_'-' ']=reverseBin(1,1,1,1,1,1,1,1),

     [0]['`'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [1]['`'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2]['`'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [3]['`'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [4]['`'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5]['`'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6]['`'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7]['`'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['a'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['a'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['a'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [3]['a'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [4]['a'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [5]['a'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['a'-' ']=reverseBin(0,1,1,1,0,1,1,0),
     [7]['a'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['b'-' ']=reverseBin(1,1,1,0,0,0,0,0),
     [1]['b'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [2]['b'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [3]['b'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [4]['b'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [5]['b'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [6]['b'-' ']=reverseBin(1,0,1,1,1,1,0,0),
     [7]['b'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['c'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['c'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['c'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [3]['c'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['c'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [5]['c'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['c'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['c'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['d'-' ']=reverseBin(0,0,0,1,1,1,0,0),
     [1]['d'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [2]['d'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [3]['d'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [4]['d'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['d'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['d'-' ']=reverseBin(0,1,1,1,0,1,1,0),
     [7]['d'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['e'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['e'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['e'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [3]['e'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['e'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [5]['e'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [6]['e'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['e'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['f'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [1]['f'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [2]['f'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [3]['f'-' ']=reverseBin(1,1,1,1,0,0,0,0),
     [4]['f'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [5]['f'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [6]['f'-' ']=reverseBin(1,1,1,1,0,0,0,0),
     [7]['f'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['g'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['g'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['g'-' ']=reverseBin(0,1,1,1,0,1,1,0),
     [3]['g'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['g'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['g'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [6]['g'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [7]['g'-' ']=reverseBin(1,1,1,1,1,0,0,0),

     [0]['h'-' ']=reverseBin(1,1,1,0,0,0,0,0),
     [1]['h'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [2]['h'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [3]['h'-' ']=reverseBin(0,1,1,1,0,1,1,0),
     [4]['h'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [5]['h'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [6]['h'-' ']=reverseBin(1,1,1,0,0,1,1,0),
     [7]['h'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['i'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [1]['i'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['i'-' ']=reverseBin(0,1,1,1,0,0,0,0),
     [3]['i'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4]['i'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['i'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['i'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['i'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['j'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [1]['j'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['j'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [3]['j'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [4]['j'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [5]['j'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [6]['j'-' ']=reverseBin(1,1,0,1,1,0,0,0),
     [7]['j'-' ']=reverseBin(0,1,1,1,0,0,0,0),

     [0]['k'-' ']=reverseBin(1,1,1,0,0,0,0,0),
     [1]['k'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [2]['k'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [3]['k'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [4]['k'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [5]['k'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [6]['k'-' ']=reverseBin(1,1,1,0,0,1,1,0),
     [7]['k'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['l'-' ']=reverseBin(0,1,1,1,0,0,0,0),
     [1]['l'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2]['l'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [3]['l'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4]['l'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['l'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['l'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['l'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['m'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['m'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['m'-' ']=reverseBin(1,1,1,0,1,1,0,0),
     [3]['m'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [4]['m'-' ']=reverseBin(1,1,0,1,0,1,1,0),
     [5]['m'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [6]['m'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [7]['m'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['n'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['n'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['n'-' ']=reverseBin(1,1,1,1,1,0,0,0),
     [3]['n'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['n'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['n'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['n'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [7]['n'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['o'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['o'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['o'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [3]['o'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['o'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['o'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['o'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [7]['o'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['p'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['p'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['p'-' ']=reverseBin(1,1,0,1,1,1,0,0),
     [3]['p'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [4]['p'-' ']=reverseBin(0,1,1,0,0,1,1,0),
     [5]['p'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [6]['p'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [7]['p'-' ']=reverseBin(1,1,1,1,0,0,0,0),

     [0]['q'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['q'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['q'-' ']=reverseBin(0,1,1,1,0,1,1,0),
     [3]['q'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['q'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['q'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [6]['q'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [7]['q'-' ']=reverseBin(0,0,0,1,1,1,1,0),

     [0]['r'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['r'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['r'-' ']=reverseBin(1,1,0,1,1,0,0,0),
     [3]['r'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [4]['r'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [5]['r'-' ']=reverseBin(0,1,1,0,0,0,0,0),
     [6]['r'-' ']=reverseBin(1,1,1,1,0,0,0,0),
     [7]['r'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['s'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['s'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['s'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [3]['s'-' ']=reverseBin(1,1,0,0,0,0,0,0),
     [4]['s'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [5]['s'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [6]['s'-' ']=reverseBin(1,1,1,1,1,0,0,0),
     [7]['s'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['t'-' ']=reverseBin(0,0,0,1,0,0,0,0),
     [1]['t'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2]['t'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [3]['t'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [4]['t'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['t'-' ']=reverseBin(0,0,1,1,0,1,0,0),
     [6]['t'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [7]['t'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['u'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['u'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['u'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['u'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['u'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['u'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [6]['u'-' ']=reverseBin(0,1,1,1,0,1,1,0),
     [7]['u'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['v'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['v'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['v'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['v'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['v'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['v'-' ']=reverseBin(0,1,1,1,1,0,0,0),
     [6]['v'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [7]['v'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['w'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['w'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['w'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [3]['w'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [4]['w'-' ']=reverseBin(1,1,0,1,0,1,1,0),
     [5]['w'-' ']=reverseBin(1,1,1,1,1,1,1,0),
     [6]['w'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [7]['w'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['x'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['x'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['x'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [3]['x'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [4]['x'-' ']=reverseBin(0,0,1,1,1,0,0,0),
     [5]['x'-' ']=reverseBin(0,1,1,0,1,1,0,0),
     [6]['x'-' ']=reverseBin(1,1,0,0,0,1,1,0),
     [7]['x'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['y'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['y'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['y'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [3]['y'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [4]['y'-' ']=reverseBin(1,1,0,0,1,1,0,0),
     [5]['y'-' ']=reverseBin(0,1,1,1,1,1,0,0),
     [6]['y'-' ']=reverseBin(0,0,0,0,1,1,0,0),
     [7]['y'-' ']=reverseBin(1,1,1,1,1,0,0,0),

     [0]['z'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [1]['z'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [2]['z'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [3]['z'-' ']=reverseBin(1,0,0,1,1,0,0,0),
     [4]['z'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['z'-' ']=reverseBin(0,1,1,0,0,1,0,0),
     [6]['z'-' ']=reverseBin(1,1,1,1,1,1,0,0),
     [7]['z'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['{'-' ']=reverseBin(0,0,0,1,1,1,0,0),
     [1]['{'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2]['{'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [3]['{'-' ']=reverseBin(1,1,1,0,0,0,0,0),
     [4]['{'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['{'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['{'-' ']=reverseBin(0,0,0,1,1,1,0,0),
     [7]['{'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['|'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [1]['|'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [2]['|'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [3]['|'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [4]['|'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [5]['|'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [6]['|'-' ']=reverseBin(0,0,0,1,1,0,0,0),
     [7]['|'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['}'-' ']=reverseBin(1,1,1,0,0,0,0,0),
     [1]['}'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [2]['}'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [3]['}'-' ']=reverseBin(0,0,0,1,1,1,0,0),
     [4]['}'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [5]['}'-' ']=reverseBin(0,0,1,1,0,0,0,0),
     [6]['}'-' ']=reverseBin(1,1,1,0,0,0,0,0),
     [7]['}'-' ']=reverseBin(0,0,0,0,0,0,0,0),

     [0]['~'-' ']=reverseBin(0,1,1,1,0,1,1,0),
     [1]['~'-' ']=reverseBin(1,1,0,1,1,1,0,0),
     [2]['~'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [3]['~'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [4]['~'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [5]['~'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [6]['~'-' ']=reverseBin(0,0,0,0,0,0,0,0),
     [7]['~'-' ']=reverseBin(0,0,0,0,0,0,0,0)
};

/* OLD:
	{
	 {0,12,54,54,12,0,28,6,24,6,0,0,0,0,0,96,30,12,30,30,
	   56,63,28,63,30,30,0,0,24,0,6,30,62,12,63,60,63,127,127,60,
		  51,30,120,103,15,99,99,28,63,30,63,30,63,51,51,99,99,51,127,30,
		    3,30,8,0,12,0,7,0,56,0,28,0,7,12,24,7,14,0,0,0,
			   0,0,0,0,8,0,0,0,0,0,0,56,24,7,110},
				 {0,30,54,54,62,99,54,6,12,12,102,12,0,0,0,48,51,15,51,51,60,3,6,51,51,51,0
				 ,0,12,0,12,51,99,30,102,102,54,70,70,102,51,12,48,102,6,119,103,54,102,51,1
				 02,51,45,51,51,99,99,51,51,6,6,24,28,0,12,0,6,0,48,0,54,0,6,0,0,6,12,0,0,0,
				 0,0,0,0,12,0,0,0,0,0,0,12,24,12,59},
				 {0,30,54,127,3,51,28,3,6,24,60,12,0,0,0,24,59,12,48,48,54,31,3,48,51,51,12,
				 12,6,63,24,48,123,51,102,3,102,22,22,3,51,12,48,54,6,127,111,99,102,51,102,
				 7,12,51,51,99,54,51,25,6,12,24,54,0,24,30,62,30,48,30,6,110,54,14,30,102,12
				 ,55,31,30,59,110,27,62,62,51,51,99,99,51,63,12,24,12,0},
				 {0,12,0,54,30,24,110,0,6,24,255,63,0,63,0,12,63,12,28,28,51,48,31,24,30,62,
				 12,12,3,0,48,24,123,51,62,3,102,30,30,3,63,12,48,30,6,107,123,99,62,51,62,2
				 8,12,51,51,107,28,30,12,6,24,24,99,0,0,48,102,51,62,51,15,51,110,12,24,54,1
				 2,127,51,51,102,51,54,3,12,51,51,99,54,51,25,7,0,56,0},
				 {0,12,0,127,48,12,59,0,6,24,60,12,0,0,0,6,55,12,6,48,127,48,51,12,51,48,0,0
				 ,6,63,24,12,123,63,102,3,102,22,22,115,51,12,51,54,70,99,115,99,6,59,30,56,
				 12,51,51,127,54,12,70,6,48,24,0,0,0,62,102,3,51,63,6,51,102,12,24,30,12,107
				 ,51,51,102,51,54,30,12,51,51,107,28,51,12,12,24,12,0},
				 {0,0,0,54,31,102,51,0,12,12,102,12,14,0,12,3,51,12,51,51,48,51,51,6,51,24,1
				 2,14,12,0,12,0,3,51,102,102,54,70,6,102,51,12,51,102,102,99,99,54,6,30,54,5
				 1,12,51,30,119,99,12,99,6,96,24,0,0,0,51,102,51,51,3,6,62,102,12,24,54,12,9
				 9,51,51,62,62,6,48,44,51,30,127,54,62,38,12,24,12,0},
				 {0,12,0,54,12,99,110,0,24,6,0,0,12,0,12,1,30,63,63,30,48,30,30,6,30,14,12,1
				 2,24,0,6,12,30,51,63,60,63,127,15,124,51,30,30,103,127,99,99,28,15,56,103,3
				 0,30,63,12,99,99,30,127,30,64,30,0,0,0,110,61,30,110,30,15,48,103,30,27,103
				 ,30,99,51,30,6,48,15,31,24,110,12,54,99,48,63,56,24,7,0},
				 {0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,
				 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,0,0,0,0,31,0,
				 0,14,0,0,0,0,0,15,120,0,0,0,0,0,0,0,31,0,0,0,0,0}
				 };
				 */