#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <memory>
#include <vector>
#include <thread>


using uthread_t = std::unique_ptr<std::thread>;
class ThreadPool
{
    ThreadPool();
    static ThreadPool s_threadPool;
    std::vector<uthread_t> m_threadPool;
public:
    static ThreadPool* Factory()
    {
        return  &s_threadPool;
    }
    template<class WORK>
    int Create(WORK _work)
    {
        m_threadPool.push_back(uthread_t(new std::thread(_work)));
        return m_threadPool.size();
    }
    void Join()
    {
        for(auto &t: m_threadPool)
        {
            if((t) && (t->joinable()))
            {
                t->join();
            }
        }
    }
};

#endif // THREADPOOL_H
