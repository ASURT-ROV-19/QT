#include<bits/stdc++.h>
using namespace std;
#define PI 3.14159265358979323846

double canonVolume(double R1,double R2,double R3,double L){

    return PI*L*((R2*R2 +R3*R3 +R2*R3)/3 -R1*R1);

}
double canonVolume_V2(double R[],double L){

    sort(R,R+3);
    return PI*L*((R[1]*R[1] +R[2]*R[2] +R[1]*R[2])/3 -R[0]*R[0]);
}
double canonMass(double Volume,double Specfic_Gravity){

    return Volume*(Specfic_Gravity-1000)/1000000;
}