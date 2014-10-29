#include <chrono>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windtunnel/Engine/Entity/Entity.hpp>
#include <Windtunnel/Engine/Engine/Engine.hpp>

int main()
{
	sf::RenderWindow window{{800, 600}, "Windtunnel"};

	// Basic particle shape
	sf::CircleShape particle_shape;
	particle_shape.setRadius(5.f);
	particle_shape.setFillColor(sf::Color::Red);

	wind::Engine engine;

	// Create array of physics objects
	float spacing = 10.f;
	std::vector<std::shared_ptr<wind::Entity>> particles;
	particles.resize((window.getSize().x/(particle_shape.getRadius()+spacing)) * (window.getSize().y/(particle_shape.getRadius()+spacing)));
	std::cout<<"num_particles: "<<particles.size()<<std::endl;

	// Assign particle positions
	for(auto particle_index=0; particle_index < particles.size(); ++particle_index)
	{
		auto& particle = particles[particle_index];
		particle = std::make_shared<wind::Entity>();

		particle->position.x = (particle_index%static_cast<int>(window.getSize().x/(particle_shape.getRadius()+spacing)));
		particle->position.y = (particle_index/static_cast<int>(window.getSize().x/(particle_shape.getRadius()+spacing)));
		particle->position*=(spacing+particle_shape.getRadius());
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
			default:
				break;
			}
		}

		window.clear();

		engine.simulate(std::chrono::duration_cast<wind::Engine::StandardDuration>(frame_duration));

		for(auto& particle : particles)
		{
			particle_shape.setPosition(particle->position.x, particle->position.y);
			window.draw(particle_shape);
		}
		window.display();

	}
}
