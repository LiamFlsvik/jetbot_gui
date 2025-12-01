#include "VideoProvider.hpp"
#include <iostream>
VideoProvider::VideoProvider(): QQuickImageProvider(QQuickImageProvider::Image){
    m_frame_ = QImage(1920,1080,QImage::Format_RGB32);
    m_frame_.fill(QColor("black"));
}

    QImage VideoProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize){
            QMutexLocker locker(&mutex_);
            //std::cout << "[VideoProvider] requestImage called" << std::endl;
            return m_frame_;
    }

    void VideoProvider::updateFrame(const QImage frame){
        QMutexLocker locker(&mutex_);
        if (frame.isNull()) {
        std::cout << "[VideoProvider] updateFrame:frame was null" << std::endl;
        } else {
            m_frame_ = frame;
            std::cout << "[VideoProvider] updateFrame:frame updated!\n";
        }
    }