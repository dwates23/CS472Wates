#include <iostream>
#include <thread>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <climits>
#include <string>
#include <functional>

using namespace std;


// Define job structure
struct Job {
    unsigned int id;
    unsigned int projectedRunTime;
    unsigned int executionTime;
    unsigned int idleTime;
    unsigned int priority;
    unsigned int passCount;
};

// Define queue manager
class QueueManager {
private:
    mutex mtx;
    condition_variable cv;
    deque<Job> foregroundQueue;
    deque<Job> backgroundQueue;
    deque<Job> batchQueue;
    unsigned int quantumLength;
    unsigned int maxPasses;

public:
    QueueManager(unsigned int quantumLength = 200, unsigned int maxPasses = 2)
        : quantumLength(quantumLength), maxPasses(maxPasses) {}

    void enter(Job job) {
        unique_lock<mutex> lock(mtx);
        foregroundQueue.push_back(job);
        cv.notify_one();
    }

    void reschedule(Job &job) {
        unique_lock<mutex> lock(mtx);
        if (job.passCount < maxPasses) {
            job.passCount++;
        } else {
            job.passCount = 0;
            auto jobIt = findJobInQueue(job.id);
            if (jobIt != foregroundQueue.end()) {
                job = *jobIt;
                foregroundQueue.erase(jobIt);
            } else if ((jobIt = findJobInQueue(job.id, backgroundQueue)) != backgroundQueue.end()) {
                job = *jobIt;
                backgroundQueue.erase(jobIt);
            } else if ((jobIt = findJobInQueue(job.id, batchQueue)) != batchQueue.end()) {
                job = *jobIt;
                batchQueue.erase(jobIt);
            }
        }
    }

    Job schedule() {
        unique_lock<mutex> lock(mtx);
        if (!foregroundQueue.empty()) {
            Job job = foregroundQueue.front();
            foregroundQueue.pop_front();
            return job;
        } else if (!backgroundQueue.empty()) {
            Job job = backgroundQueue.front();
            backgroundQueue.pop_front();
            return job;
        } else if (!batchQueue.empty()) {
            Job job = batchQueue.front();
            batchQueue.pop_front();
            return job;
        }
        return Job(); // Return empty job if no job available
    }

    void addToBackgroundQueue(Job job) {
        unique_lock<mutex> lock(mtx);
        backgroundQueue.push_back(job);
        cv.notify_one();
    }

    void addToBatchQueue(Job job) {
        unique_lock<mutex> lock(mtx);
        batchQueue.push_back(job);
        cv.notify_one();
    }

    unsigned int getQuantumLength() const {
        return quantumLength;
    }

    unsigned int getMaxPasses() const {
        return maxPasses;
    }

private:
    deque<Job>::iterator findJobInQueue(unsigned int jobId) {
        return find_if(foregroundQueue.begin(), foregroundQueue.end(),
                       [jobId](const Job &job) { return job.id == jobId; });
    }

    deque<Job>::iterator findJobInQueue(unsigned int jobId, deque<Job>& q) {
        return find_if(q.begin(), q.end(),
                       [jobId](const Job &job) { return job.id == jobId; });
    }
};

// Function to generate a normally distributed random number
double normal_distribution_rng(double mean, double stddev) {
    static default_random_engine generator;
    normal_distribution<double> distribution(mean, stddev);
    return distribution(generator);
}

// Function to generate a uniformly distributed random number
unsigned int uniform_distribution_rng(unsigned int min, unsigned int max) {
    static default_random_engine generator;
    uniform_int_distribution<unsigned int> distribution(min, max);
    return distribution(generator);
}

// Job creation thread function
void jobCreationThread(QueueManager& queueManager, unsigned int simulationTime) {
    auto start = chrono::steady_clock::now();
    while (true) {
        auto elapsedSeconds = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count();
        if (elapsedSeconds >= simulationTime)
            break;

        // Generate a new job
        Job newJob;
        newJob.id = uniform_distribution_rng(1, UINT_MAX);
        newJob.projectedRunTime = normal_distribution_rng(2000, 500);
        newJob.executionTime = 0;
        newJob.idleTime = 0;
        newJob.priority = uniform_distribution_rng(0, 9);
        newJob.passCount = 0;

        // Enter the job into the system
        queueManager.enter(newJob);

        // Sleep for a random time based on Poisson distribution
        this_thread::sleep_for(chrono::milliseconds(uniform_distribution_rng(1, 333)));
    }
}

// Processor thread function
void processorThread(QueueManager& queueManager, unsigned int simulationTime) {
    auto start = chrono::steady_clock::now();
    while (true) {
        auto elapsedSeconds = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count();
        if (elapsedSeconds >= simulationTime)
            break;

        // Schedule the next job
        Job nextJob = queueManager.schedule();
        if (nextJob.id != 0) {
            // Execute the job
            cout << "Job " << nextJob.id << " is executing..." << endl;
            this_thread::sleep_for(chrono::milliseconds(nextJob.projectedRunTime));
            cout << "Job " << nextJob.id << " completed." << endl;

            // Delete the job
            // Here we simulate the deletion by not doing anything
        } else {
            // If no job available, sleep for a while
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
}

int main(int argc, char *argv[]) {
    unsigned int simulationTime = 300; // Default simulation time in seconds

    if (argc > 1) {
        simulationTime = std::stoi(argv[1]);
    }

    QueueManager queueManager;

    // Create and run the job creation thread
    thread jobCreator(jobCreationThread, std::ref(queueManager), simulationTime);

    // Create and run the processor thread
    thread processor(processorThread, std::ref(queueManager), simulationTime);

    // Wait for threads to finish
    jobCreator.join();
    processor.join();

    return 0;
}
