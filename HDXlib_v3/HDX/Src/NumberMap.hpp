#pragma once
#include <unordered_map>
#include <vector>

// IDでアクセス出来るマップ
template <class T, class U>
class NumberMap
{
  int number_ = 0;
  std::unordered_map<T, int> Map_;
  std::vector<U> List_;
public:
  U& operator[](int Number) { return List_[Number]; }
  U& operator[](const T Key) { return List_[Map_[Key]]; }
public:
  size_t size()const noexcept { return Map_.size(); }
  bool empty()const noexcept { return Map_.empty(); }
  void clear()noexcept { number_ = 0; Map_.clear(); List_.clear(); }
  int insert(T first, U second) { Map_.insert(std::make_pair(first, number_)); List_.push_back(second); return number_++; }
  //  見つからない場合-1を返す
  int find(T Key) { return (Map_.find(Key) == Map_.end()) ? -1 : Map_[Key]; }
};

struct ID
{
  int Value;
  ID(int _Value) : Value(_Value) { }
};

inline bool operator==(const ID& _ID1, const ID& _ID2)
{
  return _ID1.Value == _ID2.Value;
}

template<>
struct std::hash<ID>
{
  size_t operator()(const ID& _ID)const
  {
    return _ID.Value;
  }
};
