#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <stdexcept>

//
// The config
//

/*! If true, the debug prints will be printed. */
constexpr bool DEBUG_PRINT = true;

/*! A type of elements that the container accepts */
using ElemType = size_t;

/*! Helper function that does conditional printing */
template <class... Args>
void debug(const std::string& fmt, Args&&... args) {
    if constexpr (DEBUG_PRINT) {
        std::ostringstream ss;
        (ss << ... << args);
        std::cout << fmt << ss.str() << std::endl;
    }
}



class GoodVec;


class Iter {
public:
    Iter(GoodVec* p_vec, size_t block_idx, size_t offset) : _p_vec(p_vec), _block_idx(block_idx), _offset(offset){}

     ElemType& operator* () const;
     Iter& operator++();

    bool operator==(const Iter& other) const {
        return _p_vec == other._p_vec && _block_idx == other._block_idx && _offset == other._offset;
    }

    bool operator!=(const Iter& other) const {
        return !(*this == other);
    }

private:
    GoodVec* _p_vec;
    size_t  _block_idx;
    size_t  _offset;
};

/*!
 * A simple container that behaves like a vector but guarantees that
 * the elements present in the container will be never reallocated. 
 * Thus, one can be sure that the iterators/pointers to the elements inside
 * the container won't get invalid as long as the element is not removed 
 * from the container.
 */
class GoodVec {
public:
	/*! Inserts a copy of the provided element into the container. */
	void push_back(const ElemType& x) {
		// If more space is required
		if (_size == _capacity) alloc_new_block();

		auto [block_idx, idx] = to_block_off(_size);

		_blocks[block_idx][idx] = x;
		++_size;
	}

	/*! Removes the last element at the back of the container and returns it. */
	ElemType pop_back() {
		if (_size < 1) throw std::runtime_error("Nothing to pop!");

		--_size;
		auto [block_idx, idx] = to_block_off(_size);

		// (!) If this were a local variable, no std::move shall be used
		// But it is not, we shall state that the caller can steal from this location
		return std::move(_blocks[block_idx][idx]);
	}

	/*! Returns a mutable reference to the element at the provided index. */
	ElemType& operator[](ElemType idx) {
		auto [block_idx, off] = to_block_off(idx);
		return _blocks[block_idx][off];
	}

	/*! Returns the number of elements currently in the container. */
	size_t size() const {
		return _size;
	}

	/*! Returns the number of currently allocated slots for elements. */
	size_t capacity() const {
		return _capacity;
	}

    Iter begin(){
        return  Iter(this, 0, 0);
    }

    Iter end() {
        auto [block_idx, off] = to_block_off(_size);
        return Iter(this, block_idx, off);
    }

private:
	/*! Allocates the additional block for data. */
	void alloc_new_block() {
		debug("\tAllocating {}-th block...", _next_block);
		++_next_block;
		_blocks.resize(_next_block);
		_capacity += BS;
	}

	/*! Maps the global index to block index and offset within this block. */
	std::pair<size_t, size_t> to_block_off(size_t glob_idx) {
		auto block_idx = glob_idx / BS;
		auto off = glob_idx % BS;
		debug("\t{} -> {}, {}", glob_idx, block_idx, off);
		return std::pair(block_idx, off);
	}
private:
	/*! Size of the internal block. */
	static constexpr size_t BS = 4;

private:
	/*! A list of blocks that hold the actual elements. */
	std::vector<std::array<ElemType, BS>> _blocks;
	/*! The current number of elements in the container. */
	size_t _size = 0;
	/*! The current capacity of the container. */
	size_t _capacity = 0;
	/*! An index of the block to be allocated. */
	size_t _next_block = 0;

    friend class Iter;
};
ElemType& Iter::operator*() const {
    return _p_vec->_blocks[_block_idx][_offset];
}
Iter& Iter::operator++() {
    if (++_offset >= GoodVec::BS) {
        _offset = 0;
        ++_block_idx;
    }
    return *this;
}
int main()
{
    GoodVec xs;

    for (size_t i = 0; i < 5; ++i) {
        xs.push_back(i);
        std::cout << "Inserted: " << xs[i] << std::endl;
    }

    // Replace std::format with std::ostringstream
    std::ostringstream size_msg;
    size_msg << "Size: " << xs.size();
    std::cout << size_msg.str() << std::endl;

    std::ostringstream capacity_msg;
    capacity_msg << "Capacity: " << xs.capacity();
    std::cout << capacity_msg.str() << std::endl;

    std::cout<<"Test completed";
}
