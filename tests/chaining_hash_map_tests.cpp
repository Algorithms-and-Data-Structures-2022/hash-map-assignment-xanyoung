#include <catch2/catch.hpp>

#include <numeric>  // iota

#include "private/utils.hpp"
#include "private/testing_chaining_hash_map.hpp"  // TestingChainingHashMap

using Catch::Contains;
using Catch::Equals;

using ChainingHashMap = assignment::TestingChainingHashMap;

SCENARIO("ChainingHashMap::ChainingHashMap") {

  SECTION("valid capacity") {
    const int capacity = GENERATE(range(1, 11));
    const double load_factor = GENERATE(range(0.1, 1.0, 0.1), 1.0);

    const auto dict = ChainingHashMap(capacity, load_factor);

    CHECK(dict.IsEmpty());
    CHECK(dict.size() == 0);

    CHECK(dict.capacity() == capacity);
    CHECK(dict.load_factor() == load_factor);
  }

  SECTION("invalid capacity") {
    const int capacity = GENERATE(range(-10, 1));
    const double load_factor = GENERATE(range(0.1, 1.0, 0.1), 1.0);

    REQUIRE_THROWS(ChainingHashMap(capacity, load_factor));
  }

  SECTION("invalid load factor") {
    const int capacity = GENERATE(range(1, 11));
    const double load_factor = GENERATE(range(0.0, -1.0, -0.1), -1.0);

    REQUIRE_THROWS(ChainingHashMap(capacity, load_factor));
  }
}

SCENARIO("ChainingHashMap::Contains") {
  const int size = GENERATE(range(1, 11));

  const auto keys = utils::rand_array(size, 0, 100, true);
  const auto values = utils::rand_array(size, -100, 100, true);

  auto dict = ChainingHashMap(keys, values, 2 * size);

  for (int key : keys) {
    CHECK(dict.Contains(key));
  }
}

SCENARIO("ChainingHashMap::Put") {

  SECTION("putting one key-value element should pass") {
    const int capacity = GENERATE(range(1, 11));
    const double load_factor = 1.0;

    auto dict = ChainingHashMap(capacity, load_factor);

    const int key = GENERATE(range(-100, 100));
    const int value = GENERATE(take(10, random(-100, 100)));

    dict.Put(key, value);

    CHECK(dict.size() == 1);
    CHECK_FALSE(dict.IsEmpty());

    CHECK(dict.capacity() == capacity);
    CHECK(dict.load_factor() == load_factor);

    CHECK_THAT(dict.keys(), Equals(std::vector<int>({key})));
    CHECK_THAT(dict.values(), Equals(std::vector<int>({value})));
  }

  SECTION("putting an element that exists should be ignored") {
    const int size = GENERATE(range(1, 11));
    const int capacity = size + 5;

    const auto keys = utils::rand_array(size, 0, capacity - 1, true);
    const auto values = utils::rand_array(size, -100, 100, true);

    auto dict = ChainingHashMap(keys, values, capacity);

    for (int key : keys) {
      dict.Put(key, 0);
    }

    CHECK(dict.size() == keys.size());
    CHECK(dict.capacity() == capacity);

    CHECK_THAT(dict.keys(), Contains(keys));
    CHECK_THAT(dict.values(), Contains(values));
  }

  SECTION("hash map resize should be invoked") {
    const int capacity = GENERATE(range(1, 11));

    const auto keys = utils::rand_array(capacity, 0, 100, true);
    const auto values = utils::rand_array(capacity, -100, 100);

    auto dict = ChainingHashMap(keys, values, capacity);

    CHECK(dict.size() == dict.capacity());
    CHECK(dict.load_factor() == Approx(1.0));

    const int key = GENERATE(take(5, random(101, 150)));
    CHECK(dict.Put(key, 0));

    CHECK(dict.size() == capacity + 1);
    CHECK(dict.capacity() == ChainingHashMap::kGrowthCoefficient * capacity);
  }
}

SCENARIO("ChainingHashMap::Remove") {

  GIVEN("non-empty hash map") {
    const auto capacity = GENERATE(range(2, 10));
    auto hash_table = ChainingHashMap(capacity, 1.0);

    auto keys = std::vector<int>(capacity - 1);
    std::iota(std::begin(keys), std::end(keys), 0);

    for (int key : keys) {
      hash_table.Put(key, key);
    }

    REQUIRE(hash_table.size() == keys.size());
    REQUIRE_THAT(hash_table.values(), Equals(keys));

    SECTION("removing by an existing key") {
      const int remove_key = GENERATE_COPY(range(0, capacity - 1));

      auto removed = hash_table.Remove(remove_key);

      CHECK_FALSE(hash_table.Contains(remove_key));
      CHECK(removed.has_value());
      CHECK(removed.value() == keys[remove_key]);
    }

    SECTION("removing by a non-existing key") {
      const int remove_key = GENERATE_COPY(range(capacity, capacity + 10));

      auto removed = hash_table.Remove(remove_key);

      CHECK_FALSE(removed.has_value());
      CHECK(hash_table.size() == keys.size());
    }
  }
}

SCENARIO("ChainingHashMap::Search") {

  const auto capacity = GENERATE(range(2, 10));
  auto hash_table = ChainingHashMap(capacity, 1.0);

  auto keys = std::vector<int>(capacity - 1);
  std::iota(std::begin(keys), std::end(keys), 0);

  for (int key : keys) {
    hash_table.Put(key, key);
  }

  REQUIRE(hash_table.size() == keys.size());
  REQUIRE_THAT(hash_table.values(), Equals(keys));

  const int search_key = GENERATE_COPY(take(100, random(0, static_cast<int>(keys.size() - 1))));

  THEN("they should be found") {
    REQUIRE(hash_table.Search(search_key));
    CHECK(hash_table.Search(search_key).value() == keys[search_key]);
  }
}

SCENARIO("ChainingHashMap::Clear") {
  const int size = GENERATE(range(1, 11));

  const auto keys = utils::rand_array(size, 0, 100, true);
  const auto values = utils::rand_array(size, -100, 100, true);

  auto dict = ChainingHashMap(keys, values, 2 * size);

  dict.Clear();

  CHECK(dict.size() == 0);
  CHECK(dict.keys().empty());
  CHECK(dict.values().empty());
}
