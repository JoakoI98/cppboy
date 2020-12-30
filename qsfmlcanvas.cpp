#include "qsfmlcanvas.h"

QSFMLCanvas::QSFMLCanvas(QWidget *parent, const QPoint &Position, const QSize &Size, unsigned int FrameTime): QWidget       (parent), myInitialized (false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);
    // Setup the widget geometry
    move(Position);
    resize(Size);
    // Setup the timer
    myTimer.setInterval(FrameTime);
}

QSFMLCanvas::QSFMLCanvas(QWidget *parent, const QSize &Size, unsigned int FrameTime): QWidget       (parent), myInitialized (false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);
    // Setup the widget geometry
    resize(Size);
    // Setup the timer
    myTimer.setInterval(FrameTime);
}

QSFMLCanvas::QSFMLCanvas(QWidget *parent, const QPoint &Position, unsigned int FrameTime): QWidget       (parent), myInitialized (false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);
    // Setup the widget geometry
    move(Position);
    // Setup the timer
    myTimer.setInterval(FrameTime);
}

QSFMLCanvas::QSFMLCanvas(QWidget *parent, unsigned int FrameTime): QWidget       (parent), myInitialized (false)
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);
    // Setup the timer
    myTimer.setInterval(FrameTime);
}

QSFMLCanvas::~QSFMLCanvas() {}

void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        // Create the SFML window with the widget handle
        RenderWindow::create(reinterpret_cast<sf::WindowHandle>(winId()));
        // Let the derived class do its specific stuff
        OnInit();
        // Setup the timer to trigger a refresh at specified framerate
        connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
        myTimer.start();
        myInitialized = true;
    }
}
QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}
void QSFMLCanvas::paintEvent(QPaintEvent*)
{
// Let the derived class do its specific stuff
    OnUpdate();
// Display on screen
    RenderWindow::display();
}
