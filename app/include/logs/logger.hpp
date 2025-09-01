#ifndef LOGS_LOGGER_HPP
#define LOGS_LOGGER_HPP

#include <deque>
#include <string>
#include <ostream>

namespace logs {

  enum class MsgType {
    Info = 1,
    Oddity = 2,
    Warning = 3,
    Error = 4,
    FatalError = 5,
  };

  std::string getShorthand(MsgType type);

  struct LogMessage {
    MsgType type;
    std::string content;
    LogMessage(MsgType type, std::string content);

    std::string toString() const {
      return "[" + getShorthand(type) + "]: " + content;
    }
  };

  class Logger {
  private: 
    static MsgType sensitivity;
    static std::deque<LogMessage> messages;
    static size_t capacity;

    static void addMessage(LogMessage message);
  public:
    // The sensitivity works in the following way:
    // any message of priority lower than the given type will be
    // completely ignored and 
    static void init(size_t capacity, MsgType sensitivity);

    static void logInfo(std::string message);
    static void logOddity(std::string message);
    static void logWarning(std::string message);
    static void logError(std::string message);
    static void logFatalError(std::string message);

    static void logDump(std::ostream& output_stream);
  };
}

#endif
