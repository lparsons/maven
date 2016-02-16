#ifndef MASSCALC_H
#define MASSCALC_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <map>
#include "mzSample.h" 
#include "mzUtils.h"

class Compound;
class Isotope;
class Adduct;


using namespace std;

// EI    M+ M-
// Cl    M+H M+X
// ACPI  M+H M+X M-X
// FI    M+H  M+X
// ESI    [M+nH]^n+  [M-nX]^n-
// FAB   M+X M+N
// ACPI  M+H  M+X

class MassCalculator { 

    public:
        enum IonizationType { ESI=0, EI=1};
        static IonizationType ionizationType;

    typedef struct {
        std::string name;
        std::string formula;
        double mass=0;
        double diff=0;
        Compound* compoundLink=NULL;
        Adduct*   adductLink=NULL;
    } Match;


    MassCalculator(){}
    double computeNeutralMass(string formula);
    double computeMass(string formula, int polarity);
    double computeC13IsotopeMass(string formula);
    map<string,double>computeLabeledMasses(string formula, int polarity);
    map<string,double>computeLabeledAbundances(string formula);
    map<string,int> getComposition(string formula);
    void matchMass(double mass, double ppm);
    string prettyName(int c, int h, int n, int o, int p, int s);
    vector<Match> enumerateMasses(double inputMass, double charge, double maxdiff);
    double adjustMass(double mass,int charge);

    vector<Isotope> computeIsotopes(string formula, int polarity);

    static bool compDiff(const Match& a, const Match& b ) { return a.diff < b.diff; }
    private:
        double getElementMass(string elmnt);

};

#endif
