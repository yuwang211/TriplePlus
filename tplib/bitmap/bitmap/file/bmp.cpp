#ifndef _TPLIB_BITMAP_BITMAP_FILE_BMP_CPP__
#define _TPLIB_BITMAP_BITMAP_FILE_BMP_CPP__


void Bitmap::saveBMP(std::string fn, std::string arg)
{
	if (arg == "" || arg == "24" || arg == "24b" || arg =="24B")
		saveBMP24b(fn);
	else if (arg == "256" || arg == "256c" || arg == "256C")
		saveBMP256(fn);
	else if (arg == "16" || arg == "16c" || arg == "16C")
		saveBMP16(fn);
	else if (arg == "2" || arg == "2c" || arg == "2C" || arg == "wb" || arg == "WB")
		saveBMP2(fn);
}

void Bitmap::saveBMP256(std::string fn)
{
	int p = (4 - (biWidth % 4)) % 4;
	int biWidthSize = biWidth + p;
	int biSizeImage = biHeight * biWidthSize;
	int biSize = biSizeImage + 54 + 1024;
	FILE *outfile;
	outfile = fopen(fn.c_str(), "wb");
	
	BYTE *head = new BYTE[54];
	BYTE *data = new BYTE[biSizeImage];
	memset(head, 0, 54);
	memset(data, 0, biSizeImage);
	
	head[0] = 'B';
	head[1] = 'M';
	Int4ToByte(bfSize, head + 2);
	head[10] = 0x36;
	head[11] = 0x04;
	head[14] = 0x28;
	Int4ToByte(biWidth, head + 18);
	Int4ToByte(biHeight, head + 22);
	head[26] = 0x01;
	head[28] = 0x08;
	Int4ToByte(biSizeImage, head +34);
	
	BYTE *curp = pixel;
	BYTE *curd = data;
	//bad code!
	for (int i = 0; i < biHeight; ++i)
	{
		for (int j = 0; j < biWidth; ++j)
		{
			int best = 0;
			int delta = abs((int)(*curp)-PALETTE256[0])
			            +abs((int)(*(curp+1))-PALETTE256[1])
						+abs((int)(*(curp+2))-PALETTE256[2]);
			int ndelta;
			for (int c = 1; c < 256; ++c)
			{
				ndelta = abs((int)(*curp)-PALETTE256[(c << 2) + 0])
			            +abs((int)(*(curp+1))-PALETTE256[(c << 2) + 1])
						+abs((int)(*(curp+2))-PALETTE256[(c << 2) + 2]);
				if (ndelta < delta)
				{
					delta = ndelta;
					best = c;
				}
			}
			(*curd) = best;
			curp += 3;
			curd ++;
		}
		curp += padding;
		curd += p;
	}
	//end of bad code
		
	
	fwrite(head, sizeof(BYTE), 54, outfile);
	fwrite(PALETTE256, sizeof(BYTE), 1024, outfile);
	fwrite(data, sizeof(BYTE), biSizeImage, outfile);
	fclose(outfile);
	
	delete[] head;
	delete[] data;
}

void Bitmap::saveBMP16(std::string fn)
{
	int p = (8 - (biWidth % 8)) % 8;
	int biWidthSize = (biWidth + p) / 2;
	int biSizeImage = biHeight * biWidthSize;
	int biSize = biSizeImage + 54 + 64;
	FILE *outfile;
	outfile = fopen(fn.c_str(), "wb");
	
	BYTE *head = new BYTE[54];
	BYTE *data = new BYTE[biSizeImage];
	memset(head, 0, 54);
	memset(data, 0, biSizeImage);
	
	head[0] = 'B';
	head[1] = 'M';
	Int4ToByte(bfSize, head + 2);
	head[10] = 0x76;
	head[11] = 0x00;
	head[14] = 0x28;
	Int4ToByte(biWidth, head + 18);
	Int4ToByte(biHeight, head + 22);
	head[26] = 0x01;
	head[28] = 0x04;
	Int4ToByte(biSizeImage, head +34);
	
	BYTE *curp = pixel;
	BYTE *curd = data;
	//bad code!
	BYTE b = 0;
	int cnt = 0;
	int best, delta, ndelta;
	for (int i = 0; i < biHeight; ++i)
	{
		//printf("I\n");
		for (int j = 0; j < biWidth; ++j)
		{
			best = 0;
			delta = abs((int)(*curp)-PALETTE16[0])
			            +abs((int)(*(curp+1))-PALETTE16[1])
						+abs((int)(*(curp+2))-PALETTE16[2]);
			for (int c = 1; c < 16; ++c)
			{
				ndelta = abs((int)(*curp)-PALETTE16[(c << 2) + 0])
			            +abs((int)(*(curp+1))-PALETTE16[(c << 2) + 1])
						+abs((int)(*(curp+2))-PALETTE16[(c << 2) + 2]);
				if (ndelta < delta)
				{
					delta = ndelta;
					best = c;
				}
			}
			curp += 3;
			if (cnt == 0) b = best;
			else{
				b = (b << 4) + best;
				(*curd) = b;
				curd++;
				//printf("A");
			}
			cnt = ((cnt + 1) & 1);
		}
		curp += padding;
		best = 0;
		for (int j = 0; j < p; ++j)
		{
			if (cnt == 0) b = best;
			else{
				b = (b << 4) + best;
				(*curd) = b;
				curd++;
			//	printf("A");
			}
			cnt = ((cnt + 1) & 1);
		}
		//printf("\n");
	}
	//end of bad code
		
	
	fwrite(head, sizeof(BYTE), 54, outfile);
	fwrite(PALETTE16, sizeof(BYTE), 64, outfile);
	fwrite(data, sizeof(BYTE), biSizeImage, outfile);
	fclose(outfile);
	
	delete[] head;
	delete[] data;
}

