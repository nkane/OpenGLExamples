/*
 * Idea from: Handmade Hero - day ~37
 */

typedef struct read_file_result
{
	unsigned int ContentsSize;
	void *Contents;
} read_file_result;

struct loaded_bitmap
{
	int Width;
	int Height;
	unsigned int *Pixels;
};

