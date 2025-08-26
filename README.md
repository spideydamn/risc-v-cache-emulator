# RISC-V Cache Emulator

Проект представляет собой эмулятор процессора RISC-V с системой кэширования, реализующий две политики вытеснения: LRU и bit-pLRU. Эмулятор выполняет трансляцию ассемблерного кода в машинный код и моделирует работу кэш-памяти с заданными параметрами.

## Особенности

- Поддержка набора инструкций RISC-V (RV32I)
- Реализация кэш-памяти с конфигурируемыми параметрами
- Две политики вытеснения: LRU и bit-pLRU
- Транслятор asm → binary
- Детальная статистика попаданий в кэш

## Параметры системы

| Параметр            | Значение    |
|---------------------|-------------|
| Размер памяти       | 524288 байт |
| Длина адреса        | 19 бит      |
| Конфигурация кэша   | look-through write-back |
| Ассоциативность     | 4           |
| Размер тега         | 10 бит      |
| Длина индекса       | 4 бита      |
| Длина смещения      | 5 битов     |
| Размер кэша         | 2048 байт   |
| Размер кэш-линии    | 32 байта    |
| Количество линий    | 64          |
| Количество наборов  | 16          |

## Реализация

### ISA
Ручной перевод C-кода в ассемблер RISC-V с сохранением семантики оригинальной программы. Каждая инструкция прокомментирована соответствующим C-кодом.

### Транслятор asm->binary
Реализован через классы:
- `Parser` - разбор ассемблерного кода
- `Serializer` - преобразование в машинный код
- `Deserializer` - обратное преобразование

### Кэш-память
- `Cache` - основной класс кэша с методами загрузки/выгрузки
- `CacheLine` - представление кэш-линии
- `RAM` - модель оперативной памяти

#### Политики вытеснения:
- **LRU**: Вытеснение least recently used линии
- **bit-pLRU**: Псевдо-LRU реализация с битовыми флагами

### Моделирование
Программа демонстрирует эффективность кэша на матричном умножении:
- LRU: 96.6571% попаданий
- bit-pLRU: 96.6406% попаданий

## Детали реализации

### Ключевые компоненты

**Emulator**
- Управляет процессом трансляции и выполнения
- Собирает статистику работы кэша

**CPUMemory**
- Регистры процессора (32 шт.)
- Интерфейс для работы с кэш-памятью

**Операции**
- Полный набор инструкций RISC-V
- Поддержка целочисленных операций и работы с памятью

### Алгоритмы работы кэша

Для обеих политик реализована обработка пограничных случаев, когда данные находятся на стыке кэш-линий. Время доступа учитывается для реализации LRU, а для bit-pLRU используются битовые векторы для отслеживания истории обращений.

## Использование

```bash
# Сборка
make

# Запуск с параметрами по умолчанию
./emulator --replacement 0 --asm rv32.asm --bin serial.bin

# Параметры:
# --replacement: 0 - обе политики, 1 - LRU, 2 - bit-pLRU
# --asm: путь к asm-файлу
# --bin: путь для бинарного файла
```

## Пример вывода
```
LRU     hit rate: 96.6571%
pLRU    hit rate: 96.6406%
```

## Детальный отчёт

## Инструментарий
- C++20
- GCC

# Описание:

| Параметр                 |                                                                   | Значение                |
|--------------------------|-------------------------------------------------------------------|-------------------------|
| MEM_SIZE                 | размер памяти                                                     | 524288 байт             |
| ADDR_LEN                 | длина адреса (CACHE_TAG_LEN + CACHE_INDEX_LEN + CACHE_OFFSET_LEN) | 19 бит                  |
| Конфигурация кэша        |                                                                   | look-through write-back |
| Политика вытеснения кэша |                                                                   | LRU и bit-pLRU          | 
| CACHE_WAY                | ассоциативность (CACHE_LINE_COUNT / CACHE_SETS)                   | 4                       |
| CACHE_TAG_LEN            | длина тега адреса (log2(MEM_SIZE * CACHE_WAY / CACHE_SIZE))       | 10 бит                  |
| CACHE_INDEX_LEN          | длина индекса блока кэш-линий                                     | 4 бита                  |
| CACHE_OFFSET_LEN         | длина смещения внутри кэш-линии                                   | 5 битов                 |
| CACHE_SIZE               | размер кэша, без учёта служебной информации                       | 2048 байт               |
| CACHE_LINE_SIZE          | размер кэш-линии (2^CACHE_OFFSET_LEN)                             | 32 байт                 |
| CACHE_LINE_COUNT         | кол-во кэш-линий (CACHE_SIZE / CACHE_LINE_SIZE)                   | 64                      |
| CACHE_SETS               | кол-во блоков кэш-линий (2^CACHE_INDEX_LEN)                       | 16                      |

