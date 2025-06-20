# Experimentos y notas sueltas sobre OpenCV

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
# los flags de librerías (para g++)
pkg-config --cflags opencv4
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
g++ ocv_install_verify.cpp -IC:/msys64/ucrt64/include/opencv4 -LC:/mysys2/ucrt64/bin -lopencv_core -lopencv_imgproc -lopencv_highgui -o ocv_install_verify 
```


**Nota**: Ctrl+Shift+V para previsualizar Markdown en VSC.
