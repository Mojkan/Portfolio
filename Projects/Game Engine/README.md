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
The engine structure was something that I had to rework many times during this development. In the beginning it feels easy and convenient to place a lot of logic inside the engine class, but you soon realise that it becomes very difficult to maintain. I therefore ended up with this solution where the engine class owns, controls and updates all the subsystems. It is also responsible for creating, destroying and resetting them. The only static part of the system is the engine class itself, which provides global access to the subsystems. This system made it much easier to manage and track the startup, the update loop and the shutdown of the engine.

The engine is started by the main.cpp file by creating an instance of the Engine class where you can specify window title, resolution, fullscreen and vsync. I originally wanted to implement a dedicated configuration file for engine settings, but I ran out of time during development. 

The engine starts with creating all the systems in the correct order. When that is done, it starts its main loop by saving all the input from the operating system, then it updates all the managers for game objects and scenes. When that is done it then renders everything and also updates the time system. When the user quits it resets and shuts down all the subsystems in reverse order.

I have not studied engine architecture before, so much of this was trial and error, research and what felt easy to use. <br/>
[View the full code for this part here!→](Scripts/)

<div align="center">
  <img src="Images/Engine2.png" width="40%" />
  <img src="Images/Engine1.png" width="50%" />
</div>

---

## Game Objects and components
For this game engine I choose to work with game objects and a component system, alot of it inspired by Unity engine. I chosed it because I had limited amount of time and didn't have enough understanding on how I could implement a ECS at or both. In afterhand choosing a game object component system was difficult enough when developing a game engine for the first time and was a perfect choice.

The 

[View the full code →]()

<div align="center">
  <img src="Gameobject1.png" width="100%" />
</div>
<div align="center">
  <img src="Gameobject2.png" width="50%" />
  <img src="Gameobject2.png" width="50%" />
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