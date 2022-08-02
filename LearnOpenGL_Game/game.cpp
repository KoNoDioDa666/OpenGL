#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "ball_object.h"
#include "post_process.h"
#include "Character.h"

using glm::vec2;

typedef std::tuple<bool, Direction, vec2> Collision;

SpriteRenderer* Renderer;
//GameObject* Player;
Character* Player;
BallObject* Ball;
PostProcessor* Effects;

// 当转到砖块时屏幕抖动时间
float ShakeTime = 0.0f;

Collision CheckCollision(BallObject& one, GameObject& two);
Collision CheckCollision(BallObject& one, Character& two);
Direction VectorDirection(vec2 target);

Game::Game(unsigned int width, unsigned int height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
	delete Ball;
	delete Effects;
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("ShaderSourceCode/sprite.vs", "ShaderSourceCode/sprite.fs", nullptr, "sprite");
	ResourceManager::LoadShader("ShaderSourceCode/screen.vs", "ShaderSourceCode/screen.fs", nullptr, "screen");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// load textures
	// load textures
	ResourceManager::LoadTexture("image/background.jpg", false, "background");
	ResourceManager::LoadTexture("image/awesomeface.png", true, "face");
	ResourceManager::LoadTexture("image/block.png", false, "block");
	ResourceManager::LoadTexture("image/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("image/paddle.png", true, "paddle");
	// load levels
	GameLevel one; 
	one.Load("levels/one.lvl", this->Width, this->Height / 2);
	GameLevel two;
	two.Load("levels/two.lvl", this->Width, this->Height / 2);
	GameLevel three; 
	three.Load("levels/three.lvl", this->Width, this->Height / 2);
	GameLevel four; 
	four.Load("levels/four.lvl", this->Width, this->Height / 2);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;
	// configure game objects
	glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	//Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
	Player = new Character(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));

	Effects = new PostProcessor(ResourceManager::GetShader("screen"), Width, Height);
}

void Game::Update(float dt)
{
	Ball->Move(dt, this->Width);
	this->DoCollisions();
	if (Ball->Position.y >= this->Height)
	{
		this->ResetLevel();
		this->ResetPlayer();
	}

	if (ShakeTime > 0.0f)
	{
		ShakeTime -= dt;
		if (ShakeTime <= 0.0f)
		{
			Effects->Shake = false;
		}
	}

	Player->Update(dt);

	// 完成后自动进入下一关
	/*if (this->Levels[this->Level].IsCompleted())
	{
		this->Level++;
		if (this->Level == 4)
		{
			this->Level = 0;
			this->ResetLevel();
			this->ResetPlayer();
		}
	}*/
}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		// move playerboard
		if (this->Keys[GLFW_KEY_A])
		{
			/*if (Player->Position.x >= 0.0f)
				Player->Position.x -= velocity;*/
			Player->Position.x -= velocity;
			Player->SetState(WalkLeft);
			if (Player->Position.x < 0.0f)
			{
				Player->Position.x = 0.0f;
			}

			if (Ball->Stuck)
			{
				//Ball->Position.x -= velocity;
				float ballPosX = Player->Position.x + PLAYER_SIZE.x / 2.0f - BALL_RADIUS;
				Ball->Position.x = ballPosX;
			}
		}
		if (this->Keys[GLFW_KEY_D])
		{
			/*if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;*/
			Player->Position.x += velocity;
			Player->SetState(WalkRight);
			if (Player->Position.x > (this->Width - Player->Size.x))
			{
				Player->Position.x = this->Width - Player->Size.x;
			}

			if (Ball->Stuck)
			{
				//Ball->Position.x += velocity;
				float ballPosX = Player->Position.x + PLAYER_SIZE.x / 2.0f - BALL_RADIUS;
				Ball->Position.x = ballPosX;
			}
		}
		if (this->Keys[GLFW_KEY_SPACE])
		{
			Ball->Stuck = false;
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		Effects->BeginRender();

		// draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
		// draw level
		this->Levels[this->Level].Draw(*Renderer);
		// draw player
		Player->Draw(*Renderer);
		// draw ball
		Ball->Draw(*Renderer);

		Effects->EndRender();
		Effects->Render(glfwGetTime());
	}
}

