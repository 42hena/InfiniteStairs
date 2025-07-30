#ifndef __COLOR_H__
#define __COLOR_H__

// »ö»ó
enum class Color : int
{
	Color_Blue = 1,
	Color_Green = 2,
	Color_Red = 4,
	Color_White = Color_Blue | Color_Green | Color_Red,
	Color_Intensity = 8,
};

#endif
