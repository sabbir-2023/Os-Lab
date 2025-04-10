#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void scanDiskScheduling(vector<int> requests, int head, int diskSize)
{
  vector<int> left, right;
  vector<int> seekSequence;
  int seekCount = 0;

  seekSequence.push_back(head);

  for (int req : requests)
  {
    if (req == 0)
      continue;

    if (req < head)
      left.push_back(req);
    else
      right.push_back(req);
  }

  for (int req : right)
  {
    seekCount += abs(head - req);
    head = req;
    seekSequence.push_back(head);
  }

  if (!left.empty())
  {
    if (head != diskSize - 1)
    {
      seekCount += abs(head - (diskSize - 1));
      head = diskSize - 1;
      seekSequence.push_back(head);
    }

    for (int i = left.size() - 1; i >= 0; i--)
    {
      seekCount += abs(head - left[i]);
      head = left[i];
      seekSequence.push_back(head);
    }
  }

  cout << "Seek Sequence: ";
  for (int pos : seekSequence)
    cout << pos << " ";
  cout << "\nTotal Seek Operations: " << seekCount << endl;
}

int main()
{
  vector<int> requests = {0, 14, 41, 53, 65, 67, 98, 122, 124, 183, 199};
  int head = 53;
  int diskSize = 200;

  scanDiskScheduling(requests, head, diskSize);

  return 0;
}
