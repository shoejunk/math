export module stk.math:true_real;
import std.core;

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
			for (auto it = parts.rbegin(); it != parts.rend(); ++it)
			{
				std::cout << *it << " ";
			}
			std::cout << "\n";
		}

	private:
		std::vector<uint64_t> parts;
	};
}
