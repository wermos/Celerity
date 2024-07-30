#pragma once

#include <atomic>
#include <chrono>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <sstream>

class ProgressReporter {
public:
    ProgressReporter(int totalScanLines, int updateInterval = 1)
        : totalScanLines(totalScanLines), scanLinesLeft(totalScanLines),
          updateInterval(updateInterval), startTime(std::chrono::steady_clock::now()), lastUpdate(startTime) {
        auto logger = spdlog::stdout_color_mt("progress_logger");
        logger->set_pattern("%v"); // Set pattern to only show the message
        spdlog::set_default_logger(logger);

        spdlog::info("Starting render with {} total scanlines", totalScanLines);
    }

    void start() {
        startTime = std::chrono::steady_clock::now();
        scanLinesLeft = totalScanLines;
    }

    void update() {
        using namespace std::chrono;
        auto now = steady_clock::now();
        if (duration_cast<seconds>(now - lastUpdate).count() >= updateInterval) {
            lastUpdate = now;
            displayProgressBar();
        }
    }

    void scanlineProcessed() {
        --scanLinesLeft;
    }

private:
    int totalScanLines;
    std::atomic<int> scanLinesLeft;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point lastUpdate;
    int updateInterval;
    std::mutex mtx;

    void displayProgressBar() {
        std::lock_guard<std::mutex> lock(mtx);
        int remaining = scanLinesLeft.load();
        int processed = totalScanLines - remaining;
        float progress = static_cast<float>(processed) / totalScanLines;

        int barWidth = 50;
        std::ostringstream bar;
        bar << "\r[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) bar << "=";
            else if (i == pos) bar << ">";
            else bar << " ";
        }
        bar << "] " << int(progress * 100.0) << "%";

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
        auto eta = progress > 0 ? static_cast<int>((elapsed / progress) * (1.0 - progress)) : 0;
        bar << " ETA: " << eta << "s  ";

        spdlog::default_logger_raw()->log(spdlog::level::info, bar.str());
    }
};
