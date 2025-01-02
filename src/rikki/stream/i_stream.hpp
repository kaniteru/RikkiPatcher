#ifndef RIKKI_PATCHER_RIKKI_PATCHER_I_STREAM_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_I_STREAM_HPP
#include "precompiled.hpp"

// ======================== C L A S S ========================
// ===    IRikkiStream
// ======================== C L A S S ========================

/* A interface class of stream. Can't specify that 'IStream' because already defined in the cpp standard. */
class IRikkiStream {
public:
    /**
     * @brief Check is migration data loaded successfully.
     * <br>If you want to write from empty stream, you don't need to check this.
     *
     * @return Returns true if json data loaded successfully.
     */
    bool is_loaded() const;

    /**
     * @brief Clears the data stream.
     */
    void clear();

    /**
     * @brief Save the json data into file.
     *
     * @return Returns true if saved successfully.
     */
    bool save() const;

public:
    /**
     * @brief Load json from the patch data file or create the empty stream.
     *
     * @param [in] file A path of patch data file.
     *
     * @code
     * IRikkiStream stream(...);
     *
     * // if you want to load the stream from json file
     * if (stream.is_loaded) { ... }
     * @endcode
     */
    explicit IRikkiStream(const path_t& file);
protected:
    const path_t m_file;              /* Path of json file */
    bool m_isLoaded;                    /* Is data loaded from json file? */
    nlohmann::ordered_json m_j; /* Json object */
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_I_STREAM_HPP
