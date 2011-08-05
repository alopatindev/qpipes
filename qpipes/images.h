#ifndef IMAGES_H
#define IMAGES_H

#include <QImage>
#include <QString>
#include <QMap>

class Images
{
    QMap<QString, QImage *> images;

public:
    QImage *getImage(bool left, bool right, bool top, bool bottom,
                     bool light = false);
    Images();
    ~Images();
};

#endif
