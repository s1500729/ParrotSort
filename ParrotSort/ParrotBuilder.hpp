#pragma once
#include "ParrotData.hpp"

class ParrotBuilder
{
	ParrotData _pink = ParrotData(U"parrots/pink/pink");
	ParrotData _black = ParrotData(U"parrots/black/black");
	ParrotData _default = ParrotData(U"parrots/default/parrot");

public:
	Parrot generate(ParrotColor color, Point pos)
	{
		switch (color)
		{
		case ParrotColor::Default:
			return Parrot(pos, _default.parrotTextures);
		case ParrotColor::Pink:
			return Parrot(pos, _pink.parrotTextures);
		case ParrotColor::Black:
			return Parrot(pos, _black.parrotTextures);
		}
	}
};