## rv32.asm

Результат перевода из C в asm RISC-V лежит в rv32.asm. Переводил просто вручную по документации, переводя строчку за строчкой. 
В целом, я описал каждую строку, в конце каждого комментария написана строка из оригинального кода. 
Возможно важно сказать, что когда мы смотрим *pc[x]*, *pb[x]*, или прибавляем ```pc += N```, ```pb += N```, так как *pc* типа *int32_t*, а *pb* типа *int16_t*, то мы и прибавляем *x* и *N* 2 или 4 раза соответственно:
```
add     t6, a1, t2          // t6 = pb + x
add     t6, t6, t2          // t6 = pb + 2 * x
```
```
add     a1, a1, s1          // pb += N                          
add     a1, a1, s1          // pb += N * 2
```
```
add     t5, a3, t2          // t5 = pc + x
add     t5, t5, t2          // t5 = pc + 2 * x
add     t5, t5, t2          // t5 = pc + 3 * x
add     t5, t5, t2          // t5 = pc + 4 * x
```
```
add     a3, a3, s1          // pc += N
add     a3, a3, s1          // pc += N * 2
add     a3, a3, s1          // pc += N * 3
add     a3, a3, s1          // pc += N * 4                      (+= size of N units of c in bytes)
```
Для циклов я сначала присваивал индексу из цикла нуль: ```addi    t1, zero, 0```, ```addi    t2, zero, 0```, ```addi    t3, zero, 0```,
а затем в конце цикла сравнивал соответственно *t1*, *t2*, *t3* со значением до которого они должны дойти, и если они не дошли, то возвращался назад на номер инструкции присваивания нуля + 1:
```blt     t3, s2, -40```, ```blt     t2, s1, -80```, ```blt     t1, s0, -112```. В конце мы возвращаемся на номер инструкции лежащей в *ra*.

В *ra* в начале программы сразу кладётся номер байта конца всех инструкций: ```addi    ra, zero, 164```. В *saved* регистры кладутся значения 64, 60, 32 для *M*, *N* и *K* соответственно.
Возможно, регистры начинающиеся на *a* не совсем уместно использованы, и везде нужно было юзать *t*, но я не знаю, 
насколько это важно, а так было сделать удобнее.

## Эмуляция

