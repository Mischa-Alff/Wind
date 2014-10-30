#include <chrono>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Wind/Engine/Entity/Entity.hpp>
#include <Wind/Engine/Engine/Engine.hpp>

int main()
{
	sf::RenderWindow window{{800, 600}, "Windtunnel"};
	window.setFramerateLimit(1000);

	// Basic particle shape
	sf::CircleShape particle_shape;
	particle_shape.setRadius(0.75f);
	particle_shape.setFillColor(sf::Color::Red);

	wind::Engine engine;

	// Create array of physics objects
	wind::Vector2u amount{30, 30};
	std::vector<std::shared_ptr<wind::Entity>> particles;
	particles.resize(amount.x*amount.y);
	std::cout<<"num_particles: "<<particles.size()<<std::endl;

	// Assign particle positions
	for(auto particle_index=0; particle_index < particles.size(); ++particle_index)
	{
		auto& particle = particles[particle_index];
		particle = std::make_shared<wind::Entity>();

		particle->position.x = particle_index%amount.y;
		particle->position.y = particle_index/amount.x;
		particle->position.x*= window.getSize().x/amount.x;
		particle->position.y*= window.getSize().y/amount.y;
		particle->mass = 10000.f;
		particle->gravity_exert=true;
		particle->gravity_affected=true;

		engine.add_entity(particle);
	}

	// Used for calculating frametimes
	auto frame_start = std::chrono::high_resolution_clock::now();
	while(window.isOpen())
	{
		auto frame_duration = std::chrono::high_resolution_clock::now() - frame_start;
		frame_start = std::chrono::high_resolution_clock::now();

		auto frame_duration_us = std::chrono::duration_cast<std::chrono::microseconds>(frame_duration);
		auto frametime_us = frame_duration_us.count();
		auto frametime_ms = frametime_us/1000.f;
		auto frametime_s  = frametime_ms/1000.f;

		window.setTitle(
			"Windtunnel :: [FPS] " + std::to_string(1.f/(frametime_s)) + 
			"\t:: [Frametime] " + std::to_string(frametime_us) + "us"
		);

		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				switch(event.key.code)
				{
				case sf::Keyboard::G:
					engine.gravity = !engine.gravity;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		window.clear();

		engine.simulate(wind::Engine::StandardDuration(30.f));

		for(auto& particle : particles)
		{
			particle_shape.setPosition(particle->position.x, particle->position.y);
			window.draw(particle_shape);
		}
		window.display();

	}
}
