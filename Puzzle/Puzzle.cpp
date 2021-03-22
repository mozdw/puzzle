#include<bangtal.h>
#include<cstdlib>
#include<ctime>
#include <string>


ObjectID Puzzle1, Puzzle2, Puzzle3, Puzzle4, Puzzle5, Puzzle6, Puzzle7, Puzzle8, Puzzle9, Puzzle10, Puzzle11, Puzzle12, Puzzle13, Puzzle14, Puzzle15, Puzzle16;
ObjectID startButton, hintButton;

TimerID gameTimer;

SoundID muyahoSound, moveSound;

bool isGameStarted = false;

int timeCount = 0;


int pieceArr[6][6] = {
	{0,0,0,0,0,0}, {0, 1, 2, 3, 4, 0}, {0, 5, 6, 7, 8, 0}, {0, 9, 10, 11, 12, 0}, {0, 13, 14, 15, 16, 0}, {0, 0, 0, 0, 0, 0}
};


bool Check() {
	
	int checkNum = 0;

	for (int y = 1; y < 5; y++)
	{

		for (int x = 1; x < 5; x++)
		{
			if (pieceArr[y][x] == y*4 + x - 4)
			{
				checkNum ++;
			}
		}

	}

	if (checkNum == 16)
	{
		return true;
	}

	else
	{
		return false;
	}

}

void Update() {

	std::string fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[1][1]) + ".png";
	const char* fileName = fileNameStr.c_str();
	setObjectImage(Puzzle1, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[1][2]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle2, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[1][3]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle3, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[1][4]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle4, fileName);


	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[2][1]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle5, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[2][2]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle6, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[2][3]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle7, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[2][4]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle8, fileName);


	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[3][1]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle9, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[3][2]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle10, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[3][3]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle11, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[3][4]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle12, fileName);



	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[4][1]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle13, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[4][2]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle14, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[4][3]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle15, fileName);

	fileNameStr = "Images/muyahoCut_" + std::to_string(pieceArr[4][4]) + ".png";
	fileName = fileNameStr.c_str();
	setObjectImage(Puzzle16, fileName);

}






void move(int piece) {

	int pieceX = (piece + 3) % 4 + 1;
	int pieceY = (piece - 1) / 4 + 1;

	if (pieceArr[pieceY+1][pieceX] == 16)
	{
		int swap = pieceArr[pieceY][pieceX];
		pieceArr[pieceY][pieceX] = pieceArr[pieceY + 1][pieceX];
		pieceArr[pieceY+1][pieceX] = swap;

		Update();
	}

	else if (pieceArr[pieceY - 1][pieceX] == 16)
	{
		int swap = pieceArr[pieceY][pieceX];
		pieceArr[pieceY][pieceX] = pieceArr[pieceY - 1][pieceX];
		pieceArr[pieceY - 1][pieceX] = swap;

		Update();
	}

	else if (pieceArr[pieceY][pieceX + 1] == 16)
	{
		int swap = pieceArr[pieceY][pieceX];
		pieceArr[pieceY][pieceX] = pieceArr[pieceY][pieceX + 1];
		pieceArr[pieceY][pieceX + 1] = swap;

		Update();
	}

	else if (pieceArr[pieceY][pieceX - 1] == 16)
	{
		int swap = pieceArr[pieceY][pieceX];
		pieceArr[pieceY][pieceX] = pieceArr[pieceY][pieceX - 1];
		pieceArr[pieceY][pieceX - 1] = swap;

		Update();
	}

	if (Check()&&isGameStarted) {
		isGameStarted = false;
		stopTimer(gameTimer);
		std::string timeStr = "퍼즐 완성까지 " + std::to_string(timeCount) + "초 걸렸습니다.\n최고 기록을 노려봐요!";
		const char* timeChar = timeStr.c_str();
		showMessage(timeChar);
		timeCount = 0;
		setObjectImage(startButton, "Images/re.png");
		showObject(startButton);
		hideObject(hintButton);
		playSound(muyahoSound);
	}

	if (isGameStarted) {
		playSound(moveSound);
	}

}


void shuffle() {

	for (int i = 0; i < 1000; i++)
	{
		move(rand() % 16 + 1);
	}
}

void Hint() {

	std::string hintStr;

	for (int y = 1; y < 5; y++)
	{

		for (int x = 1; x < 5; x++)
		{

			hintStr = hintStr + std::to_string(pieceArr[y][x]);
			hintStr = hintStr + "  ";

		}

		hintStr = hintStr + "\n";


	}

	const char* hintChar = hintStr.c_str();
	showMessage(hintChar);


}



