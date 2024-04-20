## SDL2游戏编程指南

* [2D 射击游戏]()
* [2D 顶视角射击游戏] ()
* [2D 平台游戏]
* [精灵图集的使用]
* [使用矢量字体]()
* [2D 冒险类游戏]
* [小部件开发指引]
* [2D 竖屏射击游戏]
* [2D 跑酷与射击游戏]
* [Roguelik类游戏]
* [Lookups]
* [奖章（成就）系统开发指引] 
* [2D turn based strategy tutorial]
* [2D isometric game tutorial]
* [地图编辑]
* [Mission-based 2D shoot 'em up tutorial]
* [2D Santa game tutorial]
* [2D split screen game tutorial]

### 概述

本系列教程主要讲解如何用SDL2制作游戏。整个教程分成了多个部分，来让初学者能够循序渐进地学习，而不是一开始就被太多的内容搞晕。

注: 这些教程假设读者已经熟悉C语言，对如指针，使用CMake和Makefile等高级注意已经比较熟悉。
同时我们建议你按照顺序学习，因为前面会介绍一些后面会用到的前置知识。在学习之前，建议你先阅读wiki上[关于配置SDL2](https://wiki.libsdl.org/Installation)的内容。 

### 构建

#### Creating a 2D shoot 'em up

This tutorial will show how to create a simple 2D shoot 'em up, starting with opening a window, all the way to building a highscore table. If you're new to SDL2, this would be a good place to start.

1. Opening a window
2. Drawing the player
3. Moving the player
4. Firing
5. Refactoring
6. Enemies
7. Shooting enemies
8. Enemies fighting back!
9. Effects and background graphics
10. Sound and music
11. Bitmap fonts and scoring
12. Score pods
13. Highscore table (Part 1)
14. Highscore table (Part 2)
15. Title screen and finishing touches

 Creating a 2D top-down shooter

This tutorial will show how to create a simple top-down 2D shooter that we're going to call Battle Arena Donk! Mouse controls will be used extensively throughout.

Reading the mouse
Angles and rotation
Mouse buttons and shooting
Battling enemies
Scrolling the arena
Finishing touches
Creating a 2D platformer

Learn how to create a simple multi-scrolling 2D platformer, code-named Pete's Pizza Party.

Loading and displaying the map
Scrolling the map
Controlling the character
Interacting with entities
Moving platforms
Finishing touches
Creating a sprite atlas

In this tutorial, we'll demonstrate how to create and use a sprite atlas.

Preparing the files
Creating the atlas texture
Creating the atlas meta data
Using the atlas with SDL2
Rotating, scaling, blending, and colour modulation
Working with TTF fonts

In this tutorial, we'll demonstrate how to use SDL2 TTF for text rendering.

Basic font rendering
Creating a glyph atlas
Wrapping, aligning, and typewriter effect
Unicode support
Creating a simple 2D adventure game

Learn how to make a basic 2D adventure game.

Movement and map rendering
Map scrolling and collisions
Loading a map
Entity interactions, part 1
Inventory management
Entity interactions, part 2
Fog of war
Message boxes
Loading the dungeon
The Grumpy Goblin
The Cursed Maze
Vampire Bats!
The Escape Room
Finishing touches
Creating a basic widget system

Learn how to make a widget system, for use with in-game menus.

Basic non-functional menu
Actionable menu
Loading a widget set
Select widget
Slider widget
Text input widget
Control widget
In-game menu
Widget groups
Creating a 2D vertical shoot 'em up

Learn how to create a vertical 2D shoot 'em up, that includes power-ups and enemy attack patterns.

Setting up
Enemy attack patterns (first sequence)
Power-ups
Return fire!
Enemy attack patterns (full sequence)
Bosses
More power-ups
Enemy attack patterns (final sequence)
Finishing touches
Creating a 2D run and gun game

Learn how to create a 2D run and gun game, like Contra, Turrican, and Duke Nukem.

First steps
Aiming, shooting, and ducking
Destroying targets
Enemies
Basic map
Gameplay tweaks
Larger, scrolling map
Player health + power-ups
Keycards, doors, and other solid entities
Adding a quadtree
More gameplay tweaks
Player death + effects
A full level!
Game controller support
Finishing touches
Creating a roguelike

Learn how to create a simple roguelike.

Map generation
First monster
Combat
Adding the HUD
Monsters attacking!
A* Pathfinding
Items and inventory display
Using items
Equipping items
Comparing stats
XP and levelling
Stairs
More monsters, more loot!
Doors
Death and Highscores
Status effects
Saving
Loading
The Mouse King
Finishing touches
Creating a lookup system

A short tutorial on how to make a key-value lookup system.

Creating a lookup system
Creating an in-game achievement system

Learn how to create an achievement system, known as Medals.

Unlocking Medals
Integrating with gameplay
Saving progress
A full game!
Online functionality
Threading
Creating a simple 2D turn-based strategy game

A tutorial about how to create a 2D turn-based strategy game.

Basic unit control
Controlling multiple units
Limiting movement
AP (action point) handling
Enemies and simple AI
Combat #1: Player attacking
Combat #2: Weapons, accuracy, and damage
Combat #3: Feedback and effects
Combat #4: Line of sight
Combat #5: AI attacking
Handling player death
Item handling
Adding the camera
Expanding the HUD
Map generation
Slime pools
Lilac Ghost
Blue Ghost
Red Ghost
Green Ghost
Winning and losing
Smooth camera
Threaded map generation
Finishing touches
Making a 2D isometric game

A tutorial about how to create a 2D isometric game, in an old-school flip-screen style.

Drawing tiles
Selecting tiles
Adding entities
Adding Purple Guy
Walls and trees
Occlusion testing
Loading and traversing the map
Entities and items
Buttons and bridges
Simple lighting
Mini map
Finishing touches
Making a basic 2D map editor

A tutorial about how to create a basic 2D map editor.

Simple map editor
Tile selection
Entity selection
Scrolling and picking entities
Expanded UI and mini map
Making a mission-based 2D shoot 'em up

Learn how to create a mission and objective-based 2D multi-directional shoot 'em up.

Basic fighter control
Main guns
Adding enemies
Simple AI
Collectables
The HUD
Secondary weapon: Rockets
Secondary weapon: Homing missiles
Secondary weapon: Red beam
Secondary weapon: Mines
Secondary weapon: Shield
Objectives
Start / end screens
Start of intermission
Intermission: Planets
Intermission: Comms
Intermission: Shop (1/2)
Intermission: Shop (2/2)
Intermission: Stats
Intermission: Loading / Saving
Intermission: Options
Main game loop
Scripting
Mission: Training
Mission: Collect catnip
Mission: Bombers
Mission: Rescue POWs
Mission: SS Goodboy
Mission: The Gravlax (Boss)
Title screen
Finishing touches
Making a 2D Santa game

Learn how to create a simple Santa game to celebrate Xmas!

Scrolling
Houses
Chimneys
Santa's sleigh
Gifts and coal
Scoring
HUD
Game Over
Highscore table
Sacks
Enchanted Snowman #1
Enchanted Snowman #2
Snow
Hills and trees
Finishing touches
Making a 2D split screen game

A traditional 2D split screen two-player game, using SDL2's geometry functions.

Loading models
Steering and shooting
Loading Zone(s)
Ready Player Two
Split screen
Live. Die. Repeat.
Heads Up!
Live. Die. Repeat. And Repeat.
Particles and effects
Collectables
Gooooooooooooooal(s)
Spatial Grid, part 1
Spatial Grid, part 2
Aliens3
Zones (again)
Game options
Title screen
Finishing touches