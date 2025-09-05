# RLC Circuit Calculator 🔌

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/2Ntlaks/RLC-CIRCUIT-CALCULATOR)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-blue)](https://github.com/2Ntlaks/RLC-CIRCUIT-CALCULATOR)
[![Language](https://img.shields.io/badge/language-C99-orange)](https://github.com/2Ntlaks/RLC-CIRCUIT-CALCULATOR)
[![License](https://img.shields.io/badge/license-MIT-green)](https://github.com/2Ntlaks/RLC-CIRCUIT-CALCULATOR)

A comprehensive, cross-platform series RLC circuit analyzer written in C. This professional-grade calculator performs detailed electrical analysis of resistor-inductor-capacitor circuits with advanced features like phase angle calculation, power factor analysis, and automatic circuit type detection.

## ✨ Features

### 🔧 Core Calculations
- **Reactances**: Capacitive (Xc) and Inductive (Xl) reactance calculation
- **Impedance**: Total circuit impedance with complex analysis
- **Current & Voltages**: RMS current and voltage drops across all components
- **Power Analysis**: Real power consumption and power factor calculation
- **Resonant Frequency**: Automatic calculation of natural resonant frequency

### 🎯 Advanced Analysis
- **Phase Angle Calculation**: Determines current-voltage phase relationship
- **Circuit Type Detection**: Automatically identifies inductive/capacitive/resonant behavior
- **Power Factor Assessment**: Quality rating (Excellent/Good/Fair/Poor)
- **Resonance Detection**: Identifies when circuit operates at resonance
- **Electrical Behavior Explanation**: Educational insights into circuit operation

### 🛡️ Robust Engineering
- **Cross-Platform Compatibility**: Works on Windows, Linux, and macOS
- **Input Validation**: Comprehensive error checking with user-friendly feedback
- **High Precision**: Double-precision floating-point calculations throughout
- **Memory Safety**: Protected against buffer overflows and division by zero
- **Professional Output**: Formatted engineering reports with detailed analysis

## 🚀 Quick Start

### Prerequisites
- **C Compiler**: GCC, Clang, or MSVC
- **Make** (optional, for automated building)
- **Math Library**: Standard C math library (`-lm` on Unix systems)

### 📥 Installation

#### Option 1: Quick Build
```bash
# Clone the repository
git clone https://github.com/2Ntlaks/RLC-CIRCUIT-CALCULATOR.git
cd RLC-CIRCUIT-CALCULATOR

# Build with Makefile (recommended)
make

# Run the calculator
./rlc_calculator
```

#### Option 2: Manual Compilation
```bash
# Linux/macOS
gcc -std=c99 -Wall -Wextra -O2 main.c -o rlc_calculator -lm

# Windows (MinGW)
gcc -std=c99 -Wall -Wextra -O2 main.c -o rlc_calculator.exe -lm

# Windows (MSVC)
cl /std:c99 main.c /Fe:rlc_calculator.exe
```

## 📖 Usage

### Interactive Mode
Simply run the executable and follow the prompts:

```bash
./rlc_calculator
```

The program will guide you through entering:
- **Supply Voltage** (V)
- **Frequency** (Hz) 
- **Resistance** (Ω)
- **Inductance** (mH)
- **Capacitance** (μF)

### Example Session
```
========================================
RLC CIRCUIT CALCULATOR
========================================
A comprehensive series RLC circuit analyzer
Calculates reactances, impedance, current, power, and more

Enter the circuit parameters:

Supply voltage (V): 12
Frequency (Hz): 1000  
Resistance (Ohms): 100
Inductance (mH): 50
Capacitance (μF): 10

========================================
CIRCUIT PARAMETERS
========================================
Supply Voltage:        12.00 V
Frequency:           1000.00 Hz
Resistance:           100.00 Ohms
Inductance:           50.000 mH (0.050000 H)
Capacitance:          10.000 μF (0.000010000 F)
========================================

CALCULATION RESULTS
========================================
Capacitive Reactance (Xc):     15.915 Ohms
Inductive Reactance (Xl):     314.159 Ohms
Net Reactance (Xl-Xc):        298.244 Ohms
Impedance (Z):                314.562 Ohms

RMS Current (I):               0.0381 A
Voltage across Resistor:        3.815 V
Voltage across Inductor:       11.985 V
Voltage across Capacitor:       0.607 V

Power Consumption:              0.146 W
Resonant Frequency:            225.08 Hz
Phase Angle:                    71.46 degrees
Power Factor:                  0.3179

========================================
CIRCUIT ANALYSIS
========================================
Circuit is INDUCTIVE (Xl > Xc)
- Current LAGS voltage
- Phase angle is POSITIVE
Power factor: 0.3179 (Poor)
========================================
```

## 🧪 Example Test Cases

### 1. Inductive Circuit (Xl > Xc)
```
Input:  12V, 1kHz, 100Ω, 50mH, 10μF
Result: Inductive behavior, current lags voltage by 71.46°
```

### 2. Resonant Circuit (Xl ≈ Xc)
```
Input:  10V, 225Hz, 50Ω, 50mH, 10μF  
Result: Near-resonance, impedance ≈ resistance, phase ≈ 0°
```

### 3. Capacitive Circuit (Xc > Xl)
```
Input:  5V, 100Hz, 200Ω, 10mH, 100μF
Result: Capacitive behavior, current leads voltage by -2.76°
```

More examples available in [`examples.txt`](examples.txt).

## 🔨 Build System

### Available Make Targets
```bash
make            # Build the main executable
make debug      # Build with debug symbols
make test       # Run automated tests
make clean      # Remove build artifacts
make package    # Create release package
make install    # Install to system (Unix, requires sudo)
make help       # Show all available targets
```

### Advanced Options
```bash
# Static code analysis (requires cppcheck)
make analyze

# Code formatting (requires clang-format)  
make format

# Create release package
make package
```

## 📊 Technical Specifications

### Electrical Formulas Implemented
- **Capacitive Reactance**: `Xc = 1/(2πfC)`
- **Inductive Reactance**: `Xl = 2πfL`
- **Impedance**: `Z = √(R² + (Xl - Xc)²)`
- **Current**: `I = V/Z`
- **Phase Angle**: `φ = arctan((Xl - Xc)/R)`
- **Power Factor**: `PF = cos(φ)`
- **Resonant Frequency**: `f₀ = 1/(2π√(LC))`

### Input Ranges
- **Voltage**: Any positive value (V)
- **Frequency**: Any positive value (Hz)
- **Resistance**: Any positive value (Ω)
- **Inductance**: Any positive value (mH, converted to H)
- **Capacitance**: Any positive value (μF, converted to F)

### Precision
- **Calculation Precision**: Double-precision floating-point (64-bit)
- **Pi Constant**: Full machine precision (15+ decimal places)
- **Output Precision**: 3-4 decimal places for readability

## 🎓 Educational Value

This calculator is designed for:
- **Electrical Engineering Students**: Learning AC circuit analysis
- **Engineering Professionals**: Quick circuit verification and analysis  
- **Educators**: Demonstrating RLC circuit behavior and relationships
- **Hobbyists**: Understanding filter design and resonant circuits

### Key Learning Concepts
- **Reactance vs. Resistance**: Frequency-dependent vs. frequency-independent opposition
- **Phase Relationships**: How current and voltage relate in AC circuits
- **Resonance**: The special frequency where Xl = Xc
- **Power Factor**: Efficiency indicator for AC circuits
- **Circuit Behavior**: Inductive vs. capacitive characteristics

## 🔬 Recent Improvements

This project has been significantly enhanced from the original version:

### ✅ **Major Fixes Applied**
- **Cross-Platform Compatibility**: Removed Windows-specific dependencies
- **Input Validation**: Added comprehensive error checking and recovery
- **Numerical Precision**: Standardized on double precision with accurate constants
- **Code Safety**: Eliminated division by zero risks and buffer overflows
- **Professional Output**: Enhanced formatting and detailed analysis

### ✨ **New Features Added**
- **Phase Angle Calculation**: Shows electrical behavior (leading/lagging)
- **Power Factor Analysis**: Engineering quality assessment  
- **Circuit Type Detection**: Automatically identifies circuit characteristics
- **Resonance Analysis**: Finds and explains resonant behavior
- **Build Automation**: Professional Makefile with testing and packaging
- **Documentation**: Comprehensive examples and improvement tracking

See [`IMPROVEMENTS.md`](IMPROVEMENTS.md) for detailed before/after comparison.

## 🏗️ Project Structure

```
RLC-CIRCUIT-CALCULATOR/
├── main.c              # Main source code (refactored, portable)
├── Makefile            # Cross-platform build system
├── README.md           # This documentation
├── .gitignore          # Git exclusions for C projects
├── examples.txt        # Usage examples and test cases
├── IMPROVEMENTS.md     # Detailed improvement documentation
└── rlc_calculator      # Compiled executable (after build)
```

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/AmazingFeature`)
3. **Commit** your changes (`git commit -m 'Add some AmazingFeature'`)
4. **Push** to the branch (`git push origin feature/AmazingFeature`)
5. **Open** a Pull Request

### Ideas for Contributions
- **GUI Interface**: Add graphical user interface (GTK, Qt, or web-based)
- **Frequency Sweep**: Plot impedance vs frequency curves
- **Parallel Circuits**: Extend to parallel RLC configurations  
- **Complex Notation**: Support for phasor/complex number display
- **Unit Testing**: Add comprehensive automated test suite
- **Documentation**: Improve examples and educational content

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Ntlakanipho Mgaguli** - [@2Ntlaks](https://github.com/2Ntlaks)

- 🔗 **GitHub**: [github.com/2Ntlaks](https://github.com/2Ntlaks)
- 📧 **Email**: [Contact via GitHub](https://github.com/2Ntlaks)

## 🙏 Acknowledgments

- **Electrical Engineering Community**: For feedback and suggestions
- **Open Source Contributors**: For inspiration and best practices  
- **Educational Institutions**: For promoting practical learning tools
- **Testing Community**: For helping identify and fix issues

## 📈 Version History

- **v2.0** (Current): Major refactor with cross-platform support, enhanced calculations, and professional documentation
- **v1.0**: Original Windows-only calculator with basic functionality

## 🔗 Related Projects

- **Filter Design Tools**: For designing RLC-based filters
- **Circuit Simulation Software**: SPICE, LTspice, Multisim
- **Educational Resources**: AC Circuit Analysis textbooks and courses

---

<div align="center">

**⭐ If this project helped you, please consider giving it a star!**

**🐛 Found a bug or have a suggestion? [Open an issue](https://github.com/2Ntlaks/RLC-CIRCUIT-CALCULATOR/issues)**

**📚 Want to learn more about RLC circuits? Check out the examples and documentation!**

</div>