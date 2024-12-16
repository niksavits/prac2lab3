package main

import (
  "encoding/gob"
  "encoding/json"
  "fmt"
  "os"
  "strings"
)

const (
  // Файлы для хранения данных
  filenameText = "hash_table_data.json" // Текстовый (JSON) формат
  filenameGob  = "hash_table_data.gob"  // Бинарный (GOB) формат
)

// Функция для сохранения хеш-таблицы в текстовый формат (JSON)
func saveToFileJSON(ht *HashTable) error {
  file, err := os.Create(filenameText)
  if err != nil {
    return err
  }
  defer file.Close()

  // Преобразуем хеш-таблицу в map для сериализации в JSON
  data := make(map[string]string)
  for i := 0; i < HashTableSize; i++ {
    entry := ht.Table[i] // Таблица теперь содержит данные с заглавной буквы
    for entry != nil {
      data[entry.Key] = entry.Value
      entry = entry.Next
    }
  }

  encoder := json.NewEncoder(file)
  err = encoder.Encode(data)
  if err != nil {
    return err
  }

  return nil
}

// Функция для загрузки хеш-таблицы из текстового формата (JSON)
func loadFromFileJSON(ht *HashTable) error {
  if _, err := os.Stat(filenameText); os.IsNotExist(err) {
    return nil // Файл не существует, просто выходим
  }

  file, err := os.Open(filenameText)
  if err != nil {
    return err
  }
  defer file.Close()

  data := make(map[string]string)
  decoder := json.NewDecoder(file)
  err = decoder.Decode(&data)
  if err != nil {
    return err
  }

  // Добавляем данные в хеш-таблицу
  for key, value := range data {
    ht.Set(key, value)
  }

  return nil
}

// Функция для сохранения хеш-таблицы в бинарный формат (GOB)
func saveToFileGOB(ht *HashTable) error {
  file, err := os.Create(filenameGob)
  if err != nil {
    return err
  }
  defer file.Close()

  // Преобразуем хеш-таблицу в map для сериализации
  data := make(map[string]string)
  for i := 0; i < HashTableSize; i++ {
    entry := ht.Table[i]
    for entry != nil {
      data[entry.Key] = entry.Value
      entry = entry.Next
    }
  }

  encoder := gob.NewEncoder(file)
  err = encoder.Encode(data)
  if err != nil {
    return err
  }

  return nil
}

// Функция для загрузки хеш-таблицы из бинарного формата (GOB)
func loadFromFileGOB(ht *HashTable) error {
  if _, err := os.Stat(filenameGob); os.IsNotExist(err) {
    return nil // Файл не существует, просто выходим
  }

  file, err := os.Open(filenameGob)
  if err != nil {
    return err
  }
  defer file.Close()

  data := make(map[string]string)
  decoder := gob.NewDecoder(file)
  err = decoder.Decode(&data)
  if err != nil {
    return err
  }

  // Добавляем данные в хеш-таблицу
  for key, value := range data {
    ht.Set(key, value)
  }

  return nil
}

func main() {
  // Карта для хранения именованных хеш-таблиц
  hashTables := make(map[string]*HashTable)

  // Проверка наличия аргументов
  if len(os.Args) < 2 {
    fmt.Println("Использование: go run main.go 'КОМАНДА' [ФОРМАТ]")
    return
  }

  // Получаем запрос и формат
  query := strings.TrimSpace(os.Args[1])
  format := "json" // По умолчанию используем JSON формат
  if len(os.Args) == 3 {
    format = strings.ToLower(os.Args[2])
  }

  tokens := strings.Fields(query)
  if len(tokens) == 0 {
    fmt.Println("Пустой запрос.")
    return
  }

  command := tokens[0]

  // Обработка команды
  switch command {
  case "HSET":
    if len(tokens) != 4 {
      fmt.Println("Использование: HSET имя_хэша ключ значение")
      return
    }
    hashName, key, value := tokens[1], tokens[2], tokens[3]
    htable, exists := hashTables[hashName]
    if !exists {
      // Если хеш-таблица не существует, создаём её
      htable = NewHashTable()
      hashTables[hashName] = htable
    }
    htable.Set(key, value)

    // Сохраняем данные в файл
    var err error
    if format == "json" {
      err = saveToFileJSON(htable)  // Сохранение в JSON
    } else if format == "gob" {
      err = saveToFileGOB(htable) // Сохранение в GOB
    }

    if err != nil {
      fmt.Println("Ошибка при сохранении:", err)
      return
    }

    fmt.Printf("HSET выполнен: [%s: %s] добавлен в '%s'\n", key, value, hashName)
    case "HGET":
    if len(tokens) != 3 {
      fmt.Println("Использование: HGET имя_хэша ключ")
      return
    }
    hashName, key := tokens[1], tokens[2]
    htable, exists := hashTables[hashName]
    if !exists {
      // Если хеш-таблица не существует, создаём её
      htable = NewHashTable()
      hashTables[hashName] = htable
    }

    // Загружаем данные из файла
    var err error
    if format == "json" {
      err = loadFromFileJSON(htable)  // Загрузка из JSON
    } else if format == "gob" {
      err = loadFromFileGOB(htable) // Загрузка из GOB
    }

    if err != nil {
      fmt.Println("Ошибка при загрузке данных:", err)
      return
    }

    // Получение значения по ключу
    value, found := htable.Get(key)
    if !found {
      fmt.Printf("Ключ '%s' не найден в хеше '%s'.\n", key, hashName)
    } else {
      fmt.Println(value)
    }

  case "HDEL":
    if len(tokens) != 3 {
      fmt.Println("Использование: HDEL имя_хэша ключ")
      return
    }
    hashName, key := tokens[1], tokens[2]
    htable, exists := hashTables[hashName]
    if !exists {
      // Если хеш-таблица не существует, создаём её
      htable = NewHashTable()
      hashTables[hashName] = htable
    }

    // Загружаем данные из файла
    var err error
    if format == "json" {
      err = loadFromFileJSON(htable)  // Загрузка из JSON
    } else if format == "gob" {
      err = loadFromFileGOB(htable) // Загрузка из GOB
    }

    if err != nil {
      fmt.Println("Ошибка при загрузке данных:", err)
      return
    }

    // Удаление ключа
    htable.Delete(key)

    // Сохраняем данные в файл
    if format == "json" {
      err = saveToFileJSON(htable)  // Сохранение в JSON
    } else if format == "gob" {
      err = saveToFileGOB(htable) // Сохранение в GOB
    }

    if err != nil {
      fmt.Println("Ошибка при сохранении:", err)
      return
    }

    fmt.Printf("HDEL выполнен: Ключ '%s' удален из '%s'\n", key, hashName)

  default:
    fmt.Println("Неизвестная команда:", command)
  }
}
