#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

int sstf_disk_schedule(vector<int> &req_seq, int head = 50)
{
  int total_seek = 0;
  int current_position = head;
  vector<bool> visited(req_seq.size(), false);

  cout << "SSTF Order:" << endl;

  for (int i = 0; i < req_seq.size(); i++)
  {
    int min_distance = numeric_limits<int>::max();
    int closest_request_index = -1;

    // Find the closest unvisited request
    for (int j = 0; j < req_seq.size(); j++)
    {
      if (!visited[j])
      {
        int distance = abs(req_seq[j] - current_position);
        if (distance < min_distance)
        {
          min_distance = distance;
          closest_request_index = j;
        }
      }
    }

    if (closest_request_index != -1)
    {
      cout << current_position << " > " << req_seq[closest_request_index] << endl;
      total_seek += min_distance;
      current_position = req_seq[closest_request_index];
      visited[closest_request_index] = true;
    }
  }

  cout << "Total number of seek operations: " << total_seek << endl;
  return total_seek;
}

int main()
{
  vector<int> req_seq = {176, 79, 34, 60, 92, 11, 41, 114};
  sstf_disk_schedule(req_seq, 50);

  return 0;
}
