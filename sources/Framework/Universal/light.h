/********************************************************************************* 

  *FileName: light.h  
            コウ  キガク
  *Author:  Huang QiYue
  *Version:  1.0
  *Date:  2022/04/02

**********************************************************************************/  


#ifndef _LIGHT_H_
#define _LIGHT_H_

struct stLight
{
    stLight()
    {
        type = 0;
        posX = 0.0f, posY = 0.0f, posZ = 0.0f;
        dirX = 0.0f, dirY = 0.0f, dirZ = 0.0f;
        ambientR = ambientG = ambientB = ambientA = 1;
        diffuseR = diffuseG = diffuseB = diffuseA = 1;
        specularR = specularG = specularB = specularA = 0.0f;
        range = 0.0f;
        falloff = 0.0f;
        attenuation0 = 0.0f;
        attenuation1 = 0.0f;
        attenuation2 = 0.0f;
        theta = 0.0f;
        phi = 0.0f;
    }

    int type;
    float posX, posY, posZ;
    float dirX, dirY, dirZ;
    float ambientR, ambientG, ambientB, ambientA;
    float diffuseR, diffuseG, diffuseB, diffuseA;
    float specularR, specularG, specularB, specularA;
    float range;
    float falloff;
    float attenuation0;
    float attenuation1;
    float attenuation2;
    float theta;
    float phi;
};

#endif // _LIGHT_H_