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
