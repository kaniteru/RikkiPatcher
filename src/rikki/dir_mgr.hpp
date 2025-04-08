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

enum eDir : uint32_t; //e_dir.hpp

/**
 * @brief Used get a dir path. <br>
 * eDir is defined in e_dir.hpp.
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
     * auto path = dirMgr.get(dirType);
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
