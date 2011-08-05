#ifndef PIPEIMAGE_H
#define PIPEIMAGE_H

#include "images.h"
#include <QWidget>
#include <QImage>

const int MAX_RANDOM_ROTATIONS = 20;

class PipeImage : public QWidget
{
    Images *images;
    QImage *image;
    bool left, right, top, bottom, rotatable;

public:
    PipeImage(Images *images,
              bool left=1, bool right=1, bool top=0, bool bottom=0,
              bool rotatable = true) :
        images(images), left(left), right(right), top(top), bottom(bottom),
        rotatable(rotatable)
    {
        setSides(left, right, top, bottom);
    }
    ~PipeImage();

    void setRotatable(bool rotatable = true) { this->rotatable = rotatable; }
    void rotate(bool clockwise = true);
    void rotateRandom();
    void setSides(bool left, bool right, bool top, bool bottom);
    void light();

    bool getLeft() const { return left; }
    bool getRight() const { return right; }
    bool getTop() const { return top; }
    bool getBottom() const { return bottom; }

protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif
