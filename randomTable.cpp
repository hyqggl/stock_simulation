

#include "randomTable.h"

randomTable::randomTable():gauss_V1(0),gauss_V2(0),gauss_S(0),gauss_phase(0)
{
    gaussTableGened = false;
}

randomTable::~randomTable()
{

    if (gaussTableGened) {

        for (int i = 0; i < gaussTable_Num; i++)
        {
            delete gaussTable_first[i];
            gaussTable_first[i] = NULL;
        }
        delete gaussTable_first;
        gaussTable_first = NULL;

        for (int i = 0; i < gaussTable_Num; i++)
        {
            delete gaussTable_second[i];
            gaussTable_second[i] = NULL;
        }
        delete gaussTable_second;
        gaussTable_second = NULL;

    }
}

double randomTable::gaussrand()
{

    double X;

    if ( gauss_phase == 0 ) {
        do {
            double U1 = (double)rand() / RAND_MAX;
            double U2 = (double)rand() / RAND_MAX;

            gauss_V1 = 2 * U1 - 1;
            gauss_V2 = 2 * U2 - 1;
            gauss_S = gauss_V1 * gauss_V1 + gauss_V2 * gauss_V2;
        } while(gauss_S >= 1 || gauss_S == 0);

        X = gauss_V1 * sqrt(-2 * log(gauss_S) / gauss_S);
    } else
        X = gauss_V2 * sqrt(-2 * log(gauss_S) / gauss_S);

    gauss_phase = 1 - gauss_phase;

    return X;
}

void randomTable::generateGaussTable()
{

    if (gaussTableGened) {
        cout << "Table is already generated." << endl;
        return;
    }

    //10, 30, 90, 270, 810, 2430, 7290, 21870

    gaussTable_Num = 8;
    gaussTable_first  = new int*[gaussTable_Num];
    gaussTable_second = new unsigned int*[gaussTable_Num];

    int j = 10;
    int p = 0;
    map<int, unsigned int> m;
    for (int i = 0; i < 21870; i++)
    {
        if (p >= gaussTable_Num) {
            break;
        }
        m[(int)(gaussrand() * 100)] += 1;
        if (i == j - 1)
        {
            unsigned long k = m.size();
            gaussTable_first[p] = new int[k + 1];
            gaussTable_first[p][0] = (int)k;
            gaussTable_second[p] = new unsigned int[k + 1];
            gaussTable_second[p][0] = (unsigned int)k;
            map<int, unsigned int>::iterator it;
            int counter = 0;
            for (it = m.begin(); it != m.end(); it++)
            {
                counter ++;
                gaussTable_first[p][counter]  = it->first;
                gaussTable_second[p][counter] = it->second;
            }

            p ++;
            j *= 3;
        }
    }


    gaussTableGened = true;
}


void randomTable::printGeneratedGaussList(int n)
{
    if (n > gaussTable_Num)
    {
        cout << "N is too large." << endl;
        exit(1);
    }

    if (gaussTable_first[n-1][0] != gaussTable_second[n-1][0])
    {
        cout << "Something wrong happened. gaussList numbers do not match." << endl;
        exit(1);
    }

    for (int i = 1; i <= gaussTable_first[n-1][0]; i++)
    {
        cout << gaussTable_first[n-1][i] << " : " << gaussTable_second[n-1][i] << endl;
    }
}

pair<int*, unsigned int*> randomTable::getGaussOrderSample_byGroup(int n)
{
    if (n > gaussTable_Num)
    {
        cout << "N is too large." << endl;
        exit(1);
    }

    if (gaussTable_first[n-1][0] != gaussTable_second[n-1][0])
    {
        cout << "Something wrong happened. gaussList numbers do not match." << endl;
        exit(1);
    }

    return pair<int*, unsigned int*> (gaussTable_first[n-1], gaussTable_second[n-1]);
}

pair<int*, unsigned int*> randomTable::getGaussOrderSample_byNumber(int n)
{
    if (n < 0) {
        cout << "N is too small." <<endl;
        exit(1);
    }

    if (n < (10 + 30) / 2) {
        return pair<int*, unsigned int*> (gaussTable_first[0], gaussTable_second[0]);
    } else if (n < (30 + 90) / 2) {
        return pair<int*, unsigned int*> (gaussTable_first[1], gaussTable_second[1]);
    } else if (n < (90 + 270) / 2) {
        return pair<int*, unsigned int*> (gaussTable_first[2], gaussTable_second[2]);
    } else if (n < (270 + 810) / 2) {
        return pair<int*, unsigned int*> (gaussTable_first[3], gaussTable_second[3]);
    } else if (n < (810 + 2430) / 2) {
        return pair<int*, unsigned int*> (gaussTable_first[4], gaussTable_second[4]);
    } else if (n < (2430 + 7290) / 2) {
        return pair<int*, unsigned int*> (gaussTable_first[5], gaussTable_second[5]);
    } else if (n < (7290 + 21870) / 2) {
        return pair<int*, unsigned int*> (gaussTable_first[6], gaussTable_second[6]);
    } else
        return pair<int*, unsigned int*> (gaussTable_first[7], gaussTable_second[7]);

}