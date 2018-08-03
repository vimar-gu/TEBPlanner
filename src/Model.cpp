#include "Model.h"
/************************************************************************/
/*                         CVector                                      */
/************************************************************************/
CVector CVector::rotate(double angle) const
{
    double nowdir = dir() + angle;
    double nowx = mod() * cos(nowdir);
    double nowy = mod() * sin(nowdir);
    return CVector(nowx, nowy);
}
