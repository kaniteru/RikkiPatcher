#ifndef RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
#define RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
#include "precompiled.hpp"

/* dir_mgr.hpp
 *  Included classes:
 *      - DirMgr
 */

// ======================== C L A S S ========================
// ===    DirMgr
// ======================== C L A S S ========================

enum eDir : uint32_t; //dir_mgr_enum.hpp

/**
 * @brief Used get a dir path. <br>
 * eDir is defined in dir_mgr_enum.hpp.
 */
class DirMgr {
public:
    /**
     * @brief Initialize using game directory.
     *
     * @param [in] gmDir Game directory path.
     */
    static void init(const path_t& gmDir);

    /**
     * @brief Get a target path.
     *
     * @param [in] type Target type.
     * @return Returns target path.
     *
     * @code
     * DirMgr dirMgr(...);
     * eDir dirType = ...;
     * auto path = DirMgr::get(dirType);
     * @endcode
     */
    const static path_t& get(eDir type);
private:
    static DirMgr& instance();
public:
    DirMgr(const DirMgr&) = delete;
    DirMgr& operator=(const DirMgr&) = delete;
private:
    DirMgr();
    ~DirMgr();
private:
    class impl;
    std::unique_ptr<impl> m_pImpl;
};


#endif //RIKKI_PATCHER_RIKKI_DIR_MGR_HPP
