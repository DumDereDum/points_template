#include <iostream>
#include <bitset>
#include <climits>

#include <opencv2/core/ocl.hpp>

//#include "pointed_voxel.h"
#include "templete_uncolored_voxel.h"
#include "templete_colored_voxel.h"


using namespace std;
using namespace cv;

int main()
{
    /*
    for (float f = -1.f; f <= 1.1f; f += 0.1)
    {
        //int i = (int)floatToTsdf8(f);
        //cout << f << " " << i << " " << tsdf8ToFloat(i) << endl;
        //TSDF_16 i = floatToTsdf16(f);
        //cout << f << " " << tsdf16ToFloat(i) << endl;
        //TSDF_32 i = floatToTsdf32(f);
        //cout << f << "===" << tsdf32ToFloat(i) << endl;
    }
    */
    /*
    for (int i = 0; i <= 260; i += 20)
        cout << i << " " << weight8ToInt(intToWeight8(i)) << endl;

    for (int i = 0; i <= 66000; i += 1000)
        cout << i << " " << weight16ToInt(intToWeight16(i)) << endl;

    for (int i = 1; i <= 6600000; i += i)
        cout << i << " " << weight32ToInt(intToWeight32(i)) << endl;
    */

    /*
    Color_16 c16 = toColor16(50, 150, 250);
    cout << extractR16(c16) << " " << extractG16(c16) << " " << extractB16(c16) << " " << endl;

    Color_32 c32 = toColor32(50, 150, 250);
    cout << extractR32(c32) << " " << extractG32(c32) << " " << extractB32(c32) << " " << endl;

    Color_64 c64 = toColor64(50, 150, 250);
    cout << extractR64(c64) << " " << extractG64(c64) << " " << extractB64(c64) << " " << endl;

    cout << "cv16: " << sizeof(c16) << endl;
    cout << "cv32: " << sizeof(c32) << endl;
    cout << "cv64: " << sizeof(c64) << endl;
    */

    //int num = 32;
    //std::cout << std::bitset<sizeof(c.val[0])* CHAR_BIT>(c.val[0]) << " ";
    //std::cout << std::bitset<sizeof(c.val[1])* CHAR_BIT>(c.val[1]) << "\n";

///*
    bool uncolored = false;
    bool colored = false;
    bool testSize = false;

    float tsdf = 0.76f;
    float tsdf_1 = 0.48f;
    int r = 50, g = 150, b = 250;
    int r1 = 176, g1 = 48, b1 = 214;

    if (uncolored)
    {
        UncoloredVoxel<TSDF_32, Weight_32> ucv64(tsdf);
        cout << "UncoloredVoxel<TSDF_32, Weight_32>" << endl;
        cout << "-tsdf:   " << ucv64.getTSDF() << endl << " weight: " << ucv64.getWeight() << endl;
        ucv64.setWeight(1);
        cout << "-tsdf:   " << ucv64.getTSDF() << endl << " weight: " << ucv64.getWeight() << endl;
        ucv64.setWeight(15);
        cout << "-tsdf:   " << ucv64.getTSDF() << endl << " weight: " << ucv64.getWeight() << endl;
        ucv64.setWeight(0);
        cout << "-tsdf:   " << ucv64.getTSDF() << endl << " weight: " << ucv64.getWeight() << endl;
        ucv64.setTSDF(tsdf_1);
        cout << "-tsdf:   " << ucv64.getTSDF() << endl << " weight: " << ucv64.getWeight() << endl;

        UncoloredVoxel<TSDF_16, Weight_16> ucv32(tsdf);
        cout << "UncoloredVoxel<TSDF_16, Weight_16>" << endl;
        cout << "-tsdf:   " << ucv32.getTSDF() << endl << " weight: " << ucv32.getWeight() << endl;
        ucv32.setWeight(1);
        cout << "-tsdf:   " << ucv32.getTSDF() << endl << " weight: " << ucv32.getWeight() << endl;
        ucv32.setWeight(15);
        cout << "-tsdf:   " << ucv32.getTSDF() << endl << " weight: " << ucv32.getWeight() << endl;
        ucv32.setWeight(0);
        cout << "-tsdf:   " << ucv32.getTSDF() << endl << " weight: " << ucv32.getWeight() << endl;
        ucv32.setTSDF(tsdf_1);
        cout << "-tsdf:   " << ucv32.getTSDF() << endl << " weight: " << ucv32.getWeight() << endl;

        UncoloredVoxel<TSDF_8, Weight_8> ucv16(tsdf);
        cout << "UncoloredVoxel<TSDF_8, Weight_8>" << endl;
        cout << "-tsdf:   " << ucv16.getTSDF() << endl << " weight: " << ucv16.getWeight() << endl;
        ucv16.setWeight(1);
        cout << "-tsdf:   " << ucv16.getTSDF() << endl << " weight: " << ucv16.getWeight() << endl;
        ucv16.setWeight(15);
        cout << "-tsdf:   " << ucv16.getTSDF() << endl << " weight: " << ucv16.getWeight() << endl;
        ucv16.setWeight(0);
        cout << "-tsdf:   " << ucv16.getTSDF() << endl << " weight: " << ucv16.getWeight() << endl;
        ucv16.setTSDF(tsdf_1);
        cout << "-tsdf:   " << ucv16.getTSDF() << endl << " weight: " << ucv16.getWeight() << endl;

        UncoloredVoxel<TSDF_8, Weight_16> ucverr(tsdf);
    }

    if (colored)
    {
        cout << "ColoredVoxel<TSDF_8, Weight_8, Color_16>" << endl;
        ColoredVoxel<TSDF_8, Weight_8, Color_16> cv32_0 = ColoredVoxel<TSDF_8, Weight_8, Color_16>();
        printColoredVoxel(cv32_0);
        cv32_0.setWeight(1);
        printColoredVoxel(cv32_0);
        cv32_0.setWeight(15);
        printColoredVoxel(cv32_0);
        cv32_0.setWeight(0);
        printColoredVoxel(cv32_0);
        cv32_0.setTSDF(tsdf_1);
        printColoredVoxel(cv32_0);
        cv32_0.setR(r1);
        printColoredVoxel(cv32_0);
        cv32_0.setG(g1);
        printColoredVoxel(cv32_0);
        cv32_0.setB(b1);
        printColoredVoxel(cv32_0);


        cout << "ColoredVoxel<TSDF_16, Weight_16, Color_32>" << endl;
        ColoredVoxel<TSDF_16, Weight_16, Color_32> cv64_0 = ColoredVoxel<TSDF_16, Weight_16, Color_32>();
        printColoredVoxel(cv64_0);
        cv64_0.setWeight(1);
        printColoredVoxel(cv64_0);
        cv64_0.setWeight(15);
        printColoredVoxel(cv64_0);
        cv64_0.setWeight(0);
        printColoredVoxel(cv64_0);
        cv64_0.setTSDF(tsdf_1);
        printColoredVoxel(cv64_0);
        cv64_0.setR(r1);
        printColoredVoxel(cv64_0);
        cv64_0.setG(g1);
        printColoredVoxel(cv64_0);
        cv64_0.setB(b1);
        printColoredVoxel(cv64_0);


        cout << "ColoredVoxel<TSDF_32, Weight_32, Color_64>" << endl;
        ColoredVoxel<TSDF_32, Weight_32, Color_64> cv128_0 = ColoredVoxel<TSDF_32, Weight_32, Color_64>();
        printColoredVoxel(cv128_0);
        cv128_0.setWeight(1);
        printColoredVoxel(cv128_0);
        cv128_0.setWeight(15);
        printColoredVoxel(cv128_0);
        cv128_0.setWeight(0);
        printColoredVoxel(cv128_0);
        cv128_0.setTSDF(tsdf_1);
        printColoredVoxel(cv128_0);
        cv128_0.setR(r1);
        printColoredVoxel(cv128_0);
        cv128_0.setG(g1);
        printColoredVoxel(cv128_0);
        cv128_0.setB(b1);
        printColoredVoxel(cv128_0);
    }

    if (testSize)
    {
        UncoloredVoxel<TSDF_32, Weight_32> ucv64(tsdf);
        UncoloredVoxel<TSDF_16, Weight_16> ucv32(tsdf);
        UncoloredVoxel<TSDF_8, Weight_8> ucv16(tsdf);
        cout << "ucv64: " << sizeof(ucv64) << endl;
        cout << "ucv32: " << sizeof(ucv32) << endl;
        cout << "ucv16: " << sizeof(ucv16) << endl;

        ColoredVoxel<TSDF_8, Weight_8, Color_16> cv32 = ColoredVoxel<TSDF_8, Weight_8, Color_16>();
        ColoredVoxel<TSDF_16, Weight_16, Color_32> cv64 = ColoredVoxel<TSDF_16, Weight_16, Color_32>();
        ColoredVoxel<TSDF_32, Weight_32, Color_64> cv128 = ColoredVoxel<TSDF_32, Weight_32, Color_64>();
        cout << "cv32:  " << sizeof(cv32) << endl;
        cout << "cv64:  " << sizeof(cv64) << endl;
        cout << "cv128: " << sizeof(cv128) << endl;
    }
    //*/
    return 0;
}