void Game::DoCollisions()
{
	for (GameObject& box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Collision collision = CheckCollision(*Ball, box);
			if (std::get<0>(collision))
			{
				if (!box.IsSolid)
				{
					box.Destroyed = true;
				}
				else
				{
					ShakeTime = 0.05f;
					Effects->Shake = true;
				}
				Direction dir = std::get<1>(collision);
				vec2 diff_vector = std::get<2>(collision);

				if (dir == LEFT || dir == RIGHT)
				{
					Ball->Velocity.x = -Ball->Velocity.x;
					float penetration = Ball->Radius - std::abs(diff_vector.x);
					if (dir == LEFT)
					{
						// 感觉应该是 -=，+=感觉不太对，正好反了
						Ball->Position.x -= penetration;
					}
					else
					{
						Ball->Position.x += penetration;
					}
				}
				else
				{
					Ball->Velocity.y = -Ball->Velocity.y;
					float penetration = Ball->Radius - std::abs(diff_vector.y);
					if (dir == UP)
					{
						Ball->Position.y -= penetration;
					}
					else
					{
						Ball->Position.y += penetration;
					}
				}
			}
		}
	}

	// collision with player
	Collision result = CheckCollision(*Ball, *Player);
	if (!Ball->Stuck && std::get<0>(result))
	{
		float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
		float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		float percentage = distance / (Player->Size.x / 2.0f);

		// Velocity的大小不变，只是xy分量变了
		float strength = 2.0f;
		vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		//Ball->Velocity.y = -Ball->Velocity.y;
		Ball->Velocity.y = -1.0 * std::abs(Ball->Velocity.y);
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
	}
}

void Game::ResetLevel()
{
	if (this->Level == 0)
		this->Levels[0].Load("levels/one.lvl", this->Width, this->Height / 2);
	else if (this->Level == 1)
		this->Levels[1].Load("levels/two.lvl", this->Width, this->Height / 2);
	else if (this->Level == 2)
		this->Levels[2].Load("levels/three.lvl", this->Width, this->Height / 2);
	else if (this->Level == 3)
		this->Levels[3].Load("levels/four.lvl", this->Width, this->Height / 2);
}

void Game::ResetPlayer()
{
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}

// tool functions
Collision CheckCollision(BallObject& one, GameObject& two)
{
	// AABB包围盒检测
	/*bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		 two.Position.x + two.Size.x >= one.Position.x;
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		 two.Position.y + two.Size.y >= one.Position.y;

	return collisionX && collisionY;*/

	// 球形检测
	vec2 center = vec2(one.Position + one.Radius);
	vec2 aabb_half_extents = vec2(two.Size.x / 2.0f, two.Size.y / 2.0f);
	vec2 aabb_center = two.Position + aabb_half_extents;

	vec2 difference = center - aabb_center;
	vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

	vec2 closest = aabb_center + clamped;
	difference = closest - center;
	
	if (glm::length(difference) <= one.Radius)
	{
		return std::make_tuple(true, VectorDirection(difference), difference);
	}
	else
	{
		return std::make_tuple(false, UP, vec2(0.0f, 0.0f));
	}
}

Collision CheckCollision(BallObject& one, Character& two)
{
	// AABB包围盒检测
	/*bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		 two.Position.x + two.Size.x >= one.Position.x;
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		 two.Position.y + two.Size.y >= one.Position.y;

	return collisionX && collisionY;*/

	// 球形检测
	vec2 center = vec2(one.Position + one.Radius);
	vec2 aabb_half_extents = vec2(two.Size.x / 2.0f, two.Size.y / 2.0f);
	vec2 aabb_center = two.Position + aabb_half_extents;

	vec2 difference = center - aabb_center;
	vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

	vec2 closest = aabb_center + clamped;
	difference = closest - center;

	if (glm::length(difference) <= one.Radius)
	{
		return std::make_tuple(true, VectorDirection(difference), difference);
	}
	else
	{
		return std::make_tuple(false, UP, vec2(0.0f, 0.0f));
	}
}

Direction VectorDirection(vec2 target)
{
	vec2 compass[] =
	{
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};

	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}