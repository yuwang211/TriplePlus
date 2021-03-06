#ifndef _TPLIB_BITMAP_BITMAP_FILE_PALETTE_CPP__
#define _TPLIB_BITMAP_BITMAP_FILE_PALETTE_CPP__

const BYTE Bitmap::PALETTE256[1025] = 
	{ 0,   0,   0,   0,   0,   0, 128,   0,   0, 128,   0,   0,   0, 128, 128,   0, 
	128,   0,   0,   0, 128,   0, 128,   0, 128, 128,   0,   0, 192, 192, 192,   0, 
	192, 220, 192,   0, 240, 202, 166,   0,   0,  32,  64,   0,   0,  32,  96,   0, 
	  0,  32, 128,   0,   0,  32, 160,   0,   0,  32, 192,   0,   0,  32, 224,   0, 
	  0,  64,   0,   0,   0,  64,  32,   0,   0,  64,  64,   0,   0,  64,  96,   0, 
	  0,  64, 128,   0,   0,  64, 160,   0,   0,  64, 192,   0,   0,  64, 224,   0, 
	  0,  96,   0,   0,   0,  96,  32,   0,   0,  96,  64,   0,   0,  96,  96,   0, 
	  0,  96, 128,   0,   0,  96, 160,   0,   0,  96, 192,   0,   0,  96, 224,   0, 
	  0, 128,   0,   0,   0, 128,  32,   0,   0, 128,  64,   0,   0, 128,  96,   0, 
	  0, 128, 128,   0,   0, 128, 160,   0,   0, 128, 192,   0,   0, 128, 224,   0, 
	  0, 160,   0,   0,   0, 160,  32,   0,   0, 160,  64,   0,   0, 160,  96,   0, 
	  0, 160, 128,   0,   0, 160, 160,   0,   0, 160, 192,   0,   0, 160, 224,   0, 
	  0, 192,   0,   0,   0, 192,  32,   0,   0, 192,  64,   0,   0, 192,  96,   0, 
	  0, 192, 128,   0,   0, 192, 160,   0,   0, 192, 192,   0,   0, 192, 224,   0, 
	  0, 224,   0,   0,   0, 224,  32,   0,   0, 224,  64,   0,   0, 224,  96,   0, 
	  0, 224, 128,   0,   0, 224, 160,   0,   0, 224, 192,   0,   0, 224, 224,   0, 
	 64,   0,   0,   0,  64,   0,  32,   0,  64,   0,  64,   0,  64,   0,  96,   0, 
	 64,   0, 128,   0,  64,   0, 160,   0,  64,   0, 192,   0,  64,   0, 224,   0, 
	 64,  32,   0,   0,  64,  32,  32,   0,  64,  32,  64,   0,  64,  32,  96,   0, 
	 64,  32, 128,   0,  64,  32, 160,   0,  64,  32, 192,   0,  64,  32, 224,   0, 
	 64,  64,   0,   0,  64,  64,  32,   0,  64,  64,  64,   0,  64,  64,  96,   0, 
	 64,  64, 128,   0,  64,  64, 160,   0,  64,  64, 192,   0,  64,  64, 224,   0, 
	 64,  96,   0,   0,  64,  96,  32,   0,  64,  96,  64,   0,  64,  96,  96,   0, 
	 64,  96, 128,   0,  64,  96, 160,   0,  64,  96, 192,   0,  64,  96, 224,   0, 
	 64, 128,   0,   0,  64, 128,  32,   0,  64, 128,  64,   0,  64, 128,  96,   0, 
	 64, 128, 128,   0,  64, 128, 160,   0,  64, 128, 192,   0,  64, 128, 224,   0, 
	 64, 160,   0,   0,  64, 160,  32,   0,  64, 160,  64,   0,  64, 160,  96,   0, 
	 64, 160, 128,   0,  64, 160, 160,   0,  64, 160, 192,   0,  64, 160, 224,   0, 
	 64, 192,   0,   0,  64, 192,  32,   0,  64, 192,  64,   0,  64, 192,  96,   0, 
	 64, 192, 128,   0,  64, 192, 160,   0,  64, 192, 192,   0,  64, 192, 224,   0, 
	 64, 224,   0,   0,  64, 224,  32,   0,  64, 224,  64,   0,  64, 224,  96,   0, 
	 64, 224, 128,   0,  64, 224, 160,   0,  64, 224, 192,   0,  64, 224, 224,   0, 
	128,   0,   0,   0, 128,   0,  32,   0, 128,   0,  64,   0, 128,   0,  96,   0, 
	128,   0, 128,   0, 128,   0, 160,   0, 128,   0, 192,   0, 128,   0, 224,   0, 
	128,  32,   0,   0, 128,  32,  32,   0, 128,  32,  64,   0, 128,  32,  96,   0, 
	128,  32, 128,   0, 128,  32, 160,   0, 128,  32, 192,   0, 128,  32, 224,   0, 
	128,  64,   0,   0, 128,  64,  32,   0, 128,  64,  64,   0, 128,  64,  96,   0, 
	128,  64, 128,   0, 128,  64, 160,   0, 128,  64, 192,   0, 128,  64, 224,   0, 
	128,  96,   0,   0, 128,  96,  32,   0, 128,  96,  64,   0, 128,  96,  96,   0, 
	128,  96, 128,   0, 128,  96, 160,   0, 128,  96, 192,   0, 128,  96, 224,   0, 
	128, 128,   0,   0, 128, 128,  32,   0, 128, 128,  64,   0, 128, 128,  96,   0, 
	128, 128, 128,   0, 128, 128, 160,   0, 128, 128, 192,   0, 128, 128, 224,   0, 
	128, 160,   0,   0, 128, 160,  32,   0, 128, 160,  64,   0, 128, 160,  96,   0, 
	128, 160, 128,   0, 128, 160, 160,   0, 128, 160, 192,   0, 128, 160, 224,   0, 
	128, 192,   0,   0, 128, 192,  32,   0, 128, 192,  64,   0, 128, 192,  96,   0, 
	128, 192, 128,   0, 128, 192, 160,   0, 128, 192, 192,   0, 128, 192, 224,   0, 
	128, 224,   0,   0, 128, 224,  32,   0, 128, 224,  64,   0, 128, 224,  96,   0, 
	128, 224, 128,   0, 128, 224, 160,   0, 128, 224, 192,   0, 128, 224, 224,   0, 
	192,   0,   0,   0, 192,   0,  32,   0, 192,   0,  64,   0, 192,   0,  96,   0, 
	192,   0, 128,   0, 192,   0, 160,   0, 192,   0, 192,   0, 192,   0, 224,   0, 
	192,  32,   0,   0, 192,  32,  32,   0, 192,  32,  64,   0, 192,  32,  96,   0, 
	192,  32, 128,   0, 192,  32, 160,   0, 192,  32, 192,   0, 192,  32, 224,   0, 
	192,  64,   0,   0, 192,  64,  32,   0, 192,  64,  64,   0, 192,  64,  96,   0, 
	192,  64, 128,   0, 192,  64, 160,   0, 192,  64, 192,   0, 192,  64, 224,   0, 
	192,  96,   0,   0, 192,  96,  32,   0, 192,  96,  64,   0, 192,  96,  96,   0, 
	192,  96, 128,   0, 192,  96, 160,   0, 192,  96, 192,   0, 192,  96, 224,   0, 
	192, 128,   0,   0, 192, 128,  32,   0, 192, 128,  64,   0, 192, 128,  96,   0, 
	192, 128, 128,   0, 192, 128, 160,   0, 192, 128, 192,   0, 192, 128, 224,   0, 
	192, 160,   0,   0, 192, 160,  32,   0, 192, 160,  64,   0, 192, 160,  96,   0, 
	192, 160, 128,   0, 192, 160, 160,   0, 192, 160, 192,   0, 192, 160, 224,   0, 
	192, 192,   0,   0, 192, 192,  32,   0, 192, 192,  64,   0, 192, 192,  96,   0, 
	192, 192, 128,   0, 192, 192, 160,   0, 240, 251, 255,   0, 164, 160, 160,   0, 
	128, 128, 128,   0,   0,   0, 255,   0,   0, 255,   0,   0,   0, 255, 255,   0, 
	255,   0,   0,   0, 255,   0, 255,   0, 255, 255,   0,   0, 255, 255, 255,   0,  0};

const BYTE Bitmap::PALETTE16[65] = 
	{ 0,   0,   0,   0,   0,   0, 128,   0,   0, 128,   0,   0,   0, 128, 128,   0, 
	128,   0,   0,   0, 128,   0, 128,   0, 128, 128,   0,   0, 128, 128, 128,   0, 
	192, 192, 192,   0,   0,   0, 255,   0,   0, 255,   0,   0,   0, 255, 255,   0, 
	255,   0,   0,   0, 255,   0, 255,   0, 255, 255,   0,   0, 255, 255, 255,   0,  0};
	
const BYTE Bitmap::PALETTE2[9] = 
    { 0,   0, 	0,   0, 255, 255, 255,   0};
	
#endif