#include "assignment/chaining_hash_map.hpp"

#include <cmath>      // abs
#include <cassert>    // assert
#include <stdexcept>  // invalid_argument

namespace assignment {

  int hash(int key, int capacity) {
    assert(capacity > 0);

    // Примечание: не забываем учесть отрицательные значения ключа.
    return std::abs(key) % capacity;
  }

  ChainingHashMap::ChainingHashMap(int capacity, double load_factor) : load_factor_{load_factor} {

    if (capacity <= 0) {
      throw std::invalid_argument("capacity must be greater than zero");
    }

    if (load_factor <= 0.0 || load_factor > 1.0) {
      throw std::invalid_argument("load factor must be in range (0...1]");
    }

    // изначально, кол-во ключей равно нулю
    num_keys_ = 0;

    // выделяем память под ячейки (корзинки) словаря
    buckets_.resize(capacity);
  }

  bool ChainingHashMap::Put(int key, int value) {

    // Tips:
    // 1. Если ключ уже содержится в словаре, то возвращаем false.
    // 2. Вычисляем индекс ячейки словаря при помощи хеш-функции.
    // 3. Добавляем "ключ-значение" в найденную ячейку словаря.
    // 4. Увеличиваем кол-во ключей в словаре.
    // 5. Если превышен коэффициент загрузки словаря, то расширяем словарь.

    // ... (ниже представлена часть реализации)

    // вычисление индекса ячейки словаря по ключу
    const int index = hash(key, buckets_.size());

    // добавление пары "ключ-значение" в ячейку словаря (в конец связного списка)
    buckets_[index].push_back(Node(key, value));

    // расширение словаря до новой емкости в случае превышения коэффициента заполнения
    if (num_keys_ / static_cast<double>(buckets_.size()) > load_factor_) {
      const int new_capacity = 0 /* здесь должна быть ваше выражение */;
      resize(new_capacity);
    }

    return true;
  }

  std::optional<int> ChainingHashMap::Remove(int key) {

    const int index = 0 /* напишите здесь свой код */;

    // здесь используется итератор (по сути указатель на узел списка)
    for (auto it = buckets_[index].begin(); it != buckets_[index].end(); ++it) {

      if (it->key == key) {
        // сохраняем данные удаляемого элемента
        const int removed = it->value;

        // удаляем элемент из списка по итератору (указателю)
        buckets_[index].erase(it);

        // возвращаем значение удаленного элемента
        return removed;
      }
    }

    return std::nullopt;
  }

  std::optional<int> ChainingHashMap::Search(int key) const {

    // вычисление индекса ячейки для указанного ключа
    const int index = 0 /* напишите здесь свой код */;

    // Проходимся по всем элемента в ячейке словаря.
    // В худшем случае все элементы попали в одну ячейку словаря и сложность поиска ~ O(N).
    for (const Node& node : buckets_[index]) {
      // напишите здесь свой код ...
    }

    return std::nullopt;
  }

  void ChainingHashMap::Clear() {

    // зачищаем каждую ячейку словаря
    for (Bucket& bucket : buckets_) {
      bucket.clear();
    }

    // обнуляем кол-во ключей в словаре
    num_keys_ = 0;
  }

  bool ChainingHashMap::Contains(int key) const {
    // Напишите здесь свой код ...
    return false;
  }

  bool ChainingHashMap::IsEmpty() const {
    return num_keys_ == 0;
  }

  int ChainingHashMap::capacity() const {
    return buckets_.size();
  }

  int ChainingHashMap::size() const {
    return num_keys_;
  }

  double ChainingHashMap::load_factor() const {
    return load_factor_;
  }

  void ChainingHashMap::resize(int new_capacity) {
    assert(new_capacity > buckets_.size());

    // создаем новый словарь большего размера
    auto new_buckets = std::vector<Bucket>(new_capacity);

    // пересчитываем индексы элементов словаря, учитывая новую емкость
    for (const Bucket& bucket : buckets_) {
      for (const Node& node : bucket) {
        const int new_index = 0 /* напишите здесь свой код */;
        new_buckets[new_index].push_back(node);
      }
    }

    // обновляем поле (перемещаем данные из new_buckets в buckets_)
    buckets_ = std::move(new_buckets);
  }

}  // namespace assignment
