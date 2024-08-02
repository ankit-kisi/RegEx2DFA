// WindowManagement.cpp
#include "windowManagement.h"

#include <cstdlib>  // For std::system
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
void WindowsWindowManagement::openFile(const std::string& filePath) {
  std::string command = "start \"\" \"" + filePath + "\"";
  std::system(command.c_str());
}

// Callback function to find and close windows by title
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
  std::vector<std::string>* titles =
      reinterpret_cast<std::vector<std::string>*>(lParam);
  char windowTitle[256];

  if (GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle))) {
    std::string title(windowTitle);
    for (const auto& targetTitle : *titles) {
      if (title.find(targetTitle) != std::string::npos) {
        // Send the close message
        SendMessage(hwnd, WM_CLOSE, 0, 0);
        return TRUE;  // Continue enumeration
      }
    }
  }
  return TRUE;  // Continue enumeration
}

void WindowsWindowManagement::closeWindows(
    const std::vector<std::string>& titles) {
  // Enumerate all top-level windows and close those matching the titles
  EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&titles));

  std::cout << "Attempted to close specified windows." << std::endl;
}

#endif

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
