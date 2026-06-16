#include<iostream>
#include<raylib.h>
using namespace std;
int screen_width = 1280;
int screen_height = 800;
int cpu_score = 0;
int player_score = 0;
Color green = Color{ 38,185,154,255 };
Color light_green = Color{ 129,204,184,255 };
Color Dark_green = Color{ 20,160,133,255 };
Color Yellow = Color{ 243,213,91,255 };

class ball {
public:
	float x;
	float y;
	int speed_x;
	int speed_y;
	int radius;
	ball(int _x,int _y,int _speed_x,int _speed_y,int _radius) {
		x = _x;
		y = _y;
		speed_x = _speed_x;
		speed_y = _speed_y;
		radius = _radius;
	}
	
	void draw() {
		DrawCircle(x, y, radius, Yellow);
	}
	void update() {
		x += speed_x;
		y += speed_y;

		if (y + radius >= screen_height || y - radius <= 0) {
			speed_y *= -1;
		}
		if (x + radius >= screen_width ) {
			cpu_score++;
			resetball();
		}
		if (x - radius <= 0) {
			player_score++;
			resetball();
		}
	}
	void resetball() {
		x = screen_width / 2;
		y = screen_height / 2;
		int speed_choice[2] = { -1,1 };
		speed_x *= speed_choice[GetRandomValue(0, 1)];
		speed_y *= speed_choice[GetRandomValue(0, 1)];
	}
};

class paddle {
public:
	float x, y;
	float width, height;
	int speed;
	void draw() {
		DrawRectangleRounded(Rectangle{ x,y,width,height }, 0.8, 0, WHITE);
	}
	void update() {
		if (IsKeyDown(KEY_UP)) {
			y = y - speed;
		}
	    if (IsKeyDown(KEY_DOWN)) {
			y = y + speed;
		}
		if (y <= 0) {
			y = 0;
		}
		if (y + height >= screen_height) {
			y = screen_height - height;
		}
	}
};
class cpupaddle : public paddle {
public:
	void update(int ball_y) {
		if (y + height / 2 >= ball_y) {
			y = y - speed;
		}
		if (y + height / 2 <= ball_y) {
			y = y + speed;
		}
		if (y <= 0) {
			y = 0;
		}
		if (y + height >= screen_height) {
			y = screen_height - height;
		}
	}
};
ball balls(screen_width / 2, screen_height / 2, 7, 7, 17);
paddle player1;
cpupaddle cpu;
int main() {
	 
	cout << "PONG_GAME" << endl;
	InitWindow(screen_width,screen_height, "PNG_GAME_MECHANICS");
	SetTargetFPS(60);
	player1.x = screen_width - 35;
	player1.y = screen_height / 2 - 60;
	player1.width = 25;
	player1.height = 120;
	player1.speed = 7;
	cpu.x = 10;
	cpu.y = screen_height / 2 - 60;
	cpu.width = 25;
	cpu.height = 120;
	cpu.speed = 7;
	while (WindowShouldClose() == false) {
		BeginDrawing();
		//update
		balls.update();
		player1.update();
		cpu.update(balls.y);
		// checking for collision   
		if (CheckCollisionCircleRec(Vector2{ balls.x,balls.y }, balls.radius, Rectangle{ player1.x,player1.y,player1.width,player1.height })) {
			balls.speed_x *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ balls.x,balls.y }, balls.radius, Rectangle{ cpu.x,cpu.y,cpu.width,cpu.height })) {
			balls.speed_x *= -1;
		}
		//drawing
		ClearBackground(Dark_green);
		DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, green);
		DrawCircle(screen_width / 2, screen_height / 2, 150, light_green);
		balls.draw();
		cpu.draw();
		player1.draw();
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
		DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 40, WHITE);
		DrawText(TextFormat("%i", player_score), 3*screen_width / 4 - 20, 20, 40, WHITE);

		EndDrawing();

	}



	CloseWindow();
	return 0;
}