#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef struct
{
  int burst_time;
  int arrival_time;
  string process_id;
} Process;

bool compareProcesses(const Process &a, const Process &b) { return a.burst_time < b.burst_time; }

void processScheduling(vector<Process> &process_list)
{
  int t = 0;
  vector<string> gantt;
  map<string, vector<int>> final;
  vector<int> BT, AT;

  while (!process_list.empty())
  {
    vector<Process> available;
    for (const auto &p : process_list)
    {
      if (p.arrival_time <= t)
      {
        available.push_back(p);
      }
    }

    if (available.empty())
    {
      t++;
      gantt.push_back("Free");
      continue;
    }

    sort(available.begin(), available.end(), compareProcesses);
    Process process = available[0];

    int burst_time = process.burst_time;
    int arrival_time = process.arrival_time;
    string p_id = process.process_id;

    t += burst_time;
    gantt.push_back(p_id);
    BT.push_back(burst_time);
    AT.push_back(arrival_time);

    int completion_time = t;
    int turn_around_time = completion_time - arrival_time;
    int waiting_time = turn_around_time - burst_time;

    final[p_id] = {completion_time, turn_around_time, waiting_time};

    auto it = remove_if(process_list.begin(), process_list.end(), [&p_id](const Process &p)

                        { return p.process_id == p_id; });
    process_list.erase(it, process_list.end());
  }

  cout << "Gantt Chart:\n";
  for (const auto &g : gantt)
  {
    cout << g << " ";
  }
  cout << endl;

  cout << "Arrival Time:\n";
  for (const auto &a : AT)
  {
    cout << a << " ";
  }
  cout << endl;

  cout << "Burst Time:\n";
  for (const auto &b : BT)
  {
    cout << b << " ";
  }
  cout << endl;

  cout << "Completion, Turnaround and Waiting Times:\n";
  for (const auto &entry : final)
  {
    cout << entry.first << " -> Completion: " << entry.second[0]
         << ", Turnaround: " << entry.second[1]
         << ", Waiting: " << entry.second[2] << endl;
  }
}

int main()
{
  vector<Process> process_list = {{6, 2, "p1"}, {2, 5, "p2"}, {8, 1, "p3"}, {3, 0, "p4"}, {4, 4, "p5"}};
  processScheduling(process_list);
  return 0;
}