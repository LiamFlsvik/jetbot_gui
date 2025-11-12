#include <QQuickImageProvider>
#include <QImage>
#include <QMutex>

#include <opencv2/opencv.hpp>


class VideoProvider : public QQuickImageProvider {
    public:
        VideoProvider();

        virtual QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    
        void updateFrame(const QImage frame);

    private:
        QImage m_frame_;
        QMutex mutex_;
        
};