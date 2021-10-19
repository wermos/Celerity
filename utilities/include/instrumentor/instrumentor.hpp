#ifndef INSTRUMENTOR_HPP
#define INSTRUMENTOR_HPP

#include <string>
#include <fstream>
#include <algorithm>

#include <chrono>
#include <thread>

// Lifted off of Cherno: https://gist.github.com/TheCherno/31f135eea6ee729ab5f26a6908eb3a5e
// Basic instrumentation profiler by Cherno

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Instrumentor::eet().beginSession("Session Name");        // Begin session
// {
//     InstrumentationTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// Instrumentor::get().endSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.
//

struct ProfileResult {
    std::string m_name;
    long long m_startTime, m_endTime;
    uint32_t m_threadID;
};

struct InstrumentationSession {
    std::string m_name;
};

class Instrumentor {
	public:
		Instrumentor() : m_currentSession(nullptr), m_profileCount(0)
		{}

		void beginSession(const std::string& name, const std::string& filepath = "results.json") {
			m_outputStream.open(filepath);
			writeHeader();
			m_currentSession = new InstrumentationSession{name};
		}

		void endSession() {
			writeFooter();
			m_outputStream.close();
			delete m_currentSession;
			m_currentSession = nullptr;
			m_profileCount = 0;
		}

		void writeProfile(const ProfileResult& result) {
			if (m_profileCount++ > 0)
				m_outputStream << ",";

			std::string name = result.m_name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_outputStream << "{";
			m_outputStream << "\"cat\":\"function\",";
			m_outputStream << "\"dur\":" << (result.m_endTime - result.m_startTime) << ',';
			m_outputStream << "\"name\":\"" << name << "\",";
			m_outputStream << "\"ph\":\"X\",";
			m_outputStream << "\"pid\":0,";
			m_outputStream << "\"tid\":" << result.m_threadID << ",";
			m_outputStream << "\"ts\":" << result.m_startTime;
			m_outputStream << "}";

			m_outputStream.flush();
		}

		void writeHeader() {
			m_outputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_outputStream.flush();
		}

		void writeFooter() {
			m_outputStream << "]}";
			m_outputStream.flush();
		}

		static Instrumentor& get() {
			static Instrumentor instance;
			return instance;
		}

	private:
		InstrumentationSession* m_currentSession;
		std::ofstream m_outputStream;
		int m_profileCount;
};

class InstrumentationTimer {
	public:
		InstrumentationTimer(const char* name) : m_name(name), m_stopped(false) {
			m_startTimepoint = std::chrono::high_resolution_clock::now();
		}

		void stop() {
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long startTime = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();
			long long endTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::get().writeProfile({m_name, startTime, endTime, threadID});

			m_stopped = true;
		}

		~InstrumentationTimer() {
			if (!m_stopped) {
				stop();
			}
		}

	private:
		const char* m_name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
		bool m_stopped;
};

#endif // INSTRUMENTOR_HPP
