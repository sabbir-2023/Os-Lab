#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process
{
  int burst_time;
  int arrival_time;
  string process_id;
  int remaining_time;
  int first_response_time = -1;
};

void roundRobinScheduling(vector<Process> &process_list, int time_quantum)
{
  queue<Process> ready_queue;
  vector<string> gantt;
  map<string, vector<int>> final;
  int t = 0;

 
  sort(process_list.begin(), process_list.end(), [](const Process &a, const Process &b)
       { return a.arrival_time < b.arrival_time; });

  int index = 0;
  while (index < process_list.size() || !ready_queue.empty())
  {
    while (index < process_list.size() && process_list[index].arrival_time <= t)
    {
      process_list[index].remaining_time = process_list[index].burst_time;
      ready_queue.push(process_list[index]);
      index++;
    }

    if (ready_queue.empty())
    {
      gantt.push_back("Idle");
      t++;
      continue;
    }

    Process process = ready_queue.front();
    ready_queue.pop();

    if (process.first_response_time == -1)
    {
      process.first_response_time = t - process.arrival_time;
    }

    int exec_time = min(time_quantum, process.remaining_time);
    t += exec_time;
    gantt.push_back(process.process_id);
    process.remaining_time -= exec_time;

    while (index < process_list.size() && process_list[index].arrival_time <= t)
    {
      process_list[index].remaining_time = process_list[index].burst_time;
      ready_queue.push(process_list[index]);
      index++;
    }

    if (process.remaining_time > 0)
    {
      ready_queue.push(process);
    }
    else
    {
      int completion_time = t;
      int turn_around_time = completion_time - process.arrival_time;
      int waiting_time = turn_around_time - process.burst_time;
      final[process.process_id] = {completion_time, turn_around_time, waiting_time, process.first_response_time};
    }
  }

 
  cout << "Gantt Chart:\n";
  for (const auto &g : gantt)
  {
    cout << g << " ";
  }
  cout << endl;

  cout << "\nProcess Scheduling Table:\n";
  cout << "---------------------------------------------------------\n";
  cout << "| Process | Arrival Time | Burst Time | Completion | Turnaround | Waiting | Response |\n";
  cout << "---------------------------------------------------------\n";
  for (const auto &entry : final)
  {
    cout << "| " << setw(7) << entry.first << " | "
         << setw(12) << process_list[stoi(entry.first.substr(1)) - 1].arrival_time << " | "
         << setw(10) << process_list[stoi(entry.first.substr(1)) - 1].burst_time << " | "
         << setw(10) << entry.second[0] << " | "
         << setw(10) << entry.second[1] << " | "
         << setw(7) << entry.second[2] << " | "
         << setw(8) << entry.second[3] << " |\n";
  }
  cout << "---------------------------------------------------------\n";
}

int main()
{
  vector<Process> process_list = {{5, 0, "P1"}, {4, 1, "P2"}, {2, 2, "P3"}, {1, 4, "P4"}};
  int time_quantum = 2;
  roundRobinScheduling(process_list, time_quantum);
  return 0;
}
