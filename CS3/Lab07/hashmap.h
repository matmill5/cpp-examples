// implementation basic hashmap (unordered container)
// Mikhail Nesterenko: adapted from Proc C++
// 4/15/2014

// Name:  Matthew Miller

#include <cstddef>
#include <utility>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using std::vector;
using std::list;
using std::pair;
using std::make_pair;

//////////////////////////////////////////
// hash function implemented as a class
//////////////////////////////////////////

// any Hash Class must provide 
// two methods: hash() and numBuckets().
template <typename T>
class DefaultHash {
public:
	DefaultHash(size_t numBuckets = defaultNumBuckets);
	size_t hash(const T& key) const;
	size_t numBuckets() const { return numBuckets_; }
	void setNumBuckets(int n) { numBuckets_ = n; }

private:
	// default number of buckets in the hash
	static const size_t defaultNumBuckets = 101;
	size_t numBuckets_;
};

template <typename T>
DefaultHash<T>::DefaultHash(size_t numBuckets) :
	numBuckets_(numBuckets) {}


// uses the division method for hashing.
// treats the key as a sequence of bytes, sums the ASCII
// values of the bytes, and mods the total by the number
// of buckets.
template <typename T>
size_t DefaultHash<T>::hash(const T& key) const {
	size_t res = 0;
	for (size_t i = 0; i < sizeof(key); ++i) {
		const unsigned char b =
			*(reinterpret_cast<const unsigned char *>(&key) + i);
		res += b;
	}
	return res % numBuckets_;
}


////////////////////////////////////////////////
// container class
////////////////////////////////////////////////

template <typename Key, typename Value,
	typename Compare = std::equal_to<Key>,
	typename Hash = DefaultHash<Key>>
	class hashmap {

	public:
		typedef pair<const Key, Value> Element;

		// constructor
		// invokes constructors for comparison and hash objects
		hashmap(const Compare& comp = Compare(),
			const Hash& hash = Hash());

		Element* find(const Key& x);      // returns pointer to element with key x,
										  // nullptr if not found
		pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> insert(const Element& x);    // inserts the key/value pair 
		pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> erase(const Key& x);         // erases element with key x, if exists
		Value& operator[] (const Key& x); // returns reference on value of
										  // element with key, inserts if does not exist
		void rehash(size_t n);
		void print();
	private:

		// helper function for various searches
		typename list<Element>::iterator
			findElement(const Key& x,
				const size_t bucket);

		size_t size_;   // number of elements in the container
		Compare comp_;  // comparison functor, equal_to by default
		Hash hash_;     // hash functor 

		// hash contents: vector of buckets
		// each bucket is a list containing key->value pairs
		vector<list<Element>> elems_;
};


////////////////////////////////////////////////
// container member functions
////////////////////////////////////////////////

// Construct elems_ with the number of buckets.
template <typename Key, typename Value, typename Compare, typename Hash>
hashmap<Key, Value, Compare, Hash>::hashmap(
	const Compare& comp, const Hash& hash) :
	size_(0), comp_(comp), hash_(hash) {
	elems_ = vector<list<Element>>(hash_.numBuckets());
}


// helper function
template <typename Key, typename Value,
	typename Compare, typename Hash>
	typename list<pair<const Key, Value>>::iterator // return type
	hashmap<Key, Value, Compare, Hash>::findElement(const Key& x, size_t bucket) {

	// look for the key in the bucket
	for (auto it = elems_[bucket].begin();
		it != elems_[bucket].end(); ++it)
		if (comp_(it->first, x))
			return it;

	return elems_[bucket].end(); // element not found
}


// returns a pointer to the element with key x
// returns nullptr if no element with this key
template <typename Key, typename Value, typename Compare, typename Hash>
typename hashmap<Key, Value, Compare, Hash>::Element* // return value type
hashmap<Key, Value, Compare, Hash>::find(const Key& x) {

	size_t bucket = hash_.hash(x);
	auto it = findElement(x, bucket);    // use the findElement() helper   

	if (it != elems_[bucket].end())
		// found the element. Return a pointer to it.
		return &(*it); // dereference the iterator to list 
					   // then take the address of list element

	else // didn't find the element -- return nullptr
		return nullptr;
}


// finds the element with key x, inserts an
// element with that key if none exists yet. Returns a reference to
// the value corresponding to that key.
template <typename Key, typename Value, typename Compare, typename Hash>
pair<typename hashmap<Key, Value, Compare, Hash>::Element* , bool> hashmap<Key, Value, Compare, Hash>::insert(const Element& x) {

	size_t bucket = hash_.hash(x.first);
	auto it = findElement(x.first, bucket);    // try to find the element

	// if not found, insert a new one.
	if (it == elems_[bucket].end()) {
		++size_;
		elems_[bucket].push_back(x);
		hashmap<Key, Value, Compare, Hash>::Element* insertedElem = find(x.first);
		return make_pair(insertedElem, true);
	}
	else {
		return make_pair(&(*it), false);
	}
}


// removes the Element with key x, if it exists
template <typename Key, typename Value, typename Compare, typename Hash>
pair<typename hashmap<Key, Value, Compare, Hash>::Element*, bool> hashmap<Key, Value, Compare, Hash>::erase(const Key& x) {

	size_t bucket = hash_.hash(x);
	auto it = findElement(x, bucket);    // try to find the element

	// Tracking state of erased
	bool erased = false;

	if (it != elems_[bucket].end()) { // the element exists, erase it
		elems_[bucket].erase(it);
		--size_;
		erased = true;
	}

	// find next list with size > 0
	auto nextListIt = find_if(elems_.begin() + bucket, elems_.end(),[](list <pair<const Key, Value>> e){return e.size() > 0; });

	// if no more lists with size > 0, no more next elements
	if (nextListIt == elems_.end())
		return make_pair(nullptr, erased);
	
	pair<const Key, Value> nextElement = *((*nextListIt).begin());
	return make_pair(&nextElement, erased);
}


// returns reference to value of element with key x,
// inserts if does not exist
template <typename Key, typename Value, typename Compare, typename Hash>
Value& hashmap<Key, Value, Compare, Hash>::operator[] (const Key& x) {

	Element* found = find(x);
	if (found == nullptr) { // if key not found, create new element with empty value
		auto result = insert(make_pair(x, Value())); // calling default constructor on Value
		found = result.first;
	}
	return found->second;
}

// Conducts the resizing and rehashing of hashmap
template<typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::rehash(size_t n) {

	if (hash_.numBuckets() > n) {
		// Take no action (per instructions)
	}
	else { // Do the resize and rehash
		// sets number of buckets to n 
		hash_.setNumBuckets(n);
		auto temp = std::move(elems_);

		// Clears the vector
		elems_.clear();

		// Resizes it to n
		elems_.resize(n);

		// Sets current size to 0 - no elements
		size_ = 0;

		// For each bucket and all elements of previous hashmap, 
		// reinsert with the new hashing.
		for (auto bucket : temp)
			for (auto element : bucket)
				insert(element);
	}
}

// Prints hashmap for debuggin/verification
template<typename Key, typename Value, typename Compare, typename Hash>
void hashmap<Key, Value, Compare, Hash>::print() {
	// Print all elements of hash function
	std::cout << "All values: \nKey\tValue" << std::endl;
	for_each(elems_.begin(), elems_.end(), [](list<pair<const Key, Value>> bucket) {
		for_each(bucket.begin(), bucket.end(), [](pair<const Key, Value> element) {
			std::cout << element.first << "\t" << element.second << "\n";
		});
	});
	std::cout << "Printed " << this->size_ << " elements." << std::endl;
}