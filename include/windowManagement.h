// WindowManagement.h
#ifndef WINDOWMANAGEMENT_H
#define WINDOWMANAGEMENT_H

#include <string>
#include <vector>

// Base class
class WindowManagement {
 public:
  virtual ~WindowManagement() = default;

  // Method to open a file
  virtual void openFile(const std::string& filePath) = 0;

  // Method to close windows by title
  virtual void closeWindows(const std::vector<std::string>& titles) = 0;
};

// Platform-specific implementations
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

class WindowsWindowManagement : public WindowManagement {
 public:
  void openFile(const std::string& filePath) override;
  void closeWindows(const std::vector<std::string>& titles) override;
};
#endif

#if defined(__APPLE__)
class MacOSWindowManagement : public WindowManagement {
 public:
  void openFile(const std::string& filePath) override;
  void closeWindows(const std::vector<std::string>& titles) override;
};
#endif

#if defined(__linux__)
class LinuxWindowManagement : public WindowManagement {
 public:
  void openFile(const std::string& filePath) override;
  void closeWindows(const std::vector<std::string>& titles) override;
};
#endif

// Factory function to create the appropriate WindowManagement
WindowManagement* createWindowManagement();

#endif  // WINDOWMANAGEMENT_H
