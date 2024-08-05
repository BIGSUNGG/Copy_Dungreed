#include "framework.h"
#include "MathUtility.h"

// min �̻� max ������ ������ ���� ����
int MathUtility::RandomInt(int min, int max) 
{
    max += 1;
    int result = rand() % (max - min) + min;
    return result;
}

float MathUtility::RandomFloat(float min, float max)
{
    float zeroToOne = (float)(rand()) / (float)(RAND_MAX);

    return zeroToOne *(max - min) + min;
}
