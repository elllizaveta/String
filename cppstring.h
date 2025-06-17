#ifndef TRESH_MI_CHTO_VZROSLIE_STRING_PISATT
#define TRESH_MI_CHTO_VZROSLIE_STRING_PISATT
#include <iostream>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

struct String {
 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  char* data_ = nullptr;
  void Reallocate(size_t);

 public:
  String() = default;
  String(size_t, char);
  String(const char*);  // NOLINT
  String(const char*, size_t);
  String(String&&) noexcept;
  String(const String&);
  ~String() noexcept;
  String& operator=(String&&);
  String& operator=(const String&);
  char& operator[](size_t);
  const char& operator[](size_t) const;
  char& At(size_t);
  const char& At(size_t) const;
  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;
  char* CStr();
  const char* CStr() const;
  const char* Data() const;
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String&);
  void PopBack();
  void PushBack(char);
  String& operator+=(const String&);
  void Resize(size_t, char);
  void Reserve(size_t);
  void ShrinkToFit();
  bool operator<(const String&) const;
};

String operator+(const String&, const String&);
bool operator>(const String&, const String&);
bool operator>=(const String&, const String&);
bool operator<=(const String&, const String&);
bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);
std::ostream& operator<<(std::ostream&, const String&);

#endif