#ifndef BACKEND_HPP
#define BACKEND_HPP
#include <QObject>

class Backend : public QObject {
    Q_OBJECT
    
public:
    explicit Backend(QObject* parent = nullptr);
    ~Backend();

signals:

public slots:
    void callMe();
};

#endif