void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

	if (isGameStarted)
	{
		if (object == Puzzle1)
		{
			move(1);
		}

		if (object == Puzzle2)
		{
			move(2);
		}

		if (object == Puzzle3)
		{
			move(3);
		}

		if (object == Puzzle4)
		{
			move(4);
		}

		if (object == Puzzle5)
		{
			move(5);
		}

		if (object == Puzzle6)
		{
			move(6);
		}

		if (object == Puzzle7)
		{
			move(7);
		}

		if (object == Puzzle8)
		{
			move(8);
		}

		if (object == Puzzle9)
		{
			move(9);
		}

		if (object == Puzzle10)
		{
			move(10);
		}

		if (object == Puzzle11)
		{
			move(11);
		}

		if (object == Puzzle12)
		{
			move(12);
		}

		if (object == Puzzle13)
		{
			move(13);
		}

		if (object == Puzzle14)
		{
			move(14);
		}

		if (object == Puzzle15)
		{
			move(15);
		}

		if (object == Puzzle16)
		{
			move(16);
		}

		if (object == hintButton) {
			Hint();
		}

	}

	


	if (object == startButton) {

		startTimer(gameTimer);
		playSound(moveSound);
		hideObject(startButton);
		showObject(hintButton);
		shuffle();
		isGameStarted = true;

	}

}


void timerCallback(TimerID timer) {

	if (timer == gameTimer)
	{
		timeCount++;
		setTimer(gameTimer, 1.0f);
		startTimer(gameTimer);
	}

}


int main() {

	SceneID dw = createScene(" ", "Images/muyahoBG.png");

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);


	Puzzle1 = createObject("Images/muyahoCut_1.png");
	Puzzle2 = createObject("Images/muyahoCut_2.png");
	Puzzle3 = createObject("Images/muyahoCut_3.png");
	Puzzle4 = createObject("Images/muyahoCut_4.png");
	Puzzle5 = createObject("Images/muyahoCut_5.png");
	Puzzle6 = createObject("Images/muyahoCut_6.png");
	Puzzle7 = createObject("Images/muyahoCut_7.png");
	Puzzle8 = createObject("Images/muyahoCut_8.png");
	Puzzle9 = createObject("Images/muyahoCut_9.png");
	Puzzle10 = createObject("Images/muyahoCut_10.png");
	Puzzle11 = createObject("Images/muyahoCut_11.png");
	Puzzle12 = createObject("Images/muyahoCut_12.png");
	Puzzle13 = createObject("Images/muyahoCut_13.png");
	Puzzle14 = createObject("Images/muyahoCut_14.png");
	Puzzle15 = createObject("Images/muyahoCut_15.png");
	Puzzle16 = createObject("Images/muyahoCut_16.png");

	locateObject(Puzzle1, dw, 329, 480);
	locateObject(Puzzle2, dw, 454, 480);
	locateObject(Puzzle3, dw, 578, 480);
	locateObject(Puzzle4, dw, 703, 480);

	locateObject(Puzzle5, dw, 329, 356);
	locateObject(Puzzle6, dw, 454, 356);
	locateObject(Puzzle7, dw, 578, 356);
	locateObject(Puzzle8, dw, 703, 356);

	locateObject(Puzzle9, dw, 329, 231);
	locateObject(Puzzle10, dw, 454, 231);
	locateObject(Puzzle11, dw, 578, 231);
	locateObject(Puzzle12, dw, 703, 231);

	locateObject(Puzzle13, dw, 329, 107);
	locateObject(Puzzle14, dw, 454, 107);
	locateObject(Puzzle15, dw, 578, 107);
	locateObject(Puzzle16, dw, 703, 107);


	showObject(Puzzle1);
	showObject(Puzzle2);
	showObject(Puzzle3);
	showObject(Puzzle4);
	showObject(Puzzle5);
	showObject(Puzzle6);
	showObject(Puzzle7);
	showObject(Puzzle8);
	showObject(Puzzle9);
	showObject(Puzzle10);
	showObject(Puzzle11);
	showObject(Puzzle12);
	showObject(Puzzle13);
	showObject(Puzzle14);
	showObject(Puzzle15);
	showObject(Puzzle16);


	startButton = createObject("Images/start.png");
	locateObject(startButton, dw, 500, 100);
	showObject(startButton);

	hintButton = createObject("Images/hint.png");
	locateObject(hintButton, dw, 900, 100);


	gameTimer = createTimer(1.0f);

	muyahoSound = createSound("SE/muyaho.mp3");
	moveSound = createSound("SE/move.ogg");

	srand(time(NULL));


	Update();

	startGame(dw);


}