# Copilot Instructions for Qt CMake Template

## Project Context
- This is a Qt6 C++ application using CMake
- Uses modern C++17 standards
- Follows Qt naming conventions and best practices
- Target platform: Linux (developed in distrobox)

## Important Instructions
- Prefer simple solutions
- If something should be guaranteed, do not write lengthy fallbacks for if it is missing
- Write what is asked for and not more

## Coding Standards
- Use C++17 features where appropriate
- Follow Qt coding conventions (camelCase for functions, PascalCase for classes)
- Include proper Qt headers (e.g., `#include <QApplication>`)
- Use Qt's signal-slot mechanism for UI interactions
- Prefer smart pointers for memory management
- Add error handling for Qt operations

## Architecture Guidelines
- Keep UI logic in window.cpp/window.hpp
- Main application logic in main.cpp
- Use Qt's MVC patterns where applicable
- Separate business logic from UI code

## Build System
- Use CMake with Qt6 integration
- Target name: "Temp" (can be changed)
- Ensure compatibility with distrobox environments
- Include proper Qt6 component dependencies

## Code Style
- Use 4 spaces for indentation
- Place opening braces on same line
- Use meaningful variable and function names
- Add comments for complex Qt-specific operations
