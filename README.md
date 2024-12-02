#  Run and Collect  — 3D Third-Person Adventure (Unreal Engine 5)

## Gameplay

- **Objective**: Gather as many coins as possible without being caught or running out of energy.
- **Challenges**:
  - Avoid the catchers who are chasing you around the map.
  - Keep an eye on your energy level, which depletes over time.
- **Power-ups**:
  - Collect **lightning bolts** to recharge your energy.
- **Boundaries**:
  - Stay within the limits of the map — falling off results in a game over.

## Requirements

- **Unreal Engine 5 (version 5.4.4 or later)
- **Operating System**: Windows 10/11, macOS, or Linux

## Installation

1. Download and install [Unreal Engine](https://www.unrealengine.com/download).
2. Clone this repository or download the project as a ZIP archive.

```bash
git clone https://github.com/Kindiakova/UE5_RunAndCollect.git
```

3. Open the project in Unreal Engine 5:
- Launch Unreal Engine 5.
- Open the project by selecting the .uproject file located in the project root directory.

## Project Structure
Sourse/ - contain headers and sourse c++ files
Content/ Blueprints — Contains the game's core logic and mechanics.

Characters — Stores character models and animations.

LevelPrototyping — Contains assets for designing level layouts.

Levels — Game levels and map files.

ThirdPerson — Third-person blueprint, game mode, and actions assets.

UI — User interface elements.

## Controls
- W, A, S, D — Move the character.
- Arrow Keys — Alternative for character movement.
- Spacebar — Jump.
- Mouse — Control the camera.

## Building the Project for a Platform

1. Open the project in Unreal Engine 5.
2. Go to File → Package Project → (Windows / macOS / Linux).
3. Select the build configuration:
4. Development — For testing with minimal optimizations.
5. Shipping — For the final version of the game.
6. Choose the directory where the build should be saved, and click Package.
7. Once the build is complete, you will find an executable file and the necessary resources in the specified folder.

## How to Customize the Game

You can customize some gameplay aspects by modifying blueprint parameters:

1. Adjust Energy Decay Rate

 - Open the blueprint CoinPlayer_BP.

 - Locate the parameter Power_Treshold.

 - Adjust the value to control the speed of energy reduction.

2. Modify Spawn Frequencies

 - Open the blueprint CoinMan_GameMode_BP.

 - Locate the parameters:

 - Spawn_Coin_Freq - Adjust the frequency of coin spawns.

 - Spawn_Charger_Freq - Adjust the frequency of charger spawns.

## Gameplay video 

[![Watch the video](https://img.youtube.com/vi/kJa94ESR6t4/0.jpg)](https://youtu.be/kJa94ESR6t4)

## Assets

- **[Full Map](https://www.fab.com/listings/19067e98-5f3f-4cb0-aecb-08f985f87b6c)** — The complete city map for the game.
