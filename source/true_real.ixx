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

		// Print function for convenience
		void print() const
		{
			debugln("{}", *this);

			//for (auto it = parts.rbegin(); it != parts.rend(); ++it)
			//{
			//	debug("{} ", *it);
			//}
			//debugln("");
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

		for (auto it = value.parts.rbegin(); it != value.parts.rend(); ++it)
		{
			// For the most significant part, don't pad with zeros
			if (first)
			{
				formatted_value += std::format("{}", *it);
				first = false;
			}
			else
			{
				// For other parts, pad with zeros to a fixed width
				// Assuming each part is a 64-bit integer, pad to 20 digits (maximum for uint64_t)
				formatted_value += std::format("{:020}", *it);
			}
		}
		return format_to(ctx.out(), "{}", formatted_value);
	}
};