#if PVOXEL
int main()
{
    bool tsdf   = false;
    bool weight = false;
    bool color  = false;
    bool voxel  = true;

    if (tsdf)
    {
        cout << "\nTSDF" << endl;
        cout << "TSDF_8" << endl;
        Ptr<TSDF> t8 = makePtr<TSDF_8>(0.78f);
        cout << " " << t8->get() << endl;
        t8->update(0.24f);
        cout << " " << t8->get() << endl;

        cout << "TSDF_16" << endl;
        Ptr<TSDF> t16 = makePtr<TSDF_16>(0.78f);
        cout << " " << t16->get() << endl;
        t16->update(0.24f);
        cout << " " << t16->get() << endl;

        cout << "TSDF_32" << endl;
        Ptr<TSDF> t32 = makePtr<TSDF_32>(0.78f);
        cout << " " << t32->get() << endl;
        t32->update(0.24f);
        cout << " " << t32->get() << endl;
    }

    if (weight)
    {
        cout << "\nWeight" << endl;
        cout << "Weight_8" << endl;
        Ptr<Weight> w8 = makePtr<Weight_8>();
        cout << w8->get() << endl;
        w8->increase();
        cout << w8->get() << endl;
        w8->increase();
        cout << w8->get() << endl;
        w8->reset();
        cout << w8->get() << endl;

        cout << "Weight_16" << endl;
        Ptr<Weight> w16 = makePtr<Weight_16>();
        cout << w16->get() << endl;
        w16->increase();
        cout << w16->get() << endl;
        w16->increase();
        cout << w16->get() << endl;
        w16->reset();
        cout << w16->get() << endl;

        cout << "Weight_32" << endl;
        Ptr<Weight> w32 = makePtr<Weight_32>();
        cout << w32->get() << endl;
        w32->increase();
        cout << w32->get() << endl;
        w32->increase();
        cout << w32->get() << endl;
        w32->reset();
        cout << w32->get() << endl;
    }

    if (color)
    {
        cout << "\nColor" << endl;
        cout << "Color_16" << endl;
        Ptr<Color> c16 = makePtr<Color_16>(50, 150, 250);
        cout << " " << c16->getR() << " " << c16->getG() << " " << c16->getB() << endl;
        c16->updateR(70);
        cout << " " << c16->getR() << " " << c16->getG() << " " << c16->getB() << endl;
        c16->updateG(24);
        cout << " " << c16->getR() << " " << c16->getG() << " " << c16->getB() << endl;
        c16->updateB(104);
        cout << " " << c16->getR() << " " << c16->getG() << " " << c16->getB() << endl;

        cout << "Color_32" << endl;
        Ptr<Color> c32 = makePtr<Color_32>(50, 150, 250);
        cout << " " << c32->getR() << " " << c32->getG() << " " << c32->getB() << endl;
        c32->updateR(70);
        cout << " " << c32->getR() << " " << c32->getG() << " " << c32->getB() << endl;
        c32->updateG(24);
        cout << " " << c32->getR() << " " << c32->getG() << " " << c32->getB() << endl;
        c32->updateB(104);
        cout << " " << c32->getR() << " " << c32->getG() << " " << c32->getB() << endl;

        cout << "Color_48" << endl;
        Ptr<Color> c48 = makePtr<Color_48>(50, 150, 250);
        cout << " " << c48->getR() << " " << c48->getG() << " " << c48->getB() << endl;
        c48->updateR(70);
        cout << " " << c48->getR() << " " << c48->getG() << " " << c48->getB() << endl;
        c48->updateG(24);
        cout << " " << c48->getR() << " " << c48->getG() << " " << c48->getB() << endl;
        c48->updateB(104);
        cout << " " << c48->getR() << " " << c48->getG() << " " << c48->getB() << endl;
    }

    if (voxel)
    {
        Ptr<Voxel> vuc = makePtr<Voxel_UnColored>();
        cout << "Voxel_UnColored def BITS" << endl;
        cout << "-tsdf:   " << vuc->getTSDF()->get() << endl;
        cout << " weight: " << vuc->getWeight()->get() << endl;
        vuc->getTSDF()->update(0.76);
        vuc->getWeight()->increase();
        cout << "-tsdf:   " << vuc->getTSDF()->get() << endl;
        cout << " weight: " << vuc->getWeight()->get() << endl;
        
        Ptr<Voxel> vuc16 = makePtr<Voxel_UnColored>(BITS_16);
        cout << "Voxel_UnColored 16 BITS" << endl;
        cout << "-tsdf:   " << vuc16->getTSDF()->get() << endl;
        cout << " weight: " << vuc16->getWeight()->get() << endl;
        vuc16->getTSDF()->update(0.76);
        vuc16->getWeight()->increase();
        cout << "-tsdf:   " << vuc16->getTSDF()->get() << endl;
        cout << " weight: " << vuc16->getWeight()->get() << endl;
        
        Ptr<Voxel> vuc32 = makePtr<Voxel_UnColored>(BITS_32);
        cout << "Voxel_UnColored 32 BITS" << endl;
        cout << "-tsdf:   " << vuc32->getTSDF()->get() << endl;
        cout << " weight: " << vuc32->getWeight()->get() << endl;
        vuc32->getTSDF()->update(0.76);
        vuc32->getWeight()->increase();
        cout << "-tsdf:   " << vuc32->getTSDF()->get() << endl;
        cout << " weight: " << vuc32->getWeight()->get() << endl;
        
        Ptr<Voxel> vuc64 = makePtr<Voxel_UnColored>(BITS_64);
        cout << "Voxel_UnColored 64 BITS" << endl;
        cout << "-tsdf:   " << vuc64->getTSDF()->get() << endl;
        cout << " weight: " << vuc64->getWeight()->get() << endl;
        vuc64->getTSDF()->update(0.76);
        vuc64->getWeight()->increase();
        cout << "-tsdf:   " << vuc64->getTSDF()->get() << endl;
        cout << " weight: " << vuc64->getWeight()->get() << endl;
       
        Ptr<Voxel> vc = makePtr<Voxel_Colored>();
        cout << "Voxel_Colored def BITS" << endl;
        cout << "-tsdf:   " << vc->getTSDF()->get() << endl;
        cout << " weight: " << vc->getWeight()->get() << endl;
        cout << " colors: " << vc->getColor()->getR() << " " << vc->getColor()->getG() << " " << vc->getColor()->getB() << " " << endl;
        vc->getTSDF()->update(0.76);
        vc->getWeight()->increase();
        vc->getColor()->updateR(50);
        vc->getColor()->updateG(150);
        vc->getColor()->updateB(250);
        cout << "-tsdf:   " << vc->getTSDF()->get() << endl;
        cout << " weight: " << vc->getWeight()->get() << endl;
        cout << " colors: " << vc->getColor()->getR() << " " << vc->getColor()->getG() << " " << vc->getColor()->getB() << " " << endl;
 
        Ptr<Voxel> vc32 = makePtr<Voxel_Colored>(BITS_32);
        cout << "Voxel_Colored 32 BITS" << endl;
        cout << "-tsdf:   " << vc32->getTSDF()->get() << endl;
        cout << " weight: " << vc32->getWeight()->get() << endl;
        cout << " colors: " << vc32->getColor()->getR() << " " << vc32->getColor()->getG() << " " << vc32->getColor()->getB() << " " << endl;
        vc32->getTSDF()->update(0.76);
        vc32->getWeight()->increase();
        vc32->getColor()->updateR(50);
        vc32->getColor()->updateG(150);
        vc32->getColor()->updateB(250);
        cout << "-tsdf:   " << vc32->getTSDF()->get() << endl;
        cout << " weight: " << vc32->getWeight()->get() << endl;
        cout << " colors: " << vc32->getColor()->getR() << " " << vc32->getColor()->getG() << " " << vc32->getColor()->getB() << " " << endl;

        Ptr<Voxel> vc64 = makePtr<Voxel_Colored>(BITS_64);
        cout << "Voxel_Colored 64 BITS" << endl;
        cout << "-tsdf:   " << vc64->getTSDF()->get() << endl;
        cout << " weight: " << vc64->getWeight()->get() << endl;
        cout << " colors: " << vc64->getColor()->getR() << " " << vc64->getColor()->getG() << " " << vc64->getColor()->getB() << " " << endl;
        vc64->getTSDF()->update(0.76);
        vc64->getWeight()->increase();
        vc64->getColor()->updateR(50);
        vc64->getColor()->updateG(150);
        vc64->getColor()->updateB(250);
        cout << "-tsdf:   " << vc64->getTSDF()->get() << endl;
        cout << " weight: " << vc64->getWeight()->get() << endl;
        cout << " colors: " << vc64->getColor()->getR() << " " << vc64->getColor()->getG() << " " << vc64->getColor()->getB() << " " << endl;

        Ptr<Voxel> vc128 = makePtr<Voxel_Colored>(BITS_128);
        cout << "Voxel_Colored 128 BITS" << endl;
        cout << "-tsdf:   " << vc128->getTSDF()->get() << endl;
        cout << " weight: " << vc128->getWeight()->get() << endl;
        cout << " colors: " << vc128->getColor()->getR() << " " << vc128->getColor()->getG() << " " << vc128->getColor()->getB() << " " << endl;
        vc128->getTSDF()->update(0.76);
        vc128->getWeight()->increase();
        vc128->getColor()->updateR(50);
        vc128->getColor()->updateG(150);
        vc128->getColor()->updateB(250);
        cout << "-tsdf:   " << vc128->getTSDF()->get() << endl;
        cout << " weight: " << vc128->getWeight()->get() << endl;
        cout << " colors: " << vc128->getColor()->getR() << " " << vc128->getColor()->getG() << " " << vc128->getColor()->getB() << " " << endl;
    }

    return 0;
}
#endif // PVOXEL