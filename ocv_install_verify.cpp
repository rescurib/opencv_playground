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