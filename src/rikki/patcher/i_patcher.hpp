#ifndef RIKKI_PATCHER_RIKKI_PATCHER_I_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_I_PATCHER_HPP
#include "precompiled.hpp"

class IRikkiPatcher {
public:
    /**
     * @brief Check is patch available.
     *
     * @return Returns true if patch available.
     */
    bool is_available() const;

public:
    explicit IRikkiPatcher(const path_t& dir);
    virtual ~IRikkiPatcher() = default;
protected:
    bool m_isAvailable;
    path_t m_dir;
};

class IPatcher : public IRikkiPatcher {
public:
    virtual size_t patch() = 0;
    virtual bool migration() = 0;
    virtual bool generate_migration_info() = 0;

public:
    explicit IPatcher(const path_t& dir);
protected:
    path_t m_migrDir;

    constexpr static auto FOLDER_MIGRATE = "migration";
};



#endif //RIKKI_PATCHER_RIKKI_PATCHER_I_PATCHER_HPP
