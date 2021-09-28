# Identificação Pessoal

- Nome: *Rita C. C. Cruz*
- Email: *rcchcz@gmail.com*
- Turma: *T01*

- Nome: *Victor V. Targino*
- Email: *victorvieira.rn@gmail.com*
- Turma: *T01*

# Indique quais métodos das classes abaixo foram implementados

## Implementação do Vector

**Special members (21 credits)**
- [ ] Regular constructor (3 credits)
- [x] Destructor (3 credits)
- [x] Copy constructor (3 credits)
- [x] Constructor from range (3 credits)
- [x] Constructor from initialize list (3 credits)
- [x] Assignment operator (x 2) (6 credits)

**Iterator methods (4 credits)**
- [x] `begin()` (1 credits)
- [x] `end()` (1 credits)
- [x] `cbegin()` (1 credits)
- [x] `cend()` (1 credits)

**Capacity methods (3 credits)**
- [x] `empty()` (1 credits);
- [x] `size()` (1 credits);
- [x] `capacity()` (1 credits);

**Modifiers methods (52 credits)**
- [x] `clear()` (1 credits)
- [x] `push_back()` (3 credits)
- [x] `pop_back()` (3 credits)
- [ ] `insert()` \times 6 (18 credits)
- [ ] `reserve()` (3 credits)
- [x] `shrink_to_fit()` (3 credits)
- [x] `assign()` \times 3 (9 credits)
- [ ] `erase()` \times 4 (12 credits)

**Element access methods (10 credits)**
- [x] `front()` (1 credits)
- [x] `back()` (1 credits)
- [x] `operator[]()` \times 2 (4 credits)
- [x] `at()` \times 2 (4 credits)

**Operators (2 credits)**
- [x] `operator==()` (1 credits)
- [x] `operator!=()` (1 credits)

## Implementação do Iterator

**Special members (3 credits)**
- [x] Regular constructor (1 credits)
- [x] Copy constructor (1 credits)
- [x] Assignment operator (1 credits)

**Navigation methods (12 credits)**
- [x] increment operator `++it` and `it++` (2 credits)
- [x] decrement operator `--it` and `it--` (2 credits)
- [x] forward jump operator `it + n` or `n + it`   (2 credits)
- [x] backward jump operator `it - n` or `n - it`   (2 credits)
- [x] difference between iterators `it1-it2` (1 credits)
- [x] dereference operator `*it` (1 credits)
- [x] equality/difference operators `it1==it2` and `it1!=it2` (2 credits)

# Running

```
g++ -Wall -Werror source/tests/main.cpp source/tests/include/tm/test_manager.h source/include/vector.h -o RUN_TESTS
./RUN_TESTS
```
--------
&copy; DIMAp/UFRN 2021.