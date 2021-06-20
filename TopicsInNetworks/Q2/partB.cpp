#include <bits/stdc++.h>

using namespace std;

int lambda = 5;
int mu = 8;
int N = 100000;

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
double findAvgWorkersChecked(vector<double> &arrivalQueue, vector<double> serviceQueue1, vector<double> serviceQueue2) {
	double totalTime = 0, processTime = 0;
	set<pair<double, int>> queueEvents;
	vector<double> et1 = {0.0}, et2 = {0.0};
	for (int c = 0; c < arrivalQueue.size(); ++c) {
		totalTime += arrivalQueue[c];
		double serviceTime = 0;
		queueEvents.insert({totalTime, 1});
		if (totalTime > et1.back()) {
			serviceTime = totalTime + serviceQueue1.back();
			processTime += serviceQueue1.back();
			serviceQueue1.pop_back();
			et1.push_back(serviceTime);
		} else if (totalTime > et2.back()) {
			serviceTime = totalTime + serviceQueue2.back();
			processTime += serviceQueue2.back();
			serviceQueue2.pop_back();
			et2.push_back(serviceTime);
		} else if (et1.back() < et2.back()) {
			processTime += serviceQueue1.back();
			serviceTime = et1.back() + serviceQueue1.back();
			et1.push_back(serviceTime);
			serviceQueue1.pop_back();
		} else {
			processTime += serviceQueue2.back();
			serviceTime = et2.back() + serviceQueue2.back();
			et2.push_back(serviceTime);
			serviceQueue2.pop_back();
		}
		queueEvents.insert({serviceTime, -1});
	}

	return processTime / (totalTime);
}

// Computes average response time for workers in getting checked
double findAvgResponseTime(vector<double> arrivalQueue, vector<double> serviceQueue1, vector<double> serviceQueue2) {
	double totalTime = 0, netResponseTime = 0.0;
	vector<double> et1 = {0.0}, et2 = {0.0};
	for (int c = 0; c < arrivalQueue.size(); ++c) {
		totalTime += arrivalQueue[c];
		double serviceTime = 0;
		if (totalTime > et1.back()) {
			serviceTime = totalTime + serviceQueue1.back();
			serviceQueue1.pop_back();
			et1.push_back(serviceTime);
		} else if (totalTime > et2.back()) {
			serviceTime = totalTime + serviceQueue2.back();
			serviceQueue2.pop_back();
			et2.push_back(serviceTime);
		} else if (et1.back() < et2.back()) {
			serviceTime = et1.back() + serviceQueue1.back();
			et1.push_back(serviceTime);
			serviceQueue1.pop_back();
		} else {
			serviceTime = et2.back() + serviceQueue2.back();
			et2.push_back(serviceTime);
			serviceQueue2.pop_back();
		}
		netResponseTime += serviceTime - totalTime;
	}

	return netResponseTime / (arrivalQueue.size() * 1.0);
}

// Computes average time that a worker has to wait in a queue
double findAvgWaitTime(vector<double> arrivalQueue, vector<double> serviceQueue1, vector<double> serviceQueue2) {
	double totalTime = 0, wait = 0, netWaitTime = 0.0;
	vector<double> et1 = {0.0}, et2 = {0.0};
	for (int c = 0; c < arrivalQueue.size(); ++c) {
		totalTime += arrivalQueue[c];
		double serviceTime = 0;
		wait = 0;
		if (totalTime > et1.back()) {
			serviceTime = totalTime + serviceQueue1.back();
			serviceQueue1.pop_back();
			et1.push_back(serviceTime);
		} else if (totalTime > et2.back()) {
			serviceTime = totalTime + serviceQueue2.back();
			serviceQueue2.pop_back();
			et2.push_back(serviceTime);
		} else if (et1.back() < et2.back()) {
			serviceTime = et1.back() + serviceQueue1.back();
			et1.push_back(serviceTime);
			wait = serviceTime - serviceQueue1.back() - totalTime;
			serviceQueue1.pop_back();
		} else {
			serviceTime = et2.back() + serviceQueue2.back();
			et2.push_back(serviceTime);
			wait = serviceTime - serviceQueue2.back() - totalTime;
			serviceQueue2.pop_back();
		}
		netWaitTime += wait;
	}

	return netWaitTime / (arrivalQueue.size() * 1.0);
}

// Computes average number of workers waiting in each queue
double findAvgWaitingWorkers(vector<double> arrivalQueue, vector<double> serviceQueue1, vector<double> serviceQueue2) {
	double totalTime = 0;
	set<pair<double, int>> queueEvents;
	vector<double> et1 = {0.0}, et2 = {0.0};
	for (int c = 0; c < arrivalQueue.size(); ++c) {
		totalTime += arrivalQueue[c];
		double serviceTime = 0;
		queueEvents.insert({totalTime, 1});
		if (totalTime > et1.back()) {
			serviceTime = totalTime + serviceQueue1.back();
			serviceQueue1.pop_back();
			et1.push_back(serviceTime);
		} else if (totalTime > et2.back()) {
			serviceTime = totalTime + serviceQueue2.back();
			serviceQueue2.pop_back();
			et2.push_back(serviceTime);
		} else if (et1.back() < et2.back()) {
			serviceTime = et1.back() + serviceQueue1.back();
			et1.push_back(serviceTime);
			serviceQueue1.pop_back();
		} else {
			serviceTime = et2.back() + serviceQueue2.back();
			et2.push_back(serviceTime);
			serviceQueue2.pop_back();
		}
		queueEvents.insert({serviceTime, -1});
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
		if (it.first > 1)
			it.first -= 2;
		else
			it.first = 0;
		sum += it.first * it.second;
	}

	return sum / (totalTime);
}

int main(int argc, char const *argv[]) {
	assert(lambda < 2*mu);
	srand(time(0));
	vector<vector<double>> ArrivalTimes;
	ArrivalTimes.push_back(createData(N, lambda));

	vector<vector<double>> serviceTimes;
	serviceTimes.push_back(createData(N, mu));
	serviceTimes.push_back(createData(N, mu));

	cout<<"Average Number of workers being checked : ";
	cout << (findAvgWorkersChecked(ArrivalTimes[0], serviceTimes[0], serviceTimes[1])) << endl;
	cout<<"Average Response time for workers being checked : ";
	cout << (findAvgResponseTime(ArrivalTimes[0], serviceTimes[0], serviceTimes[1])) << endl;
	cout<<"Average time for workers to wait in queue : ";
	cout << (findAvgWaitTime(ArrivalTimes[0], serviceTimes[0], serviceTimes[1])) << endl;
	cout<<"Average Number of workers waiting in queue : ";
	cout << (findAvgWaitingWorkers(ArrivalTimes[0], serviceTimes[0], serviceTimes[1])) << endl;

	return 0;
}