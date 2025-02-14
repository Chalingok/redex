/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// The StringTreeSet and StringTreeMap provide a compact encoding for
// collections of strings that tend to share prefices. The string keys that are
// currently supported are limited to only valid Java identifier characters.
template <typename ValueType>
class StringTreeMap {
 public:
  void insert(const std::string& s, ValueType value, size_t start = 0);

  void encode(std::ostringstream& oss) const;

  static std::string encode_string_tree_map(
      const std::map<std::string, ValueType>& strings);

 private:
  std::map<char, StringTreeMap<ValueType>> m_map;
  bool m_terminal{false};
  ValueType m_value;
};

class StringTreeSet {
 public:
  void insert(const std::string& s) { m_set.emplace(s); }

  void encode(std::ostringstream& oss) const;

  static std::string encode_string_tree_set(
      const std::vector<std::string>& strings);

 private:
  std::set<std::string> m_set;
};

// An map of limited string keys, with the same caveat as StringTreeMap above,
// to string values (which can be anything).
// NOTE: Given string values are assumed to be in MUTF-8 format! NO VALIDATION
// IS DONE SO GET IT RIGHT OR CHAOS WILL ENSUE.
class StringTreeStringMap {
 public:
  static std::string encode_string_tree_map(
      const std::map<std::string, std::string>& strings);
};
