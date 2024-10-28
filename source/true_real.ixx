export module stk.math:true_real;
import se;
import stk.log;

using namespace stk;

namespace stk
{
	export
	class c_true_real
	{
	public:
		explicit c_true_real(se::uint64_t value = 0)
		{
			parts.push_back(value);
		}

		// Addition operator
		c_true_real operator+(c_true_real const& rhs) const
		{
			c_true_real result;
			result.parts.resize(se::max(parts.size(), rhs.parts.size()), 0);
			se::uint64_t carry = 0;
			for (size_t i = 0; i < result.parts.size(); ++i)
			{
				se::uint64_t partThis = i < parts.size() ? parts[i] : 0;
				se::uint64_t partRhs = i < rhs.parts.size() ? rhs.parts[i] : 0;
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

		se::string to_string() const
		{
			se::string res;
			for (auto part : parts)
			{
				while (part > 0)
				{
					char digit = pop_digit(part);
					res.insert(0, 1, digit);
				}
			}
			return res;
		}

	private:
		char pop_digit(se::uint64_t& part) const
		{
			se::uint64_t digit = part % 10;
			part /= 10;
			return '0' + digit;
		}

		friend struct se::formatter<c_true_real>;
		se::vector<se::uint64_t> parts;
	};
}

template<>
struct se::formatter<stk::c_true_real>
{
	template<class ParseContext>
	constexpr auto parse(ParseContext& ctx)
	{
		return ctx.begin(); // No custom parsing logic required
	}

	template<class FormatContext>
	auto format(const stk::c_true_real& value, FormatContext& ctx)
	{
		se::string formatted_value;
		bool first = true;

		for (auto part : value.parts)
		{
			// For the most significant part, don't pad with zeros
			if (first)
			{
				formatted_value += se::format("{}", part);
				first = false;
			}
			else
			{
				// For other parts, pad with zeros to a fixed width
				// Assuming each part is a 64-bit integer, pad to 20 digits (maximum for se::uint64_t)
				formatted_value += se::format("{:020}", part);
			}
		}
		return format_to(ctx.out(), "{}", formatted_value);
	}
};
