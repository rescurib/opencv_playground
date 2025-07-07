# Experimentos y notas sueltas sobre OpenCV (C++)

## Instalación en Linux Mint / Ubuntu
```Bash
sudo apt install libopencv-dev v4l-utils
```

## Instalación de OpenCV en Windows

Instalar [MYSYS2](https://www.msys2.org/) y abrir terminal del [ambiente](https://www.msys2.org/docs/environments/) UCRT:

```Bash
pacman -Syu

# Si reinicia consola, volver a ejecutar:
pacman -Syu

# QT6 para el módulo HighGUI
pacman -S mingw-w64-ucrt-x86_64-qt6-5compat

# Instalar OpenCV para ambiente UCRT
pacman -S mingw-w64-ucrt-x86_64-opencv

# Mostrar directorios de instalación para
# cflags (g++)
pkg-config --cflags opencv4

# Mostrar flags para el linker
pkg-config --libs opencv4
```

>[!IMPORTANT]
> Para ejecutar desde CMD o PS se debe añadir a la variable de entorno de sistema PATH este directorio: C:\msys64\ucrt64\bin y por debajo de, ese añadir este otro: C:\msys64\usr\bin\

## Programa de verificación

```Cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) 
{
    // Checar si OpenCV es enlazado correctamente
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;

    // Crear imagen de prueba
    cv::Mat imagen = cv::Mat::zeros(200, 400, CV_8UC3);
    
    // Añadir texto a la imagen
    cv::putText(imagen, "OpenCV funciona!", 
                cv::Point(65, 100), 
                cv::FONT_HERSHEY_SIMPLEX, 
                1.0, 
                cv::Scalar(255, 255, 255), 
                2); 

    cv::putText(imagen, "(Presionar ESC para salir)", 
                cv::Point(5, 188), // cerca del borde inferior
                cv::FONT_HERSHEY_SIMPLEX, 
                0.5, // tamaño más pequeño
                cv::Scalar(200, 200, 200), 
                1);

    // Mostrar imagen
    cv::imshow("Verificacion", imagen);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
```

**Compilación**
```Bash
g++ ocv_install_verify.cpp -I C:/msys64/ucrt64/include/opencv4 -L C:/mysys2/ucrt64/bin -lopencv_core -lopencv_imgproc -lopencv_highgui -o ocv_install_verify 
```
## Automaización del build

`pkg-config` es una herramienta auxiliar que se utiliza al compilar aplicaciones y bibliotecas. Permite insertar las opciones correctas del compilador en la línea de comandos para que una aplicación pueda usar, por ejemplo, gcc -o test test.c `pkg-config --libs --cflags glib-2.0`, en lugar de codificar valores sobre dónde encontrar glib (u otras bibliotecas).

Para ejecutar pkg-config desde CMD o PS se debe crear la siguiente variable de entorno:

```C
PKG_CONFIG_PATH = C:\mysys64\ucrt64\lib\pkgconfig
```
En una aplicación más compleja con OpenCV se requerirá añadir diferentes flags para enlazar las librerías. Con está herramienta no tendrémos que preocuparnos por eso ya que encontrará a todas. Se puede usar directamente en nuestro Makefile:

```Bash
# Variables para OpenCV (ajustar según tu instalación si es necesario)
# 2>/dev/null redirige stderr a /dev/null si pkg-config no está instalado
OPENCV_CFLAGS = $(shell pkg-config --cflags opencv4 2>/dev/null)
OPENCV_LIBS   = $(shell pkg-config --libs opencv4 2>/dev/null)
````

**¿Por qué necesitamos estas flags?**

Cuando utilizamos una función de OpenCV, por ejemplo `cv::imread()`, estamos haciendo un llamado a un archivo que está precompilado. En Linux estos objetos de librería tienen extenciones .so o .a y en Windows .dll. Se le debe indicar al Linker que archivos debe buscar para satisfacer los símbolos.

En el caso de Windows, el directorio que agregamos con:
```Bash
-L C:/msys64/ucrt64/bin/ ../lib -l opencv_core
```
contiene los archivos dll, por ejemplo: libopencv_core.dll, mientras que el directorio C:/msys64/ucrt64/lib contiene los archivos dll.a como libopencv_core.dll.a

En MSYS2 con UCRT:
* El Linker usa: libopencv_core.dll.a
* Tu app usa en tiempo de ejecución: libopencv_core.dll

>[!NOTE]
> Referencia: **Head First C**, *David Griffiths*. Ch. 8 static and dynamic libraries.

## Prueba de webcam

Este es el verdadero *Hola, Mundo* de OpenCV. Este programa toma como argumento el índice de dispositivo de video. Si no agrega ninguno, se elije el indice 0 (webcam integrada).

```C++
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    int cam_index = 0;
    if (argc > 1) {
        cam_index = std::stoi(argv[1]);
    }

    // Elegir backend de video según plataforma
#ifdef _WIN32
    // Windows (puede usar DirectShow, MSMF o cualquiera por defecto)
    cv::VideoCapture cap(cam_index);  // usa backend por defecto en Windows
#else
    // Linux (usar V4L2 para evitar problemas con GStreamer)
    cv::VideoCapture cap(cam_index, cv::CAP_V4L2);
#endif

    if (!cap.isOpened()) {
        std::cerr << "No se pudo abrir la cámara con índice " << cam_index << std::endl;
        return 1;
    }

    std::cout << "Presiona ESC para salir.\n";
    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "No se pudo capturar el frame." << std::endl;
            break;
        }
        cv::imshow("Webcam", frame);
        int key = cv::waitKey(30);
        if (key == 27) { // ESC
            break;
        }
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
```

Podemos ver los dispostivos de video que tenemos disponibles con:
```Bash
ls /dev/video*
```
En mi caso, mi webcam usb está en /dev/video2. En Linux podemos obtener más información de nuestros dispositivos con v4l2-ctl:

```Bash
v4l2-ctl --device=/dev/video2 --list-formats-ext
```
Nos da información valiosa como las resoluciones y frame rates soportados por la cámara. Esto es muy importante a la hora de hacer aplicaciones con OpenCV.


**Nota**: Ctrl+Shift+V para previsualizar Markdown en VSC.
