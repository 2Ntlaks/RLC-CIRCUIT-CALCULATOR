/**
 * RLC Circuit Calculator - Portable Version
 * 
 * A comprehensive series RLC circuit analyzer that calculates:
 * - Reactances (Xc, Xl)
 * - Impedance (Z)
 * - Current and voltages across components
 * - Power consumption
 * - Resonant frequency
 * - Phase angle and power factor
 * 
 * Author: Ntlakanipho Mgaguli (refactored for portability)
 * Platform: Cross-platform (Windows, Linux, macOS)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

// Ensure M_PI is defined for all platforms
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constants for better readability
#define SEPARATOR "========================================\n"
#define MIN_POSITIVE 1e-12  // Minimum positive value to avoid division by zero

// Circuit input parameters
typedef struct {
    double R;           // Resistance (Ohms)
    double L;           // Inductance (Henries)
    double C;           // Capacitance (Farads)
    double V_supply;    // Supply voltage (Volts)
    double frequency;   // Frequency (Hz)
} RLCCircuit;

// Circuit calculation results
typedef struct {
    double Xc;          // Capacitive reactance (Ohms)
    double Xl;          // Inductive reactance (Ohms)
    double Z;           // Impedance (Ohms)
    double I_rms;       // RMS current (Amperes)
    double V_R;         // Voltage across resistor (Volts)
    double V_L;         // Voltage across inductor (Volts)
    double V_C;         // Voltage across capacitor (Volts)
    double power;       // Power consumption (Watts)
    double f_resonant;  // Resonant frequency (Hz)
    double phase_angle; // Phase angle (degrees)
    double power_factor;// Power factor (dimensionless)
} CircuitResults;

// Function prototypes
double get_positive_double(const char* prompt, const char* unit);
void get_circuit_inputs(RLCCircuit* circuit);
void calculate_circuit_parameters(const RLCCircuit* circuit, CircuitResults* results);
void print_input_summary(const RLCCircuit* circuit);
void print_results(const CircuitResults* results);
void print_header(void);
void clear_input_buffer(void);
bool ask_continue(void);

// Cross-platform screen clearing (optional, non-intrusive)
void clear_screen(void) {
    printf("\n" SEPARATOR);
    printf("RLC CIRCUIT CALCULATOR\n");
    printf(SEPARATOR);
}

/**
 * Get a positive double value with input validation
 */
double get_positive_double(const char* prompt, const char* unit) {
    double value;
    char input[100];
    
    while (true) {
        printf("%s", prompt);
        if (unit && strlen(unit) > 0) {
            printf(" (%s): ", unit);
        } else {
            printf(": ");
        }
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        
        // Try to parse the number
        char* endptr;
        value = strtod(input, &endptr);
        
        // Check if conversion was successful and value is positive
        if (endptr == input) {
            printf("Invalid input! Please enter a valid number.\n");
            continue;
        }
        
        if (value <= MIN_POSITIVE) {
            printf("Value must be positive! Please enter a value greater than 0.\n");
            continue;
        }
        
        break;
    }
    
    return value;
}

/**
 * Clear input buffer (for scanf cleanup)
 */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Get all circuit input parameters from user
 */
void get_circuit_inputs(RLCCircuit* circuit) {
    printf("Enter the circuit parameters:\n\n");
    
    circuit->V_supply = get_positive_double("Supply voltage", "V");
    circuit->frequency = get_positive_double("Frequency", "Hz");
    circuit->R = get_positive_double("Resistance", "Ohms");
    
    // Get inductance in mH and convert to H
    double L_mH = get_positive_double("Inductance", "mH");
    circuit->L = L_mH / 1000.0;  // Convert mH to H
    
    // Get capacitance in μF and convert to F
    double C_uF = get_positive_double("Capacitance", "μF");
    circuit->C = C_uF / 1000000.0;  // Convert μF to F
}

/**
 * Calculate all circuit parameters
 */
void calculate_circuit_parameters(const RLCCircuit* circuit, CircuitResults* results) {
    double omega = 2.0 * M_PI * circuit->frequency;
    
    // Calculate reactances
    results->Xc = 1.0 / (omega * circuit->C);
    results->Xl = omega * circuit->L;
    
    // Calculate impedance
    double X_net = results->Xl - results->Xc;
    results->Z = sqrt(circuit->R * circuit->R + X_net * X_net);
    
    // Calculate current
    results->I_rms = circuit->V_supply / results->Z;
    
    // Calculate voltages across components
    results->V_R = results->I_rms * circuit->R;
    results->V_L = results->I_rms * results->Xl;
    results->V_C = results->I_rms * results->Xc;
    
    // Calculate power (only resistive component dissipates power)
    results->power = results->I_rms * results->I_rms * circuit->R;
    
    // Calculate resonant frequency
    results->f_resonant = 1.0 / (2.0 * M_PI * sqrt(circuit->L * circuit->C));
    
    // Calculate phase angle (in degrees)
    results->phase_angle = atan2(X_net, circuit->R) * 180.0 / M_PI;
    
    // Calculate power factor
    results->power_factor = cos(results->phase_angle * M_PI / 180.0);
}

