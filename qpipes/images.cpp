#include "images.h"

QImage *Images::getImage(bool left, bool right, bool top, bool bottom,
                         bool light)
{
    QString fileName = QString::number(left) +
                       QString::number(right) +
                       QString::number(top) +
                       QString::number(bottom) +
                       QString::number(light) + ".png";

    QImage *image = images[fileName];

    if (image == 0) {
        image = new QImage(":/" + fileName);
        images[fileName] = image;
    }

    return image;
}

Images::Images()
{
}

Images::~Images()
{
    qDeleteAll(images.begin(), images.end());
    images.clear();
}
