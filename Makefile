# RLC Circuit Calculator Makefile
# Cross-platform build configuration

# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -O2 -pedantic
LDFLAGS = -lm
DEBUG_FLAGS = -g -DDEBUG

# Target executable name
TARGET = rlc_calculator
SOURCE = main.c

# Default target
all: $(TARGET)

# Build the main executable
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# Debug build
debug: $(SOURCE)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(TARGET)_debug $< $(LDFLAGS)

# Test the program with sample inputs
test: $(TARGET)
	@echo "Testing RLC Calculator..."
	@echo "12\n1000\n100\n50\n10\nn" | ./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET) $(TARGET).exe $(TARGET)_debug $(TARGET)_debug.exe
	rm -f *.o *.obj
	rm -rf bin/ obj/

# Install to system (Unix-like systems)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	chmod +x /usr/local/bin/$(TARGET)

# Uninstall from system
uninstall:
	rm -f /usr/local/bin/$(TARGET)

# Help target
help:
	@echo "RLC Circuit Calculator Build System"
	@echo "Available targets:"
	@echo "  all       - Build the main executable (default)"
	@echo "  debug     - Build with debug symbols"
	@echo "  test      - Run automated test"
	@echo "  clean     - Remove build artifacts"
	@echo "  install   - Install to /usr/local/bin (requires sudo)"
	@echo "  uninstall - Remove from /usr/local/bin (requires sudo)"
	@echo "  help      - Show this help message"

# Static analysis (if cppcheck is available)
analyze:
	@if command -v cppcheck >/dev/null 2>&1; then \
		echo "Running static analysis..."; \
		cppcheck --enable=all --std=c99 $(SOURCE); \
	else \
		echo "cppcheck not found, skipping static analysis"; \
	fi

# Format code (if clang-format is available)
format:
	@if command -v clang-format >/dev/null 2>&1; then \
		echo "Formatting code..."; \
		clang-format -i $(SOURCE); \
	else \
		echo "clang-format not found, skipping code formatting"; \
	fi

# Create release package
package: clean $(TARGET)
	@mkdir -p rlc-calculator-release
	@cp $(TARGET) rlc-calculator-release/
	@cp main.c rlc-calculator-release/
	@cp Makefile rlc-calculator-release/
	@cp README.md rlc-calculator-release/
	@echo "Creating release package..."
	@tar -czf rlc-calculator-release.tar.gz rlc-calculator-release/
	@rm -rf rlc-calculator-release/
	@echo "Release package created: rlc-calculator-release.tar.gz"

# Declare phony targets
.PHONY: all debug test clean install uninstall help analyze format package