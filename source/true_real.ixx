export module stk.math:true_real;
import std.core;
import stk.log;

using namespace stk;

namespace stk
{
	export
	class c_true_real
	{
	public:
		explicit c_true_real(uint64_t value = 0)
		{
			parts.push_back(value);
		}

		// Addition operator
		c_true_real operator+(c_true_real const& rhs) const
		{
			c_true_real result;
			result.parts.resize(std::max(parts.size(), rhs.parts.size()), 0);
			uint64_t carry = 0;
			for (size_t i = 0; i < result.parts.size(); ++i)
			{
				uint64_t partThis = i < parts.size() ? parts[i] : 0;
				uint64_t partRhs = i < rhs.parts.size() ? rhs.parts[i] : 0;
				result.parts[i] = partThis + partRhs + carry;

				// Determine if a carry is needed
				carry = (result.parts[i] < partThis || (carry != 0 && result.parts[i] == partThis));
			}

			// Handle final carry
			if (carry)
			{
				result.parts.push_back(carry);
			}

			return result;
		}

		std::string to_string() const {
			if (parts.size() != 2) {
				return "0";
			}

			const uint64_t base = 10000000000000000000ULL; // 10^19, close to 2^64
			std::string result;
			uint64_t high_copy = parts[1];
			uint64_t low_copy = parts[0];

			while (high_copy != 0 || low_copy != 0) {
				uint64_t remainder = 0;
				divide_by_base(high_copy, low_copy, base, remainder);

				// Prepend the remainder to the result string.
				// When high is not zero, we need to ensure full groups of digits.
				std::string part = std::to_string(remainder);
				if (high_copy != 0 || low_copy != 0) {
					part.insert(part.begin(), 19 - part.length(), '0');
				}
				result = part + result;
			}

			return result;
		}

		// Divides the 128-bit number by the base, modifying the high and low parts, and sets the remainder.
		void divide_by_base(uint64_t& high, uint64_t& low, uint64_t base, uint64_t& remainder) const {
			uint64_t temp_high = high;
			uint64_t temp_low = low;

			high = 0;
			low = 0;
			remainder = 0;

			for (int i = 63; i >= 0; --i) {
				remainder = (remainder << 1) | ((temp_high >> i) & 1);
				if (remainder >= base) {
					remainder -= base;
					high |= (1ULL << i);
				}

				remainder = (remainder << 1) | ((temp_low >> i) & 1);
				if (remainder >= base) {
					remainder -= base;
					low |= (1ULL << i);
				}
			}
		}

	private:
		friend struct std::formatter<c_true_real>;
		std::vector<uint64_t> parts;
	};
}

template<>
struct std::formatter<stk::c_true_real>
{
	template<class ParseContext>
	constexpr auto parse(ParseContext& ctx)
	{
		return ctx.begin(); // No custom parsing logic required
	}

	template<class FormatContext>
	auto format(const stk::c_true_real& value, FormatContext& ctx)
	{
		std::string formatted_value;
		bool first = true;

		for (auto part : value.parts)
		{
			// For the most significant part, don't pad with zeros
			if (first)
			{
				formatted_value += std::format("{}", part);
				first = false;
			}
			else
			{
				// For other parts, pad with zeros to a fixed width
				// Assuming each part is a 64-bit integer, pad to 20 digits (maximum for uint64_t)
				formatted_value += std::format("{:020}", part);
			}
		}
		return format_to(ctx.out(), "{}", formatted_value);
	}
};
