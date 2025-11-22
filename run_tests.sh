# Script para compilar y ejecutar tests
# Ejecutar desde MSYS2 MINGW64

#!/bin/bash

echo "========================================"
echo "Compilando proyecto con tests..."
echo "========================================"

cd /c/Proyectos/effective-octo-eureka

# Limpiar build anterior
rm -rf build
mkdir build
cd build

# Configurar con CMake
echo "Configurando con CMake..."
cmake .. -G "MinGW Makefiles"

if [ $? -ne 0 ]; then
    echo "Error en configuración de CMake"
    exit 1
fi

# Compilar
echo "Compilando..."
mingw32-make

if [ $? -ne 0 ]; then
    echo "Error en compilación"
    exit 1
fi

echo ""
echo "========================================"
echo "Ejecutando tests..."
echo "========================================"

# Ejecutar tests
ctest --output-on-failure

echo ""
echo "========================================"
echo "Tests completados"
echo "========================================"
