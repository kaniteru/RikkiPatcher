#ifndef RIKKI_PATCHER_RIKKI_DATA_I_DATA_HPP
#define RIKKI_PATCHER_RIKKI_DATA_I_DATA_HPP
#include "precompiled.hpp"

class IData {
public:
  virtual bool is_valid() = 0;

  virtual bool backup(const path_t& dir) = 0;

  virtual bool save() = 0;
  virtual bool save(const path_t& dir) = 0;
  // extract()
  // update()

public:
  virtual ~IData() = default;
};


#endif //RIKKI_PATCHER_RIKKI_DATA_I_DATA_HPP
