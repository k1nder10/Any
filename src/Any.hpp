#ifndef ANY_HPP
#define ANY_HPP

#include <stdexcept>
#include <typeindex>
#include <type_traits>

namespace palkin {


class Placeholder {
public:
    virtual ~Placeholder() = default;
    virtual const std::type_info& TypeInfo() const noexcept = 0;
    virtual Placeholder* Clone() const = 0;
};


template <typename T>
class Holder : public Placeholder {
public:
    constexpr Holder(const T& v) noexcept : value(v) {}

    const std::type_info& TypeInfo() const noexcept override {
        return typeid(value);
    };

    Placeholder* Clone() const override {
        return new Holder(value);
    };

    const T value;
};


class Any {
public:
    constexpr Any() noexcept : content_(nullptr) {}

    template <typename T>
    Any(T&& value) : content_(new Holder<std::decay_t<T>>(std::forward<T>(value))) {}

    Any(const Any& other) : content_(other.content_ ? 
                                     other.content_->Clone() : nullptr) {}
    
    Any& operator=(const Any& other) {
        if (this == &other) return *this;
        if (content_) delete content_; 
        
        content_ = other.content_ ? other.content_->Clone() : nullptr;
        return *this;
    }

    Any(Any&& other) : content_(nullptr) {
        if (other.content_) {
            content_ = other.content_->Clone();
            delete other.content_;
            other.content_ = nullptr;
        }
    }

    Any& operator=(Any&& other) {
        if (this == &other) return *this;
        if (content_) {
            delete content_;
            content_ = nullptr;
        }

        if (other.content_) {
            content_ = other.content_->Clone();
            delete other.content_;
            other.content_ = nullptr;
        }

        return *this;
    }

    ~Any() { 
        delete content_;
    }

    Any& Swap(Any& other) {
        std::swap(content_, other.content_);
        return *this;
    }

    void Reset() noexcept {
        if (content_) {
            delete content_;
            content_ = nullptr;
        }
    }

    const std::type_info& TypeInfo() const noexcept {
        return content_ ? content_->TypeInfo() : typeid(void);
    }

    template <typename T> friend T any_cast(const Any&);


protected:
    template <typename T>
    const T* ToPtr() const noexcept {
        if (TypeInfo() == typeid(T)) {
            return &static_cast<Holder<T>*>(content_)->value;
        }

        return nullptr;
    }


private:
    Placeholder* content_;
};


template <typename T>
T any_cast(const Any& other) {
    const T* value = other.ToPtr<T>();
    if (!value) throw std::bad_cast();
    
    return *value;
}


} // namespace palkin

#endif