#ifndef __CTOP_API_H__
#define __CTOP_API_H__

#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>

#include <cctype>
#include <string>
#include <fstream>
#include <sstream>

//  low-level process api - wraps procfs interactions

struct process_snapshot {
   DIR *dirp;
};

struct process_entry {
   pid_t pid;
};

bool ps_snapshot(struct process_snapshot *snap);
bool ps_first(struct process_snapshot *snap, struct process_entry *entry);
bool ps_next(struct process_snapshot *snap, struct process_entry *entry);
bool ps_last(struct process_snapshot *snap, struct process_entry *entry);

std::string ps_get_name(pid_t pid);
std::string ps_get_cmdline(pid_t pid);
std::tuple<uid_t, int> ps_get_status(pid_t pid);

std::string ut_uid_to_user(uid_t uid);

#endif // __CTOP_API_H__
