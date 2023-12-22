#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Ball : public Drawable
{
public:
    Ball(float t_x, float t_y);
    Ball() = delete;
    ~Ball() = default;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    Vector2f getPosition();

    void update();
    float left();
    float right();
    float top();
    float bottom();
private:
    CircleShape shape;
    const float ballRadius { 10.0f };
    const float ballVelocity {4.0f};
    Vector2f velocity {ballVelocity, ballVelocity};
    void draw(RenderTarget &target, RenderStates state) const override;
};