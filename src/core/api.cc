#include "../../include/core/api.h"

bool ps_snapshot(struct process_snapshot *snap) {
   DIR *dirp = opendir("/proc");
   if (dirp == NULL) {
      snap = NULL;
      return false;
   }
   snap->dirp = dirp;
   return true;
}

bool ps_first(struct process_snapshot *snap, struct process_entry *entry) {
   rewinddir(snap->dirp);
   return ps_next(snap, entry);
}

bool ps_next(struct process_snapshot *snap, struct process_entry *entry) {
   struct dirent *dir;
   while ((dir = readdir(snap->dirp)) != NULL) {
      if (!std::isdigit(dir->d_name[0]) || dir->d_name[0] == '.') {
         continue;
      }
      entry->pid = strtol(dir->d_name, NULL, 10);
      return true;
   }
   return false;
}

bool ps_last(struct process_snapshot *snap, struct process_entry *entry) {
   bool ret;
   while ((ret = ps_next(snap, entry))) {}
   return ret;
}

std::string ps_get_name(pid_t pid) {
   std::ifstream file("/proc/" + std::to_string(pid) + "/comm");
   std::string name;
   return (file && getline(file, name)) ? name : "N/A";
}

std::string ps_get_cmdline(pid_t pid) {
   std::ifstream file("/proc/" + std::to_string(pid) + "/cmdline");
   if (!file) return "N/A";
   
   std::stringstream buf;
   buf << file.rdbuf();
   std::string cmd = buf.str();

   for (char &c : cmd) if (c == '\0') c = ' ';
   return cmd.empty() ? "N/A" : cmd;
}

std::tuple<uid_t, int> ps_get_status(pid_t pid) {
   std::ifstream file("/proc/" + std::to_string(pid) + "/status");
   if (!file) return {-1, -1};

   std::string line;
   int thrd = -1;
   uid_t uid = -1;

   while (getline(file, line)) {
      if (line.rfind("Threads:", 0) == 0) {
         thrd = stoi(line.substr(9));
      } else if (line.rfind("Uid:", 0) == 0) {
         std::istringstream(line.substr(4)) >> uid;
      }
   }

   return {uid, thrd};
}

std::string ut_uid_to_user(uid_t uid) {
   struct passwd *pwd = getpwuid(uid);
   return (pwd) ? pwd->pw_name : "N/A";
}

