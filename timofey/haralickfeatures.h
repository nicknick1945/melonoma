#ifndef HARALICKFEATURES_H
#define HARALICKFEATURES_H
#include <QGraphicsView>
#include <math.h>

class HaralickFeatures
{

private:
    int graylvl = 0;
    int s = 0;
    double tmp0 = 0, tmp45 = 0, tmp90 = 0, tmp135 = 0;
    double mx0 = 0, mx45 = 0, mx90 = 0, mx135 = 0;
    double dx0 = 0, dx45 = 0, dx90 = 0, dx135 = 0;
    double sum0 = 0, sum45 = 0, sum90 = 0, sum135 = 0;
    double asm0 = 0, asm45 = 0, asm90 = 0, asm135 = 0;
    double con0 = 0, con45 = 0, con90 = 0, con135 = 0;
    double cor0 = 0, cor45 = 0, cor90 = 0, cor135 = 0;
    double sos0 = 0, sos45 = 0, sos90 = 0, sos135 = 0;
    double idm0 = 0, idm45 = 0, idm90 = 0, idm135 = 0;
    double sav0 = 0, sav45 = 0, sav90 = 0, sav135 = 0;
    double sva0 = 0, sva45 = 0, sva90 = 0, sva135 = 0;
    double sen0 = 0, sen45 = 0, sen90 = 0, sen135 = 0;
    double ent0 = 0, ent45 = 0, ent90 = 0, ent135 = 0;
    double dva0 = 0, dva45 = 0, dva90 = 0, dva135 = 0;
    double den0 = 0, den45 = 0, den90 = 0, den135 = 0;
    const double zero = 1e-030;
    const static int graylvls = 256;

    float sumx0[graylvls];
    float sumx45[graylvls];
    float sumx90[graylvls];
    float sumx135[graylvls];
    float arr0[graylvls][graylvls];
    float arr45[graylvls][graylvls];
    float arr90[graylvls][graylvls];
    float arr135[graylvls][graylvls];

public:
    HaralickFeatures(QImage, int);
    void CalcFeatures(QImage, int);

    double mx = 0;
    double asn = 0;
    double con = 0;
    double cor = 0;
    double sos = 0;
    double idm = 0;
    double sav = 0;
    double sva = 0;
    double sen = 0;
    double ent = 0;
    double dva = 0;
    double den = 0;

};

#endif // HARALICKFEATURES_H
