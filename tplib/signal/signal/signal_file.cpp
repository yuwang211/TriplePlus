#ifndef _TPLIB_SIGNAL_SIGNAL_SIGNAL_FILE_CPP__
#define _TPLIB_SIGNAL_SIGNAL_SIGNAL_FILE_CPP__

int SignalProc::getWavSize(std::string fn)
{
	FILE *infile;
	infile = fopen(fn.c_str(), "rb");
	if (infile == NULL) return false;
	BYTE *head = new BYTE[20];
	//RIFF WAVE Chunk
	fread(head, sizeof(BYTE), 12, infile);
	int size = ByteToInt4(head[4], head[5], head[6], head[7]);
	//Format Chunk
	fread(head, sizeof(BYTE), 8, infile);
	int sizeFC = ByteToInt4(head[4], head[5], head[6], head[7]);
	fread(head, sizeof(BYTE), sizeFC, infile);
	int formatTag = ByteToInt2(head[0], head[1]);
	int channels = ByteToInt2(head[2], head[3]);
	int samplesPerSec = ByteToInt4(head[4], head[5], head[6], head[7]);
	int avgBytesPerSec = ByteToInt4(head[8], head[9], head[10], head[11]);
	int blockAlign = ByteToInt2(head[12], head[13]);
	int bitsPerSample = ByteToInt2(head[14], head[15]);
	int dataSize = size - 36;
	int len = dataSize / blockAlign;
	delete []head;
	fclose(infile);
	return len;
}

void SignalProc::printWavInfo(std::string fn)
{
	FILE *infile;
	infile = fopen(fn.c_str(), "rb");
	if (infile == NULL) return;
	BYTE *head = new BYTE[20];
	//RIFF WAVE Chunk
	fread(head, sizeof(BYTE), 12, infile);
	int size = ByteToInt4(head[4], head[5], head[6], head[7]);
	//Format Chunk
	fread(head, sizeof(BYTE), 8, infile);
	int sizeFC = ByteToInt4(head[4], head[5], head[6], head[7]);
	fread(head, sizeof(BYTE), sizeFC, infile);
	int formatTag = ByteToInt2(head[0], head[1]);
	int channels = ByteToInt2(head[2], head[3]);
	int samplesPerSec = ByteToInt4(head[4], head[5], head[6], head[7]);
	int avgBytesPerSec = ByteToInt4(head[8], head[9], head[10], head[11]);
	int blockAlign = ByteToInt2(head[12], head[13]);
	int bitsPerSample = ByteToInt2(head[14], head[15]);
	int dataSize = size - 36;
	int len = dataSize / blockAlign;
	
	printf("Size = %d\n", size);
	printf("SizeFC = %d\n", sizeFC);
	printf("Format tag = %d\n", formatTag);
	printf("Number of channel(s) = %d\n", channels);
	printf("Samples per second = %d\n", samplesPerSec);
	printf("Average bytes per second = %d\n", avgBytesPerSec);
	printf("Block align = %d\n", blockAlign);
	printf("Bits per sample = %d\n", bitsPerSample);
	printf("Data size = %d\n", dataSize);
	printf("Number of samples = %d\n", len);
	printf("Seconds = %.2lf\n", (double)len / samplesPerSec);
	delete []head;
	fclose(infile);
}

