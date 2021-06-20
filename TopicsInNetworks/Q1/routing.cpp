    #include <bits/stdc++.h>
    using namespace std;

/******************************************************************************************/
   	
   	#define deathnote()     ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #define F               first
    #define S               second

/****************************************************************************************************/

    string topologyFile, connectionFile, rtFile, ftFile, pathFile;
    int hopDist, P;

/****************************************************************************************************/

    vector<pair<int, vector<int>>> getPath(vector<vector<int>> &adj, vector<vector<int>> &wt, vector<vector<int>> &blocked, int root) {
		int n = adj.size();
		vector<pair<int, vector<int>>> dist(n, {INT_MAX, {}});
		set<pair<int, int>> minHeap;
		minHeap.insert({0, root});

		dist[root] = {0, {}};

		while (minHeap.size()) {
			auto temp = *minHeap.begin();
			minHeap.erase(temp);
			int v = temp.second, ct = 0;

			for (auto &it : adj[v]) {
				if (dist[it].first > temp.first + wt[v][ct] && !blocked[v][it]) {
					minHeap.erase({dist[it].first, it});
					dist[it].first = temp.first + wt[v][ct];
					dist[it].second = dist[v].second;
					dist[it].second.push_back(v);
					minHeap.insert({dist[it].first, it});
				}
				ct++;
			}
		}
		return dist;
	}

	vector<vector<vector<pair<int, vector<int>>>>> getPaths(vector<vector<int>> &adj, vector<vector<int>> &wt) {
		vector<vector<pair<int, vector<int>>>> paths, paths2;
		ofstream fp;
		fp.open(rtFile);
		int n = adj.size();

		vector<vector<int>> blocked(n, vector<int>(n, 0));

		for (int c = 0; c < adj.size(); ++c) {
			paths.push_back(getPath(adj, wt, blocked, c));
			fp << "Node " << c << endl;
			int ct = 0;
			for (auto &itr : paths.back()) {
				fp << ct++ << " \t| " << itr.first << " \t| ";
				itr.second.push_back(ct - 1);
				for (auto &it : itr.second) fp << it << "->";
				fp << endl;
			}
		}

		for (int c = 0; c < adj.size(); ++c) {
			paths2.push_back({});
			for (int r = 0; r < adj.size(); ++r) {
				for (int k = 0; k < paths[c][r].second.size() - 1; ++k) {
					blocked[paths[c][r].second[k]][paths[c][r].second[k + 1]] = 1;
					blocked[paths[c][r].second[k + 1]][paths[c][r].second[k]] = 1;
				}

				auto temp = getPath(adj, wt, blocked, c);
				paths2.back().push_back(temp[r]);
				for (int k = 0; k < paths[c][r].second.size() - 1; ++k) {
					blocked[paths[c][r].second[k]][paths[c][r].second[k + 1]] = 0;
					blocked[paths[c][r].second[k + 1]][paths[c][r].second[k]] = 0;
				}
			}
			fp << "Node " << c << endl;
			int ct = 0;
			for (auto &itr : paths2.back()) {
				fp << ct++ << " \t| " << itr.first << " \t| ";
				itr.second.push_back(ct - 1);
				for (auto &it : itr.second) fp << it << "->";
				fp << endl;
			}
		}

		return {paths,paths2};
	}

    bool optimisticApproach(double bequiv, vector<vector<double>> &linkCapacity, vector<int> &routePath, bool allocate,int *labelId){
    	int n = routePath.size();
    	bool isFeasible = 1;
    	ofstream fp;
    	
    	if(allocate) fp.open(ftFile,ios_base::app);
    	
    	if(allocate && n>1){
    		fp<<"-1 -1 "<<routePath[1]<<" "<<*labelId<<endl;
    		(*labelId)++;
    	}

    	for(int i=0;i<n-1;i++){
    		int u = routePath[i];
    		int v = routePath[i+1];
    		if(allocate){
    			linkCapacity[u][v] -= bequiv;
    			linkCapacity[v][u] -= bequiv;
    			fp<<u<<" "<<(*labelId)-1<<" ";
    			if(i+1 == n-1){
    				fp<<"-1 -1"<<endl;
    			}
    			else{
    				fp<<routePath[i+2]<<" "<<(*labelId)<<endl;
    				(*labelId)++;
    			}
    		}
    		else{
    			if(bequiv > linkCapacity[u][v]) isFeasible = 0;
    		}
    	}
    	
    	if(allocate) fp.close();

    	return isFeasible;
    }

    bool pessimisticApproach(double bmax, vector<vector<double>> &linkCapacity, vector<int> &routePath, bool allocate,int *labelId){
    	int n = routePath.size();
    	bool isFeasible = 1;
    	ofstream fp;
    	
    	if(allocate) fp.open(ftFile,ios_base::app);
    	
    	if(allocate && n>1){
    		fp<<"-1 -1 "<<routePath[1]<<" "<<*labelId<<endl;
    		(*labelId)++;
    	}

    	for(int i=0;i<n-1;i++){
    		int u = routePath[i];
    		int v = routePath[i+1];
    		if(allocate){
    			linkCapacity[u][v] -= bmax;
    			linkCapacity[v][u] -=bmax;
    			fp<<u<<" "<<(*labelId)-1<<" ";
    			if(i+1 == n-1){
    				fp<<"-1 -1"<<endl;
    			}
    			else{
    				fp<<routePath[i+2]<<" "<<(*labelId)<<endl;
    				(*labelId)++;
    			}
    		}
    		else{
    			if(bmax > linkCapacity[u][v]) isFeasible = 0;
    		}
    	}
    	
    	if(allocate) fp.close();

    	return isFeasible;
    }

    void loadConnections(vector<vector<double>> &linkCapacity, vector<vector<vector<pair<int,vector<int>>>>> &routingTable){
    	int N;
    	int labelId = 1;
    	ifstream fp;
    	fp.open(connectionFile);
    	fp>>N;

    	int u,v;
    	double bmin,bavg,bmax;
        int acceptedConnections = 0;
    	ofstream f(pathFile);
    	for(int i=0;i<N;i++){
    		fp>>u>>v>>bmin>>bavg>>bmax;
    		double bequiv = min(bmax, bavg + 0.25*(bmax - bmin));
    		// Iterate over shortest and 2nd shortest path to see if connection can be accomodated
    		for(int j=0;j<2;j++){
    			if(P == 0){
    				bool feasible = optimisticApproach(bequiv, linkCapacity, routingTable[j][u][v].S, 0, &labelId);
    				if(feasible){
                        acceptedConnections++;
    					int startLabel = labelId;
    					optimisticApproach(bequiv, linkCapacity, routingTable[j][u][v].S, 1, &labelId);
    					
    					f<<i+1<<" \t| "<<u<<" \t| "<<v<<" \t| "<<routingTable[j][u][v].F<<" \t| ";
    					for(int k=startLabel;k<labelId;k++){
    						if(k==labelId-1){
    							f<<k;
    						}
    						else{
    							f<<k<<"->";
    						}
    					}
    					f<<endl;
    					break;
    				}
    			}
    			else{
    				bool feasible = pessimisticApproach(bmax, linkCapacity, routingTable[j][u][v].S, 0, &labelId);
    				if(feasible){
                        acceptedConnections++;
    					int startLabel = labelId;
    					pessimisticApproach(bmax, linkCapacity, routingTable[j][u][v].S, 1, &labelId);

    					f<<i+1<<" \t| "<<u<<" \t| "<<v<<" \t| "<<routingTable[j][u][v].F<<" \t| ";
    					for(int k=startLabel;k<labelId;k++){
    						if(k==labelId-1){
    							f<<k;
    						}
    						else{
    							f<<k<<"->";
    						}
    					}
    					f<<endl;
    					break;
    				}
    			}
    		}
    	}
    	f.close();
    	fp.close();

        cout<<"Accepted Connections : "<<acceptedConnections<<endl;
        cout<<"Total Connections :"<<N<<endl;
    }

    void loadNetworkTopology(vector<vector<int>> &topology, vector<vector<int>> &linkCost, vector<vector<double>> &linkCapacity){
    	int N,E;
    	ifstream fp;
    	fp.open(topologyFile);
    	fp>>N>>E;
    	
    	topology.resize(N);
    	linkCost.resize(N);
    	linkCapacity.resize(N);
    	for(int i=0;i<N;i++) linkCapacity[i].resize(N);

    	int u,v,cost;
    	double capacity;
    	for(int i=0;i<E;i++){
    		fp>>u>>v>>cost>>capacity;
    		topology[u].push_back(v);
    		if(hopDist == 0){
    			linkCost[u].push_back(1);
    		}
    		else{
    			linkCost[u].push_back(cost);
    		}
    		topology[v].push_back(u);
    		if(hopDist == 0){
    			linkCost[v].push_back(1);
    		}
    		else{
    			linkCost[v].push_back(cost);
    		}
    		linkCapacity[u][v] = capacity;
    		linkCapacity[v][u] = capacity;
    	}

    	fp.close();
    }

    bool validArguments(){
    	ifstream fp;
    	bool valid = true;

    	fp.open(topologyFile);
    	if(!fp.is_open()) valid = 0;
    	fp.close();

    	fp.open(connectionFile);
    	if(!fp.is_open()) valid = 0;
    	fp.close();

    	if(hopDist != 0 && hopDist != 1) valid = 0;

    	if(P != 0 && P!=1) valid = 0;

    	return valid;
    }

    int main(int argc, char **argv){
        deathnote();
        if(argc < 15){
        	cout<<"Missing arguments!!!\n";
        	return 0;
        }

        for(int i=1;i<argc;i+=2){
        	string param(argv[i]);
        	if(param == "-top"){
        		string paramValue(argv[i+1]);
        		topologyFile = paramValue;
        	}
        	else if(param == "-conn"){
        		string paramValue(argv[i+1]);
        		connectionFile = paramValue;
        	}
        	else if(param == "-rt"){
        		string paramValue(argv[i+1]);
        		rtFile = paramValue;
        	}
        	else if(param == "-ft"){
        		string paramValue(argv[i+1]);
        		ftFile = paramValue;
        	}
        	else if(param == "-path"){
        		string paramValue(argv[i+1]);
        		pathFile = paramValue;
        	}
        	else if(param == "-flag"){
        		int paramValue = stoi(argv[i+1]);
        		hopDist = paramValue;
        	}
        	else if(param == "-p"){
        		int paramValue = stoi(argv[i+1]);
        		P = paramValue;
        	}
        	else{
        		cout<<"Invalid argument : " + param<<endl;
        	}
        }

        if(!validArguments()){
        	cout<<"Parameter values are invalid!!!"<<endl;
        	return 0;
        }


        vector<vector<int>> topology;
        vector<vector<int>> linkCost;
        vector<vector<double>> linkCapacity;
        loadNetworkTopology(topology,linkCost,linkCapacity);

        // vector<vector<vector<pair<int,vector<int>>>>> routingTable;
        // routingTable[0] -> 1st shortest
        // routingTable[1] -> 2nd shortest
        vector<vector<vector<pair<int,vector<int>>>>> routingTable = getPaths(topology, linkCost);

        loadConnections(linkCapacity,routingTable);
        return 0;
    }
    