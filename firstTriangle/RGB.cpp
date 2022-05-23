#include "RGB.h"

RGB::RGB(unsigned char _r, unsigned char _g, unsigned char _b)
	: r(_r / 255.0f)
	, g(_g / 255.0f)
	, b(_b / 255.0f)
{
}