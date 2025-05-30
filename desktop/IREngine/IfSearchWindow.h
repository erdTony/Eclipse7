#pragma once

#include <QMainWindow>

#include <QPixmap>

class QGridLayout;
class QHBoxLayout;
class QImage;
class QLabel;
class QSize;
class QTextEdit;
class QWidget;

class IfSearchApplication;

class IfSearchWindow : public QMainWindow
{
    Q_OBJECT
public: // ctors
    explicit IfSearchWindow(IfSearchApplication *ifsApp = nullptr);

public slots:
    void setup();
    void clearPixmaps();
    void clearFaces();
    void setMarked(const QImage &img);
    void setDetect(const QImage &img);
    void appendFace(const QImage &faceImage);
    void appendEyes(const QImage &eyeLImage,
                    const QImage &eyeRImage);
    void setMessage(const QString &s);

signals:

public: // const

public: // non-const

public: // pointers
    IfSearchApplication * app();

public: // static
    static int maxFrameDim();
    static QSize faceThumbSize();
    static QPixmap scaledPixmap(const QImage &img, const int dim);

private:
    IfSearchApplication * mpIfsApp=nullptr;
    QWidget * mpCentralWidget=nullptr;
    QGridLayout * mpCentralGrid=nullptr;
    QGridLayout * mpFrameGrid=nullptr;
    QGridLayout * mpFaceLayout=nullptr;
    QPixmap mMarkedPixmap;
    QPixmap mDetectPixmap;
    QLabel * mpMarkedLabel;
    QLabel * mpDetectLabel;
    QList<QLabel *> mFaceLabels;
    QList<QPixmap> mFacePixmaps;
    QList<QPixmap> mEyesPixmaps;
    QList<QPixmap> mNormPixmaps;
    QTextEdit * mpMessageWidget=nullptr;
};

inline IfSearchApplication *IfSearchWindow::app() { Q_ASSERT(mpIfsApp); return mpIfsApp; }
inline int IfSearchWindow::maxFrameDim() { return 512; }
inline QSize IfSearchWindow::faceThumbSize() { return QSize(128, 128); }


