#include "../../include/core/proc.h"
#include "../../include/core/api.h"

#include <iostream>

ProcAggregator::ProcAggregator() : IResourceAggregator() {}

bool ProcAggregator::init() {
   return true;
}

void ProcAggregator::aggregate() {
   struct process_snapshot snap = {0};
   struct process_entry entry = {0};
   std::unordered_set<pid_t> pids;

   ps_snapshot(&snap);
   ps_first(&snap, &entry);
   do {
      pids.insert(entry.pid);
   } while (ps_next(&snap, &entry));

   update_proc_set(this->proc_list, pids);
}

void ProcAggregator::update_proc_set(
      unordered_map<pid_t, ProcessEntry>& old,
      const std::unordered_set<pid_t>& _new) {
   std::vector<pid_t> remove;
   for (const auto& [pid, process] : old) {
      if (_new.find(pid) == _new.end()) {
         remove.push_back(pid);
      }
   }

   for (pid_t pid : remove) {
      old.erase(pid);
   }

   for (pid_t pid : _new) {
      if (old.find(pid) == old.end()) {
         old.emplace(pid, get_static_proc_data(pid));
      }
   }
}

ProcessEntry ProcAggregator::get_static_proc_data(pid_t pid) {
   auto status = ps_get_status(pid);
   uid_t uid = std::get<0>(status);
   return ProcessEntry(
         pid,
         ps_get_name(pid),
         ps_get_cmdline(pid),
         ut_uid_to_user(uid));
}

const unordered_map<pid_t, ProcessEntry>& ProcAggregator::get_proc_list() const {
   return this->proc_list;
}

ProcContainer::ProcContainer() : IContainer() {}

bool ProcContainer::init() noexcept {
   return aggregator.init();
}

void ProcContainer::collect() noexcept {
   aggregator.aggregate();
}

void ProcContainer::draw() const noexcept {
   for (const auto& it: aggregator.get_proc_list()) {
      ProcessEntry entry = it.second;
      std::cout << "PID: " << entry.get_pid() << " NAME: " << entry.get_name() << " USER: " << entry.get_user() << " CMD: " << entry.get_cmdline() << "\r\n";
   }
}

void ProcContainer::process_key() noexcept {

}
