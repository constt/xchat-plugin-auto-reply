/*
  Simple and almost useless auto reply plugin for xchat.

  Copyright (C) 2010 Thomas Trapp; mailto: git@thomastrapp.com

  "Buggy Bawkses" is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, 
  Boston, MA  02110-1301, USA.

  See LICENSE for details.
*/

#include <string>
#include <xchat/xchat-plugin.h>
#include "string.h"

#define PNAME "AutoReply"
#define PDESC "Auto replies to a certain word"
#define PVERSION "0.1"

static xchat_plugin *ph;
static bool enabled = 1;
static std::string trigger("");
static std::string answer("");
static std::string channel("");

static int autoreply_filter_cb(char *word[], void *userdata)
{
  if( enabled && strcmp(xchat_get_info(ph, "channel"), channel.c_str()) == 0 )
  {
    if( strcasestr(word[2], trigger.c_str()) != NULL )
    {
      xchat_commandf(ph, "SAY %s", answer.c_str());
    }
  }

  return XCHAT_EAT_NONE;
}

static int autoreply_toggle_cb(char *word[], char *word_eol[], void *userdata)
{
   if( strlen(word[2]) > 0 && strlen(word[3]) > 0 )
   {
      enabled = true;
      channel.assign(xchat_get_info(ph, "channel"));
      trigger.assign(word[2]);
      answer.assign(word[3]);
      xchat_printf(ph, "Auto Reply with trigger %s and answer %s enabled (on channel %s)\n", trigger.c_str(), answer.c_str(), channel.c_str());
   }
   else
   {
      enabled = false;
      xchat_print(ph, "Auto Reply disabled\n");
   }

   return XCHAT_EAT_ALL;
}

void xchat_plugin_get_info(const char ** name, const char **desc, const char **version, void **)
{
   *name = PNAME;
   *desc = PDESC;
   *version = PVERSION;
}

extern "C" {
  int xchat_plugin_init(xchat_plugin *plugin_handle,
                        const char **plugin_name,
                        const char **plugin_desc,
                        const char **plugin_version,
                        const char *arg)
  {
     ph = plugin_handle;

     *plugin_name = PNAME;
     *plugin_desc = PDESC;
     *plugin_version = PVERSION;

     xchat_hook_command(ph, "AUTOREPLY", XCHAT_PRI_NORM, autoreply_toggle_cb, "Usage: AUTOREPLY [TRIGGERING_WORD] [AUTO_ANSWER]", 0);
     xchat_hook_print(ph, "Channel Message", XCHAT_PRI_NORM, autoreply_filter_cb, 0);

     xchat_print(ph, "Auto Reply Plugin; Usage: AUTOREPLY [TRIGGERING_WORD] [AUTO_ANSWER]; Pass no parameters to disable auto reply\n");

     return 1;
  }
}
