#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;
using BusStop = vector<pair<string, vector<string>>>;
enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	string typeStr;
	is >> typeStr;
	if (typeStr == "NEW_BUS") {
		q.type = QueryType::NewBus;
		is >> q.bus;
		int scount = 0;
		is >> scount;
		q.stops.resize(scount);
		for (auto& stop : q.stops) 
			is >> stop;
	}
	else if (typeStr == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (typeStr == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (typeStr == "ALL_BUSES") 
		q.type = QueryType::AllBuses;
	return is;
}

struct BusesForStopResponse {vector<string> buses;};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.buses.empty()) 
		os << "No stop" << endl;
	else {
		for (const auto& bus : r.buses) 
			os << bus << " ";
		os << endl;
	}
	return os;
}

struct StopsForBusResponse {
	string bus;
	BusStop StopBus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.StopBus.empty()) 
		os << "No bus" << endl;
	else {
		for (const auto& SAB : r.StopBus) {
			os << "Stop " << SAB.first << ":";
			if (SAB.second.size() == 1) 
				os << " no interchange" << endl;
			else 
				for (const auto& bus : SAB.second) 
					if (bus != r.bus) 
						os << " " << bus;
				os << endl;
		}
	}
	return os;
}

struct AllBusesResponse {map<string, vector<string>> BusToStop;};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.BusToStop.empty()) 
		os << "No buses" << endl;
	else {
		for (const auto& bus_and_stops : r.BusToStop) {
			os << "Bus " << bus_and_stops.first << ":";
			for (const auto& stop : bus_and_stops.second) 
				os << " " << stop;
			os << endl;
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		BusToStop.insert(make_pair(bus, stops));
		for (const auto& stop : stops) 
			StopBus[stop].push_back(bus);
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		return (StopBus.count(stop) == 0) ? BusesForStopResponse{ vector<string>() } : BusesForStopResponse{ StopBus.at(stop) };
	}	

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		BusStop result;
		if (BusToStop.count(bus) > 0) 
			for (const auto& stop : BusToStop.at(bus))
				result.push_back(make_pair(stop, StopBus.at(stop)));
		return StopsForBusResponse{ bus, result };
	}

	AllBusesResponse GetAllBuses() const { return AllBusesResponse{ BusToStop }; };

private:
	map<string, vector<string>> StopBus, BusToStop;
};

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}
