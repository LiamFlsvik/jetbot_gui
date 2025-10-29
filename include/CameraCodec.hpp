
#include <QImage>
#include <opencv2/imgcodecs.hpp>

namespace CameraCodec {
    //OpenCV image to QImage
    inline QImage decode_opencv_image(const std::vector<uchar> &encoded_frame){
    cv::Mat frame_ = cv::imdecode(encoded_frame,-1);
    QImage img = QImage(frame_.data, frame_.cols,frame_.rows, QImage::Format_RGB888).rgbSwapped();
    return img;

    }

}