#ifndef TEMPLETE_COLORED_VOXEL_H
#define TEMPLETE_COLORED_VOXEL_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/utils/logger.hpp>

#include "templete_uncolored_voxel.h"

using namespace std;
using namespace cv;


typedef Vec<uchar, 2> Color_16; // RRRR RGGG GGGB BBBB
typedef Vec<uchar, 4> Color_32;
typedef Vec<uchar, 8> Color_64;

Color_16 toColor16(int r, int g, int b)
{
	r = int(r / 8);
	g = int(g / 8);
	b = int(b / 8);
	return Color_16(uchar((r << 3) + (g >> 3)), uchar((g << 5) + b));
}

int extractR16(Color_16 color)
{
	return int(color.val[0] >> 3) * 8;
}

int extractG16(Color_16 color)
{
	return int(((color.val[0] & 0x00000007) << 3) + ((color.val[1] & 0x000000E0) >> 5)) * 8;
}

int extractB16(Color_16 color)
{
	return int(color.val[1] & 0x0000001F) * 8;
}

void setR16(Color_16& color, int r)
{
	r = int(r / 8);
	color.val[0] = (color.val[0] & 0x000000F8) + (r << 3);
}

void setG16(Color_16& color, int g)
{
	g = int(g / 8);
	color.val[0] = (color.val[0] & 0x00000007) + (g >> 3);
	color.val[1] = (color.val[1] & 0x000000E0) + (g << 5);
}

void setB16(Color_16& color, int b)
{
	b = int(b / 8);
	color.val[1] = (color.val[1] & 0x0000001F) + b;
}


Color_32 toColor32(int r, int g, int b)
{
	return Color_32(uchar(r), uchar(g), uchar(b), uchar(0));
}

int extractR32(Color_32 color)
{
	return int(color.val[0]);
}

int extractG32(Color_32 color)
{
	return int(color.val[1]);
}

int extractB32(Color_32 color)
{
	return int(color.val[2]);
}

void setR32(Color_32& color, int r)
{
	color.val[0] = uchar(r);
}

void setG32(Color_32& color, int g)
{
	color.val[1] = uchar(g);
}

void setB32(Color_32& color, int b)
{
	color.val[2] = uchar(b);
}


Color_64 toColor64(int r, int g, int b)
{
	return Color_64(uchar((r & 0x0000FF00) >> 8), uchar(r & 0x000000FF),
		uchar((g & 0x0000FF00) >> 8), uchar(g & 0x000000FF),
		uchar((b & 0x0000FF00) >> 8), uchar(b & 0x000000FF),
		uchar(0), uchar(0));
}

int extractR64(Color_64 color)
{
	return int((color.val[0] << 8) + color.val[1]);
}

int extractG64(Color_64 color)
{
	return int((color.val[2] << 8) + color.val[3]);
}

int extractB64(Color_64 color)
{
	return int((color.val[4] << 8) + color.val[5]);
}

void setR64(Color_64& color, int r)
{
	color.val[0] = uchar((r & 0x0000FF00) >> 8);
	color.val[1] = uchar(r & 0x000000FF);
}

void setG64(Color_64& color, int g)
{
	color.val[2] = uchar((g & 0x0000FF00) >> 8);
	color.val[3] = uchar(g & 0x000000FF);
}

void setB64(Color_64& color, int b)
{
	color.val[4] = uchar((b & 0x0000FF00) >> 8);
	color.val[5] = uchar(b & 0x000000FF);
}


template<typename TSDF, typename Weight, typename Color>
class ColoredVoxel
{
private:
	TSDF tsdf;
	Weight weight;
	Color color;
public:
	ColoredVoxel();
	ColoredVoxel(float tsdf);
	ColoredVoxel(float tsdf, int r, int g, int b);
	ColoredVoxel(float tsdf, int weight, int r, int g, int b);
	
	void update(float tsdf, int weight, int r, int g, int b);
	
	float getTSDF() const;
	void setTSDF(float tsdf);

	int getWeight() const;
	void setWeight(int weight);

	int getR() const;
	int getG() const;
	int getB() const;

	void setR(int r);
	void setG(int g);
	void setB(int b);
};


template<typename TSDF, typename Weight, typename Color>
void printColoredVoxel(ColoredVoxel<TSDF, Weight, Color> cv)
{
	cout << "-tsdf:   " << cv.getTSDF() << endl;
	cout << " weight: " << cv.getWeight() << endl;
	cout << " rgb: " << cv.getR();
	cout << " " << cv.getG();
	cout << " " << cv.getB() << endl;
}


template<typename TSDF, typename Weight, typename Color>
ColoredVoxel<TSDF, Weight, Color>::ColoredVoxel() {}

ColoredVoxel<TSDF_8, Weight_8, Color_16>::ColoredVoxel()
{
	this->tsdf = floatToTsdf8(0.f);
	this->weight = intToWeight8(0);
	this->color = toColor16(0, 0, 0);
}