void Bitmap::saveBMP2(std::string fn)
{
	int p = (32 - (biWidth % 32)) % 32;
	int biWidthSize = (biWidth + p) / 8;
	int biSizeImage = biHeight * biWidthSize;
	int biSize = biSizeImage + 54 + 8;
	FILE *outfile;
	outfile = fopen(fn.c_str(), "wb");
	
	BYTE *head = new BYTE[54];
	BYTE *data = new BYTE[biSizeImage];
	memset(head, 0, 54);
	memset(data, 0, biSizeImage);
	
	head[0] = 'B';
	head[1] = 'M';
	Int4ToByte(bfSize, head + 2);
	head[10] = 0x3E;
	head[11] = 0x00;
	head[14] = 0x28;
	Int4ToByte(biWidth, head + 18);
	Int4ToByte(biHeight, head + 22);
	head[26] = 0x01;
	head[28] = 0x01;
	Int4ToByte(biSizeImage, head +34);
	
	BYTE *curp = pixel;
	BYTE *curd = data;
	//bad code!
	BYTE b = 0;
	int cnt = 0;
	int best, delta, ndelta;
	for (int i = 0; i < biHeight; ++i)
	{
		//printf("I\n");
		for (int j = 0; j < biWidth; ++j)
		{
			best = 0;
			delta = abs((int)(*curp)-PALETTE2[0])
			            +abs((int)(*(curp+1))-PALETTE2[1])
						+abs((int)(*(curp+2))-PALETTE2[2]);
			for (int c = 1; c < 2; ++c)
			{
				ndelta = abs((int)(*curp)-PALETTE2[(c << 2) + 0])
			            +abs((int)(*(curp+1))-PALETTE2[(c << 2) + 1])
						+abs((int)(*(curp+2))-PALETTE2[(c << 2) + 2]);
				if (ndelta < delta)
				{
					delta = ndelta;
					best = c;
				}
			}
			curp += 3;
			if (cnt == 0) b = best;
			else if (cnt != 7) b = (b << 1) + best;
			else{
				b = (b << 1) + best;
				(*curd) = b;
				curd++;
				//printf("A");
			}
			cnt = ((cnt + 1) & 7);
		}
		curp += padding;
		best = 0;
		for (int j = 0; j < p; ++j)
		{
			if (cnt == 0) b = best;
			else if (cnt != 7) b = (b << 1) + best;
			else{
				b = (b << 1) + best;
				(*curd) = b;
				curd++;
			//	printf("A");
			}
			cnt = ((cnt + 1) & 7);
		}
		//printf("\n");
	}
	//end of bad code
		
	
	fwrite(head, sizeof(BYTE), 54, outfile);
	fwrite(PALETTE2, sizeof(BYTE), 8, outfile);
	fwrite(data, sizeof(BYTE), biSizeImage, outfile);
	fclose(outfile);
	
	delete[] head;
	delete[] data;
}

void Bitmap::saveBMP24b(std::string fn)
{
	FILE *outfile;
	outfile = fopen(fn.c_str(), "wb");
	BYTE *head = new BYTE[54];
	memset(head, 0, 54);
	head[0] = 'B';
	head[1] = 'M';
	Int4ToByte(bfSize, head + 2);
	head[10] = 0x36;
	head[14] = 0x28;
	Int4ToByte(biWidth, head + 18);
	Int4ToByte(biHeight, head + 22);
	head[26] = 0x01;
	head[28] = 0x18;
	Int4ToByte(biSizeImage, head +34);
	fwrite(head, sizeof(BYTE), 54, outfile);
	fwrite(pixel, sizeof(BYTE), biSizeImage, outfile);
	fclose(outfile);
	delete []head;
}

