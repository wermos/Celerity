#ifndef INSTRUMENTOR_HPP
#define INSTRUMENTOR_HPP

#include <string>
#include <fstream>
#include <algorithm>

#include <chrono>
#include <mutex>
#include <thread>

#define PROFILE 1

#if PROFILE == 1
	/**
	* __clang__ checks for the clang compiler,
	* __GNUC__ along with __GNUG__ checks for the GCC compiler,
	* and _MSC_VER checks for the MSVC compiler.
	*
	*/
	#ifndef FUNCTION__NAME
		#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
		#define FUNCTION__NAME __PRETTY_FUNCTION__
		#elif defined(_MSC_VER)
		namespace {
			// This function exists to delete the "__cdecl" part of the function
			// name from the __FUNCSIG__ output
			inline const char* cdecl_delete(const char* functionName) {
				std::string funcName(functionName);
				int i = funcName.find("__cdecl ");
				return funcName.erase(i, 8).c_str();
			}
		}
		#define FUNCTION__NAME cdecl_delete(__FUNCSIG__)
		#endif // compiler checking
	#endif // FUNCTION__NAME
	#define PROFILE_SCOPE(name) InstrumentationTimer timer##__FILE__##__LINE__(name)
	#define PROFILE_FUNCTION() PROFILE_SCOPE(FUNCTION__NAME)
	#else
	#define PROFILE_SCOPE(name)
	#define PROFILE_FUNCTION()
#endif // PROFILE

// Lifted off of Cherno: https://gist.github.com/TheCherno/31f135eea6ee729ab5f26a6908eb3a5e
// With minor modifications (most importantly, the mutex stuff) made by @davechurchill here: https://pastebin.com/qw5Neq4U
// Link to video: https://www.youtube.com/watch?v=xlAH4dbMVnU
//
// Basic (thread-safe due to upgrades) instrumentation profiler by Cherno
//
// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Instrumentor::get().beginSession("Session Name");        // Begin session
// {
//     InstrumentationTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// Instrumentor::get().endSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.

struct ProfileResult {
    std::string m_name;
    long long m_startTime, m_endTime;
    uint32_t m_threadID;
};

class Instrumentor {
	public:
		// Deleting the copy constructor and copy assignment operator; standard procedure in
		// singleton classes.
		Instrumentor (const Instrumentor&) = delete;
		Instrumentor operator=(const Instrumentor&) = delete;

		void beginSession(const std::string& name, const std::string& filepath = "results.json") {
			if (m_activeSession) {
				endSession();
			}
        	m_activeSession = true;
			m_sessionName = name;

			m_outputStream.open(filepath);
			writeHeader();
		}

		void endSession() {
			if (!m_activeSession) {
				return;
			}

        	m_activeSession = false;
			writeFooter();
			m_outputStream.close();
			m_profileCount = 0;
		}

		void writeProfile(const ProfileResult& result) {
			std::lock_guard<std::mutex> lock(m_lock);

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
			// Forced flushes are not necessary, as the OS makes sure that data in the
			// internal buffers are written to disk even if the applciation crashes.
			// Reference: https://stackoverflow.com/a/5132379/12591388
		}

		void writeHeader() {
			m_outputStream << "{\"otherData\": {},\"traceEvents\":[";
			// Force flush not necessary
		}

		void writeFooter() {
			m_outputStream << "]}";
			// Force flush not necessary
		}

		static Instrumentor& get() {
			static Instrumentor instance;
			return instance;
		}

		~Instrumentor() {
			endSession();
		} // just in case someone forgets to end the session themselves.

	private:
		// Making the constructor private so as to prevent users from constructing an object
		Instrumentor()
		{}

		std::string m_sessionName = "None";
		bool m_activeSession = false;
		std::ofstream m_outputStream;
		std::mutex m_lock;
		int m_profileCount = 0;
};

class InstrumentationTimer {
	public:
		InstrumentationTimer(const char* name)
			: m_name(name), m_profRes({name, 0, 0, 0}) {
			m_startTimepoint = std::chrono::high_resolution_clock::now();
		}

		void stop() {
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			m_profRes.m_startTime = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();
			m_profRes.m_endTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			m_profRes.m_threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::get().writeProfile(m_profRes);

			m_stopped = true;
		}

		~InstrumentationTimer() {
			if (!m_stopped) {
				stop();
			}
		}

	private:
		const char* m_name;
		ProfileResult m_profRes;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
		bool m_stopped = false;
};

#endif // INSTRUMENTOR_HPP
