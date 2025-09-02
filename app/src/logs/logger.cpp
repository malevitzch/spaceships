#include "logs/logger.hpp"

namespace logs {

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
  LogMessage::LogMessage(MsgType type, std::string content) 
  : type(type), content(content) {}

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
  void Logger::logFatalError(std::string message) {
    addMessage(LogMessage(MsgType::FatalError, message));
  }

  void Logger::logDump(std::ostream& output_stream) {
    for(LogMessage& msg : messages)
      output_stream << msg.toString() << "\n";
  }
  void Logger::logFatalAndDump(std::ostream& output_stream, std::string message) {
    logFatalError(message);
    logDump(output_stream);
  }
}
