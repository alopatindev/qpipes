#ifndef GAMELAYOUT_H
#define GAMELAYOUT_H

#include <QGridLayout>
#include <QImage>
#include "images.h"
#include "pipeimage.h"

const int DEFAULT_WIDTH = 18;
const int DEFAULT_HEIGHT = 10;

class GameLayout : public QGridLayout
{
    Q_OBJECT

    Images *images;
    PipeImage ***pipeImages;

    int width, height;
    enum CellState {free, angle, flat, begin, end};
    CellState **field;

    enum Way {toLeft, toRight, toTop, toBottom};
    Way way;
    int xBegin, yBegin;
    bool firstCheckStep;

    void addPipe(int x, int y, CellState state,
                 bool rotatable = true,
                 bool randomRotation = true);

    void addPipeLine(int x, int y, int size,
                     Qt::Orientations orientation = Qt::Horizontal,
                     bool rotatable = true,
                     bool randomRotation = true);

    inline void pathBegin(int x, int y);
    inline void pathEnd(int x, int y);

    inline void randomizeField();
    void generateField();
    Way getNextWay(int x, int y);

public slots:
    void checkStep();

signals:
    void fail();
    void win();

public:
    void holdField();
    void clearField();
    void prepareField(int width, int height);

    int getWidth() const { return width; };
    int getHeight() const { return height; };

    bool checkPath() const;

    GameLayout(QWidget *parent = 0);
    ~GameLayout();
};

#endif
