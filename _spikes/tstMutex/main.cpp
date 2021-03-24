#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <unistd.h>

struct Player
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::thread thr;

    enum State
    {
        Stopped,
        Paused,
        Playing,
        Quit
    };

    State state;
    int counter;

    void signal_state(State st)
    {
        std::cout << "before signal_state mutex lock" << std::endl;
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "after signal_state mutex lock" << std::endl;
        if (st != state)
        {
            state = st;
            std::cout << "state is now " << state << std::endl;
            std::cout << "before signal_state notify_one" << std::endl;
            cv.notify_one();
            std::cout << "after signal_state notify_one" << std::endl;
        }
    }

    // main player monitor
    void monitor()
    {
        std::cout << "enter monitor" << std::endl;
        std::cout << "before monitor mutex lock" << std::endl;
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "after monitor mutex lock" << std::endl;
        bool bQuit = false;

        std::cout << "enter bQuit loop" << std::endl;
        while (!bQuit)
        {
            std::cout << "switching for state=" << state << std::endl;
            switch (state)
            {
            case Playing:
                std::cout << ++counter << '.';
                std::cout << "before cv wait of playing" << std::endl;
                cv.wait_for(lock, std::chrono::milliseconds(200), [this]() {
                    std::cout << "predicate playing? " << (state != Playing) << std::endl;
                    return state != Playing;
                });
                break;

            case Stopped:
                std::cout << "before cv wait of stopped" << std::endl;
                cv.wait(lock, [this]() {
                    std::cout << "predicate stopped? " << (state != Stopped) << std::endl;
                    return state != Stopped;
                });
                std::cout << '\n';
                counter = 0;
                break;

            case Paused:
                std::cout << "before cv wait of paused" << std::endl;
                cv.wait(lock, [this]() {
                    std::cout << "predicate paused? " << (state != Paused) << std::endl;
                    return state != Paused;
                });
                break;

            case Quit:
                std::cout << "setting bQuit=true" << std::endl;
                bQuit = true;
                break;
            }
        }
    }

public:
    Player()
        : state(Stopped), counter(0)
    {
        std::cout << "initializing thread" << std::endl;
        thr = std::thread(std::bind(&Player::monitor, this));
        std::cout << "thread initialized" << std::endl;
    }

    ~Player()
    {
        std::cout << "enter destructor" << std::endl;
        quit();
        thr.join();
    }

    void stop()
    {
        std::cout << "stop()" << std::endl;
        signal_state(Stopped);
    }
    void play()
    {
        std::cout << "play()" << std::endl;
        signal_state(Playing);
    }
    void pause()
    {
        std::cout << "pause()" << std::endl;
        signal_state(Paused);
    }
    void quit()
    {
        std::cout << "quit()" << std::endl;
        signal_state(Quit);
    }
};

int main()
{
    Player player;
    player.play();
    sleep(3);
    player.pause();
    sleep(3);
    player.play();
    sleep(3);
    player.stop();
    sleep(3);
    player.quit();
    sleep(3);
}