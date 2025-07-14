#pragma once
#include <opencv2/core.hpp>
#include <vector>

class VideoCircularBuffer {
public:
    VideoCircularBuffer(float durantionSeconds, int fps);
    ~VideoCircularBuffer();

    void addFrame(const cv::Mat& frame);
    void getFrames(std::vector<cv::Mat>& frames) const;
    cv::Mat getFrame(size_t index) const;
    cv::Mat getNewestFrame() const;
    cv::Mat getOldestFrame() const;
    size_t size() const;
    size_t capacity() const;

    private:
    std::vector<cv::Mat> buffer_;
    int capacity_;
    int head_;
    int tail_;
};