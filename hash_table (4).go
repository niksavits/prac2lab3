package main

const HashTableSize = 100

type Entry struct {
  Key   string
  Value string
  Next  *Entry
}

// Структура хеш-таблицы
type HashTable struct {
  Table [HashTableSize]*Entry
}

// Конструктор хеш-таблицы
func NewHashTable() *HashTable {
  return &HashTable{}
}

// Хеш-функция
func (ht *HashTable) HashFunc(key string) int { // Поменял на HashFunc с заглавной буквы
  hash := 0
  for _, ch := range key {
    hash = (hash*31 + int(ch)) % HashTableSize
  }
  return hash
}

// Метод для добавления или обновления ключа
func (ht *HashTable) Set(key, value string) {
  idx := ht.HashFunc(key) // Поменял на HashFunc с заглавной буквы
  entry := ht.Table[idx]   // Поменял на Table с заглавной буквы
  for entry != nil {
    if entry.Key == key {
      entry.Value = value
      return
    }
    entry = entry.Next
  }
  newEntry := &Entry{Key: key, Value: value, Next: ht.Table[idx]}
  ht.Table[idx] = newEntry
}

// Метод для получения значения по ключу
func (ht *HashTable) Get(key string) (string, bool) {
  idx := ht.HashFunc(key) // Поменял на HashFunc с заглавной буквы
  entry := ht.Table[idx]   // Поменял на Table с заглавной буквы
  for entry != nil {
    if entry.Key == key {
      return entry.Value, true
    }
    entry = entry.Next
  }
  return "", false
}

// Метод для удаления ключа
func (ht *HashTable) Delete(key string) {
  idx := ht.HashFunc(key) // Поменял на HashFunc с заглавной буквы
  entry := ht.Table[idx]   // Поменял на Table с заглавной буквы
  var prev *Entry
  for entry != nil {
    if entry.Key == key {
      if prev == nil {
        ht.Table[idx] = entry.Next
      } else {
        prev.Next = entry.Next
      }
      return
    }
    prev = entry
    entry = entry.Next
  }
}

