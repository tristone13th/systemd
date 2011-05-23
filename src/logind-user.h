/*-*- Mode: C; c-basic-offset: 8; indent-tabs-mode: nil -*-*/

#ifndef foologinduserhfoo
#define foologinduserhfoo

/***
  This file is part of systemd.

  Copyright 2011 Lennart Poettering

  systemd is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  systemd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with systemd; If not, see <http://www.gnu.org/licenses/>.
***/

typedef struct User User;

#include "list.h"
#include "util.h"
#include "logind.h"
#include "logind-session.h"

typedef enum UserState {
        USER_OFFLINE,
        USER_LINGERING,
        USER_ONLINE,
        USER_ACTIVE,
        _USER_STATE_MAX,
        _USER_STATE_INVALID = -1
} UserState;

struct User {
        Manager *manager;

        uid_t uid;
        gid_t gid;
        char *name;

        char *state_file;
        char *runtime_path;
        char *service;
        char *cgroup_path;

        Session *display;

        dual_timestamp timestamp;

        LIST_HEAD(Session, sessions);
};

User* user_new(Manager *m, uid_t uid, gid_t gid, const char *name);
void user_free(User *u);
int user_start(User *u);
int user_stop(User *u);
int user_check_gc(User *u);
UserState user_get_state(User *u);
int user_save(User *u);
int user_load(User *u);

const char* user_state_to_string(UserState s);
UserState user_state_from_string(const char *s);

#endif
