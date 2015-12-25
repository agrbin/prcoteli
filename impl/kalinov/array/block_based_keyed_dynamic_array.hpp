#ifndef IMPL_KALINOV_ARRAY_BLOCK_BASED_KEYED_DYNAMIC_ARRAY_HPP_
#define IMPL_KALINOV_ARRAY_BLOCK_BASED_KEYED_DYNAMIC_ARRAY_HPP_

#include <unordered_map>
#include <utility>
#include <vector>

namespace kalinov {

using namespace std;

template <typename T>
class BlockBasedKeyedDynamicArray {
 public:
  typedef int key_type;
  typedef T value_type;

  BlockBasedKeyedDynamicArray() { blocks_.push_back(new vector<Element*>()); }

  BlockBasedKeyedDynamicArray(int n) {
    blocks_.push_back(new vector<Element*>());
    for (int i = 0; i < n; ++i) Insert(i, value_type());
  }

  template <typename A>
  BlockBasedKeyedDynamicArray(A const& array) {
    blocks_.push_back(new vector<Element*>());
    for (int i = 0; i < array.size(); ++i) Insert(i, array[i]);
  }

  ~BlockBasedKeyedDynamicArray() {
    for (int i = 0; i < blocks_.size(); ++i) {
      delete blocks_[i];
    }
  }

  int size() const { return elements_.size(); }

  value_type const& operator[](int index) const {
    pair<int, int> const address = GetAddressForIndex(index);
    return (*blocks_[address.first])[address.second]->value;
  }

  value_type& operator[](int index) {
    pair<int, int> const address = GetAddressForIndex(index);
    return (*blocks_[address.first])[address.second]->value;
  }

  key_type Insert(int index, value_type value) {
    pair<int, int> const address = GetAddressForIndex(index);
    Element* element = CreateElement(value, address.first);
    vector<Element*>* block = blocks_[address.first];
    block->insert(block->begin() + address.second, element);
    MaybeSplit(address.first);
    MaybeRebalance();
    return element->key;
  }

  key_type InsertAfterKey(key_type key, value_type value) {
    pair<int, int> const address = GetAddressForKey(key);
    Element* element = CreateElement(value, address.first);
    vector<Element*>* block = blocks_[address.first];
    block->insert(block->begin() + address.second + 1, element);
    MaybeSplit(address.first);
    MaybeRebalance();
    return element->key;
  }

  key_type InsertBeforeKey(key_type key, value_type value) {
    pair<int, int> const address = GetAddressForKey(key);
    Element* element = CreateElement(value, address.first);
    vector<Element*>* block = blocks_[address.first];
    block->insert(block->begin() + address.second, element);
    MaybeSplit(address.first);
    MaybeRebalance();
    return element->key;
  }

  void Remove(int index) {
    pair<int, int> const address = GetAddressForIndex(index);
    vector<Element*>* block = blocks_[address.first];
    key_type const key = (*block)[address.second]->key;
    block->erase(block->begin() + address.second);
    elements_.erase(key);
    MaybeMerge(address.first);
    MaybeRebalance();
  }

  void RemoveKey(key_type key) {
    pair<int, int> const address = GetAddressForKey(key);
    vector<Element*>* block = blocks_[address.first];
    block->erase(block->begin() + address.second);
    elements_.erase(key);
    MaybeMerge(address.first);
    MaybeRebalance();
  }

  value_type const& Get(key_type key) const {
    pair<int, int> const address = GetAddressForKey(key);
    vector<Element*>* block = blocks_[address.first];
    return (*block)[address.second]->value;
  }

  value_type& Get(key_type key) {
    pair<int, int> const address = GetAddressForKey(key);
    vector<Element*>* block = blocks_[address.first];
    return (*block)[address.second]->value;
  }

  int GetIndex(key_type key) const {
    pair<int, int> const address = GetAddressForKey(key);
    int index = address.second;
    for (int i = 0; i < address.first; ++i) {
      index += blocks_[i]->size();
    }
    return index;
  }

 private:
  struct Element {
    key_type key;
    value_type value;
    vector<Element*>* block;
  };

  Element* CreateElement(value_type value, int block_index) {
    key_type const key = next_key_++;
    Element* element = &elements_[key];
    element->key = key;
    element->value = value;
    element->block = blocks_[block_index];
    return element;
  }

  pair<int, int> GetAddressForIndex(int index) const {
    int i = 0;
    for (; i + 1 < blocks_.size(); ++i) {
      if (index < blocks_[i]->size()) break;
      index -= blocks_[i]->size();
    }
    return make_pair(i, index);
  }

  pair<int, int> GetAddressForKey(key_type key) const {
    vector<Element*>* block = elements_.find(key)->second.block;
    int block_index = 0;
    while (blocks_[block_index] != block) ++block_index;
    int i = 0;
    for (; i < block->size(); ++i) {
      if ((*block)[i]->key == key) break;
    }
    return make_pair(block_index, i);
  }

  void MaybeSplit(int block_index) {
    vector<Element*>* block = blocks_[block_index];
    if (block->size() < 2 * target_block_size_) return;
    vector<Element*>* new_block = new vector<Element*>();
    for (int i = block->size() / 2; i < block->size(); ++i) {
      Element* element = (*block)[i];
      new_block->push_back(element);
      element->block = new_block;
    }
    block->erase(block->begin() + block->size() / 2, block->end());
    blocks_.insert(blocks_.begin() + block_index + 1, new_block);
  }

  void MaybeMerge(int block_index) {
    vector<Element*>* block = blocks_[block_index];
    if (block->size() * 2 > target_block_size_) return;
    vector<Element*>* left_block =
        block_index == 0 ? nullptr : blocks_[block_index - 1];
    vector<Element*>* right_block =
        block_index + 1 == blocks_.size() ? nullptr : blocks_[block_index + 1];
    if (left_block == nullptr && right_block == nullptr) return;
    if (left_block == nullptr ||
        right_block != nullptr && right_block->size() < left_block->size()) {
      Merge(block_index + 1, block, right_block);
    } else {
      Merge(block_index, left_block, block);
    }
  }

  void Merge(int right_block_index, vector<Element*>* left_block,
             vector<Element*>* right_block) {
    for (int i = 0; i < right_block->size(); ++i) {
      Element* element = (*right_block)[i];
      left_block->push_back(element);
      element->block = left_block;
    }
    blocks_.erase(blocks_.begin() + right_block_index);
    delete right_block;
  }

  void MaybeRebalance() {
    if (size() > target_block_size_ * target_block_size_ * 4) {
      target_block_size_ *= 2;
      for (int i = 0; i < blocks_.size(); ++i) {
        MaybeSplit(i);
      }
    }
    if (target_block_size_ > 10 &&
        size() < target_block_size_ * target_block_size_ / 4) {
      target_block_size_ /= 2;
      for (int i = 0; i < blocks_.size(); ++i) {
        MaybeMerge(i);
      }
    }
  }

  int target_block_size_ = 10;
  vector<vector<Element*>*> blocks_;
  key_type next_key_ = 0;
  unordered_map<key_type, Element> elements_;
};

}  // namespace kalinov

#endif  // IMPL_KALINOV_ARRAY_BLOCK_BASED_KEYED_DYNAMIC_ARRAY_HPP_
