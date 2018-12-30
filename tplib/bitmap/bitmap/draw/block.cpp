#ifndef _TPLIB_BITMAP_BITMAP_DRAW_BLOCK_CPP__
#define _TPLIB_BITMAP_BITMAP_DRAW_BLOCK_CPP__

void Bitmap::clip(Bitmap &src, int x, int y, int h, int w)
{
	create(h, w);
	for (int i = 0; i < h; ++i)
	{
		BYTE *id = pixel + i * biWidthSize;
		BYTE *is = src.pixel + ((x + i) * src.biWidthSize + y * 3);
		for (int j = w * 3; j > 0; --j)
			*(id++) = *(is++);
	}	
}

void Bitmap::drawImage(Bitmap &src, int x, int y)
{
	for (int i = 0; i < src.biHeight; ++i)
	{
		BYTE *id = pixel + ((x + i) * biWidthSize + y * 3);
		BYTE *is = src.pixel + i * src.biWidthSize;
		for (int j = src.biWidth * 3; j > 0; --j)
			*(id++) = *(is++);
	}	
}

void Bitmap::drawImage(Bitmap &src, int x, int y, Color tp)
{
	for (int i = 0; i < src.biHeight; ++i)
	{
		BYTE *id = pixel + ((x + i) * biWidthSize + y * 3);
		BYTE *is = src.pixel + i * src.biWidthSize;
		for (int j = src.biWidth; j > 0; --j)
		{
			if ((*(id)) != tp.B || (*(id + 1)) != tp.G || (*(id + 2)) != tp.R)
			{
				*(id++) = *(is++);
				*(id++) = *(is++);
				*(id++) = *(is++);
			}
			else
			{
				id += 3;
				is += 3;
			}
		}
	}	
}

void Bitmap::drawImageShadow(Bitmap &src, int x, int y, Bitmap &tp)
{
	for (int i = 0; i < src.biHeight; ++i)
	{
		BYTE *id = pixel + ((x + i) * biWidthSize + y * 3);
		BYTE *is = src.pixel + i * src.biWidthSize;
		BYTE *itp = tp.pixel + i * tp.biWidthSize;
		for (int j = src.biWidth * 3; j > 0; --j)
		{
			(*id) = ((*id) & (*itp)) | ((*is) & ~(*itp));
			++id; ++is; ++itp;
		}
	}	
}

void Bitmap::drawImageBit(Bitmap &src, int x, int y, int op)
{
	if (op == PUT)
	{
		for (int i = 0; i < src.biHeight; ++i)
		{
			BYTE *id = pixel + ((x + i) * biWidthSize + y * 3);
			BYTE *is = src.pixel + i * src.biWidthSize;
			for (int j = src.biWidth * 3; j > 0; --j)
				*(id++) = *(is++);
		}	
	}
	else if (op == AND)
	{
		for (int i = 0; i < src.biHeight; ++i)
		{
			BYTE *id = pixel + ((x + i) * biWidthSize + y * 3);
			BYTE *is = src.pixel + i * src.biWidthSize;
			for (int j = src.biWidth * 3; j > 0; --j)
				*(id++) &= *(is++);
		}	
	}
	else if (op == OR)
	{
		for (int i = 0; i < src.biHeight; ++i)
		{
			BYTE *id = pixel + ((x + i) * biWidthSize + y * 3);
			BYTE *is = src.pixel + i * src.biWidthSize;
			for (int j = src.biWidth * 3; j > 0; --j)
				*(id++) |= *(is++);
		}	
	}
	else if (op == XOR)
	{
		for (int i = 0; i < src.biHeight; ++i)
		{
			BYTE *id = pixel + ((x + i) * biWidthSize + y * 3);
			BYTE *is = src.pixel + i * src.biWidthSize;
			for (int j = src.biWidth * 3; j > 0; --j)
				*(id++) ^= *(is++);
		}	
	}
}


void Bitmap::drawImageAlpha(Bitmap &src, int x, int y, int alpha)
{
	for (int i = 0; i < src.biHeight; ++i)
	{
		BYTE *id = pixel + ((x + i) * biWidthSize + y * 3);
		BYTE *is = src.pixel + i * src.biWidthSize;
		for (int j = src.biWidth * 3; j > 0; --j)
        {
			*(id) = ((*id) * alpha + (*(is++)) * (MAX_ALPHA - alpha)) / MAX_ALPHA;
            ++id;
        }
	}		
}

void Bitmap::drawImageAlpha(Bitmap &src, int x, int y, Bitmap &alpha)
{
	for (int i = 0; i < src.biHeight; ++i)
	{
		BYTE *id = pixel + ((x + i) * biWidthSize + y * 3);
		BYTE *is = src.pixel + i * src.biWidthSize;
		BYTE *ia = alpha.pixel + i * alpha.biWidthSize;
		for (int j = src.biWidth * 3; j > 0; --j)
		{
			(*id) = (int)(((*id) * D255 * (255 - *ia)) + ((*is) * D255 * (*ia)));
			++id; ++is; ++ia;
		}
	}	
}

void Bitmap::resize(Bitmap &src, int h, int w)
{
	create(h, w);
    int sw = src.biWidth - 1;
	int sh = src.biHeight - 1;
	int dw = biWidth - 1;
	int dh = biHeight - 1;
    int B, N, x, y;
 
    int nPixelSize = 3;
    BYTE * pLinePrev, *pLineNext;
    BYTE * pDest;
    BYTE * pA, *pB, *pC, *pD;
    for ( int i = 0; i <= dh; ++i )
    {
        pDest = pixel + i * biWidthSize;
        y = i * sh / dh;
        N = dh - i * sh % dh;
        pLinePrev = src.pixel + (y++) * src.biWidthSize;
        pLineNext = ( N == dh ) ? pLinePrev : src.pixel + y * src.biWidthSize;
        for ( int j = 0; j <= dw; ++j )
        {
            x = j * sw / dw * nPixelSize;
            B = dw - j * sw % dw;
            pA = pLinePrev + x;
            pB = pA + nPixelSize;
            pC = pLineNext + x;
            pD = pC + nPixelSize;
            if ( B == dw )
            {
                pB = pA;
                pD = pC;
            }
            for ( int k = 0; k < nPixelSize; ++k )
            {
                *pDest++ = ( BYTE )( int )(
                    ( B * N * ( *pA++ - *pB - *pC + *pD ) + dw * N * *pB
                    + dh * B * *pC + ( dw * dh - dh * B - dw * N ) * *pD
                    + dw * dh / 2 ) / ( dw * dh )
                );
                ++pB;
                ++pC;
                ++pD;
            }
        }
    }
}

#endif
