#pragma once
#include "Counter.hpp"
#include "ParrotData.hpp"
#include "ParrotColor.h"

class Parrot
{
    const int length = 10;
    int index = 0;
    Counter counter{ 6 };
    Array<Texture> textures;
    Vec2 velocity;

public:
    RectF rect;
    bool hold = false;

public:
    Parrot() {}

    Parrot(Point pos, Array<Texture> textures)
        : rect(RectF(pos, 64)), textures(textures), velocity(Vec2(Random(-1.0, 1.0), Random(-1.0, 1.0))) { }

    Parrot& operator=(const Parrot& obj)
    {
        index = obj.index;
        counter.count = obj.counter.count;
        
        return *this;
    }

    void flipY()
    {
        velocity.y *= -1;
    }

    void flipX()
    {
        velocity.x *= -1;
    }

    void update()
    {
        counter.increment();

        if (counter.isRefresh())
        {
            index = (index + 1) % length;
        }

        if (hold)
        {
            rect.pos = Cursor::Pos() - rect.size / 2;
        }
        else
        {
            rect.pos.moveBy(velocity * Scene::DeltaTime() * 100);
        }

        bool isLeft = rect.tl().x <= 0,
            isRight = rect.br().x >= Scene::Width(),
            isTop = rect.tl().y <= 0,
            isBottom = rect.br().y >= Scene::Height();

        if (hold)
        {
            if (isLeft) rect.pos.x = 1;
            if (isTop) rect.pos.y = 1;

            if (isRight) rect.pos.x = Scene::Width() - rect.size.x - 1;
            if (isBottom) rect.pos.y = Scene::Height() - rect.size.y - 1;
        }
        else
        {
            if (isLeft || isRight)
            {
                flipX();
            }

            if (isTop || isBottom)
            {
                flipY();
            }
        }


        // TODO: debug
        rect.drawFrame();
    }

    void draw()
    {
        rect(textures[index]).draw();
    }
};