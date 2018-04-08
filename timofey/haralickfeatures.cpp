#include "haralickfeatures.h"

HaralickFeatures::HaralickFeatures(QImage image, int dis)
{
    CalcFeatures(image, dis);
}


void HaralickFeatures::CalcFeatures(QImage image, int dis)
{
    for (int k = 0; k < graylvls; k++)                            //Zeroing arrays
    {
        for (int l = 0; l < graylvls; l++)
        {
            arr0[k][l] = 0;
            arr45[k][l] = 0;
            arr90[k][l] = 0;
            arr135[k][l] = 0;
        }
     sumx0[k] = 0;
     sumx45[k] = 0;
     sumx90[k] = 0;
     sumx135[k] = 0;
    }

     for (int x = dis; x < image.width() - dis; ++x)                        //Gray Level Co-occurance Matrix
         for (int y = dis; y < image.height() - dis; ++y)
         {
             int a = image.pixelColor(x, y).blue() * graylvls / 256;

             if (a == 255)
                 continue;

             int b = image.pixelColor(x + dis, y).blue() * graylvls / 256;
             int c = image.pixelColor(x - dis, y).blue() * graylvls / 256;
             int d = image.pixelColor(x, y + dis).blue() * graylvls / 256;
             int e = image.pixelColor(x, y - dis).blue() * graylvls / 256;
             int f = image.pixelColor(x + dis, y + dis).blue() * graylvls / 256;
             int g = image.pixelColor(x - dis, y - dis).blue() * graylvls / 256;
             int h = image.pixelColor(x + dis, y - dis).blue() * graylvls / 256;
             int k = image.pixelColor(x - dis, y + dis).blue() * graylvls / 256;

             if (b != 255)
             {
                 arr0[a][b]=arr0[a][b]+1;
                 arr0[b][a]=arr0[b][a]+1;
             }

             if (c != 255)
             {
                 arr0[a][c]=arr0[a][c]+1;
                 arr0[c][a]=arr0[c][a]+1;
             }

             if (d != 255)
             {
                 arr90[a][d]=arr90[a][d]+1;
                 arr90[d][a]=arr90[d][a]+1;
             }

             if (e != 255)
             {
                 arr90[a][e]=arr90[a][e]+1;
                 arr90[e][a]=arr90[e][a]+1;
             }

             if (f != 255)
             {
                 arr135[a][f]=arr135[a][f]+1;
                 arr135[f][a]=arr135[f][a]+1;
             }

             if (g != 255)
             {
                 arr135[a][g]=arr135[a][g]+1;
                 arr135[g][a]=arr135[g][a]+1;
             }

             if (h != 255)
             {
                 arr45[a][h]=arr45[a][h]+1;
                 arr45[h][a]=arr45[h][a]+1;
             }

             if (k != 255)
             {
                 arr45[a][k]=arr45[a][k]+1;
                 arr45[k][a]=arr45[k][a]+1;
             }

             s++;
         }

    for (int k = 0; k < graylvls; k++)                                 //Transfer into probabilities
        for (int l = 0; l < graylvls; l++)
        {
            arr0[k][l] /= (4 * s);
            arr45[k][l] /= (4 * s);
            arr90[k][l] /= (4 * s);
            arr135[k][l] /= (4 * s);
        }

    for (int k = 0; k < graylvls; k++)                                 //Sum of rows arrays
        {
        for (int l = 0; l < graylvls; l++)
            {
                tmp0 += arr0[k][l];
                tmp45 += arr45[k][l];
                tmp90 += arr90[k][l];
                tmp135 += arr135[k][l];
            }
            sumx0[k] += tmp0;
            sumx45[k] += tmp45;
            sumx90[k] += tmp90;
            sumx135[k] += tmp135;

            tmp0 = 0;
            tmp45 = 0;
            tmp90 = 0;
            tmp135 = 0;
        }

    for (int k = 0; k < graylvls; k++)
    {
        mx0 += k * sumx0[k];
        mx45 += k * sumx45[k];
        mx90 += k * sumx90[k];
        mx135 += k * sumx135[k];
    }

    for (int k = 0; k < graylvls; k++)
    {
        dx0 += sumx0[k]*(k - mx0)*(k - mx0);
        dx45 += sumx45[k]*(k - mx45)*(k - mx45);
        dx90 += sumx90[k]*(k - mx90)*(k - mx90);
        dx135 += sumx135[k]*(k - mx135)*(k - mx135);
    }

    for (int k = 0; k < graylvls; k++)
        for (int l = 0; l < graylvls; l++)
        {
            tmp0 += (k * l * arr0[k][l]);
            tmp45 += (k * l * arr45[k][l]);
            tmp90 += (k * l * arr90[k][l]);
            tmp135 += (k * l * arr135[k][l]);
        }

    cor0 = (tmp0 - mx0 * mx0) / dx0;                                    //Correlation (Third feature)
    cor45 = (tmp45 - mx45 * mx45) / dx45;
    cor90 = (tmp90 - mx90 * mx90) / dx90;
    cor135 = (tmp135 - mx135 * mx135) / dx135;

    tmp0 = 0;
    tmp45 = 0;
    tmp90 = 0;
    tmp135 = 0;


    for (int k = 0; k < graylvls; k++)
        for (int l = 0; l < graylvls; l++)
        {
            sum0 = sum0 + arr0[k][l];                                   //Sum of arrays (Check)
            sum45 = sum45 + arr45[k][l];
            sum90 = sum90 + arr90[k][l];
            sum135 = sum135 + arr135[k][l];
            asm0 = asm0 + arr0[k][l] * arr0[k][l];                      //Angular Second Moment(First feature)
            asm45 = asm45 + arr45[k][l] * arr45[k][l];
            asm90 = asm90 + arr90[k][l] * arr90[k][l];
            asm135 = asm135 + arr135[k][l] * arr135[k][l];
            idm0 = idm0 + arr0[k][l]/(1 + (k - l) * (k - l));           //Inverse Difference Moment (Fifth feature)
            idm45 = idm45 + arr45[k][l]/(1 + (k - l) * (k - l));
            idm90 = idm90 + arr90[k][l]/(1 + (k - l) * (k - l));
            idm135 = idm135 + arr135[k][l]/(1 + (k - l) * (k - l));
            ent0 = ent0 - arr0[k][l] * log(arr0[k][l] + zero);          //Enthropy (Ninth feature)
            ent45 = ent45 - arr45[k][l] * log(arr45[k][l] + zero);
            ent90 = ent90 - arr90[k][l] * log(arr90[k][l] + zero);
            ent135 = ent135 - arr135[k][l] * log(arr135[k][l] + zero);
            sos0 = sos0 + (k - mx0) * (k - mx0) * arr0[k][l];           //Sum of Squares (Fourth feature)
            sos45 = sos45 + (k - mx45) * (k - mx45) * arr45[k][l];
            sos90 = sos90 + (k - mx90) * (k - mx90) * arr90[k][l];
            sos135 = sos135 + (k - mx135) * (k - mx135) * arr135[k][l];
        }

   for (int n = 1; n < graylvls; n++)
      {
       for (int k = 0; k < graylvls; k++)
           for (int l = 0; l < graylvls; l++)
                 if ((n == l - k)||(n == k - l))
                     {
                       tmp0 = tmp0 + arr0[k][l];
                       tmp45 = tmp45 + arr45[k][l];
                       tmp90 = tmp90 + arr90[k][l];
                       tmp135 = tmp135 + arr135[k][l];
                     }
       den0 = den0 - tmp0 * log(tmp0 + zero);                           //Difference Enthropy (Eleventh feature)
       den45 = den45 - tmp45 * log(tmp45 + zero);
       den90 = den90 - tmp90 * log(tmp90 + zero);
       den135 = den135 - tmp135 * log(tmp135 + zero);
       con0 = con0 + n * n * tmp0;                                      //Contrast (Second Feature)
       con45 = con45 + n * n * tmp45;
       con90 = con90 + n * n * tmp90;
       con135 = con135 + n * n * tmp135;
       tmp0 = 0;
       tmp45 = 0;
       tmp90 = 0;
       tmp135 = 0;
      }

  for (int n = 2; n < (2 * graylvls + 1); n++)
     {
      for (int k = 0; k < graylvls; k++)
         for (int l = 0; l < graylvls; l++)
            {
                  if (n == l + k)
                     {
                       tmp0 = tmp0 + arr0[k][l];
                       tmp45 = tmp45 + arr45[k][l];
                       tmp90 = tmp90 + arr90[k][l];
                       tmp135 = tmp135 + arr135[k][l];
                     }
            }
      sen0 = sen0 - tmp0 * log(tmp0 + zero);                            //Sum Enthropy (Eighth feature)
      sen45 = sen45 - tmp45 * log(tmp45 + zero);
      sen90 = sen90 - tmp90 * log(tmp90 + zero);
      sen135 = sen135 - tmp135 * log(tmp135 + zero);
      sav0 = sav0 + n * tmp0;                                           //Sum Average (Sixth feature)
      sav45 = sav45 + n * tmp45;
      sav90 = sav90 + n * tmp90;
      sav135 = sav135 + n * tmp135;
      tmp0 = 0;
      tmp45 = 0;
      tmp90 = 0;
      tmp135 = 0;
     }

  for (int n = 2; n < (2 * graylvls + 1); n++)
     {
      for (int k = 0; k < graylvls; k++)
         for (int l = 0; l < graylvls; l++)
            {
                  if (n == l + k)
                     {
                        tmp0 = tmp0 + arr0[k][l];
                        tmp45 = tmp45 + arr45[k][l];
                        tmp90 = tmp90 + arr90[k][l];
                        tmp135 = tmp135 + arr135[k][l];
                     }
            }
      sva0 = sva0 + tmp0 * (n - sen0) * (n - sen0);                      //Sum Variance (Seventh feature)
      sva45 = sva45 + tmp45 * (n - sen45) * (n - sen45);
      sva90 = sva90 + tmp90 * (n - sen90) * (n - sen90);
      sva135 = sva135 + tmp135 * (n - sen135) * (n - sen135);
      tmp0 = 0;
      tmp45 = 0;
      tmp90 = 0;
      tmp135 = 0;
     }

  for (int n = 1; n < graylvls; n++)
     {
      for (int k = 0; k < graylvls; k++)
          for (int l = 0; l < graylvls; l++)
            {
                if ((n == l - k)||(n == k - l))
                    {
                      tmp0 = tmp0 + arr0[k][l];
                      tmp45 = tmp45 + arr45[k][l];
                      tmp90 = tmp90 + arr90[k][l];
                      tmp135 = tmp135 + arr135[k][l];
                    }
            }
      dva0 = dva0 + tmp0 * (n - den0) * (n - den0);                      //Difference Variance (Tenth feature)
      dva45 = dva45 + tmp45 * (n - den45) * (n - den45);
      dva90 = dva90 + tmp90 * (n - den90) * (n - den90);
      dva135 = dva135 + tmp135 * (n - den135) * (n - den135);
      tmp0 = 0;
      tmp45 = 0;
      tmp90 = 0;
      tmp135 = 0;
     }

  asn = (asm0 + asm45 + asm90 + asm135) / 4;
  con = (con0 + con45 + con90 + con135) / 4;
  cor = (cor0 + cor45 + cor90 + cor135) / 4;
  sos = (sos0 + sos45 + sos90 + sos135) / 4;
  idm = (idm0 + idm45 + idm90 + idm135) / 4;
  sav = (sav0 + sav45 + sav90 + sav135) / 4;
  sva = (sva0 + sva45 + sva90 + sva135) / 4;
  sen = (sen0 + sen45 + sen90 + sen135) / 4;
  ent = (ent0 + ent45 + ent90 + ent135) / 4;
  dva = (dva0 + dva45 + dva90 + dva135) / 4;
  den = (den0 + den45 + den90 + den135) / 4;
  //mx = (mx0 + mx45 + mx90 + mx135) / 4;

}