/**
 * Print input summary
 */
void print_input_summary(const RLCCircuit* circuit) {
    printf("\n" SEPARATOR);
    printf("CIRCUIT PARAMETERS\n");
    printf(SEPARATOR);
    printf("Supply Voltage:     %8.2f V\n", circuit->V_supply);
    printf("Frequency:          %8.2f Hz\n", circuit->frequency);
    printf("Resistance:         %8.2f Ohms\n", circuit->R);
    printf("Inductance:         %8.3f mH (%.6f H)\n", circuit->L * 1000.0, circuit->L);
    printf("Capacitance:        %8.3f μF (%.9f F)\n", circuit->C * 1000000.0, circuit->C);
    printf(SEPARATOR);
}

/**
 * Print calculation results in a formatted table
 */
void print_results(const CircuitResults* results) {
    printf("\nCALCULATION RESULTS\n");
    printf(SEPARATOR);
    printf("Capacitive Reactance (Xc): %10.3f Ohms\n", results->Xc);
    printf("Inductive Reactance (Xl):  %10.3f Ohms\n", results->Xl);
    printf("Net Reactance (Xl-Xc):     %10.3f Ohms\n", results->Xl - results->Xc);
    printf("Impedance (Z):             %10.3f Ohms\n", results->Z);
    printf("\n");
    printf("RMS Current (I):           %10.4f A\n", results->I_rms);
    printf("Voltage across Resistor:   %10.3f V\n", results->V_R);
    printf("Voltage across Inductor:   %10.3f V\n", results->V_L);
    printf("Voltage across Capacitor:  %10.3f V\n", results->V_C);
    printf("\n");
    printf("Power Consumption:         %10.3f W\n", results->power);
    printf("Resonant Frequency:        %10.2f Hz\n", results->f_resonant);
    printf("Phase Angle:               %10.2f degrees\n", results->phase_angle);
    printf("Power Factor:              %10.4f\n", results->power_factor);
    
    // Circuit analysis
    printf("\n" SEPARATOR);
    printf("CIRCUIT ANALYSIS\n");
    printf(SEPARATOR);
    
    if (fabs(results->Xl - results->Xc) < 0.001) {
        printf("Circuit is at RESONANCE (Xl ≈ Xc)\n");
        printf("- Impedance is minimum (Z = R)\n");
        printf("- Current is maximum\n");
        printf("- Phase angle is 0°\n");
    } else if (results->Xl > results->Xc) {
        printf("Circuit is INDUCTIVE (Xl > Xc)\n");
        printf("- Current LAGS voltage\n");
        printf("- Phase angle is POSITIVE\n");
    } else {
        printf("Circuit is CAPACITIVE (Xc > Xl)\n");
        printf("- Current LEADS voltage\n");
        printf("- Phase angle is NEGATIVE\n");
    }
    
    printf("Power factor: %.4f ", results->power_factor);
    if (results->power_factor > 0.9) {
        printf("(Excellent)\n");
    } else if (results->power_factor > 0.7) {
        printf("(Good)\n");
    } else if (results->power_factor > 0.5) {
        printf("(Fair)\n");
    } else {
        printf("(Poor)\n");
    }
    
    printf(SEPARATOR);
}

/**
 * Print program header
 */
void print_header(void) {
    clear_screen();
    printf("A comprehensive series RLC circuit analyzer\n");
    printf("Calculates reactances, impedance, current, power, and more\n");
    printf("\n");
}

/**
 * Ask user if they want to continue
 */
bool ask_continue(void) {
    char choice;
    printf("\nWould you like to analyze another circuit? (y/n): ");
    
    if (scanf(" %c", &choice) != 1) {
        clear_input_buffer();
        return false;
    }
    clear_input_buffer();
    
    return (choice == 'y' || choice == 'Y');
}

/**
 * Main program
 */
int main(void) {
    RLCCircuit circuit;
    CircuitResults results;
    
    print_header();
    
    do {
        // Get user inputs
        get_circuit_inputs(&circuit);
        
        // Calculate circuit parameters
        calculate_circuit_parameters(&circuit, &results);
        
        // Display results
        print_input_summary(&circuit);
        print_results(&results);
        
    } while (ask_continue());
    
    printf("\nThank you for using the RLC Circuit Calculator!\n");
    printf("Program by: Ntlakanipho Mgaguli\n");
    
    return 0;
}