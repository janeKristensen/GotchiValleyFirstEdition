
#include "GameWorld.h"
#include "Animations.h"

using namespace GotchiValley;

void GameWorld::Initialize() {
	
	componentRegistry.RegisterComponentManager<PlayerStats>();
	componentRegistry.RegisterComponentManager<EntityState>();
	componentRegistry.RegisterComponentManager<Transform>();
	componentRegistry.RegisterComponentManager<Moveable>();
	componentRegistry.RegisterComponentManager<Controlable>();
	componentRegistry.RegisterComponentManager<Collider>();
	componentRegistry.RegisterComponentManager<Sprite>();
	componentRegistry.RegisterComponentManager<Animation>();
	componentRegistry.RegisterComponentManager<Interactable>();
	componentRegistry.RegisterComponentManager<Button>();
	componentRegistry.RegisterComponentManager<Level>();
	componentRegistry.RegisterComponentManager<Behaviour>();
	componentRegistry.RegisterComponentManager<MovementBehaviour>();

	auto birdTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_sprite_sheet.png")));
	auto playerTexture = std::make_shared<sf::Texture>(std::move(sf::Texture("sprite_sheet.png")));
	auto BigEgg = std::make_shared<sf::Texture>(std::move(sf::Texture("egg_big.png")));

	auto newLevel = Level{ mLevelManager.LoadLevel(mCurrentLevelId) };
	mLevelEntity = mFactory.CreateEntity(mEntityManager, newLevel);

	CreateBird(birdTexture, { 400.f, 500.f });
	CreateBird(birdTexture, { 200.f, 200.f });
	
	mPlayer = CreatePlayer(playerTexture, {200.f, 200.f}, 80.f);

	auto button = mFactory.CreateEntity
	(
		mEntityManager,
		Sprite(BigEgg),
		Transform({ sf::Vector2f(250,150), sf::Vector2f(0,0), 80.f }),
		Collider({ sf::FloatRect({250,150}, {32,32}) }),
		Interactable()
	);
	componentRegistry.AddComponent(button,
		Button(
			[button, this]() {
				this->SetLevel(mCurrentLevelId + 1);
			}
		)
	);
}


void GameWorld::SetLevel(const std::uint32_t levelID) {

	componentRegistry.RemoveComponent<Level>(mLevelEntity);
	componentRegistry.AddComponent<Level>(mLevelEntity, Level{ mLevelManager.LoadLevel(levelID) });
}

Entity GameWorld::CreatePlayer(std::shared_ptr<sf::Texture> texture, sf::Vector2f position, float speed) {

	auto player = mFactory.CreateEntity
	(
		mEntityManager,
		Sprite(texture),
		playerAnimation,
		Transform({ position, sf::Vector2f(0,0), speed}),
		Collider({ sf::FloatRect(position, {32,32}) }),
		Moveable(),
		Controlable(),
		PlayerStats(100)
	);
	componentRegistry.AddComponent(player,
		MovementBehaviour(
			[player]() {

				auto entityTransform = componentRegistry.GetComponentOfType<Transform>(player);
				auto entityAnimation = componentRegistry.GetComponentOfType<Animation>(player);
				

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {

					entityTransform->velocity.y = -1.f;
					entityAnimation->animName = AnimationName::RUNNING;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

					entityTransform->velocity.y = 1.f;
					entityAnimation->animName = AnimationName::RUNNING;
				}				
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

					entityTransform->velocity.x = 1.f;
					entityAnimation->animName = AnimationName::RUNNING;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

					entityTransform->velocity.x = -1.f;
					entityAnimation->animName = AnimationName::RUNNING;
				}
				else {
					entityTransform->velocity.x = 0.f;
					entityAnimation->animName = AnimationName::IDLE;
					entityAnimation->frameNum = 0;
				}
			}
		)
	);

	return player;
}

void GameWorld::CreateBird(std::shared_ptr<sf::Texture> texture, sf::Vector2f position) {

	auto bird = mFactory.CreateEntity
	(
		mEntityManager,
		Sprite(texture),
		birdAnimation,
		Transform({ position }),
		Collider({ sf::FloatRect({position}, {32,32}) }),
		Interactable(),
		EntityState{ State::INITIAL }
	);
	componentRegistry.AddComponent(bird,
		Button(
			[bird, this]() {
				auto entityState = componentRegistry.GetComponentOfType<EntityState>(bird);
				auto entityAnimation = componentRegistry.GetComponentOfType<Animation>(bird);
				if (entityState->state == State::EVOLVING) {

					entityAnimation->frames[AnimationName::COLLIDING] = birdAnimation.frames[AnimationName::IDLE];
				}

				this->NotifyObservers(bird, EntityEvent::INTERACTION);
			}
		)
	);
}


void GameWorld::AddObserver(IGameObserver* observer) {

	mObservers.emplace_back(observer);
}

void GameWorld::RemoveObserver(IGameObserver* observer) {

	mObservers.remove(observer);
}

void GameWorld::NotifyObservers(const Entity& entity, const EntityEvent& eventMessage) const {
	
	for (auto observer : mObservers) {
		observer->OnNotify(entity, eventMessage);
	}
}


