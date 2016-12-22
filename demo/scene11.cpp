/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2016 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene11.h"

Scene11::Scene11() : SuperScene()
{
	srand((unsigned)time(NULL));

	text[0]->message("Scene11: Snake");

	timer.start();

	// create Canvas
	int pixelsize = 32;
	int border = 0; // multiples of (at least) 4
	canvas = new BasicEntity();
	canvas->position = Point2(SWIDTH/2, SHEIGHT/2);
	canvas->scale = Point2(pixelsize, pixelsize);
	layers[0]->addChild(canvas);

	// our PixelBuffer(width, height, bitdepth, filter, wrap)
	PixelBuffer* tmp = new PixelBuffer((SWIDTH/pixelsize)-border, (SHEIGHT/pixelsize)-border, 3, 0, 0);
	canvas->addDynamicSprite(tmp);
	delete tmp;

	// get the pixels from the texture and call it the global framebuffer
	framebuffer = canvas->sprite()->texture()->pixels();

	// fill framebuffer with background color
	backgroundcolor = RGBAColor(32, 32, 32, 255);

	// clear to background color
	for (long y=0; y<framebuffer->height; y++) {
		for (long x=0; x<framebuffer->width; x++) {
			setPixel(x, y, backgroundcolor);
		}
	}

	// clean up and reset
	clearSnake();
}


Scene11::~Scene11()
{
	layers[0]->removeChild(canvas);
	delete canvas;

	snake.clear();
}

void Scene11::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	//text[0]->message(""); // clear title
	//text[1]->message(""); // clear fps message
	//text[2]->message(""); // clear [/] next scene
	text[3]->message(""); // clear <esc> to quit
	text[10]->message(""); // clear player click count message

	// ###############################################################
	// move snake head
	// ###############################################################
	if (input()->getKeyDown( GLFW_KEY_UP )) {
		snake[0].velocity = UP;
	}
	if (input()->getKeyDown( GLFW_KEY_DOWN )) {
		snake[0].velocity = DOWN;
	}
	if (input()->getKeyDown( GLFW_KEY_LEFT )) {
		snake[0].velocity = LEFT;
	}
	if (input()->getKeyDown( GLFW_KEY_RIGHT )) {
		snake[0].velocity = RIGHT;
	}

	// ###############################################################
	// Update and draw only when it's time
	// ###############################################################
	float tsec = timer.seconds();
	if (tsec > 0.1 - deltaTime) { // 0.1 is 100 fps
		// count the snake blocks
		int s = snake.size();

		std::string scoretxt = "score ";
		scoretxt.append(rt2d::to_string<int>(s-2));
		text[2]->message(scoretxt);

		// clear snake to background
		for (int i=0; i<s-1; i++) {
			setPixel(snake[i].position.x, snake[i].position.y, backgroundcolor);
		}

		// update each block in snake
		for (int i=s-1; i>=0; i--) {
			// update position
			snake[i].position += snake[i].velocity;

			// follow the leader
			if (i>0) {
				snake[i].velocity = snake[i-1].velocity;
			}
		}

		// draw each block in snake
		for (int i=0; i<s-1; i++) {
			// color pixels in framebuffer
			setPixel(snake[i].position.x, snake[i].position.y, snake[i].color );
		}

		// draw target
		setPixel(target.position.x, target.position.y, backgroundcolor);
		setPixel(target.position.x, target.position.y, target.color);

		// head hits target!
		if (target.position == snake[0].position) {
			addBlockToSnake(); // add to the snake tail
		}

		// check self collisions
		for (int i = 0; i < s-1; i++) {
			if ( snake[0].position == snake[i+1].position ) {
				std::cout << "self collision!! score " << s-2 << std::endl;
				clearSnake();
			}
		}

		// check boundaries
		if (snake[0].position.x < 0 ||
			snake[0].position.x > framebuffer->width-1 ||
			snake[0].position.y < 0 ||
			snake[0].position.y > framebuffer->height-1
		) {
			std::cout << "boundaries collision!! score " << s-2 << std::endl;
			clearSnake();
		}

		timer.start();
	}
}


void Scene11::addBlockToSnake()
{
	int snakesize = snake.size();
	Block b;
	if (snakesize > 0) {
		// get direction from 'front' neighbour
		b.velocity = snake[snakesize-1].velocity;
		b.position = snake[snakesize-1].position - b.velocity;
	} else {
		// the snake doesn't exist yet. Middle of the screen, move to the right.
		b.position = Point_t<int>(framebuffer->width/2, framebuffer->height/2);
		b.velocity = RIGHT;
	}

	b.color = BLUE;
	// add it to the list of blocks
	snake.push_back(b);

	placeTarget();
}

void Scene11::placeTarget()
{
	// find a new spot for target (don't place it inside the snake)
	setPixel(target.position.x, target.position.y, backgroundcolor);
	Point_t<int> targetPos = snake[0].position; // force a better spot
	while (!positionIsInSnake(targetPos)) {
		targetPos = Point_t<int>(rand()%framebuffer->width, rand()%framebuffer->height);
	}
	target.position = targetPos;
	target.color = GREEN;
}

bool Scene11::positionIsInSnake(Point_t<int> testPoint)
{
	int s = snake.size();
	for (int i = 0; i < s; i++) {
		if (snake[i].position == testPoint) {
			return false;
		}
	}
	return true;
}

void Scene11::setPixel(int x, int y, RGBAColor color)
{
	int start = ((y*framebuffer->width) + x) * framebuffer->bitdepth;
	if (start > framebuffer->width * framebuffer->height * framebuffer->bitdepth || start < 0) { return; }

	framebuffer->data[start+0] = color.r;
	framebuffer->data[start+1] = color.g;
	framebuffer->data[start+2] = color.b;
	if (framebuffer->bitdepth == 4) {
		framebuffer->data[start+3] = color.a;
	}
}

void Scene11::clearSnake()
{
	int s = snake.size();

	// clear each snake block from the framebuffer
	for (int i = 0; i < s; i++) {
		// clear to background
		setPixel(snake[i].position.x, snake[i].position.y, backgroundcolor);
	}
	snake.clear();

	// reset the field
	addBlockToSnake();
	addBlockToSnake();
	snake[0].color = RED;

	placeTarget();
}
