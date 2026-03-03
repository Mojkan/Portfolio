# 2D Game Engine with SDL3 and C++

## About the engine and development
Making a 2D game engine is what I chose for my final year project while studying game programming. I have always been fascinated by game engines and this was a create opportunity for me to learn much more about them. 

This project was around 6-7 weeks, but I had already spent a couple months beforehand learning C++ and a bit of SDL2 on my own. Because of that, working with SDL3 did not feel unfamiliar. 

The game engine turned out better than what I anticipated. It currently supports several fundamental systems of a engine, including game objects, scenes, collision, audio, input, components and more, which I will list below. While developing the engine, I also created a very simple prototype game for testing and development purposes. It is available for download below.

Below, you can read about the engine, which I have divided into different sections: engine structure and architecture, game objects and components, scenes, optimizations and extras.

VIEW THE FULL PROJECT FILES HERE!: 

DOWNLOAD THE PROTOTYPE GAME HERE!: 

## Core features

- Game objects and scene system

- Support for all resolutions, Widescreen, Fullscreen and Vsync

- Engine components: Transform, UITransform, static and dynamic BoxCollider, Button and Sprite.

- Engine managers: AudioManager, PhysicsManager, GameObjectManager, SceneManager, TextureManager, RendererManager, and WindowManager

- Utilities: Render groups, tags, time system, and a custom Vector2D class

## Engine structure and architecture
The engine and structure was something that I had to rework many times during this development. In the beginning it feels easy and convenient to place a lot of logic on the engine class, but you soon realise that it becomes spaghetti code. I therefore ended up with this solution, a engine class that owned, controlled and updated all the systems. It was also responsible for creating them and destroying and resetting them. The only class that was now static was the engine class itself. This system made it very easy to track the startup, the update loop and the shutdown of the engine.

The engine is started by the main.cpp file by creating an instance of the Engine class where you can specify name, resolution, fullscreen and vsync. I wanted to have a proper file for configuring settings for the engine, but ran out of time during the development. The engine starts with creating all the systems in the correct order and when done it begins it first frame by saving all the input from the operating system, then it updates all the game objects and components. When that is done it then renders everything and also update time. When the user then quits it just resets all the system and shuts down.

I have not studied engine architecture before, this was a lot trial and error, research and what felt easy to use. <br/>
[View the full code →](Scripts/)

<div align="center">
  <img src="Images/Engine1.png" width="50%" />
  <img src="Images/Engine2.png" width="40%" />
</div>

---

## Game Objects and components
TEST
[View the full code →]()

<div align="center">
  <img src="" width="100%" />
</div>

---

## Scenes
TEST
[View the full code →]()

<div align="center">
  <img src="" width="100%" />
</div>

---

## Optimizations and extras
TEST
[View the full code →]()

<div align="center">
  <img src="" width="100%" />
</div>

---