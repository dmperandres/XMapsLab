#ifndef DATA_COMMON_INTERPRETER_H
#define DATA_COMMON_INTERPRETER_H

#include <string>
#include <vector>
#include <iostream>

#include "atomic_data.h"

namespace _common_interpreter_ns
{
// short name, name, atomic number, atomic weight, color
  // const std::vector<_atomic_data> Vec_atomic_data={
  //   {"Ag","silver",47,107.87f,QColor(255,0,0)},
  //   {"Al","aluminium",13,26.982f,QColor(255,149,0)},
  //   {"Ar","argon",18,39.95f,QColor(213,255,0)},
  //   {"As","arsenic",33,74.922f,QColor(64,255,0)},
  //   {"Au","gold",79,196.97f,QColor(0,255,85)},
  //   {"B","boron",5,10.81f,QColor(0,255,234)},
  //   {"Ba","barium",56,137.33f,QColor(0,128,255)},
  //   {"Be","beryllium",4,9.0122f,QColor(21,0,255)},
  //   {"Bi","bismuth",83,208.98f,QColor(170,0,255)},
  //   {"Br","bromine",35,79.904f,QColor(255,0,191)},
  //   {"C","carbon",6,12.011f,QColor(255,0,42)},
  //   {"Ca","calcium",20,40.078f,QColor(0,101,255)},
  //   {"Cd","cadmium",48,112.41f,QColor(255,155,0)},
  //   {"Ce","cerium",58,140.12f,QColor(106,255,0)},
  //   {"Cl","chlorine",17,35.45f,QColor(0,255,42)},
  //   {"Co","cobalt",27,58.933f,QColor(255,0,123)},
  //   {"Cr","chromium",24,51.996f,QColor(0,170,255)},
  //   {"Cs","caesium",55,132.91f,QColor(0,21,255)},
  //   {"Cu","copper",29,63.546f,QColor(128,0,255)},
  //   {"Dy","dysprosium",66,162.50f,QColor(255,0,234)},
  //   {"Er","erbium",68,167.26f,QColor(255,0,85)},
  //   {"Eu","europium",63,151.96f,QColor(255,64,0)},
  //   {"F","fluorine",9,18.998f,QColor(255,213,0)},
  //   {"Fe","iron",26,55.845f,QColor(255,0,0)},
  //   {"Ga","gallium",31,69.723f,QColor(0,255,0)},
  //   {"Gd","gadolinium",64,157.25f,QColor(0,255,149)},
  //   {"Ge","germanium",32,72.630f,QColor(0,213,255)},
  //   {"H","hydrogen",1,1.008f,QColor(0,64,255)},
  //   {"He","helium",2,4.0026f,QColor(85,0,255)},
  //   {"Hf","hafnium",72,178.49f,QColor(234,0,255)},
  //   {"Hg","mercury",80,200.59f,QColor(255,0,128)},
  //   {"Ho","holmium",67,164.93f,QColor(255,21,0)},
  //   {"I","iodine",53,126.90f, QColor(255,170,0)},
  //   {"In","indium",49,114.82f,QColor(191,255,0)},
  //   {"Ir","iridium",77,192.22f,QColor(42,255,0)},
  //   {"K","potassium",19,39.098f,QColor(0,255,106)},
  //   {"Kr","krypton",36,83.798f,QColor(0,255,255)},
  //   {"La","lanthanum",57,138.91f,QColor(0,106,255)},
  //   {"Li","lithium",3,6.94f,QColor(42,0,255)},
  //   {"Lu","lutetium",71,174.97f,QColor(191,0,255)},
  //   {"Mg","magnesium",12,24.305f,QColor(255,0,170)},
  //   {"Mn","manganese",25,54.938f,QColor(255,0,21)},
  //   {"Mo","molybdenum",42,95.95f,QColor(255,128,0)},
  //   {"N","nitrogen",7,14.007f,QColor(234,255,0)},
  //   {"Na","sodium",11,22.990f,QColor(85,255,0)},
  //   {"Nb","niobium",41,92.906f,QColor(0,255,64)},
  //   {"Nd","neodymium",60,144.24f,QColor(0,255,213)},
  //   {"Ne","neon",10,20.180f,QColor(0,149,255)},
  //   {"Ni","nickel",28,58.693f,QColor(0,0,255)},
  //   {"O","oxygen",8,15.999f,QColor(149,0,255)},
  //   {"Os","osmium",76,190.23f,QColor(255,0,213)},
  //   {"P","phosphorus",15,30.974f,QColor(0,178,255)},
  //   {"Pb","lead",82,207.2f,QColor(255,85,0)},
  //   {"Pd","palladium",46,106.42f,QColor(255,234,0)},
  //   {"Pm","promethium",61,0,QColor(128,255,0)},
  //   {"Pr","praseodymium",59,140.91f,QColor(0,255,21)},
  //   {"Pt","platinum",78,195.08f,QColor(0,255,170)},
  //   {"Rb","rubidium",37,85.468f,QColor(0,191,255)},
  //   {"Re","rhenium",75,186.21f,QColor(0,42,255)},
  //   {"Rh","rhodium",45,102.91f,QColor(106,0,255)},
  //   {"Ru","ruthenium",44,101.07f,QColor(255,0,255)},
  //   {"S","sulfur",16,32.06f,QColor(255,0,106)},
  //   {"Sb","antimony",51,121.76f,QColor(255,42,0)},
  //   {"Sc","scandium",21,44.956f,QColor(255,135,0)},
  //   {"Se","selenium",34,78.971f,QColor(0,145,255)},
  //   {"Si","silicon",14,28.085f,QColor(21,255,0)},
  //   {"Sm","samarium",62,150.36f,QColor(0,255,128)},
  //   {"Sn","tin",50,118.71f,QColor(0,234,255)},
  //   {"Sr","strontium",38,87.62f,QColor(0,85,255)},
  //   {"Ta","tantalum",73,180.95f,QColor(64,0,255)},
  //   {"Tb","terbium",65,158.93f,QColor(213,0,255)},
  //   {"Tc","technetium",43,0.0f,QColor(255,0,149)},
  //   {"Te","tellurium",52,127.60f,QColor(255,0,0)},
  //   {"Th","thorium",90,232.04f,QColor(255,110,0)},
  //   {"Ti","titanium",22,47.867f,QColor(130,255,0)},
  //   {"Tl","thallium",81,204.38f,QColor(130,0,255)},
  //   {"Tm","thulium",69,168.93f,QColor(64,255,0)},
  //   {"V","vanadium",23,50.942f,QColor(0,255,85)},
  //   {"W","tungsten",74,183.84f,QColor(0,255,234)},
  //   {"Xe","xenon",54,131.29f,QColor(0,128,255)},
  //   {"Y","yttrium",39,88.906f,QColor(21,0,255)},
  //   {"Yb","ytterbium",70,173.05f,QColor(170,0,255)},
  //   {"Zn","zinc",30,65.38f,QColor(255,0,191)},
  //   {"Zr","zirconium",40,91.224f,QColor(155,0,255)}
  // };

  const float MAX_VALUE=1e20f;

  const unsigned int NUM_PEAKS_MAX=50;
  const unsigned int NUM_PEAKS_OBS_DEFAULT=10;
  const unsigned int NUM_PEAKS_PDB_DEFAULT=2;

  const unsigned int GAUSSIAN_WIDTH_MAX=9;
  const unsigned int GAUSSIAN_WIDTH_DEFAULT=3;


  struct _value_position{
    float Value=0;
    int Position=-1;
    float Position_kev=-1;
  };
};

#endif


