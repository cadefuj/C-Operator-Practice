#include <string>
#include <iostream> 
#include <istream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#ifndef RANGE_H
#define RANGE_H

template <typename T> 
class Range {
	public: 
		[[nodiscard]] T min() const {
			return minimum;
		}
		[[nodiscard]] T max() const {
			return maximum;
		}
		void setMin(T val) {
			minimum = val;
		}
		void setMax(T val) {
			maximum = val;
		}
		Range(const T val): minimum(val), maximum(val) {}
		Range(const T low, const T high) { 
			if (high < low) {
				throw std::runtime_error("Range is out of order, " + std::to_string(low) + " is greater than " + std::to_string(high));
			}
			minimum = low;
			maximum = high;
		}
		Range(const Range& range) : minimum(range.minimum), maximum(range.maximum) {}
		Range<T> operator=(const Range& range) {
			minimum = range.minimum;
			maximum = range.maximum;
			return *this;
		}
		void assign(T low, T high) {
			std::string message = "Range is out of order, " + std::to_string(low) + " is greater than " + std::to_string(high);
			if (low > high) {
				throw std::runtime_error(message);
			}
			else {
				minimum = low;
				maximum = high;
			}
		}
		Range<T>& operator+=(const Range<T>& range) const {
			setMin(minimum + range.min());
			setMax(maximum + range.max());
			return *this;
		}
		Range<T>& operator-=(const Range<T>& range) const {
			setMin(minimum - range.min());
			setMax(maximum - range.max());
			return *this;
		}
		Range<T>& operator*=(const Range<T>& range) const {
			std::vector<T> values1;
			std::vector<T> values2;
			std::vector<T> temp;
			values1.push_back(minimum);
			values1.push_back(maximum);	
			values2.push_back(range.min());
			values2.push_back(range.max());
			for (auto val1 : values1) {
				for (auto val2 : values2) {
					temp.push_back(val1 * val2); 
				}
			}
			T minval = *min_element(temp.begin(), temp.end());
			T maxval = *max_element(temp.begin(), temp.end());
			setMin(minval);
			setMax(maxval);
			return *this;
			
		}
		Range<T>& operator/=(const Range<T>& range) const {
			if (range.min() <= 0 && range.max() >= 0) {
				throw std::runtime_error("Value of min or max value results to 0. Min: " + std::to_string(range.min()) + " , Max: " + std::to_string(range.max()));
			}
			std::vector<T> values1;
			std::vector<T> values2;
			std::vector<T> temp;
			values1.push_back(minimum);
			values1.push_back(maximum);	
			values2.push_back(range.min());
			values2.push_back(range.max());
			for (auto val1 : values1) {
				for (auto val2 : values2) {
					temp.push_back(val1 / val2); 
				}
			}
			T minval = *min_element(temp.begin(), temp.end());
			T maxval = *max_element(temp.begin(), temp.end());
			setMin(minval);
			setMax(maxval);
			return *this;
		}
		Range<T> operator+(const Range<T>& range) const {
			Range<T> temp(0); 
			temp.setMin(minimum + range.min());
			temp.setMax(maximum + range.max());
			return temp;
		}
		Range<T> operator-(const Range<T>& range) const {
			Range<T> temp(0); 
			temp.setMin(minimum - range.max());
			temp.setMax(maximum - range.min());
			return temp;
		}
		Range<T> operator*(const Range<T>& range) const {
			Range<T> temp(0);
			std::vector<T> values1;
			std::vector<T> values2;
			std::vector<T> tempvec;
			values1.push_back(minimum);
			values1.push_back(maximum);	
			values2.push_back(range.min());
			values2.push_back(range.max());
			for (auto val1 : values1) {
				for (auto val2 : values2) {
					tempvec.push_back(val1 * val2); 
				}
			}
			T minval = *min_element(tempvec.begin(), tempvec.end());
			T maxval = *max_element(tempvec.begin(), tempvec.end());
			temp.setMin(minval);
			temp.setMax(maxval);
			return temp;
		}
		Range<T> operator/(const Range<T>& range) const {
			if (range.min() <= 0 && range.max() >= 0) {
				throw std::runtime_error("Value of min or max value results to 0. Min: " + std::to_string(range.min()) + " , Max: " + std::to_string(range.max()));
			}
			Range<T> temp(0);
			std::vector<T> values1;
			std::vector<T> values2;
			std::vector<T> tempvec;
			values1.push_back(minimum);
			values1.push_back(maximum);	
			values2.push_back(range.min());
			values2.push_back(range.max());
			for (auto val1 : values1) {
				for (auto val2 : values2) {
					tempvec.push_back(val1 / val2); 
				}
			}
			T minval = *min_element(tempvec.begin(), tempvec.end());
			T maxval = *max_element(tempvec.begin(), tempvec.end());
			temp.setMin(minval);
			temp.setMax(maxval);
			return temp;
		}
		bool operator==(const Range<T>& range) const {
			if (minimum == range.min() && maximum == range.max()) {
				return true;
			}
			else {
				return false;
			}
		}
		bool operator!=(const Range<T>& range) const {
			if (minimum != range.min() && maximum != range.max()) {
				return true;
			}
			else {
				return false;
			}	
		}
		friend std::ostream& operator<<(std::ostream& os, const Range<T>& range) {
			os << "[" << range.min() << "," << range.max() << "]";
			return os;
		}
		friend std::istream& operator>>(std::istream& is, Range<T>& range) {
			if (is.fail()) {
				is.setstate(std::ios_base::failbit);
			}
			is.ignore(256, '[');
			is >> range.minimum;
			is.ignore(256, ',');
			is >> range.maximum;
			is.ignore(256, ']');
			return is;
		}
	private: 
		T minimum;
		T maximum;
};
#endif
