/*
 * This file is part of NumptyPhysics <http://thp.io/2015/numptyphysics/>
 * Coyright (c) 2015 Thomas Perl <m@thp.io>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#ifndef NUMPTYPHYSICS_APP_H
#define NUMPTYPHYSICS_APP_H

#include "Common.h"
#include "Config.h"
#include "Game.h"
#include "Scene.h"
#include "Levels.h"
#include "Canvas.h"
#include "Ui.h"
#include "Font.h"
#include "Dialogs.h"
#include "Event.h"

#include "thp_timestep.h"
#include "thp_format.h"
#include "petals_log.h"

class App : private Container
{
public:
  App(int argc, char** argv);
  ~App();
  const char* name();
  bool step();

private:
  void render();
  bool processEvent(ToolkitEvent &ev);
  virtual bool onEvent( Event& ev );

  int m_width;
  int m_height;
  bool m_quit;
  Window *m_window;
  thp::Timestep m_timestep;
};

#endif /* NUMPTYPHYSICS_APP_H */
