#include <iostream>
#include <utility>
#include <string>
#include <vector>

template <typename T>
class SensorTracker {
	private:
		std::vector<std::pair<std::string, T>> sensorData;

	public:
		void addReading(const std::string& timestamp, const T& value) {
			sensorData.push_back({timestamp, value});
		}
		void displayReadings() const {
			std::cout << "--- Temperature Readings ---" << std::endl;
			for(const auto& reading:sensorData)
				std::cout << "[" << reading.first << "]: " << reading.second << std::endl;
		}
		T calculateAverage() const {
			if(sensorData.empty())
				throw std::runtime_error("Cannot calculate average. No sensor data available.");
			T sum = T();
			for (const auto& reading : sensorData)
				sum+=reading.second;
			return sum / static_cast<T>(sensorData.size());
		}
};

//int main() {
//	std::cout << "Sensor Tracker" << std::endl;
//
//	SensorTracker<double> tracker;
//	tracker.addReading("08:00", 22.5);
//	tracker.addReading("09:00", 23.1);
//	tracker.addReading("10:00", 24.0);
//
//	tracker.displayReadings();
//	std::cout << "Average Temperature: " << tracker.calculateAverage() << std::endl << std::endl;
//
//	SensorTracker<int> emptyTracker;
//	std::cout << "--- Testing Empty Tracker ---" << std::endl;
//
//	try {
//		std::cout << emptyTracker.calculateAverage() << std::endl;
//	}
//	catch (const std::exception& e) {
//		std::cout << "Error caught: " << e.what() << std::endl;
//	}
//
//	return 0;
//}