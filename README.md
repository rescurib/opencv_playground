# Experimentos y notas sueltas sobre OpenCV

## Instalación de OpenCV en Windows

Instalar MYSYS2 y abrir terminal UCRT:

```Bash
pacman -Syu

# Si reinicia consola, volver a ejecutar:
pacman -Syu

# Instalar OpenCV para entorno UCRT
pacman -S mingw-w64-ucrt-x86_64-opencv

# Mostrar directorios de instalación de librerías
pkg-config --cflags opencv4
```

>[!IMPORTANT]
> Para ejecutar desde CMD o PS se debe añadir a la variable de entorno de sistema PATH este directorio: C:\msys64\ucrt64\bin y por debajo de, ese añadir este otro: C:\msys64\usr\bin\

Nota: Ctrl+Shift+V para previsualizar Markdown en VSC.