ColoredVoxel<TSDF_16, Weight_16, Color_32>::ColoredVoxel()
{
	this->tsdf = floatToTsdf16(0.f);
	this->weight = intToWeight16(0);
	this->color = toColor32(0, 0, 0);
}

ColoredVoxel<TSDF_32, Weight_32, Color_64>::ColoredVoxel()
{
	this->tsdf = floatToTsdf32(0.f);
	this->weight = intToWeight32(0);
	this->color = toColor64(0, 0, 0);
}


template<typename TSDF, typename Weight, typename Color>
ColoredVoxel<TSDF, Weight, Color>::ColoredVoxel(float) {}

ColoredVoxel<TSDF_8, Weight_8, Color_16>::ColoredVoxel(float tsdf)
{
	this->tsdf = floatToTsdf8(tsdf);
	this->weight = intToWeight8(0);
	this->color = toColor16(0, 0, 0);
}

ColoredVoxel<TSDF_16, Weight_16, Color_32>::ColoredVoxel(float tsdf)
{
	this->tsdf = floatToTsdf16(tsdf);
	this->weight = intToWeight16(0);
	this->color = toColor32(0, 0, 0);
}

ColoredVoxel<TSDF_32, Weight_32, Color_64>::ColoredVoxel(float tsdf)
{
	this->tsdf = floatToTsdf32(tsdf);
	this->weight = intToWeight32(0);
	this->color = toColor64(0, 0, 0);
}


template<typename TSDF, typename Weight, typename Color>
ColoredVoxel<TSDF, Weight, Color>::ColoredVoxel(float, int, int, int) {}

ColoredVoxel<TSDF_8, Weight_8, Color_16>::ColoredVoxel(float tsdf, int r, int g, int b)
{
	this->tsdf = floatToTsdf8(tsdf);
	this->weight = intToWeight8(0);
	this->color = toColor16(r, g, b);
}

ColoredVoxel<TSDF_16, Weight_16, Color_32>::ColoredVoxel(float tsdf, int r, int g, int b)
{
	this->tsdf = floatToTsdf16(tsdf);
	this->weight = intToWeight16(0);
	this->color = toColor32(r, g, b);
}

ColoredVoxel<TSDF_32, Weight_32, Color_64>::ColoredVoxel(float tsdf, int r, int g, int b)
{
	this->tsdf = floatToTsdf32(tsdf);
	this->weight = intToWeight32(0);
	this->color = toColor64(r, g, b);
}


template<typename TSDF, typename Weight, typename Color>
ColoredVoxel<TSDF, Weight, Color>::ColoredVoxel(float, int, int, int, int) {}

ColoredVoxel<TSDF_8, Weight_8, Color_16>::ColoredVoxel(float tsdf, int weight, int r, int g, int b)
{
	this->tsdf = floatToTsdf8(tsdf);
	this->weight = intToWeight8(weight);
	this->color = toColor16(r, g, b);
}

ColoredVoxel<TSDF_16, Weight_16, Color_32>::ColoredVoxel(float tsdf, int weight, int r, int g, int b)
{
	this->tsdf = floatToTsdf16(tsdf);
	this->weight = intToWeight16(weight);
	this->color = toColor32(r, g, b);
}

ColoredVoxel<TSDF_32, Weight_32, Color_64>::ColoredVoxel(float tsdf, int weight, int r, int g, int b)
{
	this->tsdf = floatToTsdf32(tsdf);
	this->weight = intToWeight32(weight);
	this->color = toColor64(r, g, b);
}


template<typename TSDF, typename Weight, typename Color>
void ColoredVoxel<TSDF, Weight, Color>::update(float, int, int, int, int) {}

void ColoredVoxel<TSDF_8, Weight_8, Color_16>::update(float tsdf, int weight, int r, int g, int b)
{
	this->tsdf = floatToTsdf8(tsdf);
	this->weight = intToWeight8(weight);
	this->color = toColor16(r, g, b);
}

void ColoredVoxel<TSDF_16, Weight_16, Color_32>::update(float tsdf, int weight, int r, int g, int b)
{
	this->tsdf = floatToTsdf16(tsdf);
	this->weight = intToWeight16(weight);
	this->color = toColor32(r, g, b);
}

void ColoredVoxel<TSDF_32, Weight_32, Color_64>::update(float tsdf, int weight, int r, int g, int b)
{
	this->tsdf = floatToTsdf32(tsdf);
	this->weight = intToWeight32(weight);
	this->color = toColor64(r, g, b);
}


template<typename TSDF, typename Weight, typename Color>
float ColoredVoxel<TSDF, Weight, Color>::getTSDF() const {}

float ColoredVoxel<TSDF_8, Weight_8, Color_16>::getTSDF() const
{
	return tsdf8ToFloat(this->tsdf);
}

float ColoredVoxel<TSDF_16, Weight_16, Color_32>::getTSDF() const
{
	return tsdf16ToFloat(this->tsdf);
}

float ColoredVoxel<TSDF_32, Weight_32, Color_64>::getTSDF() const
{
	return tsdf32ToFloat(this->tsdf);
}


