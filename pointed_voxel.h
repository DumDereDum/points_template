#ifndef POINTED_VOXEL
#define POINTED_VOXEL


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/utils/logger.hpp>

#define PVOXEL 0

using namespace std;
using namespace cv;


#if PVOXEL


class TSDF
{
public:
    TSDF() {};
    virtual float get() const = 0;
    virtual void update(float) = 0;
};

class TSDF_8 : public TSDF
{
private:
    int8_t tsdf;
public:
    TSDF_8() : TSDF() { this->tsdf = 0; }
    TSDF_8(float tsdf) : TSDF()
    {
        int8_t res = int8_t(tsdf * (-128.f));
        this->tsdf = res ? res : (tsdf < 0 ? 1 : -1);
    }
    float get() const override
    {
        return float(this->tsdf) * (-1.f / 128.f);
    }
    void update(float tsdf) override
    {
        int8_t res = int8_t(tsdf * (-128.f));
        this->tsdf = res ? res : (tsdf < 0 ? 1 : -1);
    }
};

class TSDF_16 : public TSDF
{
private:
    int16_t tsdf;
public:
    TSDF_16() : TSDF() { this->tsdf = 0; }
    TSDF_16(float tsdf) : TSDF()
    {
        int16_t res = int16_t(tsdf * (-32768.f));
        this->tsdf = res ? res : (tsdf < 0 ? 1 : -1);
    }
    float get() const override
    {
        return float(this->tsdf) * (-1.f / 32768.f);
    }
    void update(float tsdf) override
    {
        int16_t res = int16_t(tsdf * (-32768.f));
        this->tsdf = res ? res : (tsdf < 0 ? 1 : -1);
    }
};

class TSDF_32 : public TSDF
{
private:
    float tsdf;
public:
    TSDF_32() : TSDF() { this->tsdf = 0; }
    TSDF_32(float tsdf) : TSDF()
    {
        this->tsdf = tsdf;
    }
    float get() const override
    {
        return this->tsdf;
    }
    void update(float tsdf) override
    {
        this->tsdf = tsdf;
    }
};


class Weight
{
public:
    Weight() {};
    virtual int get() const = 0;
    virtual void increase() = 0;
    virtual void reset() = 0;
};

class Weight_8 : public Weight
{
private:
    uchar weight;
public:
    Weight_8() : Weight() { this->weight = 0; };
    int get() const { return int(this->weight); }
    void increase() { this->weight++; }
    void reset() { this->weight = 0; }
};

class Weight_16 : public Weight
{
private:
    short int weight;
public:
    Weight_16() : Weight() { this->weight = 0; };
    int get() const { return int(this->weight); }
    void increase() { this->weight++; }
    void reset() { this->weight = 0; }
};

class Weight_32 : public Weight
{
private:
    int weight;
public:
    Weight_32() : Weight() { this->weight = 0; };
    int get() const { return int(this->weight); }
    void increase() { this->weight++; }
    void reset() { this->weight = 0; }
};


class Color
{
public:
    Color() {};
    virtual int getR() const = 0;
    virtual int getG() const = 0;
    virtual int getB() const = 0;
    virtual void updateR(int) = 0;
    virtual void updateG(int) = 0;
    virtual void updateB(int) = 0;
};

class Color_16 : public Color
{
private:
    // RRRRRGGGGGGBBBBB
    short unsigned int color;
public:
    Color_16() : Color()
    {
        color = 0;
    }
    Color_16(int r, int g, int b) : Color()
    {
        // add checking
        r = (int)r / 8;
        g = int(g / 8);
        b = int(b / 8);
        color = (r << 11) + (g << 5) + b;
    }
    int getR() const override
    {
        return (this->color >> 11) * 8;
    }
    int getG() const override
    {
        short unsigned int copy = this->color << 6;
        return (copy >> 11) * 8;
    }
    int getB() const override
    {
        short unsigned int copy = this->color << 11;
        return (copy >> 11) * 8;
    }

    void updateR(int r) override
    {
        r = int(r / 8);
        this->color = this->color & 2047;	// 0000011111111111
        this->color = (r << 11) + this->color;
    }
    void updateG(int g) override
    {
        g = int(g / 8);
        this->color = this->color & 63519;	// 1111100000011111
        this->color = this->color + (g << 5);
    }
    void updateB(int b) override
    {
        b = int(b / 8);
        this->color = this->color & 65504; // 1111111111100000
        this->color = this->color + b;
    }
};

