#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void fcfs(const   vector<int>& requests, int head) {
    int seek_time = 0;
    int curr_track;
    for (const int& request : requests) {
        curr_track = request;
        seek_time +=   abs(curr_track - head);
        head = curr_track;
    }
      cout << "FCFS Total Seek Time: " << seek_time <<   endl;
      cout << "FCFS Average Seek Time: " << static_cast<float>(seek_time) / requests.size() <<   endl;
}

void scan(const   vector<int>& requests, int head, int max_track) {
    int seek_time = 0;
    int curr_track;
    int direction = 1; // 1 for right, -1 for left
    int index = 0;
      vector<int> temp(requests);
    temp.push_back(head);
    int size = temp.size();

      sort(temp.begin(), temp.end());

    for (int i = 0; i < size; i++) {
        if (temp[i] == head) {
            index = i;
            break;
        }
    }

    if (direction == 1) {
        for (int i = index; i < size; i++) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
        seek_time +=   abs(max_track - head);
        head = max_track;
        for (int i = index - 1; i >= 0; i--) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
    } else {
        for (int i = index; i >= 0; i--) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
        seek_time +=   abs(0 - head);
        head = 0;
        for (int i = index + 1; i < size; i++) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
    }

      cout << "SCAN Total Seek Time: " << seek_time <<   endl;
      cout << "SCAN Average Seek Time: " << static_cast<float>(seek_time) / requests.size() <<   endl;
}

void c_scan(const   vector<int>& requests, int head, int max_track) {
    int seek_time = 0;
    int curr_track;
    int direction = 1; // 1 for right, -1 for left
    int index = 0;
      vector<int> temp(requests);
    temp.push_back(0);
    temp.push_back(max_track);
      sort(temp.begin(), temp.end());
    int size = temp.size();

    for (int i = 0; i < size; i++) {
        if (temp[i] == head) {
            index = i;
            break;
        }
    }

    if (direction == 1) {
        for (int i = index; i < size; i++) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
        seek_time +=   abs(max_track - head);
        head = max_track;
        for (int i = 0; i < index - 1; i++) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
    } else {
        for (int i = index; i >= 0; i--) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
        seek_time +=   abs(0 - head);
        head = 0;
        for (int i = size - 2; i > index; i--) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
    }

      cout << "C-SCAN Total Seek Time: " << seek_time <<   endl;
      cout << "C-SCAN Average Seek Time: " << static_cast<float>(seek_time) / requests.size() <<   endl;
}

void sstf(const   vector<int>& requests, int head) {
    int seek_time = 0;
    int curr_track;
      vector<int> temp(requests);

    for (size_t i = 0; i < temp.size(); i++) {
        size_t min_index = i;
        for (size_t j = i + 1; j < temp.size(); j++) {
            if (  abs(temp[j] - head) <   abs(temp[min_index] - head)) {
                min_index = j;
            }
        }
        curr_track = temp[min_index];
        seek_time +=   abs(curr_track - head);
        head = curr_track;
        temp[min_index] = temp[i];
        temp[i] = curr_track;
    }

      cout << "SSTF Total Seek Time: " << seek_time <<   endl;
      cout << "SSTF Average Seek Time: " << static_cast<float>(seek_time) / requests.size() <<   endl;
}

void look(const   vector<int>& requests, int head, int max_track) {
    int seek_time = 0;
    int curr_track;
    int direction = 1; // 1 for right, -1 for left
    int index = 0;
      vector<int> temp(requests);

      sort(temp.begin(), temp.end());
    int size = temp.size();

    for (int i = 0; i < size; i++) {
        if (temp[i] == head) {
            index = i;
            break;
        }
    }

    if (direction == 1) {
        for (int i = index; i < size; i++) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
        for (int i = size - 2; i >= index; i--) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
    } else {
        for (int i = index; i >= 0; i--) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
        for (int i = 1; i <= index; i++) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
    }

      cout << "LOOK Total Seek Time: " << seek_time <<   endl;
      cout << "LOOK Average Seek Time: " << static_cast<float>(seek_time) / requests.size() <<   endl;
}

void c_look(const   vector<int>& requests, int head) {
    int seek_time = 0;
    int curr_track;
    int direction = 1; // 1 for right, -1 for left
    int index = 0;
      vector<int> temp(requests);
    temp.push_back(head);
      sort(temp.begin(), temp.end());
    int size = temp.size();

    for (int i = 0; i < size; i++) {
        if (temp[i] == head) {
            index = i;
            break;
        }
    }

    if (direction == 1) {
        for (int i = index; i < size; i++) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
        for (int i = 0; i < index - 1; i++) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
    } else {
        for (int i = index; i >= 0; i--) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
        for (int i = size - 2; i >= index; i--) {
            curr_track = temp[i];
            seek_time +=   abs(curr_track - head);
            head = curr_track;
        }
    }

      cout << "C-LOOK Total Seek Time: " << seek_time <<   endl;
      cout << "C-LOOK Average Seek Time: " << static_cast<float>(seek_time) / requests.size() <<   endl;
}

int main() {
    int size, head, max_track;
      cout << "Enter the number of requests: ";
      cin >> size;
      vector<int> arr(size);
      cout << "Enter the requests: ";
    for (int i = 0; i < size; i++) {
          cin >> arr[i];
    }
      cout << "Enter the initial head position: ";
      cin >> head;
      cout << "Enter the maximum track number: ";
      cin >> max_track;
      cout <<   endl;

      cout << "FCFS:" <<   endl;
    fcfs(arr, head);
      cout <<   endl;

      cout << "SCAN:" <<   endl;
    scan(arr, head, max_track);
      cout <<   endl;

      cout << "C-SCAN:" <<   endl;
    c_scan(arr, head, max_track);
      cout <<   endl;

      cout << "SSTF:" <<   endl;
    sstf(arr, head);
      cout <<   endl;

      cout << "LOOK:" <<   endl;
    look(arr, head, max_track);
      cout <<   endl;

      cout << "C-LOOK:" <<   endl;
    c_look(arr, head);
    return 0;
}

