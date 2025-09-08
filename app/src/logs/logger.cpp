#include "logs/logger.hpp"
#include <fstream>

namespace logs {

  // TODO: This maybe could use the paths?
  constexpr std::string default_log_name = "log.txt";

  std::string getShorthand(MsgType type) {
    switch(type) {
      case MsgType::Info:
        return "INFO";
      case MsgType::Oddity:
        return "ODD";
      case MsgType::Warning:
        return "WARNING";
      case MsgType::Error:
        return "ERROR";
      case MsgType::FatalError:
        return "FATAL";
      default:
        return "???";
    }
  }

  constexpr std::string reset_color = "\033[0m";
  std::string getColorEscapeSequence(MsgType type) {
    switch(type) {
      case MsgType::Info:
        return "\033[38;5;27m";
      case MsgType::Oddity:
        return "\033[38;5;154m";
      case MsgType::Warning:
        return "\033[38;5;11m";
      case MsgType::Error:
        return "\033[38;5;214m";
      case MsgType::FatalError:
        return "\033[38;5;9m";
      default:
        return "";
    }
  }


  LogMessage::LogMessage(MsgType type, std::string content) 
  : type(type), content(content) {}

  std::string LogMessage::toString() const {
    return "[" + getShorthand(type) + "]: " + content;
  }
  std::string LogMessage::prettyToString() const {
    return getColorEscapeSequence(type)
      + "[" + getShorthand(type) + "]: " + content + reset_color;
  }



  std::deque<LogMessage> Logger::messages;
  size_t Logger::capacity;
  MsgType Logger::sensitivity;

  void Logger::addMessage(LogMessage message) {
    // Ignore messages that are not considered important enough
    // by the 'sensitivity' filter
    if(message.type < sensitivity) return;

    messages.push_back(message);
    while(messages.size() > capacity) messages.pop_back();
  }

  void Logger::init(size_t capacity, MsgType sensitivity) {
    messages.clear();
    Logger::capacity = capacity;
    Logger::sensitivity = sensitivity;
  }

  void Logger::logInfo(std::string message) {
    addMessage(LogMessage(MsgType::Info, message));
  }
  void Logger::logOddity(std::string message) {
    addMessage(LogMessage(MsgType::Oddity, message));
  }
  void Logger::logWarning(std::string message) {
    addMessage(LogMessage(MsgType::Warning, message));
  }
  void Logger::logError(std::string message) {
    addMessage(LogMessage(MsgType::Error, message));
  }
  void Logger::logFatal(std::string message) {
    addMessage(LogMessage(MsgType::FatalError, message));
  }

  void Logger::logDump(std::ostream& output_stream, bool pretty) {
    for(LogMessage& msg : messages)
      output_stream << (pretty ? msg.prettyToString() : msg.toString()) << "\n";
  }
  void Logger::logDump(std::string filename, bool pretty) {
    std::ofstream out(filename);
    logDump(out, pretty);
  }
  void Logger::logDump(bool pretty) {
    logDump(default_log_name);
  }

  void Logger::logFatalAndDump(std::string message,
                               std::ostream& output_stream, bool pretty) {
    logFatal(message);
    logDump(output_stream, pretty);
  }
  void Logger::logFatalAndDump(std::string message,
                               std::string filename, bool pretty) {
    logFatal(message);
    logDump(filename, pretty);
  }
  void Logger::logFatalAndDump(std::string message, bool pretty) {
    logFatal(message);
    logDump(pretty);
  }

  namespace testing {
    void logAll() {
      logs::Logger::logInfo("Phony Info");
      logs::Logger::logOddity("Phony Oddity");
      logs::Logger::logWarning("Phony Warning");
      logs::Logger::logError("Phony Error");
      logs::Logger::logFatal("Phony Fatal Error");
    }
  }
}
