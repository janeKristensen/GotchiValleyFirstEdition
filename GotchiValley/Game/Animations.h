#pragma once
#include "Components.h"

namespace GotchiValley {

	const AnimationData animEgg = AnimationData
	(
		1,
		{
			sf::IntRect({ 0,0 }, { 32,32 }),
		}
	);

	const AnimationData animBird = AnimationData
	(
		4,
		{
			sf::IntRect({ 0,32 }, { 32,32 }),
			sf::IntRect({ 32,32 }, { 32,32 }),
			sf::IntRect({ 64,32 }, { 32,32 }),
			sf::IntRect({ 96,32 }, { 32,32 }),

		},
		2.f
	);

	const AnimationData animCollision = AnimationData
	(
		4,
		{
			sf::IntRect({ 0,160 }, { 32,32 }),
			sf::IntRect({ 32,160 }, { 32,32 }),
			sf::IntRect({ 64,160 }, { 32,32 }),
			sf::IntRect({ 96,160 }, { 32,32 }),

		},
		2.f
	);




	const AnimationData animStanding = AnimationData
	(
		13,
		{
			sf::IntRect({ 0,0 }, { 32,32 }),
			sf::IntRect({ 32,0 }, { 32,32 }),
			sf::IntRect({ 64,0 }, { 32,32 }),
			sf::IntRect({ 96,0 }, { 32,32 }),
			sf::IntRect({ 128,0 }, { 32,32 }),
			sf::IntRect({ 160,0 }, { 32,32 }),
			sf::IntRect({ 192,0 }, { 32,32 }),
			sf::IntRect({ 224,0 }, { 32,32 }),
			sf::IntRect({ 256,0 }, { 32,32 }),
			sf::IntRect({ 288,0 }, { 32,32 }),
			sf::IntRect({ 320,0 }, { 32,32 }),
			sf::IntRect({ 352,0 }, { 32,32 }),
			sf::IntRect({ 384,0 }, { 32,32 }),
		},
		10.f
	);

	const AnimationData animRunning = AnimationData
	(
		8,
		{
			sf::IntRect({ 0,0 }, { 32,32 }),
			sf::IntRect({ 32,32 }, { 32,32 }),
			sf::IntRect({ 64,32 }, { 32,32 }),
			sf::IntRect({ 96,32 }, { 32,32 }),
			sf::IntRect({ 128,32 }, { 32,32 }),
			sf::IntRect({ 160,32 }, { 32,32 }),
			sf::IntRect({ 192,32 }, { 32,32 }),
			sf::IntRect({ 224,32 }, { 32,32 }),
		},
		16.f
	);

	const AnimationData animColliding = AnimationData
	(
		4,
		{
			sf::IntRect({ 0,196}, { 32,32 }),
			sf::IntRect({ 32,196 }, { 32,32 }),
			sf::IntRect({ 64,196 }, { 32,32 }),
			sf::IntRect({ 96,196 }, { 32,32 }),
		},
		24.f
	);


	const Animation eggAnimation = Animation
	(
		{
			//{AnimationName::INITIAL, animEgg},
			{AnimationName::IDLE, animEgg},
			{AnimationName::COLLIDING, animEgg},
			{AnimationName::INTERACTING, animEgg},
		},
		0, 0, 0,
		AnimationName::IDLE
	);

	const Animation birdAnimation = Animation
	(
		{
			//{AnimationName::INITIAL, animEgg},
			{AnimationName::IDLE, animBird},
			{AnimationName::COLLIDING, animBird},
			{AnimationName::EVOLVING, animCollision},
			{AnimationName::INTERACTING, animBird},
		},
		0, 0, 0,
		AnimationName::IDLE
	);

	const Animation playerAnimation = Animation
	(
		{
			{AnimationName::INITIAL, animStanding},
			{AnimationName::IDLE, animStanding},
			{AnimationName::RUNNING, animRunning},
			{AnimationName::COLLIDING, animColliding},
			{AnimationName::INTERACTING, animStanding }
		},
		0, 0, 0,
		AnimationName::IDLE
	);

}

	