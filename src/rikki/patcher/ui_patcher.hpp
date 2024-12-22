#ifndef UI_PATCHER_HPP
#define UI_PATCHER_HPP
#include "precompiled.hpp"
#include "i_patcher.hpp"

class UITextPatcher : public IPatcher {
public:
    size_t patch() final;
    bool migration() final;
    bool generate_migration_info() final;

public:
    explicit UITextPatcher(const path_t& src);
private:
    path_t m_db;
    path_t m_migrDB;

    constexpr static auto FOLDER_BASE = "ui/texts";
};


#endif //UI_PATCHER_HPP
