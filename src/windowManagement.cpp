// WindowManagement.cpp
#include "windowManagement.h"

#include <cstdlib>  // For std::system
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
void WindowsWindowManagement::openFile(const std::string& filePath) {
  std::string command = "start " + filePath;
  std::system(command.c_str());
}

void WindowsWindowManagement::closeWindows(
    const std::vector<std::string>& titles) {
  for (const auto& title : titles) {
    HWND hwnd = FindWindow(NULL, title.c_str());
    if (hwnd) {
      SendMessage(hwnd, WM_CLOSE, 0, 0);
    } else {
      std::cerr << "Window with title '" << title << "' not found."
                << std::endl;
    }
  }
}
#endif

#if defined(__APPLE__)
void MacOSWindowManagement::openFile(const std::string& filePath) {
  std::string command = "open " + filePath;
  std::system(command.c_str());
}

void MacOSWindowManagement::closeWindows(
    const std::vector<std::string>& titles) {
  for (const auto& title : titles) {
    std::string command =
        "osascript -e 'tell application \"Preview\" to close (every window "
        "whose name contains \"" +
        title + "\")'";
    std::system(command.c_str());
  }
}
#endif

#if defined(__linux__)
void LinuxWindowManagement::openFile(const std::string& filePath) {
  std::string command = "xdg-open " + filePath;
  std::system(command.c_str());
}

void LinuxWindowManagement::closeWindows(
    const std::vector<std::string>& titles) {
  for (const auto& title : titles) {
    std::string command = "wmctrl -l | grep \"" + title +
                          "\" | awk '{print $1}' | xargs -I {} wmctrl -ic {}";
    std::system(command.c_str());
  }
}
#endif

WindowManagement* createWindowManagement() {
#if defined(_WIN32) || defined(_WIN64)
  return new WindowsWindowManagement();
#elif defined(__APPLE__)
  return new MacOSWindowManagement();
#elif defined(__linux__)
  return new LinuxWindowManagement();
#else
  std::cerr << "Unsupported platform." << std::endl;
  return nullptr;
#endif
}