bool Bitmap::loadBMP(std::string fn)
{
	FILE *infile;
	infile = fopen(fn.c_str(), "rb");
	if (infile == NULL) return false;
	BYTE *head = new BYTE[54];
	fread(head, sizeof(BYTE), 54, infile);
	biWidth = ByteToInt4(head + 18);
	biHeight = ByteToInt4(head + 22);
	padding = (4 - ((3 * biWidth) % 4)) % 4;
	biWidthSize = biWidth * 3 + padding;
	biSizeImage = biHeight * biWidthSize;
	bfSize = biSizeImage + 54;
	if (pixel != NULL) delete []pixel;
	pixel = new BYTE[biSizeImage];
	if (head[28] == 0x18)
	{
		fread(pixel, sizeof(BYTE), biSizeImage, infile);
		padding = (4 - ((3 * biWidth) % 4)) % 4;
		biWidthSize = biWidth * 3 + padding;
	}
	else if (head[28] == 0x08)
	{
		int p = (4 - (biWidth % 4)) % 4;
		biWidthSize = biWidth + p;
		biSizeImage = biHeight * biWidthSize;
		BYTE *pal = new BYTE[1025];
		fread(pal, sizeof(BYTE), 1024, infile);
		BYTE *data = new BYTE[biSizeImage];
		fread(data, sizeof(BYTE), biSizeImage, infile);
		BYTE *curp = pixel;
		BYTE *curd = data;
		for (int i = 0; i < biHeight; ++i)
		{
			for (int j = 0; j < biWidth; ++j)
			{
				(*(curp++)) = pal[((*curd) << 2) + 0];
				(*(curp++)) = pal[((*curd) << 2) + 1];
				(*(curp++)) = pal[((*curd) << 2) + 2];
				curd ++;
			}
			curp += padding;
			curd += p;
		}
	}
	else if (head[28] == 0x04)
	{
		int p = (8 - (biWidth % 8)) % 8;
		biWidthSize = (biWidth + p) / 2;
		biSizeImage = biHeight * biWidthSize;
		BYTE *pal = new BYTE[65];
		fread(pal, sizeof(BYTE), 64, infile);
		BYTE *data = new BYTE[biSizeImage];
		fread(data, sizeof(BYTE), biSizeImage, infile);
		BYTE *curp = pixel;
		BYTE *curd = data;
		int cnt = 0;
		int cur = ((*curd) & 0xF0) >> 4;
		for (int i = 0; i < biHeight; ++i)
		{
			for (int j = 0; j < biWidth; ++j)
			{
				(*(curp++)) = pal[(cur << 2) + 0];
				(*(curp++)) = pal[(cur << 2) + 1];
				(*(curp++)) = pal[(cur << 2) + 2];
				if (cnt == 0)
				{
					cur = ((*curd) & 0x0F);
					cnt = 1;
					curd++;
				}
				else
				{
					cur = ((*curd) & 0xF0) >> 4;
					cnt = 0;
				}
			}
			curp += padding;
			for (int j = 0; j < p; ++j)
			if (cnt == 0)
			{
				cur = ((*curd) & 0x0F);
				cnt = 1;
				curd++;
			}
			else
			{
				cur = ((*curd) & 0xF0) >> 4;
				cnt = 0;
			}
		}
	}	
	else if (head[28] == 0x01)
	{
		int p = (32 - (biWidth % 32)) % 32;
		biWidthSize = (biWidth + p) / 8;
		biSizeImage = biHeight * biWidthSize;
		BYTE *pal = new BYTE[9];
		fread(pal, sizeof(BYTE), 8, infile);
		BYTE *data = new BYTE[biSizeImage];
		fread(data, sizeof(BYTE), biSizeImage, infile);
		BYTE *curp = pixel;
		BYTE *curd = data;
		int cnt = 0;
		int cur = (((*curd) >> 7) & 1);
		for (int i = 0; i < biHeight; ++i)
		{
			for (int j = 0; j < biWidth; ++j)
			{
				(*(curp++)) = pal[(cur << 2) + 0];
				(*(curp++)) = pal[(cur << 2) + 1];
				(*(curp++)) = pal[(cur << 2) + 2];
				cnt = ((cnt + 1) & 7);
				if (cnt == 7)
				{
					curd++;
					cur = ((*curd) & 0x80) >> 7;
				}
				else
				{
					cur = (((*curd) >> (7 - cnt)) & 1);
				}
			}
			curp += padding;
			for (int j = 0; j < p; ++j)
			{
				cnt = ((cnt + 1) & 7);
				if (cnt == 7)
				{
					curd++;
					cur = ((*curd) & 0x80) >> 7;
				}
				else
				{
					cur = (((*curd) >> (7 - cnt)) & 1);
				}
			}
		}
	}
	
	padding = (4 - ((3 * biWidth) % 4)) % 4;
	biWidthSize = biWidth * 3 + padding;
	biSizeImage = biHeight * biWidthSize;
	bfSize = biSizeImage + 54;
	delete []head;
	fclose(infile);
	return true;
}


#endif
