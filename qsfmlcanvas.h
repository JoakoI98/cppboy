#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QTimer>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
public:
    explicit QSFMLCanvas(QWidget *parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 0);
    explicit QSFMLCanvas(QWidget *parent, const QSize& Size, unsigned int FrameTime = 0);
    explicit QSFMLCanvas(QWidget *parent, const QPoint& Position, unsigned int FrameTime = 0);
    explicit QSFMLCanvas(QWidget *parent, unsigned int FrameTime = 0);

    virtual ~QSFMLCanvas();

private:
    virtual void showEvent(QShowEvent*);
    virtual QPaintEngine* paintEngine() const;
    virtual void paintEvent(QPaintEvent*);
    virtual void OnInit() = 0;
    virtual void OnUpdate() = 0;
    QTimer myTimer;
    bool myInitialized;

};


class MyCanvas : public QSFMLCanvas
{
    public :
    MyCanvas(QWidget* parent, const QPoint& Position, const QSize& Size): QSFMLCanvas(parent, Position, Size){}
    MyCanvas(QWidget* parent, const QSize& Size): QSFMLCanvas(parent, Size){}
    MyCanvas(QWidget* parent, const QPoint& Position): QSFMLCanvas(parent, Position){}
    MyCanvas(QWidget* parent): QSFMLCanvas(parent){}
    void OnInit(){}
    void OnUpdate(){
        RenderWindow::clear(sf::Color(0, 128, 0));
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        draw(shape);
    }
};


#endif // QSFMLCANVAS_H
