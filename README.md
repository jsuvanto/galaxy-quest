# galaxy-quest

A space game made for a programming course.

This game was done as a pair assignment for a programming course at TUT. The second author of this repository is @moptim.

The files under Student/ and StudentTests/ are done by us. The files under Course/ and CourseTests/ are made by the course personnel.

## Features 
The assignment consists of the following required and optional features:

### Required
- user interface
- instant ship movement
- the Galaxy class, which implements IGalaxy, that must pass the course's unit tests
- turn based gameplay
- the Statistics class, which implements IStatistics, and unit tests for it
### Optional
- recovery from errors in initiation file
- several dialogs
- game progress and statistics shown on screen
- interaction between player and NPC ships
- ship movement at a constant speed
- scrollable map
- custom engine and a ship that uses it
- high score list

## Classes

The following classes are inherited from course code:
- EventHandler
- Galaxy
- Statistics
- PlayerShip

The following classes are self-made:
- MainWindow
- GalaxyMap
- InstructionsDialog
- StarSystemGraphic
- WarpDrivePlusPlus
- HighScoreList
