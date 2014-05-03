/**
 * @author Frano Petric
 *
 * \section Description
 * This is the loader for Logger module
 */

#include <signal.h>
#include <boost/shared_ptr.hpp>
#include <alcommon/albroker.h>
#include <alcommon/almodule.h>
#include <alcommon/albrokermanager.h>
#include <alcommon/altoolsmain.h>

#include "logmodule_ja.hpp"


#ifdef LOGGER_JA_IS_REMOTE
# define ALCALL
#else
# ifdef _WIN32
#  define ALCALL __declspec(dllexport)
# else
#  define ALCALL
# endif
#endif

extern "C"
{
  ALCALL int _createModule(boost::shared_ptr<AL::ALBroker> pBroker)
  {
    // init broker with the main broker instance
    // from the parent executable
    AL::ALBrokerManager::setInstance(pBroker->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(pBroker);
    //AL::ALBrokerManager::getInstance()->addBroker(AL::ALBrokerManager::getInstance()->getBrokerByIPPort("161.53.68.46", 9559));
    AL::ALModule::createModule<Logger>( pBroker, "Logger" );

    return 0;
  }

  ALCALL int _closeModule()
  {
    return 0;
  }
}

#ifdef LOGGER_JA_IS_REMOTE
  int main(int argc, char *argv[])
  {
    // pointer to createModule
    TMainType sig;
    sig = &_createModule;
    // call main
    ALTools::mainFunction("Logger", argc, argv, sig);
  }
#endif

