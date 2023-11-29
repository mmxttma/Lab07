// Lab07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
    // Create our window and world with gravity 0,1
    RenderWindow window(VideoMode(800, 600), "Bounce");
    World world(Vector2f(0, 1));

    // Create the ball
    PhysicsCircle ball;
    ball.setCenter(Vector2f(400, 325));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);
    ball.applyImpulse(Vector2f(0, 0.15));
    // Create the walls
    PhysicsRectangle wall1, wall2, wall3;
    wall1.setSize(Vector2f(800, 20));
    wall1.setCenter(Vector2f(400, 10));
    wall1.setStatic(true);
    world.AddPhysicsBody(wall1);

    wall2.setSize(Vector2f(20, 1160));
    wall2.setCenter(Vector2f(10, 0));
    wall2.setStatic(true);
    world.AddPhysicsBody(wall2);

    wall3.setSize(Vector2f(20, 1160));
    wall3.setCenter(Vector2f(790, 0));
    wall3.setStatic(true);
    world.AddPhysicsBody(wall3);

    PhysicsRectangle middle;
    middle.setSize(Vector2f(100, 40));
    middle.setCenter(Vector2f(400, 295));
    middle.setStatic(true);
    world.AddPhysicsBody(middle);
    int bangCount(0);
    middle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
        cout << "bang " << bangCount << endl;
        bangCount++;
        if (bangCount == 2) {
            exit(0);
        }
        };

    // Create the floor
    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);
    int thudCount(0);
    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
        };
    wall1.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
        };
    wall2.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
        };
    wall3.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
        };
    Clock clock;
    Time lastTime(clock.getElapsedTime());
    while (true) {
        // calculate MS since last frame
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }
        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(floor);
        window.draw(wall1);
        window.draw(wall2);
        window.draw(wall3);
        window.draw(middle);
        window.display();
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
