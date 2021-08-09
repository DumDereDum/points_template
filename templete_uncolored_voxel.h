#ifndef TEMPLETE_UNCOLORED_VOXEL_H
#define TEMPLETE_UNCOLORED_VOXEL_H


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/utils/logger.hpp>

using namespace std;
using namespace cv;

#define MAX_WEIGHT 255

typedef uchar TSDF_8;
typedef Vec<uchar, 2> TSDF_16;
typedef Vec<uchar, 4> TSDF_32;


inline TSDF_8 floatToTsdf8(float num)
{
	return num > 0 ? (uchar(num * 127.f)) : (uchar(num * -127.f) + 128);
}

inline float tsdf8ToFloat(TSDF_8 num)
{
	return num > 128 ? (0 - float(num - 128) / 127.f) : (float(num) / 127.f);
}


inline TSDF_16 floatToTsdf16(float num)
{
	return num > 0 ? TSDF_16(0, uchar(num * 255.f)) : TSDF_16(uchar(num * -255.f), 0);
}

inline float tsdf16ToFloat(TSDF_16 num)
{
	return num.val[0] > 0 ? (float(num.val[0]) / -255.f) : (float(num.val[1]) / 255.f);
}


inline TSDF_32 floatToTsdf32(float num)
{
	TSDF_32 res;
	if (num > 0)
	{
		if (num <= 0.5)
			res = TSDF_32(0, 0, uchar(num * 510.f), 0);
		else
			res = TSDF_32(0, 0, uchar(255), uchar((num - 0.5) * 510.f));
	}
	else
	{
		if (num >= -0.5)
			res = TSDF_32(uchar(num * -510.f), 0, 0, 0);
		else
			res = TSDF_32(uchar(255), uchar((num + 0.5) * -510.f), 0, 0);
	}
	return res;
}

inline float tsdf32ToFloat(TSDF_32 num)
{
	return num.val[0] != 0 ? (float(num.val[0]) + float(num.val[1])) / -510.f : (float(num.val[2]) + float(num.val[3])) / 510.f;
}


typedef uchar Weight_8;
typedef Vec<uchar, 2> Weight_16;
typedef Vec<uchar, 4> Weight_32;

Weight_8 intToWeight8(int weight)
{
	return weight > 255 ? uchar(255) : uchar(weight & 0x000000FF);
}


int weight8ToInt(Weight_8 weight)
{
	return int(weight);
}

Weight_16 intToWeight16(int weight)
{
	return weight > 65535 ? Weight_16(uchar(255), uchar(255)) : Weight_16(uchar((weight & 0x0000FF00) >> 8), uchar(weight & 0x000000FF));
}

int weight16ToInt(Weight_16 weight)
{
	return (int(weight.val[0]) << 8) + int(weight.val[1]);
}


Weight_32 intToWeight32(int weight)
{
	return Weight_32(uchar((weight & 0xFF000000) >> 24), uchar((weight & 0x00FF0000) >> 16),
		uchar((weight & 0x0000FF00) >> 8), uchar(weight & 0x000000FF));
}


int weight32ToInt(Weight_32 weight)
{
	return (int(weight.val[0]) << 24) + (int(weight.val[1]) << 16) + (int(weight.val[2]) << 8) + int(weight.val[3]);
}

template<typename TSDF, typename Weight>
class UncoloredVoxel
{
private:
	TSDF tsdf;
	Weight weight;
public:
	UncoloredVoxel();
	UncoloredVoxel(float tsdf);

	float getTSDF() const;
	void setTSDF(float tsdf);

	int getWeight() const;
	void setWeight(int weight);

	void update(float tsdf, int weigth);
};

template<typename TSDF, typename Weight>
void printUncoloredVoxel(UncoloredVoxel<TSDF, Weight> ucv)
{
	cout << "-tsdf:   " << ucv.getTSDF() << endl;
	cout << " weight: " << ucv.getWeight() << endl;
}

template<typename TSDF, typename Weight>
UncoloredVoxel<TSDF, Weight>::UncoloredVoxel() {}

UncoloredVoxel<TSDF_8, Weight_8>::UncoloredVoxel()
{
	this->tsdf = floatToTsdf8(0.f);
	this->weight = intToWeight8(0);
}

