#include "pipeimage.h"

#include <QPainter>

PipeImage::~PipeImage()
{
}

void PipeImage::rotate(bool clockwise)
{
    if (!rotatable)
        return;

    if (clockwise)
        setSides(bottom, top, left, right);
    else
        setSides(top, bottom, right, left);
}

void PipeImage::rotateRandom()
{
    int count = qrand() % MAX_RANDOM_ROTATIONS;
    for (int i = 0; i <= count; ++i)
        rotate();
}

void PipeImage::setSides(bool left, bool right, bool top, bool bottom)
{
    this->left = left; this->right = right;
    this->top = top; this->bottom = bottom;

    image = images->getImage(left, right, top, bottom);
    setMinimumSize(image->width(), image->height());
    update();
}

void PipeImage::light()
{
    image = images->getImage(left, right, top, bottom, true);
    update();
}

void PipeImage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), *image);
}

void PipeImage::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
            rotate(false);
            break;
        case Qt::RightButton:
            rotate();
            break;
        default:
            break;
    }
}
