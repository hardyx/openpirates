openPirates by Scott Smith (Pickle)
	       @ pickle136@gmail_dot_com

About:
  openPirates is a fan game inspired by the classic game 'Sid Meier's Pirates!' and 'Pirates! Gold' by Microprose.
  The purpose of this project is to capture the original feeling of the original, but while doing so try to improve and refine
  gameplay. openPirates is also designed to be cross-platform and run on any system (any system that support SDL libraries).
  The project is also being designed to make game data user configurable, meaning users can create entirly different worlds.

Compile / Install:
  Refer to the INSTALL.TXT document

Controls:
  The game is setup to use the keyboard/mouse/joystick.
  (Note: the current system lacks a user interface which might be added sometime in the future. For now things are hardcoded.)

  Internal Event		Keyboard	Joystick	Mouse
    Up/Down/Left/Right		arrows		0-3		motion (cursor only)
    Action/Select		space		4		left button
    In-game Menu		escape		5

Gameplay:
  Refer to GAMEPLAY.TXT

License:
  Released under the GPLv3 license. The details of the license are in GPL.TXT

Contributions:
  Patches/Data/Gfx/Sfx/Bug reports are all welcome, although as the project lead I reserve the right to accept or reject
  any content provided. Anything that is submited is expected to have been released (or given permission) under GPL license.
  Write access to the source will most likely not be given (but not ruled out if the right person becomes involved)

Modifications/Data:
  openPirates is designed to allow as many parameters and settings to be user changeable. This will allow the user to create
  completely new worlds/nations/cities in the pirates gameplay theme.

  data.conf	: this file contains all the data for the openPirates world. Including nations, ships, cities, and any string data.
		  Warning: modifying things incorrectly could cause undesired results. For example the application expects the string
		  data to be in order and an exact number of strings. Removing one would shift all the string data. Be careful.

  options.conf	: this file contains platform setting such as resolution/sound/font settings. Although it contains some gameplay
		  options like number of waves/clouds.

  data/gfx's	: place graphics in the this location. Some graphics are in subfolders i.e ships. If the graphics are replaced
		  and contain more tiles than before remember to update the data.conf.

  data/sfx's	: place graphics in the this location.

  data/maps	: place maps in the this location. Be sure to update data.conf with tile coordinates, tiles sizes, and map names.

  data/font	: place any ttf fonts here and change names in the options.conf

Status:
  Much of the data structure and simulation data is in place.
  Map navgation is finished with the exception of wind physics.
  Major menus are almost complete
  Battle modes development has started
  Fencing Mode not compete
  Treasure Map system not compete
  Simulation AI system not compete

Credits:
  monotype corvisa font	: http://www.webpagepublicity.com (asked for permission, no response yet. Site described font as free.)
  gfx's/sfx's 		: hunt for gold project, http://huntforgold.sourceforge.net/home.html
  wave			: Badwolf (from gp32x.com)
  window border		: xnopasaranx (from gp32x.com)
  map tiles		: Evildragon (from gp32x.com)


