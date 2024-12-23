#include "zip_util.hpp"
#include "string_util.hpp"

/*size_t ZipUtil::zip(const std::vector<path_t>& src, const path_t& dst, bool withPw, std::string_view pw) {
    static auto cleanup = [](void* pHandle) {
        mz_zip_writer_close(pHandle);
        mz_zip_writer_delete(&pHandle);
    };

    size_t result = 0;
    auto pWriter = mz_zip_writer_create();

    if (!pWriter) {
        return result;
    }

    if (withPw) {
        mz_zip_writer_set_aes(pWriter, 1); // enable aes256 because startup.json encrypted using aes256
        mz_zip_writer_set_password(pWriter, pw.data());
    }

    //mz_zip_writer_set_compress_method(pWriter, MZ_COMPRESS_METHOD_DEFLATE);
    //mz_zip_writer_set_compress_level(pWriter, MZ_COMPRESS_LEVEL_DEFAULT);

    if (mz_zip_writer_open_file(pWriter, StringUtil::u8_to_cstr(dst.generic_u8string()), 0, 0) != MZ_OK) {
        cleanup(pWriter);
        return result;
    }

    for (const auto& f : src) {
        const auto res = mz_zip_writer_add_path(pWriter, StringUtil::u8_to_cstr(f.generic_u8string()), nullptr, 0, 0);
        if (res == MZ_OK)
            result++;
        std::cout << "res: " << res << std::endl;
    }

    cleanup(pWriter);
    return result;
    return 0;
}*/

/*size_t ZipUtil::unzip(const path_t& src, const path_t& dst, bool withPw, std::string_view pw) {
    static auto cleanup = [](void* pHandle) {
        mz_zip_reader_close(pHandle);
        mz_zip_reader_delete(&pHandle);
    };

    size_t result = 0;
    auto pReader = mz_zip_reader_create();

    if (!pReader) {
        return result;
    }

    if (withPw) {
        //mz_stream_wzaes_set_password(pReader, pw.data());
        mz_zip_reader_set_password(pReader, pw.data());
    }

    if (mz_zip_reader_open_file(pReader, StringUtil::u8_to_cstr(src.generic_u8string())) != MZ_OK) {
        cleanup(pReader);
        return result;
    }

    if (mz_zip_reader_goto_first_entry(pReader) != MZ_OK) {
        cleanup(pReader);
        return result;
    }

    do {
        mz_zip_file* pFile = nullptr;

        if (mz_zip_reader_entry_get_info(pReader, &pFile) != MZ_OK) {
            continue;
        }

        if (!pFile) {
            continue;
        }

        const auto output = path_t(dst).append(pFile->filename);
        std::cout << pFile->aes_version << std::endl;
        if (const auto res =
            mz_zip_reader_entry_save_file(pReader, StringUtil::u8_to_cstr(output.generic_u8string())); res == MZ_OK) {
            result++;
        } else
        std::cout << res << std::endl;
    }
    while (mz_zip_reader_goto_next_entry(pReader) == MZ_OK);

    mz_zip_reader_entry_close(pReader);
    cleanup(pReader);
    return result;
    return 0;
}*/
