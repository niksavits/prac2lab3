package main

import (
  "testing"
  "fmt"
  "github.com/stretchr/testify/assert"
)
// Тестируем конструктор хеш-таблицы
func TestNewHashTable(t *testing.T) {
  ht := NewHashTable()

  // Проверяем, что таблица пуста
  for i := 0; i < HashTableSize; i++ {
    assert.Nil(t, ht.Table[i], "Таблица должна быть пуста на старте")
  }
}

// Тестируем добавление и получение элементов
func TestSetAndGet(t *testing.T) {
  ht := NewHashTable()

  // Добавляем пару ключ-значение
  ht.Set("key1", "value1")
  ht.Set("key2", "value2")

  // Проверяем, что значения были успешно добавлены
  val, ok := ht.Get("key1")
  assert.True(t, ok, "Значение по ключу 'key1' должно быть найдено")
  assert.Equal(t, "value1", val, "Неверное значение для ключа 'key1'")

  val, ok = ht.Get("key2")
  assert.True(t, ok, "Значение по ключу 'key2' должно быть найдено")
  assert.Equal(t, "value2", val, "Неверное значение для ключа 'key2'")

  // Проверяем, что несуществующий ключ возвращает false
  val, ok = ht.Get("nonexistent")
  assert.False(t, ok, "Значение для несуществующего ключа должно быть не найдено")
  assert.Equal(t, "", val, "Значение для несуществующего ключа должно быть пустым")
}

// Тестируем обновление значения
func TestUpdateValue(t *testing.T) {
  ht := NewHashTable()

  // Добавляем пару ключ-значение
  ht.Set("key1", "value1")
  ht.Set("key1", "new_value1")

  // Проверяем, что значение было обновлено
  val, ok := ht.Get("key1")
  assert.True(t, ok, "Значение по ключу 'key1' должно быть найдено")
  assert.Equal(t, "new_value1", val, "Неверное значение для ключа 'key1' после обновления")
}

// Тестируем удаление элемента
func TestDelete(t *testing.T) {
  ht := NewHashTable()

  // Добавляем пару ключ-значение
  ht.Set("key1", "value1")
  ht.Set("key2", "value2")

  // Удаляем ключ 'key1'
  ht.Delete("key1")

  // Проверяем, что ключ 'key1' был удален
  val, ok := ht.Get("key1")
  assert.False(t, ok, "Значение для ключа 'key1' должно быть не найдено после удаления")
  assert.Equal(t, "", val, "Значение для ключа 'key1' должно быть пустым после удаления")

  // Проверяем, что ключ 'key2' все еще существует
  val, ok = ht.Get("key2")
  assert.True(t, ok, "Значение по ключу 'key2' должно быть найдено после удаления другого ключа")
  assert.Equal(t, "value2", val, "Неверное значение для ключа 'key2'")
}

// Тестируем удаление элемента в цепочке (с коллизиями)
func TestDeleteWithCollision(t *testing.T) {
  ht := NewHashTable()

  // Добавляем элементы, которые могут попасть в одну корзину
  ht.Set("key1", "value1")
  ht.Set("key2", "value2")

  // Удаляем первый ключ, который вызывает коллизию
  ht.Delete("key1")

  // Проверяем, что 'key1' был удален
  val, ok := ht.Get("key1")
  assert.False(t, ok, "Значение для ключа 'key1' должно быть не найдено после удаления")
  assert.Equal(t, "", val, "Значение для ключа 'key1' должно быть пустым после удаления")

  // Проверяем, что 'key2' все еще существует
  val, ok = ht.Get("key2")
  assert.True(t, ok, "Значение по ключу 'key2' должно быть найдено после удаления ключа 'key1'")
  assert.Equal(t, "value2", val, "Неверное значение для ключа 'key2'")
}

// Тестируем, что хеш-таблица корректно работает при коллизиях
func TestCollisionHandling(t *testing.T) {
  ht := NewHashTable()

  // Ключи, которые могут попасть в одну корзину (зависит от реализации хеш-функции)
  ht.Set("key1", "value1")
  ht.Set("key2", "value2")

  // Проверяем, что оба ключа сохраняются корректно
  val, ok := ht.Get("key1")
  assert.True(t, ok, "Значение по ключу 'key1' должно быть найдено")
  assert.Equal(t, "value1", val, "Неверное значение для ключа 'key1'")

  val, ok = ht.Get("key2")
  assert.True(t, ok, "Значение по ключу 'key2' должно быть найдено")
  assert.Equal(t, "value2", val, "Неверное значение для ключа 'key2'")
}

// Тестируем удаление элемента из пустой таблицы
func TestDeleteFromEmptyTable(t *testing.T) {
  ht := NewHashTable()

  // Попытка удалить элемент из пустой таблицы
  ht.Delete("key1")
// Проверяем, что таблица все еще пуста
val, ok := ht.Get("key1")
assert.False(t, ok, "Значение для ключа 'key1' должно быть не найдено после удаления из пустой таблицы")
assert.Equal(t, "", val, "Значение для ключа 'key1' должно быть пустым после удаления из пустой таблицы")
}

// Тестируем вставку в разные корзины
func TestInsertInDifferentBuckets(t *testing.T) {
ht := NewHashTable()

// Вставляем несколько элементов, которые должны попасть в разные корзины
ht.Set("key1", "value1")
ht.Set("key2", "value2")
ht.Set("key3", "value3")

// Проверяем, что все элементы можно получить
val, ok := ht.Get("key1")
assert.True(t, ok, "Значение по ключу 'key1' должно быть найдено")
assert.Equal(t, "value1", val, "Неверное значение для ключа 'key1'")

val, ok = ht.Get("key2")
assert.True(t, ok, "Значение по ключу 'key2' должно быть найдено")
assert.Equal(t, "value2", val, "Неверное значение для ключа 'key2'")

val, ok = ht.Get("key3")
assert.True(t, ok, "Значение по ключу 'key3' должно быть найдено")
assert.Equal(t, "value3", val, "Неверное значение для ключа 'key3'")
}

// Тестируем загрузку хеш-таблицы до максимума
func TestLoadFactor(t *testing.T) {
ht := NewHashTable()

// Вставляем много элементов, чтобы проверить производительность и загрузку таблицы
for i := 0; i < HashTableSize/2; i++ {
  ht.Set(fmt.Sprintf("key%d", i), fmt.Sprintf("value%d", i))
}

// Проверяем, что элементы корректно вставлены
for i := 0; i < HashTableSize/2; i++ {
  val, ok := ht.Get(fmt.Sprintf("key%d", i))
  assert.True(t, ok, "Значение должно быть найдено")
  assert.Equal(t, fmt.Sprintf("value%d", i), val, "Неверное значение")
}
}

// Тестируем удаление из пустой таблицы и получение после этого
func TestDeleteAndGetFromEmptyTable(t *testing.T) {
ht := NewHashTable()

// Проверяем, что Get возвращает пустое значение для пустой таблицы
val, ok := ht.Get("nonexistent")
assert.False(t, ok, "Значение для несуществующего ключа должно быть не найдено")
assert.Equal(t, "", val, "Значение для несуществующего ключа должно быть пустым")

// Удаляем из пустой таблицы
ht.Delete("nonexistent")

// Проверяем, что таблица все еще пуста
val, ok = ht.Get("nonexistent")
assert.False(t, ok, "Значение для несуществующего ключа должно быть не найдено после удаления")
assert.Equal(t, "", val, "Значение для несуществующего ключа должно быть пустым после удаления")
}