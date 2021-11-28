#ifndef SAFE_QUEUE
#define SAFE_QUEUE

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

//FIGURE OUT HOW TO PROPERLY CONVERT TO TEMPLATE
class SafeQueue{
    std::queue<std::string> queue;
    std::mutex mutex;
    std::condition_variable condition;
public:
    SafeQueue(){};
    ~SafeQueue(){};

    void enqueue(std::string t){
        std::lock_guard lock(mutex);
        queue.push(t);
        condition.notify_one();
    }

    std::string dequeue(){
        std::unique_lock lock(mutex);
        condition.wait(lock, [this]{return !queue.empty();});
        std::string value = queue.front();
        queue.pop();
        return value;
    }

    std::string tryDequeue(){
        std::lock_guard lock(mutex);
        if (queue.empty()) return "";
        else {
            std::string value = queue.front();
            queue.pop();
            return value;
        }
    }
};

#endif