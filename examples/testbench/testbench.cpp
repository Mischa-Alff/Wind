#include <chrono>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Wind/Engine/Body/Body.hpp>
#include <Wind/Engine/Shape/Shape.hpp>
#include <Wind/Engine/Shape/CircleShape.hpp>
#include <Wind/Engine/Entity/Entity.hpp>
#include <Wind/Engine/Engine/Engine.hpp>
#include <Wind/Engine/Partitioning/QuadTree.hpp>
#include <Wind/Engine/Integration/RK4.hpp>
#include <Wind/Engine/Integration/Euler.hpp>

void draw_quadtree(sf::RenderWindow &window, const wind::QuadTree *tree);

int main()
{
	sf::RenderWindow window{{800, 600}, "Windtunnel"};
	window.setFramerateLimit(1000);

	// Basic particle shape
	sf::CircleShape particle_drawable;
	particle_drawable.setRadius(0.75f);
	particle_drawable.setFillColor(sf::Color::Red);

	std::shared_ptr<wind::QuadTree> quadtree = std::make_shared<wind::QuadTree>(
		wind::QuadTree{{
			{window.getSize().x/2.f, window.getSize().y/2.f},
			{window.getSize().x/2.f, window.getSize().y/2.f}
		}}
	);

	quadtree->max_depth = 5;
	quadtree->max_elements_before_split = 10;

	wind::Engine engine;

	engine.set_integrator(wind::Integrators::RK4);

	bool render_quadtree=true;
	engine.use_quadtree = true;
	engine.set_quadtree(quadtree);

	// Create array of physics objects
	wind::Vector2u amount{20, 20};
	std::vector<std::shared_ptr<wind::Entity>> particles;
	particles.resize(amount.x*amount.y);
	std::cout<<"num_particles: "<<particles.size()<<std::endl;

	// Create particle shapes and bodies
	std::shared_ptr<wind::Body> particle_body=std::make_shared<wind::Body>();
	std::shared_ptr<wind::Shape> particle_shape=std::make_shared<wind::CircleShape>(0.75f);
	particle_body->add_shape(particle_shape);

	// Assign particle positions
	for(auto particle_index=0; particle_index < particles.size(); ++particle_index)
	{
		auto& particle = particles[particle_index];
		particle = std::make_shared<wind::Entity>();

		particle->position.x = particle_index%amount.y+1;
		particle->position.y = particle_index/amount.x+1;
		particle->position.x*= window.getSize().x/(amount.x+1);
		particle->position.y*= window.getSize().y/(amount.y+1);
		particle->mass = 10000.f;
		particle->gravity_exert=true;
		particle->gravity_affected=true;

		particle->set_body(particle_body);

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
				case sf::Keyboard::Q:
					engine.use_quadtree = !engine.use_quadtree;
					break;
				case sf::Keyboard::R:
					render_quadtree = !render_quadtree;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		window.clear(sf::Color::Black);

		engine.simulate(wind::Engine::StandardDuration(30.f));

		if(render_quadtree)draw_quadtree(window, quadtree.get());

		for(auto& particle : particles)
		{
			particle_drawable.setPosition(particle->position.x, particle->position.y);
			window.draw(particle_drawable);
		}
		window.display();

	}
}

void draw_quadtree(sf::RenderWindow &window, const wind::QuadTree *tree)
{
	if(tree->get_nodes()!=nullptr)
	{
		draw_quadtree(window, &(tree->get_nodes()[0]));
		draw_quadtree(window, &(tree->get_nodes()[1]));
		draw_quadtree(window, &(tree->get_nodes()[2]));
		draw_quadtree(window, &(tree->get_nodes()[3]));
	}
	else
	{
		sf::RectangleShape shape;
		shape.setFillColor({0,0,0,0});
		if(tree->get_entities().empty())
		{
			shape.setOutlineColor({255,0,0, 127});
			shape.setOutlineThickness(2);
		}
		else
		{
			shape.setOutlineColor({0,255,0, 127});
			shape.setOutlineThickness(2);
		}
		shape.setPosition({tree->get_bounds().center.x-tree->get_bounds().half_size.x+2.f, tree->get_bounds().center.y-tree->get_bounds().half_size.y+2.f});
		shape.setSize({tree->get_bounds().half_size.x*2.f-2.f,tree->get_bounds().half_size.y*2.f-2.f});
		window.draw(shape);
	}
}
