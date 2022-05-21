#pragma once

#include <list>
#include <vector>

#include "assignment/private/hash_map.hpp"  // HashMap

namespace assignment {

  /**
   * Реализация тривиальной хеш-функции на базе модульной арифметики.
   *
   * Вычисленный хеш гарантированно лежит в отрезке [0, capacity).
   *
   * @param key - значение целочисленного ключа
   * @param capacity максимальное количество ячеек в словаре
   * @return значение хеша
   */
  int hash(int key, int capacity);

  /**
   * Реализация интерфейса "хеш-словарь" на базе метода цепочек.
   */
  struct ChainingHashMap : HashMap {
   public:
    // тип данных "ячейка словаря" (связный список из узлов)
    // [0] => [{key 1, value 1}, {key 2, value 2}]    -> hash(key 1) = hash(key 2) коллизия
    // [1] => []
    // ...
    // [capacity - 1] = [{key 3, value 3}]
    using Bucket = std::list<Node>;

    // константы
    static constexpr int kGrowthCoefficient = 2;  // коэффициент увеличения емкости словаря
    static constexpr double kDefaultLoadFactor = 0.75;  // коэффициент заполнения словаря

    /**
     * Создание словаря с указанной емкостью и коэффициентом заполнения.
     *
     * @param capacity - значение начальной емкости словаря
     * @param load_factor - значение коэффициента заполнения словаря
     */
    explicit ChainingHashMap(int capacity, double load_factor = kDefaultLoadFactor);

    /**
     * Добавление пары "ключ-значение" в словарь.
     *
     * @param key - значение ключа
     * @param value - данные, привязанные к ключу
     * @return true - элемент добавлен, false - данные с указанным ключом уже есть в словаре
     */
    bool Put(int key, int value) override;

    /**
     * Удаление пары "ключ-значение" из словаря.
     *
     * @param key - значение ключа
     * @return данные удаленного элемента
     */
    std::optional<int> Remove(int key) override;

    /**
     * Поиск данных в словаре по ключу.
     *
     * @param key - значение ключа
     * @return найденные данные
     */
    std::optional<int> Search(int key) const override;

    /**
     * Очистка словаря.
     *
     * Текущая емкость сохраняется.
     */
    void Clear() override;

    /**
     * Проверка наличия элемента по ключу.
     *
     * @param key - значение ключа
     * @return true - элемент по ключу есть, false - элемент отсутствует
     */
    bool Contains(int key) const override;

    bool IsEmpty() const override;

    int capacity() const override;

    int size() const override;

    double load_factor() const override;

   protected:
    // кол-во ключей в словаре
    int num_keys_;

    // коэффициент заполнения словаря (кол-во ключей делить на емкость словаря)
    const double load_factor_;

    // ячейки (корзинки) словаря с парами "ключ-значение"
    std::vector<Bucket> buckets_;

    /**
     * Увеличение емкости словаря.
     *
     * Создается новый словарь большей емкости.
     * Для элементов из старого словаря вычисляются новые индексы ячеек.
     *
     * @param new_capacity - новая емкость словаря
     */
    void resize(int new_capacity);
  };

}  // namespace assignment
