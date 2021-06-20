#include <bits/stdc++.h>

using namespace std;

int lambda = 5;
int mu = 8;
int N =  100000;

// Generates random variable following exponential distribution
// Returns interarrival time between two occurances that follow
// exponential distribution 
double getExponentialRandomVariable(double param) {
	double uniformRandomValue = ((double)rand() + 1) / ((double)(RAND_MAX) + 1);
	double exponentialRandomValue = (double)(-(log(1 - uniformRandomValue)) / param);

	return exponentialRandomValue;
}

// Creates an array of size N following exponential distribution
// Each element represents the interarrival time between two 
// consecutive workers in a given queue
vector<double> createData(int n, double mean) {
	vector<double> result;
	for (int c = 0; c < n; ++c) {
		result.push_back(getExponentialRandomVariable(mean));
	}
	return result;
}

// Computes the average number of workers getting checked in a given queue
double findAvgWorkersChecked(vector<double> arrivalQueue, vector<double> serviceQueue) {
	double totalTime = 0, processingTime = 0;
	vector<double> endTime = {0.0};
	set<pair<double, int>> queueEvents;
	set<double> checkWorkersInQueue;

	for (int c = 0; c < arrivalQueue.size(); ++c) {
		totalTime += arrivalQueue[c];

		while (checkWorkersInQueue.size() && *checkWorkersInQueue.begin() <= totalTime) checkWorkersInQueue.erase(checkWorkersInQueue.begin());
		if (checkWorkersInQueue.size() > 5) continue;

		processingTime += serviceQueue[c];
		queueEvents.insert({totalTime, 1});
		endTime.push_back(max(totalTime, endTime.back()) + serviceQueue[c]);
		checkWorkersInQueue.insert(endTime.back());
		queueEvents.insert({endTime.back(), -1});
	}

	return processingTime / (totalTime);
}

// Computes average response time for workers in getting checked
double findAvgResponseTime(vector<double> arrivalQueue, vector<double> serviceQueue) {
	double totalTime = 0, netProcessTime = 0.0;
	vector<double> endTime = {0.0};
	set<double> queueEvents;

	for (int c = 0; c < arrivalQueue.size(); ++c) {
		totalTime += arrivalQueue[c];
		while (queueEvents.size() && *queueEvents.begin() <= totalTime) queueEvents.erase(queueEvents.begin());
		if (queueEvents.size() > 5) continue;
		double serviceTime = 0;
		if (totalTime > endTime.back())
			serviceTime = totalTime + serviceQueue[c];
		else
			serviceTime = endTime.back() + serviceQueue[c];

		queueEvents.insert({serviceTime, -1});
		endTime.push_back(serviceTime);
		netProcessTime += serviceTime - totalTime;
	}

	return netProcessTime / (arrivalQueue.size() * 1.0);
}

// Computes average time that a worker has to wait in a queue
double findAvgWaitTime(vector<double> arrivalQueue, vector<double> serviceQueue) {
	double totalTime = 0, wait = 0, netWaitTime = 0.0;
	vector<double> endTime = {0.0};
	set<double> queueEvents;

	assert(arrivalQueue.size() == serviceQueue.size());
	for (int c = 0; c < arrivalQueue.size(); ++c) {
		totalTime += arrivalQueue[c];
		while (queueEvents.size() && *queueEvents.begin() <= totalTime) queueEvents.erase(queueEvents.begin());
		if (queueEvents.size() > 5) continue;
		double serviceTime = 0;
		if (totalTime > endTime.back())
			serviceTime = totalTime + serviceQueue[c];
		else
			serviceTime = endTime.back() + serviceQueue[c];
		queueEvents.insert({serviceTime, -1});
		endTime.push_back(serviceTime);
		wait = serviceTime - totalTime - serviceQueue[c];
		netWaitTime += wait;
	}

	return netWaitTime / (arrivalQueue.size() * 1.0);
}

// Computes average number of workers waiting in each queue
double findAvgWaitingWorkers(vector<double> arrivalQueue, vector<double> serviceQueue) {
	double totalTime = 0;
	vector<double> endTime = {0.0};
	set<pair<double, int>> queueEvents;
	set<double> checkWorkersInQueue;

	for (int c = 0; c < arrivalQueue.size(); ++c) {
		totalTime += arrivalQueue[c];

		while (checkWorkersInQueue.size() && *checkWorkersInQueue.begin() <= totalTime) checkWorkersInQueue.erase(checkWorkersInQueue.begin());
		if (checkWorkersInQueue.size() > 5) continue;

		queueEvents.insert({totalTime, 1});
		endTime.push_back(max(totalTime, endTime.back()) + serviceQueue[c]);
		checkWorkersInQueue.insert(endTime.back());
		queueEvents.insert({endTime.back(), -1});
	}

	totalTime = 0;
	int curr = 0;

	unordered_map<int, double> ct;
	while (queueEvents.size()) {
		auto it = *queueEvents.begin();
		queueEvents.erase(queueEvents.begin());

		ct[curr] += it.first - totalTime;
		totalTime = it.first;
		curr += it.second;
	}

	double sum = 0;

	for (pair<int, double> it : ct) {
		if (it.first > 0) it.first--;
		sum += it.first * it.second;
	}

	return sum / (totalTime);
}

int main(int argc, char const *argv[]) {
	assert(lambda < mu);
	srand(time(0));
	vector<vector<double>> ArrivalTimes;
	ArrivalTimes.push_back(createData(N, lambda));
	ArrivalTimes.push_back(createData(N, lambda));

	vector<vector<double>> serviceTimes;
	serviceTimes.push_back(createData(N, mu));
	serviceTimes.push_back(createData(N, mu));

	cout<<"For Queue 1:"<<endl;
	cout<<"Average Number of workers being checked : ";
	cout << findAvgWorkersChecked(ArrivalTimes[0], serviceTimes[0]) << endl;
	cout<<"Average Response time for workers being checked : ";
	cout << findAvgResponseTime(ArrivalTimes[0], serviceTimes[0]) << endl;
	cout<<"Average time for workers to wait in queue : ";
	cout << findAvgWaitTime(ArrivalTimes[0], serviceTimes[0]) << endl;
	cout<<"Average Number of workers waiting in queue : ";
	cout << findAvgWaitingWorkers(ArrivalTimes[0], serviceTimes[0]) << endl << endl;
	
	cout<<"For Queue 2:"<<endl;
	cout<<"Average Number of workers being checked : ";
	cout << findAvgWorkersChecked(ArrivalTimes[1], serviceTimes[1]) << endl;
	cout<<"Average Response time for workers being checked : ";
	cout << findAvgResponseTime(ArrivalTimes[1], serviceTimes[1]) << endl;
	cout<<"Average time for workers to wait in queue : ";
	cout << findAvgWaitTime(ArrivalTimes[1], serviceTimes[1]) << endl;
	cout<<"Average Number of workers waiting in queue : ";
	cout << findAvgWaitingWorkers(ArrivalTimes[1], serviceTimes[1]) << endl;

	return 0;
}