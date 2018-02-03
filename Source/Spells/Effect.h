#pragma once
#include <string>
#include <vector>
#include <algorithm>

enum class StatType
{
	Strength,
	Armor
};

class Modifier
{
public:
	enum class Type
	{
		Addon = 0,
		Factor
	};


	Modifier(float value,StatType statType, Type type = Type::Addon)
		:
		value(value),
		target(statType),
		type(type)
	{}

	bool operator==(const Modifier& rhs) const
	{
		return value == rhs.value && type == rhs.type;
	}

	StatType target;
	Type type;
	float value;
};

using ModifierPtr = std::unique_ptr<Modifier>;

inline ModifierPtr make_modifier(float value, StatType statType, Modifier::Type type = Modifier::Type::Addon)
{
	return std::make_unique<Modifier>(value, statType, type);
}

class Stat
{
	StatType type;
	float baseValue = 0;

	std::vector<Modifier> modifiers;

public:
	Stat(StatType type)
		:
		type(type)
	{}

	void addModifier(const Modifier& mod)
	{
		modifiers.emplace_back(mod);
	}

	void removeModifier(const Modifier& mod)
	{
		auto newEnd = std::remove(modifiers.begin(), modifiers.end(), mod);
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
			if (mod.type == Modifier::Type::Factor)
			{
				factor *= mod.value;
			}
			else
			{
				addon += mod.value;
			}
		}

		return (baseValue + addon) * factor;
	}

	StatType getType() const
	{
		return type;
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
	{
		
	}

	void endTurn()
	{
		mod->value -= 1.f;
		if (mod->value <= 0.f)
		{
			status = Status::Inactive;
		}
	}


private:
	int turnDuration;
	ModifierPtr mod;
};