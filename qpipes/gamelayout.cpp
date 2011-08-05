#include "gamelayout.h"

#include "pipeimage.h"
#include <QTime>

void GameLayout::addPipe(int x, int y, CellState state,
                         bool rotatable, bool randomRotation)
{
    if (field[x][y] != free || state == free)
        return;

    bool left, right, top, bottom;
    switch (state) {
        case angle:
            left = 1; right = 0; top = 1; bottom = 0;
            break;

        case flat:
            left = 1; right = 1; top = 0; bottom = 0;
            break;

        case begin:
            left = 0; right = 0; top = 0; bottom = 1;
            break;

        case end:
            left = 0; right = 0; top = 1; bottom = 0;
            break;

        default:
            left = 0; right = 0; top = 0; bottom = 0;
            break;
    }

    pipeImages[x][y]->setSides(left, right, top, bottom);

    if (randomRotation)
        pipeImages[x][y]->rotateRandom();

    pipeImages[x][y]->setRotatable(rotatable);
    QGridLayout::addWidget(pipeImages[x][y], y, x);
    field[x][y] = state;
}

void GameLayout::addPipeLine(int x, int y, int size,
                             Qt::Orientations orientation,
                             bool rotatable,
                             bool randomRotation)
{
    int i;

    if (orientation == Qt::Horizontal)
        for (i = x; i < x+size; ++i)
            addPipe(i, y, flat, rotatable, randomRotation);
    else
        for (i = y; i < y+size; ++i)
            addPipe(x, i, flat, rotatable, randomRotation);
}

inline void GameLayout::pathBegin(int x, int y)
{
    xBegin = x; yBegin = y;
    addPipe(x, y, begin, false, false);
}

inline void GameLayout::pathEnd(int x, int y)
{
    addPipe(x, y, end, false, false);
}

inline void GameLayout::randomizeField()
{
    int i, j;

    for (i = 0; i < width; ++i)
        for (j = 0; j < height; ++j)
            addPipe(i, j, (CellState)(qrand() % (flat + 1)),
                    true, true);
}

inline void GameLayout::generateField()
{
    int x = 1 + qrand() % (width-2), y = 0;
    int lastX, lastY, size;

    pathBegin(x, y);
    ++y;

    while (y < height-1) {
        lastX = x; lastY = y;
        addPipe(x, y, angle);

        size = 1 + qrand() % (width/2);
        if (x > width/2) {
            if (size-x < 0)
                size = x;
            x -= size;
            addPipeLine(x+1, y, size, Qt::Horizontal);
        } else {
            if (size+x > width-1)
                size = width-1 - x;
            x += size;
            addPipeLine(lastX, lastY, size, Qt::Horizontal);
        }
        addPipe(x, y, angle);

        size = 1 + qrand() % (height/4);
        if (size+y > height-1)
            size = height-1 - y;
        y += size;
        addPipeLine(x, lastY, size, Qt::Vertical);
    }
    pathEnd(x, height-1);

    randomizeField();
}

void GameLayout::holdField()
{
    int i, j;

    for (i = 0; i < width; ++i)
        for (j = 0; j < height; ++j)
            pipeImages[i][j]->setRotatable(false);
}

void GameLayout::clearField()
{
    int i, j;

    for (i = 0; i < width; ++i) {
        for (j = 0; j < height; ++j)
            delete pipeImages[i][j];
        delete pipeImages[i];
    }
    delete pipeImages;
}

void GameLayout::prepareField(int width, int height)
{
    firstCheckStep = true; way = toBottom;
    this->width = width; this->height = height;

    field = new CellState*[width];
    pipeImages = new PipeImage**[width];

    int i, j;
    for (i = 0; i < width; ++i) {
        field[i] = new CellState[height];
        pipeImages[i] = new PipeImage*[height];

        for (j = 0; j < height; ++j) {
            pipeImages[i][j] = new PipeImage(images);
            field[i][j] = free;
        }
    }

    generateField();
}

GameLayout::Way GameLayout::getNextWay(int x, int y)
{
    if (way != toLeft && pipeImages[x][y]->getRight())
        return toRight;
    if (way != toRight && pipeImages[x][y]->getLeft())
        return toLeft;
    if (way != toBottom && pipeImages[x][y]->getTop())
        return toTop;
    if (way != toTop && pipeImages[x][y]->getBottom())
        return toBottom;
}

void GameLayout::checkStep()
{
    static int x, y;

    if (firstCheckStep) {
        x = xBegin; y = yBegin; firstCheckStep = false;
        pipeImages[x][y]->light();
        return;
    }

    way = getNextWay(x, y);

    switch (way)
    {
        case toLeft:
            --x;
            if (x < 0 || !pipeImages[x][y]->getRight()) {
                emit fail(); return;
            }
            break;
        case toRight:
            ++x;
            if (x > width-1 || !pipeImages[x][y]->getLeft()) {
                emit fail(); return;
            }
            break;
        case toTop:
            --y;
            if (y < 0 || !pipeImages[x][y]->getBottom()) {
                emit fail(); return;
            }
            break;
        case toBottom:
            ++y;
            if (y > height-1 || !pipeImages[x][y]->getTop()) {
                emit fail(); return;
            }
            break;
    }

    pipeImages[x][y]->setRotatable(false);
    pipeImages[x][y]->light();

    if (field[x][y] == end)
        emit win();

    if (field[x][y] == free)
        emit fail();
}

GameLayout::GameLayout(QWidget *parent) : QGridLayout(parent)
{
    setSpacing(0);
    images = new Images;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
}

GameLayout::~GameLayout()
{
}
