#ifndef UI_FONT_PATCH_STREAM_HPP
#define UI_FONT_PATCH_STREAM_HPP
#include "precompiled.hpp"
#include "i_stream.hpp"
#include "rikki/data/ui_font/ui_font.hpp"

/* ui_font_patch_stream.hpp
 *  Included classes:
 *      - UIFontPatchStream
 */

// ======================== C L A S S ========================
// ===    UIFontPatchStream
// ======================== C L A S S ========================

class UIFontPatchStream : public IRikkiStream {
public:
    /**
     * @brief Get all added fonts from stream.
     *
     * @return  Returns vector of added fonts.
     */
    font_vector_t get_fonts();

    /**
     * @brief Add fonts into stream.
     *
     * @param [in] fonts Fonts to add.
     * @return Returns count of added fonts.
     */
    size_t add_fonts(const font_vector_t &fonts);

public:
    explicit UIFontPatchStream(const path_t& file);
};


#endif //UI_FONT_PATCH_STREAM_HPP
