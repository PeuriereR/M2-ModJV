#include "analyticfieldridgeattenuate.h"

PerlinNoise AnalyticFieldRidgeAttenuate::pn;

AnalyticFieldRidgeAttenuate::AnalyticFieldRidgeAttenuate(){}

AnalyticFieldRidgeAttenuate::AnalyticFieldRidgeAttenuate(float a, float l, int o, float f):amplitude(a), lambda(l), octave(o), facteur(f){}

float linear(float hauteur, float noise, float borneSupp, float borneInf){
    // Fonction d'atténuation

    float newH = hauteur + noise;
    if(newH < borneInf)
        return 0;
    if(newH > borneSupp)
        return 1;

    borneSupp -= borneInf; // on remet entre 0 et borneSupp + borneInf (borneINf est negatif)
    newH -= borneInf;
    return newH / borneSupp;
}


float AnalyticFieldRidgeAttenuate::getH(const Vec2 &v) const{

    // 1ere somme de bruit
    float a  = amplitude;
    float l = lambda;
    float z = pn.noise(v/l)*a;

    float borneSupp = amplitude * 0.5;
    float borneInf = -amplitude * 0.9;
    for (int i = 0; i < octave-1; ++i) {

        a *= facteur;
        l *= facteur;
        float noise = pn.noise(v/l)*a;
        // Attenuation
        z += noise * linear(z,noise,borneSupp,borneInf);
    }

    // 2eme somme de bruit
    a = amplitude;
    l = lambda;
    float z2 = pn.noiseShuffle(v/l)*a;

    for (int i = 0; i < octave-1; ++i) {
        a *= facteur;
        l *= facteur;
        float noise = pn.noiseShuffle(v/l)*a;
        // Attenuation
        z2 += noise * linear(z,noise,borneSupp,borneInf);
    }

    // Minimum pour les ridges
    float val = qMin(z,z2);
    return val;

}
