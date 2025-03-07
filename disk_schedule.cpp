#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int disk_schedule(vector<int> &req_seq, int head = 50)
{
  int total_seek = 0;
  int current_position = head;

  cout << "serial:" << endl;
  for (int request : req_seq)
  {
    cout << current_position << " > " << request << endl;
    total_seek += abs(request - current_position);
    current_position = request;
  }

  cout << "Total number of seek operations: " << total_seek << endl;
  return total_seek;
}

int main()
{
  vector<int> req_seq = {176, 79, 34, 60, 92, 11, 41, 114};
  disk_schedule(req_seq, 50);

  return 0;
}
