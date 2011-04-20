

#include "HabuThreads.hpp"

using namespace HabuTech;

class ThreadedClass : public Thread
{
private:
  static void _cdecl ThreadRoutine(void* vpParams);
public:
  ThreadedClass();
  ~ThreadedClass();
};


ThreadedClass::ThreadedClass()
{
  Thread::SetRoutine(&ThreadRoutine, this);
}

ThreadedClass::~ThreadedClass()
{

}

void ThreadedClass::ThreadRoutine(void* vpParameters)
{
  ThreadedClass* pThis = (ThreadedClass*)vpParameters;

  pThis->SignalStarted();

  int i = 0;
  while(pThis->Continue())
  {
    i++;
    Wait(50);
  }

  pThis->SignalStopped();
  return;
}

int main()
{
  //class Mutex* pMutex = new Mutex();
  //pMutex->Lock();
  //pMutex->Unlock();
  //pMutex->Lock();

  //class Event* pEvent = new Event();
  //pEvent->WaitForSignal();
  //pEvent->WaitForSignal();


  ThreadedClass* pExample = new ThreadedClass();
  pExample->Start();
  Wait(5000);
  pExample->Pause();
  Wait(5000);
  pExample->Resume();
  Wait(5000);
  pExample->Stop();
  delete pExample;
  return 0;
}