#include <iostream>
#include <vector>
#include <algorithm> // For std::find

using namespace std;

int predict(const vector<int> &pages, const vector<int> &frames, int index)
{
  int farthest = index;
  int result = -1;

  for (int i = 0; i < frames.size(); i++)
  {
    int j;
    for (j = index; j < pages.size(); j++)
    {
      if (frames[i] == pages[j])
      {
        if (j > farthest)
        {
          farthest = j;
          result = i;
        }
        break;
      }
    }
    if (j == pages.size())
    {
      return i;
    }
  }

  return (result == -1) ? 0 : result;
}

int optimalPageReplacement(const vector<int> &pages, int capacity)
{
  vector<int> frames;
  int faults = 0;

  for (int i = 0; i < pages.size(); i++)
  {
    int page = pages[i];

    if (find(frames.begin(), frames.end(), page) != frames.end())
    {
      continue;
    }

    if (frames.size() < capacity)
    {
      frames.push_back(page);
    }
    else
    {
      int indexToReplace = predict(pages, frames, i + 1);
      frames[indexToReplace] = page;
    }

    faults++;
  }

  return faults;
}

int main()
{
  vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3};
  int capacity = 4;

  int pageFaults = optimalPageReplacement(pages, capacity);
  cout << "Total Page Faults (Optimal): " << pageFaults << endl;

  return 0;
}
