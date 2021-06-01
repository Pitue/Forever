#ifndef __FOREVER_TS_DEQUE_H__
#define __FOREVER_TS_DEQUE_H__

#include <deque>
#include <thread>
#include <mutex>
#include <initializer_list>
#include <type_traits>

namespace fr {
	/*A thread safe deque with most functionality of the std::deque*/
	template <typename type>
	class TsDeque {
		static_assert(std::is_copy_constructible<type>::value, "type has to be copy constructible!");
		std::deque<const type*> deque_;
		std::mutex write_mutex_;

		mein name ist marc!!!!!!
	public:
		TsDeque(): deque_() {}
		TsDeque(size_t size): deque_(size) {}
		TsDeque(size_t size, const type& val): deque_(size) {
			for (size_t i = 0; i < size; i++) deque_.at(i) = new type(val);
		}
		TsDeque(std::initializer_list<const type&> list) {
			for (auto& x : list) {
				deque_.push_back(new type(x));
			}
		}
		~TsDeque() {
			for (auto& x : deque_) {
				delete x;
				x = nullptr;
			}
		}

		//basic
		size_t size() const {
			return deque_.size();
		}
		bool empty() const { return deque_.empty(); }

		//read access
		type operator [] (size_t ind) const {
			return read(ind);
		}
		type read(size_t ind) const { return *deque_.at(ind); }
		type at(size_t ind) const { return read(ind); }
		type front() const {
			return *deque_.front();
		}
		type back() const {
			return *deque_.back();
		}

		//write access
		//overriding
		void clear() {
			std::scoped_lock(write_mutex_);
			for (auto& x : deque_) delete x;
			deque_.clear();
		}
		void write(size_t ind, const type& val) {
			std::scoped_lock(write_mutex_);
			delete deque_.at(ind);
			deque_.at(ind) = new type(val);
		}
		//use carefully
		void erase(std::deque<const type*>::const_iterator it) {
			std::scoped_lock(write_mutex_);
			delete* it;
			deque_.erase(it);
		}
		//use carefully
		void erase(std::deque<const type*>::const_iterator first, std::deque<const type*>::const_iterator last) {
			std::scoped_lock(write_mutex_);
			for (auto it = first; it < last; it++) { delete* it; }
			deque_.erase(first, last);
		}
		void pop_front() {
			std::scoped_lock(write_mutex_);
			delete deque_.front();
			deque_.pop_front();
		}
		void pop_back() {
			std::scoped_lock(write_mutex_);
			delete deque_.back();
			deque_.pop_back();
		}

		//inserting
		void insert(std::deque<const type*>::const_iterator wh, const type& val) {
			std::scoped_lock(write_mutex_);
			deque_.insert(wh, new type(val));
		}
		void insert(std::deque<const type*>::const_iterator wh, type&& val) {
			std::scoped_lock(write_mutex_);
			deque_.insert(wh, new type(val));
		}
		void push_back(const type& val) {
			std::scoped_lock(write_mutex_);
			deque_.push_back(new type(val));
		}
	};
}

#endif // !__FOREVER_TS_VECTOR_H__
