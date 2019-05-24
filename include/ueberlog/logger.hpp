#ifndef UEBERLOG_LOGGER_HPP
#define UEBERLOG_LOGGER_HPP

/* easy logger */
class Logger {
  public:
    static Logger &i() {
      static Logger inst;
      return inst;
    }
    enum class Level {
      debug,
      warn,
      error
    };
    private:
#if defined NDEBUG
    Level level{Level::error};
#else
    Level level{Level::debug};
#endif
    public:
    template<typename ...Args>
    void debug( const char *message, Args ...args ) {
      if( level <= Level::debug ) {
        printf ( "[DEBUG]: %s in %d line: ", __FILE__, __LINE__ );
        print  ( message, args...);
      }
    }

    template<typename ...Args>
    void warn( const char *message, Args ...args ) {
      if( level <= Level::warn ) {
        printf ( "[WARN]: %s in %d line: ", __FILE__, __LINE__ );
        print  ( message, args...);
      }
    }

    template<typename ...Args>
    void error( const char *message, Args ...args ) {
      if( level <= Level::error ) {
        printf ( "[ERROR]: %s in %d line: ", __FILE__, __LINE__ );
        print  (message, args...);
      }
    }
    template <typename ...Args>
    void print( const char *message, Args ...args) {
      char *point = const_cast<char *>(message);
      int argscount{0};
      while(*point != '\0') {
        if( *point == '%' ) argscount++;
        point++;
      }
      if( argscount == sizeof...(args) ) {
        printf (message, args...);
      }
    }
    template<>
      void print( const char *message) {
        printf ("%s", message);
      }

};


#endif //UEBERLOG_LOGGER_HPP
