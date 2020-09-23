#ifndef ANY_HPP
#define ANY_HPP

#include <typeindex>


namespace palkin {


class placeholder {
public:
    virtual ~placeholder() = default;

    virtual const std::type_info& type_info() const = 0;

    virtual placeholder* clone() const = 0;
};


template <class T>
class concrete_holder : public placeholder {
public:
    using value_type = T;

    concrete_holder(const value_type& value) : held(value) {}

    const std::type_info& type_info() const override {
        return typeid(held);
    };

    placeholder* clone() const override {
        return new concrete_holder(held);
    };

    const value_type held; 
    placeholder* content;
};


class any {
public:
    any() : content(nullptr) {}
    any(const any& other) : content(other.content ? other.content->clone() : nullptr) {}

private:
    placeholder* content;
};


} // namespace palkin

#endif