#pragma once

#include "assignment/chaining_hash_map.hpp"  // ChainingHashMap

#include <algorithm>  // sort
#include <vector>
#include <unordered_set>

namespace assignment {

  struct TestingChainingHashMap : ChainingHashMap {

    TestingChainingHashMap(int capacity, double load_factor) : ChainingHashMap(capacity, load_factor) {}

    std::vector<int> keys() const {
      std::unordered_set<int> keys;
      keys.reserve(num_keys_);

      for (const auto& bucket : buckets_) {
        for (const auto [key, _] : bucket) {
          keys.insert(key);
        }
      }

      auto keys_vector = std::vector<int>(keys.begin(), keys.end());
      std::sort(keys_vector.begin(), keys_vector.end());

      return keys_vector;
    }

    std::vector<int> values() const {
      std::unordered_set<int> values;
      values.reserve(num_keys_);

      for (const auto& bucket : buckets_) {
        for (const auto [_, value] : bucket) {
          values.insert(value);
        }
      }

      auto values_vector = std::vector<int>(values.begin(), values.end());
      std::sort(values_vector.begin(), values_vector.end());

      return values_vector;
    }

    TestingChainingHashMap(const std::vector<int>& keys, const std::vector<int>& values, int capacity)
        : ChainingHashMap(capacity, 1.0) {

      for (int index = 0; index < keys.size(); ++index) {
        const int bucket_index = hash(keys[index], buckets_.size());
        buckets_[bucket_index].emplace_back(keys[index], values[index]);
      }

      num_keys_ = keys.size();
    }
  };

}  // namespace assignment