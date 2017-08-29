#pragma pack(push, 1)
struct bitmap_header
{
	unsigned short int FileType;
	unsigned int	   FileSize;
	unsigned short int Reserved1;
	unsigned short int Reserved2;
	unsigned int	   BitmapOffset;
	unsigned int	   Size;
	int		   Width;
	int		   Height;
	unsigned short int Planes;
	unsigned short int BitsPerPixel;
	unsigned int	   Compression;
	unsigned int	   SizeOfBitmap;
	int		   HorizontalResolution;
	int		   VerticalResolution;
	unsigned int	   ColorUsed;
	unsigned int 	   ColorsImportant;

	unsigned int	   RedMask;
	unsigned int	   GreenMask;
	unsigned int	   BlueMask;
}
#pragma pop(pop)

struct bit_scan_result
{
	bool 		Found;
	unsigned int	Index;
}

inline bit_scan_result
FindLeastSignificantSetBit(unsigned int value)
{
	bit_scan_result Result = {};

	// only for MSVC
	Result.Found = _BitScanForward((unsigned long *)&Result.Index, value);

	// non-MSVC code
	/*
	for (unsigned int Test = 0; Test < 32; ++Test)
	{
		if (Value & (1 << Test))
		{
			Result.Index = Test;
			Result.Found = true;
			break;
		}
	}
	*/
	
	return Result;
}
