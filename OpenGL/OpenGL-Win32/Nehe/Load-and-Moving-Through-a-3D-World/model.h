/*
 *	model.h
 */

typedef struct tagVERTEX
{
	float X;
	float Y;
	float Z;
	float U;
	float V;
} VERTEX;

typedef struct tagTRIANGLE
{
	VERTEX Vertex[3];
} TRIANGLE;

typedef struct tagSECTOR
{
	int NumberTriangles;
	TRIANGLE *Triangle;
} SECTOR;

