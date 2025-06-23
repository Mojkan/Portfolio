# Ruin

## Game Description

In *Ruin*, you must salvage the broken body of a goddess whose sacred domain was desecrated by imperialists from distant lands. This caused her heart to fill with hatred, and she unleashed a great plague upon the world.

Your mission is to enter the forgotten temple, discover her scattered remains, and reassemble her to restore the peace that was lost.

In *Ruin*, you will:
- Interact with mysterious objects
- Explore an ancient temple
- Solve puzzles
- Avoid an enemy

## My main contributions as a Game Programmer

- Implemented an adjustable third-person camera system  
- Created physics-based movable puzzle blocks  
- Developed rotating lever mechanics for the clock puzzle  
- Built an inventory system for collecting keys and items

## The player camera
The third person camera was one of the more difficult things to implement to this game. The camera has the ability to avoid walls, is snappy but have can smoothly follow the player at the same time. It can also be very close to walls or the player without clipping through.

The camera avoids walls by raycasting from the player to the desired position and applying an offset based on the normal of the impact point. By doing this the camera will never clip throught the wall and can easily be applied to any type of object by giving them a layer.

The camera can also handle tight corners where the camera comes close to the player. This is solved by having a focus point further away behind the player, the camera will still always focus on the player but it wont become jittery if the player comes very close.

<div align="center">
  <img src="Images/ruincamera1.gif" width="45%" />
  <img src="Images/ruincamera2.gif" width="45%" />
</div>

## The puzzle blocks