template<typename TSDF, typename Weight, typename Color>
void ColoredVoxel<TSDF, Weight, Color>::setTSDF(float tsdf) {}

void ColoredVoxel<TSDF_8, Weight_8, Color_16>::setTSDF(float tsdf)
{
	this->tsdf = floatToTsdf8(tsdf);
}

void ColoredVoxel<TSDF_16, Weight_16, Color_32>::setTSDF(float tsdf)
{
	this->tsdf = floatToTsdf16(tsdf);
}

void ColoredVoxel<TSDF_32, Weight_32, Color_64>::setTSDF(float tsdf)
{
	this->tsdf = floatToTsdf32(tsdf);
}


template<typename TSDF, typename Weight, typename Color>
int ColoredVoxel<TSDF, Weight, Color>::getWeight() const {}

int ColoredVoxel<TSDF_8, Weight_8, Color_16>::getWeight() const
{
	return weight8ToInt(this->weight);
}

int ColoredVoxel<TSDF_16, Weight_16, Color_32>::getWeight() const
{
	return weight16ToInt(this->weight);
}

int ColoredVoxel<TSDF_32, Weight_32, Color_64>::getWeight() const
{
	return weight32ToInt(this->weight);
}


template<typename TSDF, typename Weight, typename Color>
void ColoredVoxel<TSDF, Weight, Color>::setWeight(int weight) {}

void ColoredVoxel<TSDF_8, Weight_8, Color_16>::setWeight(int weight)
{
	this->weight = intToWeight8(weight);
}

void ColoredVoxel<TSDF_16, Weight_16, Color_32>::setWeight(int weight)
{
	this->weight = intToWeight16(weight);
}

void ColoredVoxel<TSDF_32, Weight_32, Color_64>::setWeight(int weight)
{
	this->weight = intToWeight32(weight);
}


template<typename TSDF, typename Weight, typename Color>
int ColoredVoxel<TSDF, Weight, Color>::getR() const {}

int ColoredVoxel<TSDF_8, Weight_8, Color_16>::getR() const
{
	return extractR16(this->color);
}

int ColoredVoxel<TSDF_16, Weight_16, Color_32>::getR() const
{
	return extractR32(this->color);
}

int ColoredVoxel<TSDF_32, Weight_32, Color_64>::getR() const
{
	return extractR64(this->color);
}


template<typename TSDF, typename Weight, typename Color>
int ColoredVoxel<TSDF, Weight, Color>::getG() const {}

int ColoredVoxel<TSDF_8, Weight_8, Color_16>::getG() const
{
	return extractG16(this->color);
}

int ColoredVoxel<TSDF_16, Weight_16, Color_32>::getG() const
{
	return extractG32(this->color);
}

int ColoredVoxel<TSDF_32, Weight_32, Color_64>::getG() const
{
	return extractG64(this->color);
}


template<typename TSDF, typename Weight, typename Color>
int ColoredVoxel<TSDF, Weight, Color>::getB() const {}

int ColoredVoxel<TSDF_8, Weight_8, Color_16>::getB() const
{
	return extractB16(this->color);
}

int ColoredVoxel<TSDF_16, Weight_16, Color_32>::getB() const
{
	return extractB32(this->color);
}

int ColoredVoxel<TSDF_32, Weight_32, Color_64>::getB() const
{
	return extractB64(this->color);
}


template<typename TSDF, typename Weight, typename Color>
void ColoredVoxel<TSDF, Weight, Color>::setR(int r) {}

void ColoredVoxel<TSDF_8, Weight_8, Color_16>::setR(int r)
{
	setR16(this->color, r);
}

void ColoredVoxel<TSDF_16, Weight_16, Color_32>::setR(int r)
{
	setR32(this->color, r);
}

void ColoredVoxel<TSDF_32, Weight_32, Color_64>::setR(int r)
{
	setR64(this->color, r);
}


template<typename TSDF, typename Weight, typename Color>
void ColoredVoxel<TSDF, Weight, Color>::setG(int g) {}

void ColoredVoxel<TSDF_8, Weight_8, Color_16>::setG(int g)
{
	setG16(this->color, g);
}

void ColoredVoxel<TSDF_16, Weight_16, Color_32>::setG(int g)
{
	setG32(this->color, g);
}

void ColoredVoxel<TSDF_32, Weight_32, Color_64>::setG(int g)
{
	setG64(this->color, g);
}


template<typename TSDF, typename Weight, typename Color>
void ColoredVoxel<TSDF, Weight, Color>::setB(int b) {}

void ColoredVoxel<TSDF_8, Weight_8, Color_16>::setB(int b)
{
	setB16(this->color, b);
}

void ColoredVoxel<TSDF_16, Weight_16, Color_32>::setB(int b)
{
	setB32(this->color, b);
}

void ColoredVoxel<TSDF_32, Weight_32, Color_64>::setB(int b)
{
	setB64(this->color, b);
}

#endif // !TEMPLETE_COLORED_VOXEL_H