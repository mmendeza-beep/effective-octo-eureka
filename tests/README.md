# Testing Guide - AuthScreen Project

## 📋 Descripción

Este proyecto incluye un sistema completo de pruebas automatizadas usando **Google Test** framework.

## 🧪 Tipos de Pruebas Implementadas

### 1. **Pruebas de Caja Negra**
- Validación de contraseñas sin conocer implementación interna
- Tests de casos límite y combinaciones

### 2. **Pruebas Unitarias**
- `test_password_validator.cpp` - Validación de contraseñas
- `test_database.cpp` - Operaciones de base de datos

### 3. **Pruebas de Integración**
- `test_integration.cpp` - Interacción entre módulos
- Flujo completo de autenticación

### 4. **Pruebas de Sistema y UAT**
- `test_system.cpp` - Escenarios de usuario
- Límite de 5 intentos
- Recuperación de contraseña

### 5. **Pruebas de Rendimiento**
- `test_performance.cpp` - Carga, estrés, volumen
- Validaciones múltiples
- Consultas a BD bajo carga

### 6. **Pruebas de Seguridad**
- `test_security.cpp` - Inyección SQL
- Autenticación y autorización
- Validación de entrada

### 7. **Pruebas de Usabilidad**
- `test_usability.cpp` - Experiencia de usuario
- Navegación y accesibilidad

### 8. **Pruebas de Recuperación**
- `test_recovery.cpp` - Resiliencia ante fallas
- BD corrupta, archivos faltantes

## 🚀 Cómo Ejecutar las Pruebas

### Compilar con Tests

Desde **MSYS2 MINGW64**:

```bash
cd /c/Proyectos/effective-octo-eureka
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

### Ejecutar Todas las Pruebas

```bash
ctest --output-on-failure
```

### Ejecutar Tests Específicos

```bash
# Solo tests de password validator
./AuthScreenTests --gtest_filter=PasswordValidatorTest.*

# Solo tests de seguridad
./AuthScreenTests --gtest_filter=SecurityTest.*

# Solo tests de rendimiento
./AuthScreenTests --gtest_filter=PerformanceTest.*
```

### Ejecutar con Verbose

```bash
./AuthScreenTests --gtest_verbose
```

## 📊 Cobertura de Pruebas

| Categoría | Archivo | Tests |
|-----------|---------|-------|
| Caja Negra | test_password_validator.cpp | 15+ |
| Unitarias | test_password_validator.cpp, test_database.cpp | 25+ |
| Integración | test_integration.cpp | 6+ |
| Sistema/UAT | test_system.cpp | 10+ |
| Rendimiento | test_performance.cpp | 8+ |
| Seguridad | test_security.cpp | 20+ |
| Usabilidad | test_usability.cpp | 12+ |
| Recuperación | test_recovery.cpp | 14+ |

## 🔍 Ejemplos de Uso

### Verificar Validación de Contraseña

```bash
./AuthScreenTests --gtest_filter=PasswordValidatorTest.AcceptsValidPasswords
```

### Verificar Seguridad SQL Injection

```bash
./AuthScreenTests --gtest_filter=SecurityTest.SQLInjection*
```

### Verificar Rendimiento

```bash
./AuthScreenTests --gtest_filter=PerformanceTest.LoadTest*
```

## 📝 Requisitos

- Google Test (instalado via MSYS2)
- SFML 2.5+
- SQLite3
- CMake 3.16+

## 🛠️ Instalación de Dependencias

```bash
# En MSYS2 MINGW64
pacman -S mingw-w64-x86_64-gtest mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc
```

## ✅ Verificación

Para verificar que todo funciona:

```bash
cd build
ctest --output-on-failure
```

Deberías ver algo como:

```
Test project C:/Proyectos/effective-octo-eureka/build
    Start 1: PasswordValidatorTest.RejectsTooShort
1/X Test #1: PasswordValidatorTest.RejectsTooShort ...   Passed
...
100% tests passed, 0 tests failed
```

## 🐛 Troubleshooting

### Error: "cannot find -lgtest"
```bash
pacman -S mingw-w64-x86_64-gtest
```

### Error: "CMake cannot find GTest"
```bash
# Asegúrate de estar en MSYS2 MINGW64, no MSYS2 MSYS
```

### Tests fallan
```bash
# Ejecuta con verbose para ver detalles
./AuthScreenTests --gtest_verbose
```