Была реализована политика вытеснения [*LRU*](#lru) и [*bit-pLRU*](#bit-plru), дающие на программе rv32.asm и рассчитанных параметрах системы результат в **96.6571** и **96.6406** процентов попадания соответсвенно. Был реализован перевод в машинный код.

Эмулятор работает так, что изначально в *main.cpp* создается объект класса [*Emulator*](#class-emulator), вызывается [```emulator.Serialize(assembler, bin);```](#serialize),
и код ассемблера переводится в машинный и кладется в файл, по умолчанию "serial.bin" или в файл, указанный в аргументе *bin* программы, а затем уже из созданного файла читаются и исполняются инструкции в функции [```emulator.Deserialize(bin)```](#deserialize). 
В итоге после завершения работы считается количество кэш попаданий, соотносится с количеством обращений к кэшу и выводится функцией [```emulator.ShowStats();```](#show-stats). Всё это описано в функции ```void Emulate(ExclusionPolicy exclusion_policy, const std::string& assembler, const std::string& bin)``` в *main.cpp*.





### class Emulator

**Поля:**
- [**```CPUMemory memory```**](#class-cpumemory) - представляющее память процессора, а конкретно 32 целочисленных регистра и счетчик [*program_counter*](#program-counter)
- **```ExclusionPolicy exclusion_policy```** - политика вытеснения, которую мы указываем при создании объекта [*Emulator*](#class-emulator),
для дальнейшего вывода статистики в соответствующем методе [```void ShowStats() const```](#show-stats)

**Методы:**
- <a id="serialize"></a>**```void Serialize(const std::string& read_path, const std::string& write_path) const```** - просто вызывает статический метод парсера [*ReadFile*](#read-file), куда передаются *read_path* и *write_path*, в котором по итогу распаршивается .asm.

- <a id="deserialize"></a>**```void Deserialize(const std::string& serial_file)```** - записывает все команды из полученного бинарного файла с помощью десериализатора в вектор [*CommandToken*-ов](#class-commandtoken), затем отдает исполняться препроцессору.

- <a id="show-stats"></a>**```void ShowStats() const```** выводит политику вытеснения и процентное соотношение количества кэш попаданий к количеству всех обращений к кэшу.





### class Parser

У ранее упомянутого класса Parser всего одна функция [*ReadFile*](#read-file) распарсить .asm и с помощью объекта класса [*Serializer*](#class-serializer) создать машинный код.

**Методы:**
- <a id="read-file"></a>**```static void ReadFile(const std::string& read_path, const std::string& write_path)```** - Проходится по всем строкам файла и при помощи [*serializer*](#class-serializer) записывает каждую инструкцию в бинарном виде. **Конкретнее**: создает [Serializer](#class-serializer) для вывода машинного кода в файл с именем *write_path*, открывает файл *read_file* вывода с именем *read_path*. Проходится построчно по *read_file*, сохраняя каждую строку в переменную *line*. Парсит каждую строку при помощи [*ParseLine(line)*](#parse-line),
вызывает каждый раз метод [*execute*](#execute) класса [*Serializer*](#class-serializer), в который передает конвертированную в [*CommandToken*](#class-commandtoken) распаршенную ранее строку.

**Функции:**
- <a id="parse-line"></a>**```std::pair<std::string, std::vector<std::string>> ParseLine(const std::string& line)```** - Распаршивает каждую отдельную строку на команду std::string и набор операндов std::vector\<std::string\>
- **```CommandToken ConvertStringToToken(const std::pair<std::string, std::vector<std::string>>& string_data)```** - по полученному ранее из [*ParseLine*](#parse-line) значению возвращает [CommandToken](#class-commandtoken) - более удобный вид ```std::pair<std::string, std::vector<std::string>>```





### class Serializer
Нужен для перевода и записи [CommandToken](#class-commandtoken) в машинный код.

**Поля:**
- **```std::ofstream stream```** - поток вывода машинного кода

**Методы:**
- <a id="execute"></a>**```void execute(const CommandToken& token)```** - создает из токена класс инструкции при помощи [```std::unordered_map<OperationCode, std::shared_ptr<Operation>> token_to_class```](#token-to-class) и с помощью уже его метода создает бинарное значение, записывает его в *stream*

**Глобальные переменные:**
- **```std::unordered_map<std::string, OperationCode> operation_codes```** - мапа для перевода из *string* названия операции в *enum OperationCode*
- <a id="token-to-class"></a>**```std::unordered_map<OperationCode, std::shared_ptr<Operation>> token_to_class```** - мапа для перевода из *OperationCode* в объект класса [*Operation*](#class-operation)





### class Preprocessor
Нужен для того, чтобы перемещаться по инструкциям и исполнять их в заданном программой порядке. Для этого используется [*program_counter*](#programm-counter) в классе [*CPUMemory*](class-cpumemory), который указывает на исполняемую в данный момент операцию.
 
**Методы:**
- **```static void calculate(const std::vector<CommandToken>& program, CPUMemory& memory)```** - статический метод, который, пока поле *program_counter* объекта [*CPUMemory*](#class-cpumemory) не достигнет конца программы, увеличивает его и исполняет каждую операцию на которую он указывает





### class Operation
Класс операции, вектор которых как раз хранится в эмуляторе. Является базовым классом всех операций. В нем определены виртуальные методы, которые наследуются в каждой операции.

**Методы:**
- **```void execute(const std::vector<std::string>& operands, CPUMemory& memory)```** - выполняет операцию, которой соответствует определенный класс. При определении операндов, если требуется берет значения из регистров при помощи [*ParseRegister(src, dest, memory)*](#parse-register) или переводит строку, соответствующую числу в 16- или в 10-ричной системе счисления, в целый тип данных при помощи [*ParseNumber(src, dest)*](#parse-number) и *str_to_num(string)*. При выполнении записи или взятия из памяти, обращается к памяти к соответствующим функциям в зависимости от того, сколько байт и в знаковой или беззнаковой форме нам нужно взять.
- **```uint32_t GetBin(const std::vector<std::string>& operands)```** возвращает машинный код соответствующей инструкции
- <a id="parse-bin"></a>**```void ParseBin(uint32_t bin_command, OperationCode& command, std::vector<std::string>& operands)```** производит обратную операцию распаршивания машинного кода в *OperationCode* и вектор операндов.

**Глобальные переменные:**
- **```const uint8_t kInstructionSize = 4```** - размер в байтах одной инструкции
- **```std::unordered_map<std::string, uint32_t> bin_register```** - мапа для перевода названия регистра в его порядковый номер
- **```std::unordered_map<uint32_t, std::string> bin_to_string_register```** - мапа для порядкового номера регистра в его название

**Функции:**
- <a id="parse-number"></a>**```void ParseNumber(const std::string& src, int32_t& dest)```** - запись в dest числа src если оно является числом, или *preprocessor error*
- <a id="parse-register"></a>**```void ParseRegister(const std::string& src, int32_t& dest, CPUMemory& memory)```** - запись в dest значение регистра src если оно является названием регистра, или *preprocessor error*





### class CPUMemory
Нужен для эмуляции регистров процессора и подключает кэш, к которому при необходимости обращается.

**Поля:**
- [**```Cache cache```**](#class-cache) - кэш процессора
- <a id="program-counter"></a>**```uint32_t program_counter```** - счетчик указывающий на текущую инструкцию
- **```std::vector<int32_t> registers```** - вектор со значениями регистров

**Методы:**
- **```void Load(uint8_t dest, uint64_t source, uint8_t size = 1)```** - загрузка из кэша определенного количества байт, в зависимости от инструкции
- **```void Store(uint8_t source, uint64_t address, uint8_t size = 1)```** - загрузка в кэш определенного количества байт в зависимости от инструкции





### class Cache
Моделирует кэш процессора. Все методы по загрузке и выгрузке вызывающиеся из [*CPUMemory*](#class-cpumemory) вызывают методы [*Load*](#cache-load), [*LoadUnordered*](#cache-load), [*Store*](#cache-store), 
куда передают количество битов которые надо загрузить или выгрузить. В этих же методах проверяется, не находится ли 
байт, полу-слово или слово по данному адресу на стыке строк оперативной памяти. То есть не будет ли находится лишь часть информации в
выгруженной в кэш кэш-строке. Функция [*FindLine*](#find-line) же ищет строку по заданному адресу и возвращает её. Если такая неприятная ситуация произошла,
то берем сразу две строки: по данному адресу и по адресу следующей строки, то есть (address - offset + CACHE_LINE_SIZE).
Если всё хорошо, то берём только строку по данному адресу. 

<a id="lru"></a>Вся суть работы в функции [*FindLine*](#find-line). Для политики **LRU** в данном цикле:
```
for (uint64_t i = 0; i < CACHE_WAY; ++i) {
    if (memory[i][cache_index].tag == ram_line_number) {
        cache_block_number = i;
        is_hit = true;
        ++hits;
        break;
    } else if (memory[i][cache_index].time < oldest_time) {
        oldest_time = memory[i][cache_index].time;
        cache_block_number = i;
    }
}
```
Я пробегаюсь по всем подходящим мне по модулю *CACHE_SETS* кэш-блокам и ищу соответствие с тегом. Если нахожу, то останавливаю цикл и у нас кэш попадание.
Параллельно в цикле ищу минимальное время, на случай, если тег не найдется. Тогда у нас кэш-промах. Если что-то лежит в строке с самым старым временем,
то возвращаю его в ОЗУ. Далее просто записываю новые данные, время и тэг в строку. Данные берутся из оперативы. В тэг я записываю адрес без *offset*,
чтобы понимать, где конкретно лежит строка в оперативе. 

<a id="bit-plru"></a>Для политики **bit-pLRU** я снова ищу одновременно либо кэш строку с подходяшим тэгом, либо первый *[MRU](#mru) = 0*. Для [*MRU*](#mru) у меня специальное поле вектор *uint64_t*, где каждый *uint64_t* соответствует одной строке кэш линий, чтобы быстрее работать с битовыми операциями.
```
for (uint64_t i = 0; i < CACHE_WAY; ++i) {
            if (memory[i][cache_index].tag == ram_line_number) {
                cache_block_number = i;
                is_hit = true;
                ++hits;
                break;
            } else if (memory[i][cache_index].time < oldest_time) {
                oldest_time = memory[i][cache_index].time;
                cache_block_number = i;
            }
        }
```
Затем ставлю у найденной строки *[MRU](#mru) = 1*. Если после этого у всех кеш линий в строке *[MRU](#mru) == 1*, то обнуляю [*MRU*](#mru):
```
MRU[cache_index] |= (1 << cache_block_number);

        if  (MRU[cache_index] == (1 << CACHE_WAY) - 1) {
            MRU[cache_index] = 0;
        }
```

Ну и в обоих случаях если кэш промах, то загружаю в [*RAM*](#class-ram) стоящую на найденном месте кэш линию и загружаю из ОЗУ под новым тегом.

Также реализованны вспомогательные методы - инструменты, которые заменяют биты из
инта в векторе булов, или наоборот берут часть вектора и переводят её в инт.

**Поля:**
- [**```RAM ram```**](#class-ram) - оперативная память
- **```std::vector<std::vector<CacheLine>> memory```** - std::vector<std::vector<CacheLine>> - вектор блоков кэш линий
- <a id="mru"></a>**```std::vector<uint64_t> MRU```** - поле для работы [*bit-pLRU*](#bit-plru)
- **```ExclusionPolicy exclusion_policy```** - политика вытеснения
- **```uint64_t misses```** - количество кэш-попаданий
- **```uint64_t hits```** - количество кэш-промахов
- **```int64_t time```** - время очередного обращения к кэш-памяти (инкрементится каждый раз в [*FindLine*](#find-line))

**Методы:**
- <a id="cache-load"></a>**```int64_t Load(uint64_t address, uint8_t size = 1)```** - выгрузка *size* байт, проверка выход за пределы кэш строки
- <a id="cache-store"></a>**```void Store(int64_t value, uint64_t address, uint8_t size = 1)```** - загрузка *size* байт, проверка выход за пределы кэш строки
- <a id="find-line"></a>**```CacheLine& FindLine(uint64_t address)```** - разветвление на [*LRU*](#lru) и [*bit-pLRU*](#bit-plru)
- **```CacheLine& FindLineLRU(uint64_t address)```** - поиск кэш линии с политикой вытеснения [*LRU*](#lru)
- **```CacheLine& FindLineBitPLRU(uint64_t address)```** - поиск кэш линии с политикой вытеснения [*bit-pLRU*](#bit-plru)





### class RAM
Большой вектор булов размера *MEM_SIZE*, моделирует озу.

**Поля:**
- **```std::vector<bool> memory```** - сама память

**Методы:**

- **```void Get(std::vector<bool>& dest, uint64_t address)```** - записывает в *dest* *CACHE_LINE_SIZE* байт памяти по адресу address
- **```void Put(const std::vector<bool>& line, uint64_t address)```** - записывает *line* в озу по адресу *address*





### class CacheLine
Кэш линия, содержащая *CACHE_LINE_SIZE * BYTE_SIZE* битов (вектор булов), флаг времени, тэг строки - адрес в оперативе.

**Поля:**
- **```uint64_t time```** - время последнего обращения для [LRU](#lru)
- **```uint64_t tag```** - тэг из адресса в озу
- **```std::vector<bool> data```** - сами данные





### class Deserializer
Определяет каждую конкретную операцию, читает и распаршивает машинный код, возвращает [CommandToken](#class-commandtoken)

**Поля:**
- **```std::ifstream stream```** - поток машинного кода
- **```std::string path```** - путь к файлу машинного кода

**Методы:**
- **```CommandToken execute()```** - читает 4 байта из файла машинного кода

**Функции:**
- **```CommandToken ParseBin(uint32_t bin_command)```** - определяет команду, создает класс операции и вызывает у нее метод [*ParseBin*](#parse-bin)

### class CommandToken

**Поля:**
- **```OperationCode command = OperationCode::NONE```** - код операции из *enum OperationCode*
- **```std::vector<std::string> operands```** - операнды