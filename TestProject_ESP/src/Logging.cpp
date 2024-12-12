#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

class LoggingFile {
private:
    String filePath;
    size_t maxFileSize; // Maximum file size in bytes
    size_t maxLogEntries; // Maximum number of log entries (optional)
    bool isMounted;

    void rotateLogs() {
        File file = LittleFS.open(filePath, "r");
        if (!file) return;

        // Read the file and keep the last `maxLogEntries` lines
        String logs = "";
        size_t lineCount = 0;
        while (file.available()) {
            String line = file.readStringUntil('\n');
            logs += line + '\n';
            lineCount++;
            if (lineCount > maxLogEntries) {
                logs = logs.substring(logs.indexOf('\n') + 1); // Remove the first line
            }
        }
        file.close();

        // Rewrite the file with rotated logs
        file = LittleFS.open(filePath, "w");
        if (file) {
            file.print(logs);
            file.close();
        }
    }

public:
    LoggingFile(String path = "/log.txt", size_t maxFileSize = 1024 * 1024, size_t maxLogEntries = 1000)
        : filePath(path), maxFileSize(maxFileSize), maxLogEntries(maxLogEntries), isMounted(false) {}

    bool begin() {
        isMounted = LittleFS.begin();
        return isMounted;
    }

    void log(const String &message) {
        if (!isMounted) return;

        File logFile = LittleFS.open(filePath, "a");
        if (!logFile) {
            Serial.println("Failed to open log file for appending.");
            return;
        }

        // Prepare the log entry with a timestamp
        String logEntry = "[" + String(millis()) + "] " + message + "\n";

        // Check if adding this log would exceed the maximum file size
        if ((logFile.size() + logEntry.length()) > maxFileSize) {
            logFile.close();
            rotateLogs();
            logFile = LittleFS.open(filePath, "a"); // Reopen for appending
            if (!logFile) return;
        }

        logFile.print(logEntry);
        logFile.close();
    }

    void clear() {
        if (!isMounted) return;

        File logFile = LittleFS.open(filePath, "w");
        if (logFile) logFile.close();
    }

    void readLogs() {
        if (!isMounted) return;

        File logFile = LittleFS.open(filePath, "r");
        if (!logFile) {
            Serial.println("Failed to open log file for reading.");
            return;
        }

        Serial.println("Logs:");
        while (logFile.available()) {
            Serial.println(logFile.readStringUntil('\n'));
        }
        logFile.close();
    }
};
