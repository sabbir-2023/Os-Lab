#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

struct Process
{
  int priority;
  int arrival_time;
  int burst_time;
  string process_id;
  int remaining_bt;

  Process(int p, int a, int b, const string &id)
      : priority(p), arrival_time(a), burst_time(b), process_id(id), remaining_bt(b) {}
};

void printTable(const map<string, vector<int>> &final_list, const map<string, int> &response_times)
{
  cout << "\n";
  cout << left << setw(12) << "Process ID"
       << setw(15) << "Arrival Time"
       << setw(12) << "Burst Time"
       << setw(18) << "Completion Time"
       << setw(18) << "Turnaround Time"
       << setw(14) << "Waiting Time"
       << "Response Time" << endl;

  for (const auto &p : final_list)
  {
    const string &p_id = p.first;
    const vector<int> &times = p.second;
    cout << left
         << setw(12) << p_id
         << setw(15) << times[0]
         << setw(12) << times[1]
         << setw(18) << times[2]
         << setw(18) << times[3]
         << setw(14) << times[4]
         << response_times.at(p_id) << endl;
  }
}

void prioritySchedulingPreemptive(vector<Process> &process_list, int time_quantum = 1)
{

  sort(process_list.begin(), process_list.end(), [](const Process &a, const Process &b)
       { return a.priority > b.priority; });

  int t = 0;
  vector<string> gantt;
  map<string, vector<int>> final_list;
  map<string, int> remaining_bt;
  map<string, int> first_execution;
  bool all_processes_arrived = false;

  for (auto &p : process_list)
  {
    remaining_bt[p.process_id] = p.burst_time;
  }

  while (!remaining_bt.empty())
  {
    vector<Process> available_processes;

    for (auto &p : process_list)
    {
      if (p.arrival_time <= t && remaining_bt.find(p.process_id) != remaining_bt.end())
      {
        available_processes.push_back(p);
      }
    }

    if (!available_processes.empty())
    {

      sort(available_processes.begin(), available_processes.end(), [](const Process &a, const Process &b)
           { return a.priority > b.priority; });

      Process process = available_processes[0];
      string p_id = process.process_id;

      if (first_execution.find(p_id) == first_execution.end())
      {
        first_execution[p_id] = t;
      }

      gantt.push_back(p_id);

      int execution_time = min(time_quantum, remaining_bt[p_id]);
      t += execution_time;
      remaining_bt[p_id] -= execution_time;

      if (remaining_bt[p_id] == 0)
      {
        int completion_time = t;
        int turnaround_time = completion_time - process.arrival_time;
        int waiting_time = turnaround_time - process.burst_time;
        final_list[p_id] = {process.arrival_time, process.burst_time, completion_time, turnaround_time, waiting_time};
        remaining_bt.erase(p_id);
      }
    }
    else
    {
      gantt.push_back("Idle");
      t += time_quantum;
    }

    if (!all_processes_arrived)
    {
      all_processes_arrived = all_of(process_list.begin(), process_list.end(), [t](const Process &p)
                                     { return p.arrival_time <= t; });
    }
  }

  map<string, int> response_times;
  for (const auto &p : final_list)
  {
    string p_id = p.first;
    int response_time = first_execution[p_id] - final_list[p_id][0];
    response_times[p_id] = response_time;
  }

  // Print Gantt chart
  cout << "\nGantt Chart: ";
  for (const string &id : gantt)
  {
    cout << id << " ";
  }
  cout << endl;

  printTable(final_list, response_times);
}

int main()
{
  vector<Process> process_list = {
      Process(10, 0, 5, "P1"),
      Process(20, 1, 4, "P2"),
      Process(30, 2, 2, "P3"),
      Process(40, 4, 1, "P4")};

  prioritySchedulingPreemptive(process_list, 1);

  return 0;
}
