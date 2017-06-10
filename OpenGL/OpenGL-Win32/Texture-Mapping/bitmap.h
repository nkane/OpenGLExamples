#pragma pack(push, 1)
struct bitmap_header
{
	unsigned short int FileType;
	unsigned int   	   FileSize;
	unsigned short int Reserved1;
	unsigned short int Reversed2;
	unsigned int   	   BitmapOffset;
	unsigned int   	   Size;
	int	       	   Width;
	int	           Height;
	unsigned short int Planes;
	unsigned short int BitsPerPixel;
	unsigned int       Compression;
	unsigned int   	   SizeOfBitmap;
	int	       	   HorizontalResolution;
	int	           VerticleResolution;
	unsigned int   	   ColorsUsed;
	unsigned int       ColorsImportant;

	unsigned int       RedMask;
	unsigned int       GreenMask;
	unsigned int  	   BlueMask;
};
#pragma pack(pop)

