#ifndef BUFFERED_CHANNEL_H
#define BUFFERED_CHANNEL_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <stdexcept>
#include <utility>

template<typename T>
class buffered_channel {
public:
    explicit buffered_channel(size_t buffer_size)
        : capacity_(buffer_size) {
        if (buffer_size == 0) {
            throw std::invalid_argument("Buffer size must be positive");
        }
    }

    ~buffered_channel() {
        close();
    }

    buffered_channel(const buffered_channel&) = delete;
    buffered_channel& operator=(const buffered_channel&) = delete;
    buffered_channel(buffered_channel&&) = delete;
    buffered_channel& operator=(buffered_channel&&) = delete;

    void send(T value) {
        std::unique_lock<std::mutex> lock(mutex_);

        not_full_.wait(lock, [this]() {
            return queue_.size() < capacity_ || closed_;
            });

        if (closed_) {
            throw std::runtime_error("Channel is closed");
        }

        queue_.push(std::move(value));
        not_empty_.notify_one();
    }

    std::pair<T, bool> recv() {
        std::unique_lock<std::mutex> lock(mutex_);

        not_empty_.wait(lock, [this]() {
            return !queue_.empty() || closed_;
            });

        if (!queue_.empty()) {
            T value = std::move(queue_.front());
            queue_.pop();
            not_full_.notify_one();
            return { std::move(value), true };
        }

        return { T(), false };
    }

    void close() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!closed_) {
            closed_ = true;
            not_empty_.notify_all();
            not_full_.notify_all();
        }
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    size_t capacity_;
    bool closed_ = false;
};

#endif