UncoloredVoxel<TSDF_16, Weight_16>::UncoloredVoxel()
{
	this->tsdf = floatToTsdf16(0.f);
	this->weight = intToWeight16(0);
}

UncoloredVoxel<TSDF_32, Weight_32>::UncoloredVoxel()
{
	this->tsdf = floatToTsdf32(0.f);
	this->weight = intToWeight32(0);
}


template<typename TSDF, typename Weight>
UncoloredVoxel<TSDF, Weight>::UncoloredVoxel(float) {}

UncoloredVoxel<TSDF_8, Weight_8>::UncoloredVoxel(float tsdf)
{
	this->tsdf = floatToTsdf8(tsdf);
	this->weight = intToWeight8(0);
}

UncoloredVoxel<TSDF_16, Weight_16>::UncoloredVoxel(float tsdf)
{
	this->tsdf = floatToTsdf16(tsdf);
	this->weight = intToWeight16(0);
}

UncoloredVoxel<TSDF_32, Weight_32>::UncoloredVoxel(float tsdf)
{
	this->tsdf = floatToTsdf32(tsdf);
	this->weight = intToWeight32(0);
}


template<typename TSDF, typename Weight>
float UncoloredVoxel<TSDF, Weight>::getTSDF() const {}

float UncoloredVoxel<TSDF_8, Weight_8>::getTSDF() const
{
	return tsdf8ToFloat(this->tsdf);
}

float UncoloredVoxel<TSDF_16, Weight_16>::getTSDF() const
{
	return tsdf16ToFloat(this->tsdf);
}

float UncoloredVoxel<TSDF_32, Weight_32>::getTSDF() const
{
	return tsdf32ToFloat(this->tsdf);
}


template<typename TSDF, typename Weight>
void UncoloredVoxel<TSDF, Weight>::setTSDF(float tsdf) {}

void UncoloredVoxel<TSDF_8, Weight_8>::setTSDF(float tsdf)
{
	this->tsdf = floatToTsdf8(tsdf);
}

void UncoloredVoxel<TSDF_16, Weight_16>::setTSDF(float tsdf)
{
	this->tsdf = floatToTsdf16(tsdf);
}

void UncoloredVoxel<TSDF_32, Weight_32>::setTSDF(float tsdf)
{
	this->tsdf = floatToTsdf32(tsdf);
}


template<typename TSDF, typename Weight>
int UncoloredVoxel<TSDF, Weight>::getWeight() const {}

int UncoloredVoxel<TSDF_8, Weight_8>::getWeight() const
{
	return weight8ToInt(this->weight);
}

int UncoloredVoxel<TSDF_16, Weight_16>::getWeight() const
{
	return weight16ToInt(this->weight);
}

int UncoloredVoxel<TSDF_32, Weight_32>::getWeight() const
{
	return weight32ToInt(this->weight);
}


template<typename TSDF, typename Weight>
void UncoloredVoxel<TSDF, Weight>::setWeight(int weight) {}

void UncoloredVoxel<TSDF_8, Weight_8>::setWeight(int weight)
{
	this->weight = intToWeight8(weight);
}

void UncoloredVoxel<TSDF_16, Weight_16>::setWeight(int weight)
{
	this->weight = intToWeight16(weight);
}

void UncoloredVoxel<TSDF_32, Weight_32>::setWeight(int weight)
{
	this->weight = intToWeight32(weight);
}


template<typename TSDF, typename Weight>
void UncoloredVoxel<TSDF, Weight>::update(float tsdf, int weight) {}

void UncoloredVoxel<TSDF_8, Weight_8>::update(float tsdf, int weight)
{
	this->tsdf = floatToTsdf8(tsdf);
	this->weight = intToWeight8(weight);
}

void UncoloredVoxel<TSDF_16, Weight_16>::update(float tsdf, int weight)
{
	this->tsdf = floatToTsdf16(tsdf);
	this->weight = intToWeight16(weight);
}

void UncoloredVoxel<TSDF_32, Weight_32>::update(float tsdf, int weight)
{
	this->tsdf = floatToTsdf32(tsdf);
	this->weight = intToWeight32(weight);
}

#endif // !TEMPLETE_UNCOLORED_VOXEL_H