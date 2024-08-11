
#include <iostream>
#include <chrono>
#include <thread>

#include "../header/sim.h"
#include "../header/ix.h"
#include "../header/const.h"

const int Sim::numParticles = 10;

Sim::Sim() : options(Options()), container(Container(0.2f, 0, 0.0000001f))
{
    this->win.create(sf::VideoMode(SIZE_Y * SCALE, SIZE_X * SCALE), "Basic Fluid Simulation", sf::Style::Titlebar | sf::Style::Close);
}

Sim::~Sim() {}

void Sim::Setup() {}

void Sim::Run()
{
    this->Setup();
    sf::Vector2i previousMouse = sf::Mouse::getPosition(this->win);
    sf::Vector2i currentMouse = sf::Mouse::getPosition(this->win);

    while (this->win.isOpen())
    {
        sf::Event e;
        while (this->win.pollEvent(e))
        {
            switch (e.type)
            {
            case sf::Event::Closed:
                this->win.close();
                break;
            case sf::Event::KeyReleased:
                if (e.key.code == sf::Keyboard::Key::C)
                {
                    Color c = (this->options.GetColor() == Color::Default) ? Color::Hsb : (this->options.GetColor() == Color::Hsb) ? Color::Velocity
                                                                                                                                   : Color::Default;

                    this->options.SetColor(c);
                }
                break;
            default:
                break;
            }
        }

        switch (exampleType)
        {
        case TWO_FLUID:
            if (this->container.GetDensityPointer()[IX(1, 1, this->container.GetSizeX(), this->container.GetSizeY())] == 0)
            {
                this->container.AddDensity((SIZE_X / 2), 1, 500);
                this->container.AddDensity((SIZE_X / 2), SIZE_Y - 2, 500);
            }
            break;
        case ONE_FLUID_BASIC_CORNER:
            if (this->container.GetDensityPointer()[IX(1, 1, this->container.GetSizeX(), this->container.GetSizeY())] == 0)
                this->container.AddDensity(SIZE_X / 2, 1, 500);
            break;
        case ONE_FLUID_BASIC_CENTER_ALLDIR:
            if (this->container.GetDensityPointer()[IX(1, 1, this->container.GetSizeX(), this->container.GetSizeY())] == 0)
                this->container.AddDensity((SIZE_X / 2), (SIZE_Y / 2), 500);
            break;
        case ORIGINAL_FLUID:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                this->container.AddDensity(currentMouse.y / SCALE, currentMouse.x / SCALE, 200);
            break;
        default:
            break;
        };

        currentMouse = sf::Mouse::getPosition(this->win);

        float amountX = currentMouse.x - previousMouse.x;
        float amountY = currentMouse.y - previousMouse.y;

        switch (exampleType)
        {
        case TWO_FLUID:
            if (this->container.GetDensityPointer()[IX(1, 1, this->container.GetSizeX(), this->container.GetSizeY())] < 2)
            {
                this->container.AddVelocity(SIZE_X / 2, 2, 0, 10);
                this->container.AddVelocity(SIZE_X / 2, SIZE_Y - 3, 0, -10);
            }
            break;
        case ONE_FLUID_BASIC_CORNER:
            if (this->container.GetDensityPointer()[IX(1, 1, this->container.GetSizeX(), this->container.GetSizeY())] < 2)
                this->container.AddVelocity(SIZE_X / 2, 2, 0, 10);
            break;
        case ONE_FLUID_BASIC_CENTER_ALLDIR:
            if (this->container.GetDensityPointer()[IX(1, 1, this->container.GetSizeX(), this->container.GetSizeY())] < 2)
            {
                this->container.AddVelocity(SIZE_X / 2, SIZE_Y / 2 + 1, 0, 10);
                this->container.AddVelocity(SIZE_X / 2 + 1, SIZE_Y / 2, 10, 0);
                this->container.AddVelocity(SIZE_X / 2, SIZE_Y / 2 - 1, 0, -10);
                this->container.AddVelocity(SIZE_X / 2 - 1, SIZE_Y / 2, -10, 0);
            }
            break;
        case ORIGINAL_FLUID:
            this->container.AddVelocity(currentMouse.y / SCALE, currentMouse.x / SCALE, amountY / 10, amountX / 10);
            break;
        default:
            break;
        };

        previousMouse = currentMouse;

        this->container.Step();
        this->container.Render(this->win, this->options.GetColor());
        this->container.FadeDensity(SIZE_X * SIZE_Y);

        this->win.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_DELAY));
    }
}
