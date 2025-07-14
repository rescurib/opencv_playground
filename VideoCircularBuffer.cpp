#include "VideoCircularBuffer.h"

FrameCircularBuffer::FrameCircularBuffer(float durationSeconds, int fps)
{
    if(fps <= 0)
    {
        fps = 1;
    }

    capacity_ = static_cast<int>(std::round(durationSeconds * fps));

    if(capacity_ <= 0)
    {
        capacity_ = 1; // Al menos un frame debe ser almacenado
    }

    buffer_.resize(capacity_);
    head_ = 0;
    tail_ = 0;
}

FrameCircularBuffer::~FrameCircularBuffer()
{
    // No es necesario liberar memoria explícitamente, std::vector lo maneja automáticamente
}

void FrameCircularBuffer::addFrame(const cv::Mat& frame)
{
    buffer_[head_] = frame.clone();  // Clonar el frame para evitar problemas de referencia
    head_ = (head_ + 1) % capacity_; // Mover el head al siguiente índice

    if(head_ == tail_) // Si el buffer está lleno, mover tail
    {
        tail_ = (tail_ + 1) % capacity_;
    }
}

std::vector<cv::Mat> FrameCircularBuffer::getFrames(std::vector<cv::Mat>& frames) const
{
    frames.clear();
    int index = tail_;
    while(index != head_)
    {
        frames.push_back(buffer_[index]);
        index = (index + 1) % capacity_;
    }
}