#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

class Block : public Drawable
{
public:
    Block(float t_x, float t_y, float t_width, float t_height);
    Block() = delete;
    ~Block() = default;

    void update();
    Vector2f getPosition();

    float left();
    float right();
    float top();
    float bottom();

    bool isDestroyed();
    void destroy();
    Vector2f getSize ();

private:
    virtual void draw(RenderTarget& target, RenderStates state) const override;
    RectangleShape  shape;
    bool destroyed {false};
};