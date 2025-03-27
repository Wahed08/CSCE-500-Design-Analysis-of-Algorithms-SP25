#include<bits/stdc++.h>
using namespace std;

struct Job {
    int r;
    int p;
};
bool compareJobs(const Job& a, const Job& b) {
    return a.r < b.r; // sorting the jobs by releasing time
}
// Structure for elements in the priority queue
struct QueueElement {
    int remaining; // Remaining processing time
    int job_idx;   // Index in the sorted jobs array

    // Operator to prioritize jobs with shorter remaining time
    bool operator>(const QueueElement& other) const {
        return remaining > other.remaining;
    }
};
int main() {

    int n;
    cin >> n;
    vector<Job> jobs(n);
    for (int i = 0; i < n; ++i) {
        cin >> jobs[i].r >> jobs[i].p;
    }

    sort(jobs.begin(), jobs.end(), compareJobs);
    // Min-heap to select the job with the shortest remaining time
    priority_queue<QueueElement, vector<QueueElement>, greater<QueueElement>> pq;

    int current_time = 0;
    int next_job_idx = 0; // Index of the next job to be added to the queue
    int total_completion_time = 0;

    while (next_job_idx < n || !pq.empty()) {
        // Add all jobs that have been released by the current time
        while (next_job_idx < n && jobs[next_job_idx].r <= current_time) {
            pq.push({jobs[next_job_idx].p, next_job_idx});
            next_job_idx++;
        }
        if (pq.empty()) {
            // No jobs available; jump to the next release time
            current_time = jobs[next_job_idx].r;
            continue;
        }
        // Get the job with the shortest remaining time
        QueueElement current_job = pq.top();
        pq.pop();

        // Determine the next event time (next job release or completion of current job)
        int next_release = (next_job_idx < n) ? jobs[next_job_idx].r : INT_MAX;
        int duration = min(next_release - current_time, current_job.remaining);

        // Process the job
        current_time += duration;
        current_job.remaining -= duration;

        if (current_job.remaining == 0) {
            total_completion_time += current_time;
        } else {
            pq.push(current_job);
        }
    }
    cout << total_completion_time << endl;
    return 0;
}
