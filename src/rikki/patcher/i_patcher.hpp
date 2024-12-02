#ifndef RIKKI_PATCHER_RIKKI_PATCHER_I_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_I_PATCHER_HPP
#include "precompiled.hpp"

class IPatcher {
public:
    /**
     * @brief Check is patch available.
     *
     * @return Returns true if patch available.
     */
    bool is_available() const;

    virtual size_t patch() = 0;
    virtual bool migration() = 0;
protected:
    virtual bool generate_migration_info();

public:
    explicit IPatcher(const path_t& dir);
protected:
    bool m_isAvailable;
    path_t m_dir;
    path_t m_migraDir;
private:
    constexpr static auto FOLDER_MIGRATE = "migrate";
};



#endif //RIKKI_PATCHER_RIKKI_PATCHER_I_PATCHER_HPP