class Color_32 : public Color
{
private:
    // RRRRRRRRRRGGGGGGGGGGGGBBBBBBBBBB
    int color;
public:
    Color_32() : Color()
    {
        color = 0;
    }
    Color_32(int r, int g, int b) : Color()
    {
        // add checking
        color = (r << 22) + (g << 10) + b;
    }
    int getR() const override
    {
        return this->color >> 22;
    }
    int getG() const override
    {
        unsigned int copy = this->color << 12;
        return copy >> 22;
    }
    int getB() const override
    {
        unsigned int copy = this->color << 22;
        return copy >> 22;
    }

    void updateR(int r) override
    {
        this->color = this->color & 4194303; // 00000000001111111111111111111111
        this->color = (r << 22) + this->color;
    }
    void updateG(int g) override
    {
        this->color = this->color & 4290774015;	// 11111111110000000000001111111111
        this->color = this->color + (g << 10);
    }
    void updateB(int b) override
    {
        this->color = this->color & 4294966272; // 11111111111111111111110000000000
        this->color = this->color + b;
    }
};

class Color_48 : public Color
{
private:
    short unsigned int r, g, b;
public:
    Color_48() : Color()
    {
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }
    Color_48(int r, int g, int b) : Color()
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    int getR() const override { return int(this->r); }
    int getG() const override { return int(this->g); }
    int getB() const override { return int(this->b); }

    void updateR(int r) override { this->r = r; }
    void updateG(int g) override { this->g = g; }
    void updateB(int b) override { this->b = b; }
};

class Color_64 : public Color
{
private:
    short unsigned int r;
    unsigned int g;
    short unsigned int b;
public:
    Color_64() : Color()
    {
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }
    Color_64(int r, int g, int b) : Color()
    {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    int getR() const override { return int(this->r); }
    int getG() const override { return int(this->g); }
    int getB() const override { return int(this->b); }

    void updateR(int r) override { this->r = r; }
    void updateG(int g) override { this->g = g; }
    void updateB(int b) override { this->b = b; }
};


enum VSize { BITS_8, BITS_16, BITS_32, BITS_64, BITS_128 };

class Voxel
{
public:
    Voxel() {};
    virtual Ptr<TSDF> getTSDF() = 0;
    virtual Ptr<Weight> getWeight() = 0;
    virtual Ptr<Color> getColor() = 0;
};

class Voxel_UnColored : public Voxel
{
private:
    Ptr<TSDF> tsdf;
    Ptr<Weight> weight;
public:
    Voxel_UnColored(VSize vs = BITS_16) : Voxel()
    {
        if (vs == BITS_16)
        {
            // total size: 16 bits
            this->tsdf = makePtr<TSDF_8>();
            this->weight = makePtr<Weight_8>();
        }
        else if (vs == BITS_32)
        {
            // total size: 32 bits
            this->tsdf = makePtr<TSDF_16>();
            this->weight = makePtr<Weight_16>();
        }
        else if (vs == BITS_64)
        {
            // total size: 64 bits
            this->tsdf = makePtr<TSDF_32>();
            this->weight = makePtr<Weight_32>();
        }

    };

    Ptr<TSDF> getTSDF() override { return this->tsdf; }
    Ptr<Weight> getWeight() override { return this->weight; }
    Ptr<Color> getColor() override {
        //CV_Error(Error::StsNotImplemented, "Not implemented");
        //CV_LOG_DEBUG(NULL, "There is no color data in this voxel");
        cout << "There is no color data in this voxel" << endl;
        return makePtr<Color_16>();
    }
};

class Voxel_Colored : public Voxel
{
private:
    Ptr<TSDF> tsdf;
    Ptr<Weight> weight;
    Ptr<Color> color;
public:
    Voxel_Colored(VSize vs = BITS_32) : Voxel()
    {
        if (vs == BITS_32)
        {
            // total size: 32 bits
            this->tsdf = makePtr<TSDF_8>();
            this->weight = makePtr<Weight_8>();
            this->color = makePtr<Color_16>();
        }
        else if (vs == BITS_64)
        {
            // total size: 64 bis
            this->tsdf = makePtr<TSDF_16>();
            this->weight = makePtr<Weight_16>();
            this->color = makePtr<Color_32>();
        }
        else if (vs == BITS_128)
        {
            // total size: 128 bits
            this->tsdf = makePtr<TSDF_32>();
            this->weight = makePtr<Weight_32>();
            this->color = makePtr<Color_64>();
        }

    };

    Ptr<TSDF> getTSDF() { return this->tsdf; };
    Ptr<Weight> getWeight() { return this->weight; };
    Ptr<Color> getColor() { return this->color; };
};
#endif // PVOXEL

#endif // !POINTED_VOXEL