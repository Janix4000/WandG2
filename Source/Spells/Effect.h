#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Modifier
{
public:
	enum class Type
	{
		Addon = 0,
		Factor
	};

	Modifier(float value, Type type = Type::Addon)
		:
		value(value),
		type(type)
	{}

	bool operator==(const Modifier& rhs) const
	{
		return value == rhs.value && type == rhs.type;
	}

	Type type;
	float value;
};

class Stat
{
	std::string name = "";
	float baseValue = 0;

	std::vector<const Modifier*> modifiers;

public:
	void addModifier(const Modifier& mod)
	{
		modifiers.emplace_back(&mod);
	}

	void removeModifier(const Modifier& mod)
	{
		auto newEnd = std::remove(modifiers.begin(), modifiers.end(), &mod);
		modifiers.erase(newEnd, modifiers.end());
	}

	void addToBaseValue(float add)
	{
		baseValue += add;
	}

	float getValue() const
	{
		float addon = 0;
		float factor = 1;

		for (const auto& mod : modifiers)
		{
			if (mod->type == Modifier::Type::Factor)
			{
				factor *= mod->value;
			}
			else
			{
				addon += mod->value;
			}
		}

		return (baseValue + addon) * factor;
	}

	void removeAllModifiers()
	{
		modifiers.clear();
	}
};



class Effect
{
	enum class Status
	{
		Active,
		Inactive
	} status = Status::Active;

public:
	Effect()
		:
		mod(3.f)
	{}

	void endTurn()
	{
		mod.value -= 1.f;
		if (mod.value <= 0.f)
		{
			status = Status::Inactive;
		}
	}


private:
	int turnDuration;
	Modifier mod;
};