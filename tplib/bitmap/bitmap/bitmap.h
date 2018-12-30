#ifndef _TPLIB_BITMAP_BITMAP_BITMAP_H__
#define _TPLIB_BITMAP_BITMAP_BITMAP_H__


class Bitmap{

	public:
		
		static const int PUT = 0;
		static const int AND = 1;
		static const int OR = 2;
		static const int XOR = 3;
		
		static const int MAX_ALPHA = 100;
		
		int bfSize;			//file size
		int padding;		//padding
		int biSizeImage;	//bitmap size
		int biWidthSize;	//bitmap size for each line
		
		int biWidth;		//bitmap width
		int biHeight;		//bitmap height
		BYTE *pixel;
		
	//class structure
		Bitmap() {pixel = NULL;}
		~Bitmap() { if (pixel != NULL) delete []pixel;}
		Bitmap& operator = (const Bitmap &b) = delete;
		Bitmap(const Bitmap &b) = delete;
		
	//check if a coordinate is legal
		bool legal(int x, int y);
	
	//class initializer, in bitmap.cpp
		void create(int height, int width);
	
	//copy a new bitmap, int bitmap.cpp
		void clone(const Bitmap &src);
	
	//file operation, in bitmap_file.cpp
	
	/*
	 * bmp
	 */
		bool loadBMP(std::string fn);
	
	/*
	 *	function save arg for file-type:
	 *	"", "24", "24b", "24B" : 24-bit bitmap
	 *	"256", "256c","256C", 256-color bitmap
	 *	"16", "16c", "16C", 16-color bitmap
	 *	"2", "2c", "2C", "wb", "WB", white-black bitmap
	 */
		void saveBMP(std::string fn, std::string arg = "");
	
	/*
	 * jpg
	 */
	//	bool openJPG(std::string fn);
	
	
	
	//block operation, in bitmap_block.cpp
	
		void clip(Bitmap &src, int x, int y, int h, int w);
				
		void drawImage(Bitmap &src, int x, int y);
		void drawImage(Bitmap &src, int x, int y, Color transparent);
		void drawImageShadow(Bitmap &src, int x, int y, Bitmap &tp);		
		void drawImageBit(Bitmap &src, int x, int y, int op);
		void drawImageAlpha(Bitmap &src, int x, int y,int alpha);
		void drawImageAlpha(Bitmap &src, int x, int y, Bitmap &alpha);
		
		void resize(Bitmap &src, int h, int w);
	
	//draw operation, in bitmap_draw.cpp
	//	pixel operation
	
		Color getPixel(int x, int y);
		void putPixel(int x, int y, Color c);
		
	//	graphics operation
		void drawLine(int x1, int y1, int x2, int y2, Color c);
		void drawBLine(int x1, int y1, int x2, int y2, Color c, int b = 1);
		void drawHorizontal(int x, int y1, int y2, Color c);
		void drawVertical(int x1, int x2, int y, Color c);
		void drawRect(int x1, int y1, int x2, int y2, Color c);
		void fillRect(int x1, int y1, int x2, int y2, Color c);
		void drawCircle(int x0, int y0, int r, Color c);
		void fillCircle(int x0, int y0, int r, Color c);
		void drawEllipse(int x0, int y0, int a, int b, Color c);
		void fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color c);	
		//       fill an area from p(x, y), where the color distance from p is no more than d, 
		//       the distance of clWhite and clBlack is 1
		void fillArea(int x, int y, Color c, double d = 0); 
		
	
	private:	
		static const BYTE PALETTE256[1025];
		static const BYTE PALETTE16[65];
		static const BYTE PALETTE2[9];
		
		static constexpr double D255 = (1.0 / 255.0);
		
		static const int DIRECTION[4][2];
		
		static int ByteToInt2(BYTE *arg0) { return *((WORD *) arg0); }
		static int ByteToInt4(BYTE *arg0) { return *((int *) arg0); }
		static void Int2ToByte(int arg0, BYTE *arg1) {*((WORD *)arg1) = arg0; }
		static void Int4ToByte(int arg0, BYTE *arg1) {*((int *)arg1) = arg0; }
	
		//only used in saveBMP
		void saveBMP24b(std::string fn);
		void saveBMP256(std::string fn);
		void saveBMP16(std::string fn);
		void saveBMP2(std::string fn);
		//only used in drawCircle & fillCircle
		void drawCircle_8_(int x0, int y0, int x, int y, Color c);
		//only used in drawEllipse
		void drawEllipse_4_(int x0, int y0, int x, int y, Color c);
		
	
};

const int Bitmap::DIRECTION[4][2] = {{-1,0}, {0,1}, {1,0}, {0, -1}};

#include "bitmap.cpp"
#include "file/palette.cpp"
#include "file/bmp.cpp"
#include "draw/block.cpp"
#include "draw/draw.cpp"

//#include "file/jpg.cpp"

#endif