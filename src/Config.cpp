/*
 * This file is part of NumptyPhysics <http://thp.io/2015/numptyphysics/>
 * Coyright (c) 2008, 2009 Tim Edmonds <numptyphysics@gmail.com>
 * Coyright (c) 2012, 2014, 2015 Thomas Perl <m@thp.io>
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

#include "Config.h"

#include "petals_log.h"

#include <sstream>
#include <fstream>


const Rect BOUNDS_RECT( -WORLD_WIDTH/4, -WORLD_HEIGHT,
			WORLD_WIDTH*5/4, WORLD_HEIGHT );

std::string Config::findFile(const std::string &name)
{
    std::string global_name(OS->globalDataDir() + Os::pathSep + name);
    if (OS->exists(global_name)) {
        return global_name;
    }

    return name;
}

Blob *
Config::readBlob(const std::string &name)
{
    std::string filename = findFile(name);
    std::ifstream is(filename.c_str(), std::ios::in);

    if (!is.is_open()) {
        LOG_FATAL("Could not open file '%s'", name.c_str());
        exit(1);
    }

    is.seekg(0, is.end);
    size_t length = is.tellg();
    is.seekg(0, is.beg);

    char *buffer = new char [length];

    is.read (buffer, length);
    is.close();

    return new Blob(buffer, length);
}

std::pair<bool,std::string>
Config::readFile(const std::string &name)
{
    std::string filename = findFile(name);
    std::ifstream is(filename.c_str(), std::ios::in);

    if (!is.is_open()) {
        return std::make_pair(false, "");
    }

    is.seekg(0, is.end);
    size_t length = is.tellg();
    is.seekg(0, is.beg);

    char *buffer = new char [length+1];
    buffer[length] = '\0';

    is.read (buffer,length);
    is.close();
    std::string result = buffer;
    delete[] buffer;

    return std::make_pair(true, result);
}

std::string
Config::defaultLevelPath()
{
    return OS->globalDataDir();
}

std::string
Config::userLevelFileName(const std::string &name)
{
    return OS->userDataDir() + Os::pathSep + name;
}

std::string
Config::userRecordingCollectionDir(const std::string &name)
{
    return OS->userDataDir() + Os::pathSep + "Recordings" + Os::pathSep + name;
}

std::string
Config::joinPath(const std::string &dir, const std::string &name)
{
    return dir + Os::pathSep + name;
}

std::string
Config::baseName(const std::string &name)
{
    size_t sep = name.rfind(Os::pathSep);
    return (sep == std::string::npos) ? name : name.substr(sep);
}
