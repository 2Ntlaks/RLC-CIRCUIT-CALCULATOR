#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define Pi 3.14159
//Function to get users input for the components of the series RLC components
void getUsersInput(int* Resistor, float* Inductor, float* Capacitor,float* Voltage,float* Frequency)
{
    printf("Enter Voltage of the circuit: ");
    scanf("%f",Voltage);
    printf("Enter frequency of the circuit: ");
    scanf("%f",Frequency);
    printf("Enter a resistor in ohms: ");
    scanf("%d",Resistor);
    printf("Enter inductor of the circuit in mH: ");
    scanf("%f",Inductor);
    printf("Enter Capacitor of the circuit in micro Farads: ");
    scanf("%f",Capacitor);
    system("CLS");
}
//Function to Convert Inductor and capacitor to standard units
void Conversion(float* Inductor, float* Capacitor)
{
    *Inductor = *Inductor * 1e-3;
    *Capacitor = *Capacitor *1e-6;
}
//Function to calcualte reactance in the circuit
double CapacitiveReactance(double Frequency,double Capacitor)
{
    return (float)1/(2*Pi*Frequency*Capacitor);
}
//Function to inductive reactance in the circuit
double InductiveReactance(double Frequency,double Inductor)
{
    return (2*Pi*Frequency*Inductor);
}
//Function to calculate Impendence in the circuit
double Impedence(int Resistor, float Frequency,float Capacitor,float inductor)
{
    return (double)sqrt(pow(Resistor,2)+ pow(CapacitiveReactance(Frequency,Capacitor)- InductiveReactance(Frequency,inductor),2));
}
//Function to current in the circuit
double CurrentIrms(float Volt,float Impendence)
{
    return Volt/Impendence;
}
//Function to Calculate voltage on the Resistance
double voltageOnResistor( float I_rms,int Resistor)
{
    return (I_rms*Resistor);
}
//Function to calculate Voltage on Capacitor
double voltageOnCapacitor( float I_rms,double Xc)
{
    return I_rms*Xc;
}
//Function to calculate voltage in inductor
double voltageOnInductor( float I_rms,double Xl)
{
    return (I_rms*Xl);
}
//Function to calculate Power
double Power(float I_rms, int Resistor)
{
    return (pow(I_rms,2)*Resistor);
}
//Function to calculate Resonant Frequency
double ResonantFrequency(double Capacitor,double Inductor)
{
    return (double)1/(2*Pi*sqrt(Capacitor*Inductor));
}

int main()
{
    //Variable declaration
    int R;
    float C,L,Xl,Xc,Z,Freq,Volt;
    double I_rms,Vr,Vl,Vc;

    printf("\t\t<-----------|WELCOME TO RLC CIRCUIT CALCULATOR|----------->\n\n");
    getUsersInput(&R,&L,&C,&Volt,&Freq);
    Conversion(&L,&C);
     //Function calling
    Xc = CapacitiveReactance(Freq,C);
    Xl =InductiveReactance(Freq,L);
    Z = Impedence(R,Freq,C,L);
    I_rms = CurrentIrms(Volt,Z);
    Vr = voltageOnResistor(I_rms,R);
    Vc = voltageOnCapacitor(I_rms,Xc);
    Vl = voltageOnInductor(I_rms,Xl);

    //Display in results
    printf("\nCapacitive Reactance              : %.1lf \xEA\n",Xc);
    printf("Inductive Reactance                : %.2lf \xEA\n",Xl);
    printf("Impendence of the circuit          : %.2lf \xEA\n",Z);
    printf("Current through the circuit        : %.4lf \x41\n",I_rms);
    printf("Voltage across Resistor            : %.2lf \x56\n",Vr);
    printf("Voltage across Capacitor           : %.2lf \x56\n",Vc);
    printf("Voltage across Inductor            : %.2lf \x56\n",Vl);
    printf("Power in the circuit               : %.3lf \x57\n",Power(I_rms,R));
    printf("Resonant Frequency                 : %.2lf Hz", ResonantFrequency(C,L));
    printf("\n");
    //Display in Tabular form
    printf("\n %-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n","Xc[\xEA]","Xl[\xEA]","Z[\xEA]","I_rms[\x41]","Vr[\x56]","Vl[\x56]","Vc[\x56]","P[\x57]","Fr[Hz]");
    printf("%-12.1lf %-12.2lf %-12.2lf %-12.4lf %-12.2lf %-12.2lf %-12.2lf %-12.3lf %-12.2lf",Xc,Xl,Z,I_rms,Vr,Vc,Vl,Power(I_rms,R),ResonantFrequency(C,L));
    return 0;
}
