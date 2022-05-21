#pragma once

#include <optional>

#include "assignment/private/node.hpp"  // Node

namespace assignment {

  /**
   * Интерфейс структуры данных "хеш-словарь".
   */
  struct HashMap {

    /**
     * Добавление пары "ключ-значение" в словарь.
     *
     * @param key - значение ключа
     * @param value - данные, привязанные к ключу
     * @return true - элемент добавлен, false - данные с указанным ключом уже есть в словаре
     */
    virtual bool Put(int key, int value) = 0;

    /**
     * Удаление пары "ключ-значение" из словаря по ключу.
     *
     * @param key - значение ключа
     * @return данные удаленного элемента
     */
    virtual std::optional<int> Remove(int key) = 0;

    /**
     * Поиск данных в словаре по ключу.
     *
     * @param key - значение ключа
     * @return найденные данные
     */
    virtual std::optional<int> Search(int key) const = 0;

    /**
     * Очистка словаря.
     *
     * Текущая емкость сохраняется.
     */
    virtual void Clear() = 0;

    /**
     * Проверка наличия элемента по ключу.
     *
     * @param key - значение ключа
     * @return true - элемент по ключу есть, false - элемент отсутствует
     */
    virtual bool Contains(int key) const = 0;

    /**
     * Проверка словаря на наличие элементов.
     *
     * @return true - словарь пустой, false - не пустой
     */
    virtual bool IsEmpty() const = 0;

    /**
     * Возвращает текущую емкость словаря.
     *
     * @return значение емкости словаря
     */
    virtual int capacity() const = 0;

    /**
     * Возвращает текущее количество пар "ключ-значение" в словаре.
     *
     * @return значение количества элементов в словаре
     */
    virtual int size() const = 0;

    /**
     * Возвращает установленный коэффициент заполнения словаря.
     *
     * @return значение коэффициента заполнения словаря
     */
    virtual double load_factor() const = 0;
  };

}  // namespace assignment
