#pragma once

namespace assignment {

  /**
   * Узел, который хранит в себе пару "ключ-значение".
   */
  struct Node {
    // поля
    int key;
    int value;

    // конструктор
    Node(int key, int value) : key{key}, value(value) {}
  };

}  // namespace assignment