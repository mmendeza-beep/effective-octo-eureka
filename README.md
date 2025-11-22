# Pantalla de Autenticación

Proyecto de C++ con interfaz gráfica para autenticación de usuarios.

## Requisitos

- CMake 3.16+
- SFML 2.5+
- SQLite3
- Google Test (para pruebas)

## Compilación

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

## Ejecución

```bash
./AuthScreen.exe
```

## Pruebas

Para ejecutar las pruebas automatizadas:

```bash
cd build
ctest --output-on-failure
```

Ver [tests/README.md](tests/README.md) para más información sobre las pruebas.

## Características

- Campo de email (usuario)
- Campo de contraseña (5-10 caracteres, 1 mayúscula, 1 carácter especial)
- 5 intentos máximos
- Base de datos SQLite con tabla usuarios
- Suite completa de pruebas automatizadas