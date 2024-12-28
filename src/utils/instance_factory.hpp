#ifndef RIKKI_PATCHER_UTILS_INSTANCE_FACTORY_HPP
#define RIKKI_PATCHER_UTILS_INSTANCE_FACTORY_HPP
#include "precompiled.hpp"

#define INSTFAC(C) InstanceFactory::instance().get<C>()

class InstanceFactory {
public:
    static InstanceFactory& instance();

    template<class T>
    std::shared_ptr<T> get();

    size_t get_count();

    template<class T, typename... Args>
    bool make(Args&&... args);

    template<class T>
    bool reset();

    void clear();

public:
    InstanceFactory() = default;
    InstanceFactory(const InstanceFactory&) = delete;
    InstanceFactory& operator=(const InstanceFactory&) = delete;
private:
    std::shared_mutex m_mtx;
    std::unordered_map<std::type_index, std::shared_ptr<void>> m_instances;
};

inline
InstanceFactory& InstanceFactory::instance() {
    static InstanceFactory instance;
    return instance;
}

template<class T>
inline
std::shared_ptr<T> InstanceFactory::get() {
    std::shared_lock lock(m_mtx);
    const auto it = m_instances.find(typeid(T));

    if (it == m_instances.end()) {
        return nullptr;
    }

    return std::static_pointer_cast<T>(it->second);
}

inline
size_t InstanceFactory::get_count() {
    std::shared_lock lock(m_mtx);
    return m_instances.size();
}

template<class T, typename ...Args>
inline
bool InstanceFactory::make(Args&&... args) {
    if (this->get<T>()) {
        return false;
    }

    std::unique_lock lock(m_mtx);
    auto inst = std::make_shared<T>(args...);
    m_instances[typeid(T)] = std::move(inst);
    return true;
}

template<class T>
inline
bool InstanceFactory::reset() {
    std::unique_lock lock(m_mtx);
    const auto it = m_instances.find(typeid(T));

    if (it == m_instances.end()) {
        return false;
    }

    m_instances.erase(it->first);
    return true;
}

inline
void InstanceFactory::clear() {
    std::unique_lock lock(m_mtx);

    for (const auto& it : m_instances) {
        m_instances.erase(it.first);
    }
}


#endif //RIKKI_PATCHER_UTILS_INSTANCE_FACTORY_HPP