template <typename T>
bool SignalProc::loadWav(T &s, std::string fn, int &N)
{
	FILE *infile;
	infile = fopen(fn.c_str(), "rb");
	if (infile == NULL) return false;
	BYTE *head = new BYTE[20];
	//RIFF WAVE Chunk
	fread(head, sizeof(BYTE), 12, infile);
	int size = ByteToInt4(head[4], head[5], head[6], head[7]);
	//Format Chunk
	fread(head, sizeof(BYTE), 8, infile);
	int sizeFC = ByteToInt4(head[4], head[5], head[6], head[7]);
	fread(head, sizeof(BYTE), sizeFC, infile);
	int formatTag = ByteToInt2(head[0], head[1]);
	int channels = ByteToInt2(head[2], head[3]);
	int samplesPerSec = ByteToInt4(head[4], head[5], head[6], head[7]);
	int avgBytesPerSec = ByteToInt4(head[8], head[9], head[10], head[11]);
	int blockAlign = ByteToInt2(head[12], head[13]);
	int bitsPerSample = ByteToInt2(head[14], head[15]);
	//Fact Chunk
	fread(head, sizeof(BYTE), 8, infile);
	if (head[0] == 'f')    
	{
		int sizeFact = ByteToInt4(head[4], head[5], head[6], head[7]);
		fread(head, sizeof(BYTE), sizeFact, infile);
		fread(head, sizeof(BYTE), 8, infile);
	}
	//Data Chunk
	//dataSize = ByteToInt4(head[4], head[5], head[6], head[7]);
	int dataSize = size - 36;
	int len = dataSize / blockAlign;
	SHORTINT *data = new SHORTINT[len];
	fread(data, sizeof(SHORTINT), len, infile);
	fclose(infile);
	N = len;
	for (int i = 0; i < N; ++i)
		s[i] = (double)data[i];
	delete []head;
	delete []data;
	return true;
}

template <typename T>
void SignalProc::saveWav(const T &s, std::string fn, int N)
{
	int len = N;
	int formatTag = 1;
	int channels = 1;
	int samplesPerSec = 44100;
	int avgBytesPerSec = 88200;
	int blockAlign = 2;
	int bitsPerSample = 16;
	int dataSize = len * blockAlign;
	int size = dataSize + 36;
	SHORTINT *data = new SHORTINT[len];
	for (int i = 0; i < N; ++i)
		data[i] = (SHORTINT)s[i];
	FILE *outfile;
	outfile = fopen(fn.c_str(), "wb");
	BYTE *head = new BYTE[44];
	memset(head, 0, 44);
	head[0] = 'R'; head[1] = 'I'; head[2] = 'F'; head[3] = 'F';
	Int4ToByte(head[4], head[5], head[6], head[7], size);
	head[8] = 'W'; head[9] = 'A'; head[10] = 'V';head[11] = 'E';
	head[12] = 'f'; head[13] = 'm'; head[14] = 't';head[15] = ' ';
	Int4ToByte(head[16], head[17], head[18], head[19], 16);
	Int2ToByte(head[20], head[21], formatTag);
	Int2ToByte(head[22], head[23], channels);
	Int4ToByte(head[24], head[25], head[26], head[27], samplesPerSec);
	Int4ToByte(head[28], head[29], head[30], head[31], avgBytesPerSec);
	Int2ToByte(head[32], head[33], blockAlign);
	Int2ToByte(head[34], head[35], bitsPerSample);
	head[36] = 'd'; head[37] = 'a'; head[38] = 't'; head[39] = 'a';
	Int4ToByte(head[40], head[41], head[42], head[43], dataSize);
	fwrite(head, sizeof(BYTE), 44, outfile);
	fwrite(data, sizeof(SHORTINT), len, outfile);
	fclose(outfile);
	delete []head;
	delete []data;
}

int SignalProc::ByteToInt2(BYTE c0, BYTE c1)
{
	return c0 + (c1 << 8);
}

int SignalProc::ByteToInt4(BYTE c0, BYTE c1, BYTE c2, BYTE c3)
{
	return c0 + (c1 << 8) + (c2 << 16) + (c3 << 24);
}

void SignalProc::Int2ToByte(BYTE &c0, BYTE &c1, int x)
{
	c0 = (BYTE)((x >> 0) & 0xFF);
	c1 = (BYTE)((x >> 8) & 0xFF);
}

void SignalProc::Int4ToByte(BYTE &c0, BYTE &c1, BYTE &c2, BYTE &c3, int x)
{
	c0 = (BYTE)((x >> 0) & 0xFF);
	c1 = (BYTE)((x >> 8) & 0xFF);
	c2 = (BYTE)((x >> 16) & 0xFF);
	c3 = (BYTE)((x >> 24) & 0xFF);
}



#endif
