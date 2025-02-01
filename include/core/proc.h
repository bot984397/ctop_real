#ifndef __CTOP_PROC_H__
#define __CTOP_PROC_H__

#include <unordered_set>
#include <functional>

#include "../core/aggregator.h"
#include "../core/api.h"
#include "../core/util.h"
#include "../ui/container.h"

using std::unordered_map;

class ProcessEntry {
private:
   pid_t m_pid;
   long m_threads;
   std::string m_name;
   std::string m_cmdline;
   std::string m_user;
   StaticFiloQueue<uint8_t, 10> m_cpu_history;
   StaticFiloQueue<uint8_t, 10> m_mem_history;
   StaticFiloQueue<uint8_t, 10> m_gpu_history;
   double m_cpu_usage;
   double m_mem_usage;
   double m_gpu_usage;

public:
   ProcessEntry(pid_t pid, std::string name, std::string cmdline, 
                std::string user)
      : m_pid(pid), m_name(name), m_cmdline(cmdline), m_user(user) {}

   const pid_t& get_pid() const noexcept { return m_pid; }
   const long& get_threads() const noexcept { return m_threads; }
   const std::string& get_name() const noexcept { return m_name; }
   const std::string& get_cmdline() const noexcept { return m_cmdline; }
   const std::string& get_user() const noexcept { return m_user; }
};

class ProcAggregator : public IResourceAggregator {
private:
   unordered_map<pid_t, ProcessEntry> proc_list;

   void update_proc_set(unordered_map<pid_t, ProcessEntry>& old,
                        const std::unordered_set<pid_t>& _new);
   
   ProcessEntry get_static_proc_data(pid_t pid);
   void get_dynamic_proc_data(ProcessEntry& entry);
public:
   ProcAggregator();

   bool init() override;
   void aggregate() override;

   const unordered_map<pid_t, ProcessEntry>& get_proc_list() const;
};

class ProcContainer : public IContainer {
private:
   ProcAggregator aggregator;

   bool filter_selected;
   std::string filter_string;
   size_t selected_proc_idx;
public:
   ProcContainer();

   bool init() noexcept override;
   void collect() noexcept override;
   void draw() const noexcept override;
   void process_key() noexcept override;
};

#endif // __CTOP_PROC_H__
